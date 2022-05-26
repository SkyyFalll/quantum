#pragma once
#include "../main.h"
#include "Script.hpp"
#include <optional>
#include <chrono>

void Script::ScriptExceptionHandler(PEXCEPTION_POINTERS exp)
{
}

Script::Script(HelperVoid func, std::optional<std::size_t> stack_size) :
	m_Function(func),
	m_ScriptFiber(nullptr),
	m_MainFiber(nullptr)
{
	m_ScriptFiber = CreateFiber(stack_size.has_value() ? stack_size.value() : 0, [](void* param)
		{
			auto this_script = static_cast<Script*>(param);
			this_script->FiberFunction();
		}, this);
}

Script::~Script()
{
	if (m_ScriptFiber)
		DeleteFiber(m_ScriptFiber);
}

void Script::Tick()
{
	m_MainFiber = GetCurrentFiber();
	if (!m_WakeTime.has_value() || m_WakeTime.value() <= std::chrono::high_resolution_clock::now())
	{
		SwitchToFiber(m_ScriptFiber);
	}
}

void Script::ScriptYield(std::optional<std::chrono::high_resolution_clock::duration> time)
{
	if (time.has_value())
	{
		m_WakeTime = std::chrono::high_resolution_clock::now() + time.value();
	}
	else
	{
		m_WakeTime = std::nullopt;
	}

	SwitchToFiber(m_MainFiber);
}

Script* Script::GetCurrent()
{
	return static_cast<Script*>(GetFiberData());
}

void Script::FiberFunction()
{
	__try
	{
		[this]()
		{
			try
			{
				m_Function();
			}
			catch (std::exception const& ex)
			{
				auto ex_class = typeid(ex).name() + 6;
				printf("Script threw an C++ expection! %s: %s\n", ex_class, ex.what());
			}
			catch (...)
			{
				printf("Script threw a C++ exception!\n");
			}
		}();
	}
	__except (ScriptExceptionHandler(GetExceptionInformation()), EXCEPTION_EXECUTE_HANDLER)
	{
		printf("Script threw an exception!\n");
	}
	printf("Script finished!\n");
	while (true)
	{
		ScriptYield();
	}
}