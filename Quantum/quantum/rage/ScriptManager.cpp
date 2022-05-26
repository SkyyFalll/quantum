#include "../main.h"
#include "Array.hpp"
#include "ScriptManager.hpp"
#include <mutex>
#include "Base.hpp"

void ScriptManager::AddScript(std::unique_ptr<Script> script)
{
	std::lock_guard lock(m_Mutex);
	m_Scripts.push_back(std::move(script));
}

void ScriptManager::RemoveAllScripts()
{
	std::lock_guard lock(m_Mutex);
	m_Scripts.clear();
}

void ScriptManager::Tick()
{
	static bool EnsureMainFiber = (ConvertThreadToFiber(nullptr), true);
	static bool ensure_native_handlers = (g_NativeInvoker.CacheHandlers(), true);
	std::lock_guard lock(m_Mutex);
	for (auto&& script : m_Scripts)
	{
		script->Tick();
	}
}