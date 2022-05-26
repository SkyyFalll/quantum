#pragma once
#pragma comment(lib, "dxgi.lib")
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
#include <MinHook.h>
#include <wrl/client.h>
#include <minwindef.h>
#include "obfuscator.h"
#include "rage/fwddec.hpp"
#include "rage/Base.hpp"
#include "Invoker.hpp"
#include "rage/Enums.hpp"
#include <cstdarg>
#include <d3d11.h>
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/VMTHook.hpp"
#include <DXGI.h>

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//#define IS_DEBUG_VERSION

#pragma warning(disable: 4477)
#pragma warning(disable: 4313)
#pragma warning(disable: 4081)
#pragma warning(disable: 4838)

#pragma intrinsic(_ReturnAddress)

#define MENU_BUILD_DATE __DATE__
#define MENU_BUILD_TIME __TIME__

#pragma message("========== Building Quantum ==========")
#pragma message("Date -> " MENU_BUILD_DATE)
#pragma message("Time -> " MENU_BUILD_TIME)
#pragma message("======================================")

#ifdef IS_RGL_VERSION

#define WORKING_DUMP_BASE 0x7FF62CBA0000

inline std::uintptr_t GTA_JMP_RBX = 0x7FF62DCC6970; // 23 C3 C1 E0 0C  (-1)
inline std::uintptr_t GTA_NATIVE_REGISTRATION = 0x7FF62F8DFBF0; // 48 8D 0D ? ? ? ? 48 8B 14 FA
inline std::uintptr_t GTA_GET_NATIVE_HANDLER = 0x7FF62D5D8934; // 48 8D 0D ? ? ? ? 48 8B 14 FA (First call)
inline std::uintptr_t GTA_RETURN_FALSE_SUB = 0x7FF6324E68EF; // 32 C0 C3 (Any)
inline std::uintptr_t GTA_SET_VECTOR_RESULTS = 0x7FF62E11D60C; // 83 79 18 00 48 8B D1 74 4A 
inline std::uintptr_t GTA_GET_SESSION_HOST_NET_GAME_PLAYER = 0x7FF62DBCFE98; // 40 53 48 83 EC 20 48 8B 49 20 48 8D 54 24 ? (Go back until you find call near ptr)
inline std::uintptr_t GTA_GET_NET_GAME_PLAYER_FROM_PHYSICAL_INDEX = 0x7FF62E1CB98C; // 80 F9 20 73 13 
inline std::uintptr_t GTA_GET_SCRIPT_INDEX_FROM_ENTITY = 0x7FF62E124DE8; // 48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 8B 15 ? ? ? ? 48 8B F9 48 83 C1 10 33 DB
inline std::uintptr_t GTA_GET_ENTITY_FROM_SCRIPT_GUID = 0x7FF62D5A8F68; // 40 53 48 83 EC 20 48 63 DA E8 ? ? ? ? 48 85 C0 74 21 (First call you see)
inline std::uintptr_t GTA_GET_NET_OBJECT_BY_NET_ID = 0x7FF62DBD1C44; // 48 89 5C 24 ? 48 89 6C 24 ? 66 89 54 24 ? (Find jmp xref with 1 xref from caller)
inline std::uintptr_t GTA_GET_LOCAL_PLAYER_PED = 0x7FF62D226E54; // 48 8B 05 ? ? ? ? 48 8B 40 08 C3 
inline std::uintptr_t GTA_GET_SYNC_TREE_FROM_CLONE_TYPE = 0x7FF62DC8F128; // 0F B7 CA 83 F9 07 
inline std::uintptr_t GTA_STREAMED_SCRIPTS = 0x7FF62F174FA0; // 48 8D 0D ? ? ? ? E8 ? ? ? ? 83 38 FF 74 2D 
inline std::uintptr_t GTA_LOCAL_SCRIPT_HANDLERS = 0x7FF62F14ADB0; // 40 53 48 83 EC 20 80 79 30 00 0F 84 ? ? ? ? (Last loc -> loc then net)
inline std::uintptr_t GTA_NETWORKED_SCRIPT_HANDLERS = 0x7FF62F14BB50; // // 40 53 48 83 EC 20 80 79 30 00 0F 84 ? ? ? ? (Last loc -> loc then net)
inline std::uintptr_t GTA_REMOVE_PLAYER_FROM_PLAYER_MGR = 0x7FF62DCA6F74; // 48 89 5C 24 ? 57 48 83 EC 20 48 8B DA 48 8B F9 E8 ? ? ? ? 84 C0 75 14 
inline std::uintptr_t GTA_REGISTER_GAME_FILE = 0x7FF62E1462A0; // 48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 
inline std::uintptr_t GTA_CHANGE_NET_OBJ_OWNER = 0x7FF62E1C62D4; // 48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 54 41 56 41 57 48 81 EC ? ? ? ? 44 8A 62 4B 
inline std::uintptr_t GTA_GET_VEHICLE_PAINT_LIST_ARRAY = 0x7FF62D199E24; // 4C 8B 0D ? ? ? ? 45 33 C0 4D 85 C9
inline std::uintptr_t GTA_PACK_CLONE_REMOVE = 0x7FF62E1D9730; // 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 30 41 80 78 ? ? 
inline std::uintptr_t GTA_PACK_CLONE_SYNC = 0x7FF62E1E0AAC; // 48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 02 
inline std::uintptr_t GTA_MODEL_INFO_LIST_POOL = 0x7FF62E993BB0; // 0F B7 05 ? ? ? ? 45 33 C9 4C 8B DA 66 85 C0 0F 84 ? ? ? ? 44 0F B7 C0 33 D2 8B C1 41 F7 F0 48 8B 05 ? ? ? ? 4C 8B 14 D0 EB 09 41 3B 0A 74 54 (Last add instr with addr)
inline std::uintptr_t GTA_WATER_TUNE_XML = 0x7FF62E83FBF4; // F3 0F 11 05 ? ? ? ? F3 0F 10 05 ? ? ? ? F3 0F 11 0D ? ? ? ? 0F 28 0D ? ? ? ? 
inline std::uintptr_t GTA_WATER_QUAD_XML = 0x7FF62EDB4170; // 48 8D 0D ? ? ? ? 66 44 89 05 ? ? ? ? E8 ? ? ? ? 0F B7 05 ? ? ? ? 
inline std::uintptr_t GTA_WATER_QUAD_XML_COUNT = 0x7FF62EDB4178; // 48 8D 0D ? ? ? ? 66 44 89 05 ? ? ? ? E8 ? ? ? ? 0F B7 05 ? ? ? ?  (+ 0x8)
inline std::uintptr_t GTA_HUD_COLOUR_POOL = 0x7FF62EAE0690; // 41 8B 8C 84 ? ? ? ? 41 0F B6 C0 
inline std::uintptr_t GTA_PED_FACTORY = 0x7FF62F04CB48; // 48 8B 05 ? ? ? ? 48 8B 40 08 C3 
inline std::uintptr_t GTA_ATTACHMENT_EXTENSION_INST_POOL = 0x7FF62F9C06E8; // 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 85 C0 74 0E 48 8B D6 48 8B C8 E8 ? ? ? ? 48 8B D8 48 89 5F 48 
inline std::uintptr_t GTA_GAME_GLOBALS = 0x7FF62F8E0BD0; // 4C 8D 05 ? ? ? ? 4D 8B 08 4D 85 C9 74 11 
inline std::uintptr_t GTA_SUPER_GRIP_FLOAT = 0x7FF62E4801A4; // F3 0F 59 15 ? ? ? ? F3 41 0F 58 D2 F3 0F 59 D0 
inline std::uintptr_t GTA_NETWORK_OBJECT_MGR_INTERFACE = 0x7FF62F43B450; // 48 8B 05 ? ? ? ? 44 0F B7 8C FB ? ? ? ? 4C 8D 05 ? ? ? ? 48 8B 88 ? ? ? ? 48 8D 15 ? ? ? ? 48 8B 01 FF 50 30 48 8B 05 ? ? ? ? 44 0F B7 8C FB ? ? ? ? 48 8B 88 ? ? ? ? (Any)
inline std::uintptr_t GTA_NETWORK_PLAYER_MGR_INTERFACE = 0x7FF62F9CA8E0; // 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? C3
inline std::uintptr_t GTA_FORCE_SCRIPT_HOST = 0x7FF62D5BD09C; // 48 89 5C 24 ? 57 48 83 EC 50 48 8B FA 48 8B D9 E8 ? ? ? ? 83 7B 10 08 
inline std::uintptr_t GTA_SMALL_HOST_TOKEN_PATCH = 0x7FF62F89ECEB; // C6 05 ? ? ? ? ? 48 8B CB E8 ? ? ? ? 84 C0 75 08 
inline std::uintptr_t GTA_NETWORK_OBJECT_MGR_TABLE = 0x7FF62E598C88;
inline std::uintptr_t GTA_NET_OBJ_PED_NODE_DATA_ACCESSOR_TABLE = 0x7FF62E5A5FC8;
inline std::uintptr_t GTA_NET_OBJ_OBJECT_NODE_DATA_ACCESSOR_TABLE = 0x7FF62E5A22E8;
inline std::uintptr_t GTA_REMOVE_WEAPON_EVENT_TABLE = 0x7FF62E5ADB18;
inline std::uintptr_t GTA_REMOVE_ALL_WEAPONS_EVENT_TABLE = 0x7FF62E5ADBE8;
inline std::uintptr_t GTA_GAME_WEATHER_EVENT_TABLE = 0x7FF62E5AD8A8;
inline std::uintptr_t GTA_GAME_CLOCK_EVENT_TABLE = 0x7FF62E5AD7D8;
inline std::uintptr_t GTA_SCRIPTED_GAME_EVENT_TABLE = 0x7FF62E5AE738;
inline std::uintptr_t GTA_EXPLOSION_EVENT_TABLE = 0x7FF62E5ADE48;
inline std::uintptr_t GTA_FIRE_EVENT_TABLE = 0x7FF62E5ADD88;
inline std::uintptr_t GTA_INCREMENT_STAT_EVENT_TABLE = 0x7FF62E5B0458;
inline std::uintptr_t GTA_PED_INST_POOL = 0x7FF62F04C9B8; // In first vtable func
inline std::uintptr_t GTA_OBJ_INST_POOL = 0x7FF62F074310; // In first vtable func
inline std::uintptr_t GTA_VEH_LIST_POOL = 0x7FF62F3B8718; // In first vtable func
inline std::uintptr_t GTA_GET_CHAT_MSG_DATA = 0x7FF62DD231F8; // 48 8B C4 48 89 58 08 48 89 70 10 57 48 83 EC 20 48 8B F1 48 8D 48 18 33 DB 48 8B FA 89 58 18 E8 ? ? ? ? 85 C0 74 4C 8B 44 24 40 39 05 ? ? ? ? 75 40 41 B8 ? ? ? ? 
inline std::uintptr_t GTA_WRITE_SYNC_DATA_STRING = 0x7FF62DE54D4C; // 48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 54 41 56 41 57 48 83 EC 20 33 F6 4C 8B E2 
inline std::uintptr_t GTA_WRITE_SYNC_DATA_QWORD = 0x7FF62DE5501C; // 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 41 8B F0 48 8B EA 48 8B D9 41 83 F8 20 
inline std::uintptr_t GTA_ASSIGN_PHYSICAL_INDEX = 0x7FF62E1DD2A8; // 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 20 41 8A E8 
inline std::uintptr_t GTA_WAYPOINT_PATH_DATA = 0x7FF62EAFA710; // 48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 83 EC 20 48 8D B9 ? ? ? ? 48 8B D9 45 33 F6 48 8B 0F 41 8A E8 (Find 1 xref with ptr to wp data)

