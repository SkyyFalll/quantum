#include "main.h"
#include "Crossmap.hpp"
#include "Invoker.hpp"

NativeCallContext::NativeCallContext() {
	m_ReturnValue = &m_ReturnStack[0];
	m_Args = &m_ArgumentStack[0];
}
void NativeInvoker::CacheHandlers()
{
	for (const rage::scrNativeMapping& mapping : g_crossmap)
	{
		rage::scrNativeHandler handler = ptr.m_GNH(
			ptr.m_NRT, mapping.second);
		m_handler_cache.emplace(mapping.first, handler);
	}
}

void NativeInvoker::BeginCall() {
	m_call_context.Reset();
}
void NativeInvoker::EndCall(rage::scrNativeHash hash)
{
	if (auto it = m_handler_cache.find(hash); it != m_handler_cache.end()) {
		rage::scrNativeHandler handler = it->second;
		__try {
			handler(&m_call_context);
			ptr.m_FV(&m_call_context);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			printf("Exception caught while trying to call 0x%s native.\n", hash);
		}
	}
	else {
		printf("Failed to find 0x%s native's handler.\n", hash);
	}
}