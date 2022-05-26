#pragma once
#include <locale>
#include <iostream>
#include <sstream>
#include <fstream>
#include <Windows.h>
#include <Wincrypt.h>
#include <winternl.h>
#include <stdint.h>
#include <cstdint>
#include <stdio.h>
#include <cmath>
#include <array>
#include <vector>
#include <stack>
#include <unordered_map>
#include <iomanip>
#include <functional>
#include <shlobj_core.h>
#include <intrin.h>
#include <utility>
#include <MinHook.h>
#include "obfuscator.h"
#include "rage/fwddec.hpp"
#include "rage/Base.hpp"

namespace rage
{
	class scrNativeCallContext
	{
	public:
		void Reset()
		{
			m_ArgCount = 0;
			m_DataCount = 0;
		}

		template <typename T>
		void PushArgument(T&& value)
		{
			static_assert(sizeof(T) <= sizeof(std::uint64_t));
			*reinterpret_cast<std::remove_cv_t<std::remove_reference_t<T>>*>(reinterpret_cast<std::uint64_t*>(m_Args) + (m_ArgCount++)) = std::forward<T>(value);
		}

		template <typename T>
		T& GetArgument(std::size_t index)
		{
			static_assert(sizeof(T) <= sizeof(std::uint64_t));
			return *reinterpret_cast<T*>(reinterpret_cast<std::uint64_t*>(m_Args) + index);
		}

		template <typename T>
		void SetArgument(std::size_t index, T&& value)
		{
			static_assert(sizeof(T) <= sizeof(std::uint64_t));
			*reinterpret_cast<std::remove_cv_t<std::remove_reference_t<T>>*>(reinterpret_cast<std::uint64_t*>(m_Args) + index) = std::forward<T>(value);
		}

		template <typename T>
		T* GetReturnValue()
		{
			return reinterpret_cast<T*>(m_ReturnValue);
		}

		PVOID GetReturnPointer()
		{
			return m_ReturnValue;
		}

		template <typename T>
		void SetReturnValue(T&& value)
		{
			*reinterpret_cast<std::remove_cv_t<std::remove_reference_t<T>>*>(m_ReturnValue) = std::forward<T>(value);
		}
	protected:
		void* m_ReturnValue;
		std::uint32_t m_ArgCount;
		void* m_Args;
		std::int32_t m_DataCount;
		std::uint32_t m_Data[48];
	};

	using scrNativeHash = std::uint64_t;
	using scrNativeMapping = std::pair<scrNativeHash, scrNativeHash>;
	using scrNativeHandler = void(*)(scrNativeCallContext*);

	class scrNativeRegistration;

#pragma pack(push, 1)
	class scrNativeRegistrationTable
	{
		scrNativeRegistration* m_Entries[0xFF];
		std::uint32_t m_unk;
		bool m_Initialized;
	};
#pragma pack(pop)

	static_assert(sizeof(scrNativeCallContext) == 0xE0);
}

class NativeCallContext : public rage::scrNativeCallContext
{
public:
	NativeCallContext();
private:
	std::uint64_t m_ReturnStack[10];
	std::uint64_t m_ArgumentStack[100];
};

class NativeInvoker
{
public:
	explicit NativeInvoker() = default;
	~NativeInvoker() = default;

	void CacheHandlers();

	void BeginCall();
	void EndCall(rage::scrNativeHash hash);

	template <typename T>
	void PushArgument(T&& value)
	{
		m_call_context.PushArgument(std::forward<T>(value));
	}

	template <typename T>
	T& GetReturnValue()
	{
		return *m_call_context.GetReturnValue<T>();
	}

	PVOID GetReturnAdress()
	{
		return m_call_context.GetReturnPointer();
	}
private:
	NativeCallContext m_call_context;
	std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler> m_handler_cache;
};

inline NativeInvoker g_NativeInvoker;