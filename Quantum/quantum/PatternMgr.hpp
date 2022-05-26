#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <functional>

class PManage {
public:
	PManage(void* hand = 0);
	PManage(std::uintptr_t hand = 0);

	template <typename T>
	inline std::enable_if_t<std::is_pointer<T>::value, T> As() {
		return static_cast<T>(m_Ptr);
	}

	template <typename T>
	inline std::enable_if_t<std::is_lvalue_reference<T>::value, T> As() {
		return *static_cast<std::add_pointer_t<std::remove_reference_t<T>>>(m_Ptr);
	}

	template <typename T>
	inline std::enable_if_t<std::is_same<T, std::uintptr_t>::value, T> As() {
		return reinterpret_cast<T>(m_Ptr);
	}

	PManage Add(int offset);
	PManage Sub(int offset);
	PManage Rip(int offset = 4);

	inline operator bool() { return m_Ptr != nullptr; }

private:
	void* m_Ptr;
};

class SModule {
public:
	SModule(HMODULE hMod);
	SModule(std::string name);

	PManage GBegin();
	PManage GEnd();
	PManage GExport(std::string proc_name);

private:
	PManage m_Begin;
	PManage m_End;
	size_t m_Size{};
	std::string m_Name{};
};

class FPattern {
public:
	struct Element
	{
		std::uint8_t m_Data{};
		bool m_Wildcard{};
		Element(uint8_t data, bool wildcard) :
			m_Data(data), m_Wildcard(wildcard)
		{ }
	};

	FPattern(const char* pattern);
	PManage Scan(SModule region = SModule(nullptr));

private:
	const char* m_Pat;
	std::vector<Element> m_Elements;
};

struct PatternHIST {
	std::string m_Name;
	FPattern m_Pattern;
	std::function<void(PManage)> m_Callback;

	PatternHIST(std::string name, FPattern pattern, std::function<void(PManage)> callback);
};

class PatternB {
public:
	int iTotalPatternC = 0;
	int iFoundPatternC = 0;
	void Add(std::string name, FPattern pattern, std::function<void(PManage)> callback);
	void Run(std::string moduleName = nullptr, bool silent = false);
	void Run(HMODULE hModule, bool silent = false);
	std::vector<PatternHIST> m_Patterns;
};