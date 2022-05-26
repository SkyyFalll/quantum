#include <Windows.h>
#include "PatternMgr.hpp"
#include <functional>
#include <sstream>


PManage::PManage(void* hand) { m_Ptr = hand; }
PManage::PManage(std::uintptr_t hand) { m_Ptr = reinterpret_cast<void*>(hand); }

PManage PManage::Add(int offset) {
	return PManage(As<std::uintptr_t>() + offset);
}
PManage PManage::Sub(int offset) {
	return PManage(As<std::uintptr_t>() - offset);
}
PManage PManage::Rip(int offset) {
	if (!m_Ptr) return nullptr;
	return Add(As<std::int32_t&>()).Add(offset);
}

SModule::SModule(HMODULE hMod) :
	m_Begin(hMod), m_End(nullptr), m_Size(0) {
	auto dosHeader = PManage(m_Begin).As<IMAGE_DOS_HEADER*>();
	auto ntHeader = PManage(m_Begin).Add(dosHeader->e_lfanew).As<IMAGE_NT_HEADERS*>();
	m_Size = ntHeader->OptionalHeader.SizeOfImage;
	m_End = PManage(m_Begin.Add(m_Size));
}

SModule::SModule(std::string name) :
	SModule(GetModuleHandleA(name.c_str())) {}

PManage SModule::GBegin() {
	return m_Begin;
}

PManage SModule::GEnd() {
	return m_End;
}

PManage SModule::GExport(std::string proc_name) {
	return PManage(GetProcAddress(m_Begin.As<HMODULE>(), proc_name.c_str()));
}

FPattern::FPattern(const char* pattern) {
	auto toUpper = [](char c) -> char {
		return c >= 'a' && c <= 'z' ? static_cast<char>(c + ('A' - 'a')) : static_cast<char>(c);
	};

	auto isHex = [&](char c) -> bool {
		switch (toUpper(c)) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
			return true;
		default:
			return false;
		}
	};

	do {
		if (*pattern == ' ')
			continue;
		if (*pattern == '?') {
			Element e = Element({}, true);
			m_Elements.push_back(e);
			continue;
		}

		if (*(pattern + 1) && isHex(*pattern) && isHex(*(pattern + 1))) {
			char str[3] = { *pattern, *(pattern + 1), '\0' };
			auto data = std::strtol(str, nullptr, 16);

			Element e = Element(static_cast<std::uint8_t>(data), false);
			m_Elements.push_back(e);
		}
	} while (*(pattern++));
}

PManage FPattern::Scan(SModule region) {
	auto compareMemory = [](std::uint8_t* data, Element* elem, std::size_t num) -> bool {
		for (std::size_t i = 0; i < num; ++i) {
			if (!elem[i].m_Wildcard)
				if (data[i] != elem[i].m_Data)
					return false;
		}
		return true;
	};

	for (std::uintptr_t i = region.GBegin().As<std::uintptr_t>(), end = region.GEnd().As<std::uintptr_t>(); i != end; ++i) {
		if (compareMemory(reinterpret_cast<std::uint8_t*>(i), m_Elements.data(), m_Elements.size())) {
			return PManage(i);
		}
	}
	return nullptr;
}

PatternHIST::PatternHIST(std::string name, FPattern pattern, std::function<void(PManage)> callback) :
	m_Name(std::move(name)),
	m_Pattern(std::move(pattern)),
	m_Callback(std::move(callback))
{}

void PatternB::Add(std::string name, FPattern pattern, std::function<void(PManage)> callback) {
	m_Patterns.emplace_back(name, pattern, callback);
	iTotalPatternC++;
}

void PatternB::Run(std::string moduleName, bool silent) {
	Run(GetModuleHandleA(moduleName.c_str()), silent);
}

void PatternB::Run(HMODULE hModule, bool silent) {
	SModule* pMod = new SModule(hModule);
	bool all_found = true;
	for (auto& entry : m_Patterns) {
		if (auto result = entry.m_Pattern.Scan(*pMod)) {
			if (entry.m_Callback) {
				if (result.As<uintptr_t>() != NULL) {
					iFoundPatternC++;
					std::invoke(std::move(entry.m_Callback), result);
				}
			}
			else {
				all_found = false;
			}
		}
	}
	m_Patterns.clear();
	delete pMod;
}