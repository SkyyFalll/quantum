#pragma once
#include "../main.h"
#include <optional>
#include <chrono>
#include <string>
class Script
{
public:
	using HelperVoid = void(*)();
public:
	explicit Script(HelperVoid func, std::optional<std::size_t> stack_size = std::nullopt);
	~Script();

	void Tick();
	void ScriptYield(std::optional<std::chrono::high_resolution_clock::duration> time = std::nullopt);
	static Script* GetCurrent();
	static void ScriptExceptionHandler(PEXCEPTION_POINTERS exp);
private:
	void FiberFunction();
private:
	void* m_ScriptFiber;
	void* m_MainFiber;
	HelperVoid m_Function;
	std::optional<std::chrono::high_resolution_clock::time_point> m_WakeTime;
};
#define TRY_CLAUSE  __try
#define EXCEPT_CLAUSE  __except (Script::ScriptExceptionHandler(GetExceptionInformation()), EXCEPTION_EXECUTE_HANDLER) { }
#define QUEUE_JOB_BEGIN_CLAUSE(...) g_NativeQueue->QueueJob([__VA_ARGS__] { __try
#define QUEUE_JOB_END_CLAUSE __except (Script::ScriptExceptionHandler(GetExceptionInformation()), EXCEPTION_EXECUTE_HANDLER) {} });