inline std::uintptr_t GTA_SEND_CLONE_SYNC_PATCH = 0x7FF62E1E0AAC; // netObjectMgrBase + 0xA8‬ 
inline std::uintptr_t GTA_BUILDING_INST_POOL = 0x7FF62F1108F8; // ptr in 1st vt fn
inline std::uintptr_t GTA_WRITE_SYNC_DATA_BOOL = 0x7FF62DE54B70; // 1st jumpout first static virtual in datawriter

inline std::uintptr_t GTA_GET_MODEL_INFO = 0x7FF62E1B6A38; // 0F B7 05 ? ? ? ? 45 33 C9 4C 8B DA 66 85 C0 0F 84 ? ? ? ? 44 0F B7 C0 33 D2 8B C1 41 F7 F0 48 8B 05 ? ? ? ? 4C 8B 14 D0 EB 09 41 3B 0A 74 54 
inline std::uintptr_t GTA_PROCESS_NET_OBJ = 0x7FF62E1C5AC0; // 

inline std::uintptr_t GTA_PACK_CLONE_CREATE = 0x7FF62E1C6DB0; // 7FF7F9349D48

inline std::uintptr_t GTA_SEND_CLONE_SYNC = 0x7FF62E1DAF7C; //

#elif defined(IS_STEAM_VERSION)

