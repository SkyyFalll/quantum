#pragma once
#include "../main.h"
#include "Script.hpp"
#include <mutex>

class ScriptManager
{
public:
	explicit ScriptManager() = default;
	~ScriptManager() = default;

	void AddScript(std::unique_ptr<Script> script);
	void RemoveAllScripts();

	void Tick();
private:
	std::recursive_mutex m_Mutex;
	std::vector<std::unique_ptr<Script>> m_Scripts;
};

inline ScriptManager g_ScriptManager;