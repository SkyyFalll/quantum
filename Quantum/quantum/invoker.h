#pragma once
#include "callspoofer.h"
#include "globals.h"

#define NATIVE_CXT_MAX_ARGS 32
#define NATIVE_CXT_ARG_SIZE 8

class native_call_cxt {
protected:
	void* m_ret_data;
	std::uint32_t m_arg_count;
	void* m_arg_data;
	std::uint32_t m_dat_count;
	std::uint32_t m_vec_data[48];
public:
	template <typename t>
	t get_arg(std::uint64_t index) {
		return *(t*)(&m_arg_data + (index * NATIVE_CXT_ARG_SIZE));
	}
	template <typename t>
	void set_arg(std::uint64_t index, t value) {
		return *(t*)(&m_arg_data + (index * NATIVE_CXT_ARG_SIZE)) = value;
	}
	void print_args() {
		std::cout << __FUNCTION__":";
		for (std::uint32_t i = 0; i < m_arg_count; i++)
			std::cout << " " << std::hex << ((std::uint64_t*)(m_arg_data))[i];
		std::cout << std::endl;
	}
};

class native_cxt
	: native_call_cxt {
private:
	std::uint8_t m_temp_stack[NATIVE_CXT_MAX_ARGS * NATIVE_CXT_ARG_SIZE];
public:
	native_cxt() {
		ZeroMemory(m_temp_stack, sizeof m_temp_stack);
		m_ret_data = &m_temp_stack;
		m_arg_data = &m_temp_stack;
	}
	template <typename t>
	void push_arg(t arg) {
		if (sizeof t > NATIVE_CXT_ARG_SIZE)
			throw "invalid argument size";
		if (sizeof t < NATIVE_CXT_ARG_SIZE)
			ZeroMemory(&m_temp_stack[m_arg_count * NATIVE_CXT_ARG_SIZE], NATIVE_CXT_ARG_SIZE);
		*(t*)(&m_temp_stack[m_arg_count * NATIVE_CXT_ARG_SIZE]) = arg;
		m_arg_count++;
	}
	template <typename t>
	t get_result() {
		//SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((void(*)(native_cxt*))GTA_SET_VECTOR_RESULTS), this);
		return *(t*)(m_temp_stack);
	}
};

//template<typename r, class...a>
//static r invoke(std::uint64_t hash, a const&...args) {
//	native_cxt cxt;
//	((cxt.push_arg(args)), ...);
//	std::uint64_t handler = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint64_t, std::uint64_t))GTA_GET_NATIVE_HANDLER), GTA_NATIVE_REGISTRATION, hash);
//	if (handler)
//		SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), (native_cxt * (*)(native_cxt*))(handler), &cxt);
//	return cxt.get_result<r>();
//}

template <typename Ret, typename ...Args>
FORCEINLINE Ret invoke(rage::scrNativeHash hash, Args &&...args)
{
	g_NativeInvoker.BeginCall();
	(g_NativeInvoker.PushArgument(std::forward<Args>(args)), ...);
	g_NativeInvoker.EndCall(hash);
	if constexpr (!std::is_same_v<Ret, void>)
	{
		return g_NativeInvoker.GetReturnValue<Ret>();
	}
}