#define WORKING_DUMP_BASE 0x7FF7F7D20000

inline std::uintptr_t GTA_JMP_RBX = 0x7FF7F8E485BC; // 23 C3 C1 E0 0C  (-1)
inline std::uintptr_t GTA_NATIVE_REGISTRATION = 0x7FF7FAA651B0; // 48 8D 0D ? ? ? ? 48 8B 14 FA
inline std::uintptr_t GTA_GET_NATIVE_HANDLER = 0x7FF7F8759518; // 48 8D 0D ? ? ? ? 48 8B 14 FA (First call)
inline std::uintptr_t GTA_RETURN_FALSE_SUB = 0x7FF7F92E2167; // 32 C0 C3 (Any)
inline std::uintptr_t GTA_SET_VECTOR_RESULTS = 0x7FF7F92A0E88; // 83 79 18 00 48 8B D1 74 4A 
inline std::uintptr_t GTA_GET_SESSION_HOST_NET_GAME_PLAYER = 0x7FF7F8D50DC8; // 40 53 48 83 EC 20 48 8B 49 20 48 8D 54 24 ? (Go back until you find call near ptr)
inline std::uintptr_t GTA_GET_NET_GAME_PLAYER_FROM_PHYSICAL_INDEX = 0x7FF7F934E92C; // 80 F9 20 73 13 
inline std::uintptr_t GTA_GET_SCRIPT_INDEX_FROM_ENTITY = 0x7FF7F92A8690; // 48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 8B 15 ? ? ? ? 48 8B F9 48 83 C1 10 33 DB
inline std::uintptr_t GTA_GET_ENTITY_FROM_SCRIPT_GUID = 0x7FF7F8A470D8; // 40 53 48 83 EC 20 48 63 DA E8 ? ? ? ? 48 85 C0 74 21 (First call you see)
inline std::uintptr_t GTA_GET_NET_OBJECT_BY_NET_ID = 0x7FF7F8D52B68; // 48 89 5C 24 ? 48 89 6C 24 ? 66 89 54 24 ? (Find jmp xref with 1 xref from caller)
inline std::uintptr_t GTA_GET_LOCAL_PLAYER_PED = 0x7FF7F83A7298; // 48 8B 05 ? ? ? ? 48 8B 40 08 C3 
inline std::uintptr_t GTA_GET_SYNC_TREE_FROM_CLONE_TYPE = 0x7FF7F8E10D7C; // 0F B7 CA 83 F9 07 
inline std::uintptr_t GTA_STREAMED_SCRIPTS = 0x7FF7FA2F92E0; // 48 8D 0D ? ? ? ? E8 ? ? ? ? 83 38 FF 74 2D 
inline std::uintptr_t GTA_LOCAL_SCRIPT_HANDLERS = 0x7FF7FA2CF370; // 40 53 48 83 EC 20 80 79 30 00 0F 84 ? ? ? ? (Last loc -> loc then net)
inline std::uintptr_t GTA_NETWORKED_SCRIPT_HANDLERS = 0x7FF7FA2CF138; // // 40 53 48 83 EC 20 80 79 30 00 0F 84 ? ? ? ? (Last loc -> loc then net)
inline std::uintptr_t GTA_REMOVE_PLAYER_FROM_PLAYER_MGR = 0x7FF7F8E28BC8; // 48 89 5C 24 ? 57 48 83 EC 20 48 8B DA 48 8B F9 E8 ? ? ? ? 84 C0 75 14 
inline std::uintptr_t GTA_REGISTER_GAME_FILE = 0x7FF7F92C9A74; // 48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 
inline std::uintptr_t GTA_CHANGE_NET_OBJ_OWNER = 0x7FF7F934926C; // 48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 54 41 56 41 57 48 81 EC ? ? ? ? 44 8A 62 4B 
inline std::uintptr_t GTA_GET_VEHICLE_PAINT_LIST_ARRAY = 0x7FF7F831A1C0; // 4C 8B 0D ? ? ? ? 45 33 C0 4D 85 C9
inline std::uintptr_t GTA_PACK_CLONE_REMOVE = 0x7FF7F935C59C; // 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 30 41 80 78 ? ? 
inline std::uintptr_t GTA_PACK_CLONE_SYNC = 0x7FF7F9363918; // 48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 02 
inline std::uintptr_t GTA_MODEL_INFO_LIST_POOL = 0x7FF7F9B17ED0; // 0F B7 05 ? ? ? ? 45 33 C9 4C 8B DA 66 85 C0 0F 84 ? ? ? ? 44 0F B7 C0 33 D2 8B C1 41 F7 F0 48 8B 05 ? ? ? ? 4C 8B 14 D0 EB 09 41 3B 0A 74 54 (Last add instr with addr)
inline std::uintptr_t GTA_WATER_TUNE_XML = 0x7FF7F99C3C54; // F3 0F 11 05 ? ? ? ? F3 0F 10 05 ? ? ? ? F3 0F 11 0D ? ? ? ? 0F 28 0D ? ? ? ? 
inline std::uintptr_t GTA_WATER_QUAD_XML = 0x7FF7F9F38470; // 48 8D 0D ? ? ? ? 66 44 89 05 ? ? ? ? E8 ? ? ? ? 0F B7 05 ? ? ? ? 
inline std::uintptr_t GTA_WATER_QUAD_XML_COUNT = 0x7FF7F9F38478; // 48 8D 0D ? ? ? ? 66 44 89 05 ? ? ? ? E8 ? ? ? ? 0F B7 05 ? ? ? ?  (+ 0x8)
inline std::uintptr_t GTA_HUD_COLOUR_POOL = 0x7FF7F9C64990; // 41 8B 8C 84 ? ? ? ? 41 0F B6 C0 
inline std::uintptr_t GTA_PED_FACTORY = 0x7FF7FA1D0C50; // 48 8B 05 ? ? ? ? 48 8B 40 08 C3 
inline std::uintptr_t GTA_ATTACHMENT_EXTENSION_INST_POOL = 0x7FF7FAB45CA8; // 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 85 C0 74 0E 48 8B D6 48 8B C8 E8 ? ? ? ? 48 8B D8 48 89 5F 48 
inline std::uintptr_t GTA_GAME_GLOBALS = 0x7FF7FAA66190; // 4C 8D 05 ? ? ? ? 4D 8B 08 4D 85 C9 74 11 
inline std::uintptr_t GTA_SUPER_GRIP_FLOAT = 0x7FF7F9603524; // F3 0F 59 15 ? ? ? ? F3 41 0F 58 D2 F3 0F 59 D0 
inline std::uintptr_t GTA_NETWORK_OBJECT_MGR_INTERFACE = 0x7FF7FA5C0DF0; // 48 8B 05 ? ? ? ? 44 0F B7 8C FB ? ? ? ? 4C 8D 05 ? ? ? ? 48 8B 88 ? ? ? ? 48 8D 15 ? ? ? ? 48 8B 01 FF 50 30 48 8B 05 ? ? ? ? 44 0F B7 8C FB ? ? ? ? 48 8B 88 ? ? ? ? (Any)
inline std::uintptr_t GTA_NETWORK_PLAYER_MGR_INTERFACE = 0x7FF7FAB4FE98; // 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? C3
inline std::uintptr_t GTA_FORCE_SCRIPT_HOST = 0x7FF7F873DB9C; // 48 89 5C 24 ? 57 48 83 EC 50 48 8B FA 48 8B D9 E8 ? ? ? ? 83 7B 10 08 
inline std::uintptr_t GTA_SMALL_HOST_TOKEN_PATCH = 0x7FF7FAA227B1; // C6 05 ? ? ? ? ? 48 8B CB E8 ? ? ? ? 84 C0 75 08 
inline std::uintptr_t GTA_NETWORK_OBJECT_MGR_TABLE = 0x7FF7F971C298;
inline std::uintptr_t GTA_NET_OBJ_PED_NODE_DATA_ACCESSOR_TABLE = 0x7FF7F97295D8;
inline std::uintptr_t GTA_NET_OBJ_OBJECT_NODE_DATA_ACCESSOR_TABLE = 0x7FF7F97258F8;
inline std::uintptr_t GTA_REMOVE_WEAPON_EVENT_TABLE = 0x6A021CF02A47AF78;
inline std::uintptr_t GTA_REMOVE_ALL_WEAPONS_EVENT_TABLE = 0x7FF7F97311F8;
inline std::uintptr_t GTA_GAME_WEATHER_EVENT_TABLE = 0x7FF7F9730EB8;
inline std::uintptr_t GTA_GAME_CLOCK_EVENT_TABLE = 0x7FF7F9730DE8;
inline std::uintptr_t GTA_SCRIPTED_GAME_EVENT_TABLE = 0x7FF7F9731D48;
inline std::uintptr_t GTA_EXPLOSION_EVENT_TABLE = 0x7FF7F9731458;
inline std::uintptr_t GTA_FIRE_EVENT_TABLE = 0x7FF7F9731398;
inline std::uintptr_t GTA_INCREMENT_STAT_EVENT_TABLE = 0x7FF7F9733A68;
inline std::uintptr_t GTA_PED_INST_POOL = 0x7FF7FA1D0AA0; // In first vtable func
inline std::uintptr_t GTA_OBJ_INST_POOL = 0x7FF7FA1F7540; // In first vtable func
inline std::uintptr_t GTA_VEH_LIST_POOL = 0x7FF7FA539AE8; // In first vtable func
inline std::uintptr_t GTA_GET_CHAT_MSG_DATA = 0x7FF7F8EA4F04; // 48 8B C4 48 89 58 08 48 89 70 10 57 48 83 EC 20 48 8B F1 48 8D 48 18 33 DB 48 8B FA 89 58 18 E8 ? ? ? ? 85 C0 74 4C 8B 44 24 40 39 05 ? ? ? ? 75 40 41 B8 ? ? ? ? 
inline std::uintptr_t GTA_WRITE_SYNC_DATA_STRING = 0x7FF7F8FD7254; // 48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 54 41 56 41 57 48 83 EC 20 33 F6 4C 8B E2 
inline std::uintptr_t GTA_WRITE_SYNC_DATA_QWORD = 0x7FF7F8FD7524; // 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 41 8B F0 48 8B EA 48 8B D9 41 83 F8 20 
inline std::uintptr_t GTA_ASSIGN_PHYSICAL_INDEX = 0x7FF7F9360114; // 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 20 41 8A E8 
inline std::uintptr_t GTA_WAYPOINT_PATH_DATA = 0x7FF7F9C7EA10; // 48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 83 EC 20 48 8D B9 ? ? ? ? 48 8B D9 45 33 F6 48 8B 0F 41 8A E8 (Find 1 xref with ptr to wp data)

