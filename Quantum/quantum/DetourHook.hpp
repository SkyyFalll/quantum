#pragma once

namespace Bruh
{
	class DetourHook
	{
	public:
		explicit DetourHook(std::string name, void *target, void *detour);
		~DetourHook() noexcept;

		DetourHook(DetourHook&& that) = delete;
		DetourHook& operator=(DetourHook&& that) = delete;
		DetourHook(DetourHook const&) = delete;
		DetourHook& operator=(DetourHook const&) = delete;

		void Enable();
		void Disable();

		template <typename T>
		T GetOriginal();

		void FixHookAdress();
	private:
		std::string m_Name;
		void *m_Target;
		void *m_Detour;
		void *m_Original{};
	};

	template <typename T>
	inline T DetourHook::GetOriginal()
	{
		return static_cast<T>(m_Original);
	}
}