inline std::uintptr_t GTA_SEND_CLONE_SYNC_PATCH = 0x7FF7F935DDE8; // netObjectMgrBase + 0xA8‬ 
inline std::uintptr_t GTA_BUILDING_INST_POOL = 0x7FF7FA294588; // ptr in 1st vt fn

inline std::uintptr_t GTA_WRITE_SYNC_DATA_BOOL = 0x7FF7F8FD7078; // 1st jumpout first static virtual in datawriter

inline std::uintptr_t GTA_GET_MODEL_INFO = 0x7FF7F9339E24; // 0F B7 05 ? ? ? ? 45 33 C9 4C 8B DA 66 85 C0 0F 84 ? ? ? ? 44 0F B7 C0 33 D2 8B C1 41 F7 F0 48 8B 05 ? ? ? ? 4C 8B 14 D0 EB 09 41 3B 0A 74 54 
inline std::uintptr_t GTA_PROCESS_NET_OBJ = 0x7FF7F9348A60; // 

inline std::uintptr_t GTA_PACK_CLONE_CREATE = 0x7FF7F9349D48;
#endif

#define TRANSLATE_RUNTIME_RVA(v) {\
    std::uint64_t cache = v;\
    std::uint64_t base = reinterpret_cast<std::uint64_t>(GetModuleHandle(NULL));\
    if (base != WORKING_DUMP_BASE){\
        v = (base + (v - WORKING_DUMP_BASE));\
        if (v == cache || v == base || v == NULL || v == WORKING_DUMP_BASE) {\
            Sleep(40000);\
            return false;\
        }\
    }\
}\

namespace KEYBOARD {

    inline bool IS_KEYBOARD_INPUT_JUST_PRESSED(std::int32_t key) {
        return GetAsyncKeyState(key) & 0x0001;
    }

    inline bool IS_KEYBOARD_INPUT_PRESSED(std::int32_t key) {
        return GetAsyncKeyState(key) & 0x8000;
    }
}

inline HMODULE g_hmodule{};
inline HANDLE g_main_thread{};
inline DWORD g_main_thread_id{};
inline bool g_running{ true };

enum eGameState : std::uint32_t
{
    Playing = 0
};

namespace funcs {
    using DoesCamExist = bool(*)(Cam cam);
    using NativeHandler = rage::scrNativeHandler(*)(rage::scrNativeRegistrationTable*, rage::scrNativeHash);
    using FixVectors = void(*)(rage::scrNativeCallContext*);
    using FileRegister = uint32_t*(*)(int*, const char*, bool, const char*, bool);
	using WndProc = LRESULT(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    using GetPlayerName = const char* (_fastcall*)(int32_t index);
    using GetNetPlayer = int64_t(_fastcall*)(int32_t index);
}
class pointers
{
public:
    funcs::DoesCamExist m_DCE{};
    funcs::FixVectors m_FV{};
    funcs::FileRegister m_FR{};
    funcs::NativeHandler m_GNH{};
	funcs::WndProc* m_WP{};
	funcs::GetPlayerName m_GPN{};
	funcs::GetNetPlayer m_GNP{};
    std::uint64_t* m_FC{};
    char* m_GB{};
    bool* m_ISS{};
    eGameState* m_GS{};
    rage::scrNativeRegistrationTable* m_NRT{};
	HWND m_GW{};
    IDXGISwapChain* m_SC{};
    bool g_testui{ true };
    bool g_init{ true };
    void g_onloop()
    {
        if (g_init) {
            void* d3d_device{};
            printf("Crash here: Dead SC\n");
            if (!SUCCEEDED(m_SC->GetDevice(__uuidof(ID3D11Device), &d3d_device)))
            {
                printf("Error getting buffer from swap chain: %s\n", m_SC->GetDevice(__uuidof(ID3D11Device), (void**)d3d_device));
            }
            if (SUCCEEDED(m_SC->GetDevice(__uuidof(ID3D11Device), &d3d_device)))
            {
                printf("D3D Engine: true\n");
            }
            else
            {
                printf("D3D Engine: false\n");
            }
            m_d3d_device->GetImmediateContext(&m_d3d_device_context);
            printf("D3D Engine 2: true\n");
            ImGui::CreateContext();
            printf("D3D Engine 3: true\n");
            ImGui_ImplDX11_Init(m_d3d_device, m_d3d_device_context);
            printf("D3D Engine 4: true\n");
            ImGui_ImplWin32_Init(m_GW);
            printf("D3D Engine 5: true\n");
        }
        ImGui::GetIO().MouseDrawCursor = true;
        ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        //ImGui::Begin("Test");
        //if (ImGui::Button("Unload")) {
        //    g_running = false;
        //}
        //ImGui::Button("Test");
        //ImGui::End();
        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }
    void g_wndproc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        if (msg == WM_KEYUP && wParam == VK_F4) {
            g_testui = !g_testui;
        }
        if (ImGui::GetCurrentContext()) ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
    }
    void pre_reset()
    {
        ImGui_ImplDX11_InvalidateDeviceObjects();
    }
    void post_reset()
    {
        ImGui_ImplDX11_CreateDeviceObjects();
    }
    ID3D11Device* m_d3d_device;
    ID3D11DeviceContext* m_d3d_device_context;
};

inline pointers ptr;

struct Hooks
{
    static bool DoesCamExist(Cam cam);
    static LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    static constexpr auto swapchain_num_funcs = 19;
    static constexpr auto swapchain_present_index = 8;
    static constexpr auto swapchain_resizebuffers_index = 13;
    static HRESULT swapchain_present(IDXGISwapChain* this_, UINT sync_interval, UINT flags);
    static HRESULT swapchain_resizebuffers(IDXGISwapChain* this_, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swapchain_flags);
};

class Hooking
{
    friend Hooks;
public:
    void* m_OriginalDoesCamExist{};
    void* m_OriginalWndProc{};
    void* m_OriginalPresentIndex{};
    void* m_OriginalPresentBuffersIndex{};
};

inline Hooking hook;

inline void printfnl(const char* msg, ...) {
    std::va_list args{};
    va_start(args, msg);
    printf("%s\n", msg);
    va_end(args);
}