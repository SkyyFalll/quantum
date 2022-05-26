#include "menu.h"
#include "main.h"
#include "PatternMgr.hpp"
#include <random>
#include <timeapi.h>
#include "rage/Script.hpp"
#include "rage/ScriptManager.hpp"
#include "imgui/VMTHook.hpp"

void game_patch_return_stub() { return; }
bool game_patch_return_input_bool_stub(bool input) { return input; }
bool game_patch_return_true_stub() { return true; }
bool game_patch_return_false_stub() { return false; }
std::uint64_t game_patch_return_six_stub() { return 6; }
native_call_cxt* native_cxt_return_stub(native_call_cxt* cxt) { return cxt; }

bool should_send_event_to_player_shim(std::uint64_t net_game_event, std::uint8_t* net_game_player) {
	return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
}

bool pack_metric_data_shim(std::uint64_t rl_metric, std::uint64_t data) {
	return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
}

bool receive_clone_create_shim(std::uint64_t networkobjectmgr, std::uint8_t* net_game_player, std::uint64_t r8, std::uint16_t clonetype, std::uint16_t networkid, std::uint64_t a7, std::uint64_t a8, std::uint32_t timestamp) {
	if (clonetype >= 0 && clonetype < 14) {
		std::uint64_t network_player_mgr = *(std::uint64_t*)GTA_NETWORK_PLAYER_MGR_INTERFACE;
		if (network_player_mgr != NULL) {
			std::uint64_t sync_tree = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint64_t, std::uint16_t))GTA_GET_SYNC_TREE_FROM_CLONE_TYPE), networkobjectmgr, clonetype);
			if (sync_tree != NULL) {

				// this is ghetto as fuck, but who cares
				std::uint32_t hash = *(std::uint32_t*)((sync_tree + 0x2820) + 0xC8);	// automobile
				std::uint64_t model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 5) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);	// bike
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 5) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);	// boat
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 5) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x1620) + 0x150);	// door
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 1) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x2820) + 0xC8);	// heli
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 5) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x1620) + 0x150);	// object
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 1) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x3360) + 0xC4);	// ped
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 6) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x1620) + 0x120);	// pickup
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 1) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x920) + 0xFC);	// pickup placement
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 1) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);	// plane
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 5) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);	// submarine
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 5) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x35F0) + 0x400);	// player
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 6) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);	// trailer
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 5) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);	// train
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 5) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				std::uint64_t net_object = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint16_t))GTA_GET_NET_OBJECT_BY_NET_ID), networkid);
				if (net_object != NULL) {
					if (*reinterpret_cast<std::add_pointer_t<std::uint16_t>>(net_object + 0x8) != clonetype) {
						std::stringstream ss;
						ss << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Crash", ss.str());
						SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint64_t, std::uint8_t*))GTA_REMOVE_PLAYER_FROM_PLAYER_MGR), network_player_mgr, net_game_player);
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
					std::uint64_t local_ped = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)())GTA_GET_LOCAL_PLAYER_PED));
					if (local_ped != NULL) {
						if (net_object == *(std::uint64_t*)(local_ped + 0xD0)) {
							std::stringstream ss;
							ss << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
							map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Crash", ss.str());
							SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint64_t, std::uint8_t*))GTA_REMOVE_PLAYER_FROM_PLAYER_MGR), network_player_mgr, net_game_player);
							return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
						}
					}
					if (*(std::uint16_t*)(net_object + 0x8) != clonetype) {
						std::stringstream ss;
						ss << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Crash", ss.str());
						SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint64_t, std::uint8_t*))GTA_REMOVE_PLAYER_FROM_PLAYER_MGR), network_player_mgr, net_game_player);
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}
			}
			else {
				std::stringstream ss;
				ss << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
				map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Crash", ss.str());
				SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint64_t, std::uint8_t*))GTA_REMOVE_PLAYER_FROM_PLAYER_MGR), network_player_mgr, net_game_player);
				return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
			}
		}
		g_received_net_obj[g_received_net_obj_count].m_timestamp = GetTickCount64();
		g_received_net_obj[g_received_net_obj_count].m_net_id = networkid;
		g_received_net_obj[g_received_net_obj_count].m_owner_physical_index = net_game_player[0x2D];
		g_received_net_obj[g_received_net_obj_count].m_clone_type = clonetype;
		g_received_net_obj_count = (++g_received_net_obj_count < 100) ? g_received_net_obj_count : NULL;
		return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((bool(*)(std::uint64_t, std::uint8_t*, std::uint64_t, std::uint16_t, std::uint16_t, std::uint64_t, std::uint64_t, std::uint32_t))g_receive_clone_create_cache), networkobjectmgr, net_game_player, r8, clonetype, networkid, a7, a8, timestamp);
	}
	else {
		std::stringstream ss;
		ss << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
		map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Crash", ss.str());
		return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
	}
}

std::uint64_t receive_clone_sync_shim(std::uint64_t networkobjectmgr, std::uint8_t* net_game_player, std::uint64_t r8, std::uint16_t clonetype, std::uint16_t networkid, std::uint64_t a7, std::uint64_t a8, std::uint32_t timestamp) {
	if (clonetype >= 0 && clonetype < 14) {
		std::uint64_t network_player_mgr = *(std::uint64_t*)GTA_NETWORK_PLAYER_MGR_INTERFACE;
		if (network_player_mgr != NULL) {
			std::uint64_t sync_tree = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint64_t, std::uint16_t))GTA_GET_SYNC_TREE_FROM_CLONE_TYPE), networkobjectmgr, clonetype);
			if (sync_tree != NULL) {

				// this is ghetto as fuck, but who cares
				std::uint32_t hash = *(std::uint32_t*)((sync_tree + 0x2820) + 0xC8);	// automobile
				std::uint64_t model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 5) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);	// bike
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 5) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);	// boat
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 5) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x1620) + 0x150);	// door
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 1) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x2820) + 0xC8);	// heli
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 5) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x1620) + 0x150);	// object
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 1) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x3360) + 0xC4);	// ped
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 6) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x1620) + 0x120);	// pickup
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 1) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x920) + 0xFC);	// pickup placement
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 1) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);	// plane
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 5) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);	// submarine
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 5) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x35F0) + 0x400);	// player
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 6) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);	// trailer
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 5) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);	// train
				model_info = get_model_info_ptr(hash);
				if (model_info) {
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
					if (model_type != 5) {
						std::stringstream ss;
						ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "ST Model Mismatch", ss.str());
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
					}
				}

				std::uint64_t net_object = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint16_t))GTA_GET_NET_OBJECT_BY_NET_ID), networkid);
				if (net_object != NULL) {
					if (*reinterpret_cast<std::add_pointer_t<std::uint16_t>>(net_object + 0x8) != clonetype) {
						std::stringstream ss;
						ss << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Crash", ss.str());
						SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint64_t, std::uint8_t*))GTA_REMOVE_PLAYER_FROM_PLAYER_MGR), network_player_mgr, net_game_player);
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_six_stub);
					}
					std::uint64_t local_ped = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)())GTA_GET_LOCAL_PLAYER_PED));
					if (local_ped != NULL) {
						if (net_object == *(std::uint64_t*)(local_ped + 0xD0)) {
							std::stringstream ss;
							ss << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
							map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Crash", ss.str());
							SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint64_t, std::uint8_t*))GTA_REMOVE_PLAYER_FROM_PLAYER_MGR), network_player_mgr, net_game_player);
							return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_six_stub);
						}
					}
					if (*(std::uint16_t*)(net_object + 0x8) != clonetype) {
						std::stringstream ss;
						ss << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
						map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Crash", ss.str());
						SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint64_t, std::uint8_t*))GTA_REMOVE_PLAYER_FROM_PLAYER_MGR), network_player_mgr, net_game_player);
						return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_six_stub);
					}
				}
			}
			else {
				std::stringstream ss;
				ss << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
				map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Crash", ss.str());
				SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint64_t, std::uint8_t*))GTA_REMOVE_PLAYER_FROM_PLAYER_MGR), network_player_mgr, net_game_player);
				return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_six_stub);
			}
		}
		g_received_net_obj[g_received_net_obj_count].m_timestamp = GetTickCount64();
		g_received_net_obj[g_received_net_obj_count].m_net_id = networkid;
		g_received_net_obj[g_received_net_obj_count].m_owner_physical_index = net_game_player[0x2D];
		g_received_net_obj[g_received_net_obj_count].m_clone_type = clonetype;
		g_received_net_obj_count = (++g_received_net_obj_count < 100) ? g_received_net_obj_count : NULL;
		return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((bool(*)(std::uint64_t, std::uint8_t*, std::uint64_t, std::uint16_t, std::uint16_t, std::uint64_t, std::uint64_t, std::uint32_t))g_receive_clone_sync_cache), networkobjectmgr, net_game_player, r8, clonetype, networkid, a7, a8, timestamp);
	}
	else {
		std::stringstream ss;
		ss << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
		map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Crash", ss.str());
		return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_six_stub);
	}
}

bool receive_clone_remove_shim(std::uint64_t network_object_mgr, std::uint8_t* net_game_player, std::uint64_t r5, std::uint16_t network_id, std::uint64_t r7) {
	std::uint64_t local_ped = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)())GTA_GET_LOCAL_PLAYER_PED));
	if (local_ped != NULL) {
		std::uint64_t net_object = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint16_t))GTA_GET_NET_OBJECT_BY_NET_ID), network_id);
		if (net_object == *(std::uint64_t*)(local_ped + 0xD0)) {
			std::stringstream ss;
			ss << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(net_game_player[0x2D]));
			map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Crash Attempt", ss.str());
			return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
		}
	}
	return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((bool(*)(std::uint64_t, std::uint8_t*, std::uint64_t, std::uint16_t, std::uint64_t))g_receive_clone_remove_cache), network_object_mgr, net_game_player, r5, network_id, r7);
}

void remove_weapon_event_read_sync_data_shim(std::uint64_t net_game_event, std::uint64_t sync_data, std::uint64_t net_game_player, std::uint64_t unk) {
	if (g_protection_remove_weapon) {
		if (g_notify_attacks) {
			std::uint64_t player_info = *(std::uint64_t*)(net_game_player + 0xA8);
			if (player_info != NULL) {
				std::stringstream ss;
				ss << "From: " << (char*)(player_info + 0x7C);
				map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Remove Weapon", ss.str());
			}
		}
		SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_stub);
	}
	SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((void(*)(std::uint64_t, std::uint64_t, std::uint64_t, std::uint64_t))g_remove_weapon_event_read_sync_data_cache), net_game_event, sync_data, net_game_player, unk);
}

void remove_all_weapons_event_read_sync_data_shim(std::uint64_t net_game_event, std::uint64_t sync_data, std::uint64_t net_game_player, std::uint64_t unk) {
	if (g_protection_remove_all_weapons) {
		if (g_notify_attacks) {
			std::uint64_t player_info = *(std::uint64_t*)(net_game_player + 0xA8);
			if (player_info != NULL) {
				std::stringstream ss;
				ss << "From: " << (char*)(player_info + 0x7C);
				map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Remove All Weapons", ss.str());
			}
		}
		SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_stub);
	}
	SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((void(*)(std::uint64_t, std::uint64_t, std::uint64_t, std::uint64_t))g_remove_all_weapons_event_read_sync_data_cache), net_game_event, sync_data, net_game_player, unk);
}

void game_weather_event_read_sync_data_shim(std::uint64_t net_game_event, std::uint64_t sync_data, std::uint64_t net_game_player, std::uint64_t unk) {
	if (g_protection_weather_change) {
		if (g_notify_attacks) {
			std::uint64_t player_info = *(std::uint64_t*)(net_game_player + 0xA8);
			if (player_info != NULL) {
				std::stringstream ss;
				ss << "From: " << (char*)(player_info + 0x7C);
				map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Weather", ss.str());
			}
		}
		SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_stub);
	}
	SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((void(*)(std::uint64_t, std::uint64_t, std::uint64_t, std::uint64_t))g_game_weather_event_read_sync_data_cache), net_game_event, sync_data, net_game_player, unk);
}

void game_clock_event_read_sync_data_shim(std::uint64_t net_game_event, std::uint64_t sync_data, std::uint64_t net_game_player, std::uint64_t unk) {
	SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_stub);
}

bool scripted_game_event_callback_shim(std::uint64_t net_game_event, std::uint64_t net_game_player, std::uint64_t unk) {
	std::uint64_t player_info = *(std::uint64_t*)(net_game_player + 0xA8);
	if (player_info != NULL) {
		std::int32_t* args = (std::int32_t*)(net_game_event + 0x70);
		std::int32_t count = *(std::int32_t*)(net_game_event + 0x224);

		if (args[0] == -1256990787) { // Crash
			return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_true_stub);
		}

		if (args[0] == -498955166) {
			return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_true_stub);
		}

		if (args[0] == 564131320) {
			return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_true_stub);
		}

		if (args[0] == 1152017566) {
			std::stringstream ss;
			ss << "Off-Host Kick" << std::endl << "From: " << (char*)(player_info + 0x7C);
			map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Script", ss.str());
			return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_true_stub);
		}

		if (args[0] == 297770348) {
			std::stringstream ss;
			ss << "Off-Host Kick" << std::endl << "From: " << (char*)(player_info + 0x7C);
			map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Script", ss.str());
			return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_true_stub);
		}

		if (args[0] == -1246838892) {
			std::stringstream ss;
			ss << "Off-Host Kick" << std::endl << "From: " << (char*)(player_info + 0x7C);
			map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Script", ss.str());
			return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_true_stub);
		}

		if (args[0] == -2120750352) {
			std::stringstream ss;
			ss << "Off-Host Kick" << std::endl << "From: " << (char*)(player_info + 0x7C);
			map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Script", ss.str());
			return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_true_stub);
		}

		if (args[0] == -701823896) {
			std::stringstream ss;
			ss << "CEO Kick" << std::endl << "From: " << (char*)(player_info + 0x7C);
			map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Script", ss.str());
			return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_true_stub);
		}

		if (args[0] == -327286343) {
			std::stringstream ss;
			ss << "CEO Ban" << std::endl << "From: " << (char*)(player_info + 0x7C);
			map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Script", ss.str());
			return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_true_stub);
		}

		if (args[0] == 189238289) {
			std::stringstream ss;
			ss << "Transaction Error" << std::endl << "From: " << (char*)(player_info + 0x7C);
			map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Script", ss.str());
			return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_true_stub);
		}

		if (args[0] == 561831609) {
			std::stringstream ss;
			ss << "Empty Banner" << std::endl << "From: " << (char*)(player_info + 0x7C);
			map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Script", ss.str());
			return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_true_stub);
		}

		if (args[0] == -1089379066) {
			std::stringstream ss;
			ss << "Kick From Vehicle" << std::endl << "From: " << (char*)(player_info + 0x7C);
			map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Script", ss.str());
			return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_true_stub);
		}

		if (args[0] == -125347541) {
			std::stringstream ss;
			ss << "Load Screen" << std::endl << "From: " << (char*)(player_info + 0x7C);
			map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Script", ss.str());
			return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_true_stub);
		}

		if (args[0] == -1246838892) {
			std::stringstream ss;
			ss << "Black Screen" << std::endl << "From: " << (char*)(player_info + 0x7C);
			map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Script", ss.str());
			return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_true_stub);
		}

		if (args[0] == -327286343) {
			std::stringstream ss;
			ss << "Force Into Mission" << std::endl << "From: " << (char*)(player_info + 0x7C);
			map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Script", ss.str());
			return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_true_stub);
		}

		if (args[0] == -1961284186) {
			std::stringstream ss;
			ss << "Cops Turn Blind Eye" << std::endl << "From: " << (char*)(player_info + 0x7C);
			map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Script", ss.str());
			return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_true_stub);
		}

		if (args[0] == -615431083) {
			std::stringstream ss;
			ss << "Off The Radar" << std::endl << "From: " << (char*)(player_info + 0x7C);
			map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Script", ss.str());
			return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_true_stub);
		}

		if (args[0] == -125347541) {
			switch (args[5]) {
			case 1: {
				std::stringstream ss;
				ss << "TP - Eclipse Towers" << std::endl << "From: " << (char*)(player_info + 0x7C);
				map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Script", ss.str());
				break;
			}
			case 6: {
				std::stringstream ss;
				ss << "TP - Alta St." << std::endl << "From: " << (char*)(player_info + 0x7C);
				map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Script", ss.str());
				break;
			}
			case 7: {
				std::stringstream ss;
				ss << "TP - Del Perro" << std::endl << "From: " << (char*)(player_info + 0x7C);
				map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Script", ss.str());
				break;
			}
			case 8: {
				std::stringstream ss;
				ss << "TP - Power" << std::endl << "From: " << (char*)(player_info + 0x7C);
				map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Script", ss.str());
				break;
			}
			case 9: {
				std::stringstream ss;
				ss << "TP - Spanish" << std::endl << "From: " << (char*)(player_info + 0x7C);
				map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Script", ss.str());
				break;
			}
			case 10: {
				std::stringstream ss;
				ss << "TP - Las" << std::endl << "From: " << (char*)(player_info + 0x7C);
				map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Script", ss.str());
				break;
			}
			default: {
				std::stringstream ss;
				ss << "TP - Unknown" << std::endl << "From: " << (char*)(player_info + 0x7C);
				map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Script", ss.str());
				break;
			}
			}
			return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_true_stub);
		}

		if (count < 8) {
			std::cout << "scripted_game_event:";
			for (std::int32_t i = 0; i < count; i++) std::cout << " " << args[i];
			std::cout << std::endl;
		}
	}
	return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((bool(*)(std::uint64_t, std::uint64_t, std::uint64_t))g_scripted_game_event_callback_cache), net_game_event, net_game_player, unk);
}

bool explosion_event_callback_shim(std::uint64_t net_game_event, std::uint64_t net_game_player, std::uint64_t unk) {
	if (g_protection_explosion) {
		if (g_notify_attacks) {
			std::uint64_t player_info = *(std::uint64_t*)(net_game_player + 0xA8);
			if (player_info != NULL) {
				std::stringstream ss;
				ss << "Type: " << *(std::int32_t*)(net_game_event + 0x30) << std::endl << "From: " << (char*)(player_info + 0x7C);
				map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Explosion", ss.str());
			}
		}
		return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_true_stub);
	}
	return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((bool(*)(std::uint64_t, std::uint64_t, std::uint64_t))g_explosion_event_callback_cache), net_game_event, net_game_player, unk);
}

bool fire_event_callback_shim(std::uint64_t net_game_event, std::uint64_t net_game_player, std::uint64_t unk) {
	if (g_protection_fire) {
		if (g_notify_attacks) {
			std::uint64_t player_info = *(std::uint64_t*)(net_game_player + 0xA8);
			if (player_info != NULL) {
				std::stringstream ss;
				ss << "From: " << (char*)(player_info + 0x7C);
				map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Fire", ss.str());
			}
		}
		return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_true_stub);
	}
	return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((bool(*)(std::uint64_t, std::uint64_t, std::uint64_t))g_fire_event_callback_cache), net_game_event, net_game_player, unk);
}

bool increment_stat_event_callback_shim(std::uint64_t net_game_event, std::uint64_t net_game_player, std::uint64_t unk) {
	bool is_report = false;
	std::uint32_t hash = *(std::uint32_t*)(net_game_event + 0x30);

	switch (hash) {
	case 0x9C6A0C42: //MPPLY_GRIEFING
	case 0x62EB8C5A: //MPPLY_VC_ANNOYINGME
	case 0x0E7072CD: //MPPLY_VC_HATE
	case 0x762F9994: //MPPLY_TC_ANNOYINGME
	case 0xB722D6C0: //MPPLY_TC_HATE
	case 0x3CDB43E2: //MPPLY_OFFENSIVE_LANGUAGE
	case 0xE8FB6DD5: //MPPLY_OFFENSIVE_TAGPLATE
	case 0xF3DE4879: //MPPLY_OFFENSIVE_UGC
	case 0xAA238FF0: //MPPLY_BAD_CREW_NAME
	case 0x03511A79: //MPPLY_BAD_CREW_MOTTO
	case 0x3B566D5C: //MPPLY_BAD_CREW_STATUS
	case 0x368F6FD9: //MPPLY_BAD_CREW_EMBLEM
	case 0xCBFD04A4: //MPPLY_GAME_EXPLOITS
	case 0x9F79BA0B: //MPPLY_EXPLOITS
		is_report = true;
		break;
	default:
		is_report = false;
		break;
	}
	if (g_protection_explosion || is_report) {
		if (g_notify_attacks) {
			std::uint64_t player_info = *(std::uint64_t*)(net_game_player + 0xA8);
			if (player_info != NULL) {
				std::stringstream ss;
				ss << "Hash: " << std::hex << hash << std::endl << "Value: " << *(std::int32_t*)(net_game_event + 0x34) << std::endl << "From: " << (char*)(player_info + 0x7C);
				map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Stat", ss.str());
			}
		}
		return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_true_stub);
	}
	return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((bool(*)(std::uint64_t, std::uint64_t, std::uint64_t))g_increment_stat_event_callback_cache), net_game_event, net_game_player, unk);
}

void spawn_net_obj_ped_shim(std::uint64_t rcx, std::uint64_t rdx) {
	std::uint32_t hash = *(std::uint32_t*)(rdx + 0xC4);
	if (!STREAMING::IS_MODEL_VALID(hash)) {
		std::stringstream ss;
		ss << "Hash: " << std::hex << hash;
		map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Blacklisted ped", ss.str());
		SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_stub);
	}
	SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((void(*)(std::uint64_t, std::uint64_t))g_spawn_net_obj_ped_cache), rcx, rdx);
}

void spawn_net_obj_object_shim(std::uint64_t rcx, std::uint64_t rdx) {
	std::uint32_t hash = *(std::uint32_t*)(rdx + 0x150);
	if (!STREAMING::IS_MODEL_VALID(hash)) {
		std::stringstream ss;
		ss << "Hash: " << std::hex << hash;
		map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Blacklisted object", ss.str());
		SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_stub);
	}
	if (STREAMING::IS_MODEL_A_VEHICLE(hash)) {
		std::stringstream ss;
		ss << "Hash: " << std::hex << hash;
		map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Freeze object", ss.str());
		SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_stub);
	}
	SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((void(*)(std::uint64_t, std::uint64_t))g_spawn_net_obj_object_cache), rcx, rdx);
}

native_call_cxt* am_mp_property_int_disable_control_action_hook(native_call_cxt* cxt) {
	return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), native_cxt_return_stub, cxt);
}

native_call_cxt* am_mp_property_int_set_current_ped_weapon_hook(native_call_cxt* cxt) {
	return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), native_cxt_return_stub, cxt);
}

native_call_cxt* am_mp_smpl_interior_int_disable_control_action_hook(native_call_cxt* cxt) {
	return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), native_cxt_return_stub, cxt);
}

native_call_cxt* am_mp_smpl_interior_int_set_current_ped_weapon_hook(native_call_cxt* cxt) {
	return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), native_cxt_return_stub, cxt);
}

native_call_cxt* shop_controller_set_warning_message_hook(native_call_cxt* cxt) {
	return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), native_cxt_return_stub, cxt);
}

static bool(*get_chat_msg_data_t)(std::uint64_t, std::uint64_t) = NULL;
bool get_chat_msg_data_hook(std::uint64_t output, std::uint64_t sync_data) {
	bool return_value = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), get_chat_msg_data_t, output, sync_data);

	char* msg = (char*)(output);
	bool is_team = *(bool*)(output + 0x108);

	std::int32_t player = -1;
	for (std::int32_t i = 0; i < 32; i++) {
		std::uint64_t net_game_player = ((std::uint64_t(*)(std::uint8_t))GTA_GET_NET_GAME_PLAYER_FROM_PHYSICAL_INDEX)((std::uint8_t)(i));
		if (net_game_player == NULL)
			continue;
		std::uint64_t player_info = *(std::uint64_t*)(net_game_player + 0xA8);
		if (player_info == NULL)
			continue;
		if (*(std::uint64_t*)(player_info + 0x60) == *(std::uint64_t*)(output + 0x100)) {
			player = i;
			break;
		}
	}
	if (player != -1) {
		printf("%s is typing...", PLAYER::GET_PLAYER_NAME(player));
		printf("%s: %s", PLAYER::GET_PLAYER_NAME(player), msg);
		for (std::int32_t i = 0; i < ARRAYSIZE(g_chat_commands); i++) {
			if (std::string(msg) == g_chat_commands[i]) {
				if (g_chat_command_clients[player].m_has_access) {
					g_chat_command_clients[player].m_mod_active[i] = !g_chat_command_clients[player].m_mod_active[i];
					std::stringstream ss;
					if (i != 0) {
						std::int32_t handle[26];
						ss << "~b~Chat Cmd:~s~ You toggled ~y~" << g_chat_commands[i] << " " << g_chat_command_clients[player].m_mod_active[i] ? "~g~on~s~." : "~r~off~s~.";
						NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_network_selected_player, &handle[0], 13);
						NETWORK::NETWORK_SEND_TEXT_MESSAGE(ss.str().c_str(), &handle[0]);
						ss.str("");
						ss.clear();
					}
					ss << "~b~Chat Cmd:~s~ ~b~" << PLAYER::GET_PLAYER_NAME(player) << "~s~ has toggled ~y~" << g_chat_commands[i] << "~s~ " << g_chat_command_clients[player].m_mod_active[i] ? "~g~on~s~." : "~r~off~s~.";
					print_notification(7000, ss.str());
				}
			}
		}
	}
	return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_input_bool_stub, return_value);
}

static void* (*assign_physical_index_t)(void*, std::uint8_t*, std::uint8_t) = NULL;
void* assign_physical_index_hook(void* network_player_mgr, uint8_t* net_game_player, uint8_t new_index) {
	if (new_index == 255) {
		if (g_misc_player_join_leave_notify) {
			std::uint64_t player_info = *(std::uint64_t*)(net_game_player + 0xA8);
			if (player_info != NULL) {
				std::stringstream ss;
				ss << "Slot: " << (std::int32_t)(net_game_player[0x2D]) << std::endl << "Name: " << (char*)(player_info + 0x7C);
				map_notification("CHAR_DEFAULT", "<C>Notice</C>", "~r~Player Leaving", ss.str());
			}
		}
		if (net_game_player[0x2D] >= 0 && net_game_player[0x2D] < 32) {
			g_network_player_vars[net_game_player[0x2D]].reset_vars();
			g_chat_command_clients[net_game_player[0x2D]].revoke_access();
		}
	}
	else if (g_misc_player_join_leave_notify) {
		std::uint64_t player_info = *(std::uint64_t*)(net_game_player + 0xA8);
		if (player_info != NULL) {
			std::stringstream ss;
			ss << "Slot: " << (std::int32_t)(new_index) << std::endl << "Name: " << (char*)(player_info + 0x7C);
			map_notification("CHAR_DEFAULT", "<C>Notice</C>", "~g~Player Joining", ss.str());
		}
	}
	return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), assign_physical_index_t, network_player_mgr, net_game_player, new_index);
}

std::string g_advertisement_strings[] = {
	"~r~quantum.menu",
	"~o~quantum.menu",
	"~y~quantum.menu",
	"~g~quantum.menu",
	"~b~quantum.menu",
	"~p~quantum.menu",
	"~r~best cheats",
	"~o~best crashes",
	"~y~best kicks",
	"~g~best protxn",
	"~b~best options",
	"~p~superior",
};

static bool(*write_sync_data_string_t)(void*, const char*, std::size_t) = NULL;
bool write_sync_data_string_hook(void* sync_data, const char* input, std::size_t length) {

	std::int32_t my_index = PLAYER::PLAYER_ID();

	if (!strcmp(input, SOCIALCLUB::_SC_GET_NICKNAME())) {
		if (g_menu_network_spoofing_name_active) {
			return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), write_sync_data_string_t, sync_data, g_menu_network_spoofing_name.c_str(), g_menu_network_spoofing_name.size());
		}
	}
	else if (is_player_session_host(my_index)) {
		std::string string_to_spoof = input;
		bool was_dev_found = false;
		for (std::int32_t i = 0; i < 32; i++) {
			if (NETWORK::NETWORK_PLAYER_IS_ROCKSTAR_DEV(i)) {
				was_dev_found = true;
				break;
			}
		}
		if (!was_dev_found) {
			for (std::int32_t i = 0; i < 32; i++) {
				if (i == my_index) continue;
				const char* raw_name = PLAYER::GET_PLAYER_NAME(i);
				if (raw_name != nullptr) {
					if (!strcmp(input, raw_name)) {
						if (g_network_player_vars[i].m_spoofing_name_active) {
							string_to_spoof = g_network_player_vars[i].m_spoofing_name;
							return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), write_sync_data_string_t, sync_data, string_to_spoof.c_str(), string_to_spoof.size() + 1);
						}
						else if (std::bind(std::bernoulli_distribution(), std::default_random_engine())()) {
							string_to_spoof = g_advertisement_strings[rand() % std::size(g_advertisement_strings)];
							return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), write_sync_data_string_t, sync_data, string_to_spoof.c_str(), string_to_spoof.size() + 1);
						}
					}
				}
			}
		}
	}
	return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), write_sync_data_string_t, sync_data, input, length);
}

static void(*pack_clone_create_t)(std::uint64_t, std::uint64_t, std::uint8_t*, std::uint64_t) = NULL;
void pack_clone_create_hook(std::uint64_t network_object_mgr, std::uint64_t net_obj, std::uint8_t* net_game_player, std::uint64_t unk) {

	//freeze car targetted

	std::uint16_t net_type_cache = *reinterpret_cast<std::add_pointer_t<std::uint16_t>>(net_obj + 0x8);
	std::uint16_t net_id_cache = *reinterpret_cast<std::add_pointer_t<std::uint16_t>>(net_obj + 0xA);
	if (g_network_player_vars[net_game_player[0x2D]].m_do_spam_crash) {
		if (g_network_player_vars[net_game_player[0x2D]].m_spam_crash_entity != NULL) {
			std::uint64_t target_entity = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::int32_t))GTA_GET_ENTITY_FROM_SCRIPT_GUID), g_network_player_vars[net_game_player[0x2D]].m_spam_crash_entity);
			if (target_entity) {
				std::uint64_t target_net_obj = *(std::uint64_t*)(target_entity + 0xD0);
				if (target_net_obj) {
					if (target_net_obj == net_obj) {
						for (std::int32_t i = 0; i < 15; i++) {
							if (net_obj) {
								*reinterpret_cast<std::add_pointer_t<std::uint16_t>>(net_obj + 0xA) = rand() % INT16_MAX;
								*reinterpret_cast<std::add_pointer_t<std::uint16_t>>(net_obj + 0x8) = i;
							}
							SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), pack_clone_create_t, network_object_mgr, net_obj, net_game_player, unk);
						}
					}
				}
			}
			g_network_player_vars[net_game_player[0x2D]].m_spam_crash_entity = NULL;
			g_network_player_vars[net_game_player[0x2D]].m_do_spam_crash = false;
		}
	}
	*reinterpret_cast<std::add_pointer_t<std::uint16_t>>(net_obj + 0xA) = net_id_cache;
	*reinterpret_cast<std::add_pointer_t<std::uint16_t>>(net_obj + 0x8) = net_type_cache;
	SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), pack_clone_create_t, network_object_mgr, net_obj, net_game_player, unk);
}

static void(*send_clone_sync_t)(std::uint64_t, std::uint8_t*, std::uint64_t, std::uint64_t, std::uint64_t, bool) = NULL;
void send_clone_sync_hook(std::uint64_t a1, std::uint8_t* net_game_player, std::uint64_t net_obj, std::uint64_t a4, std::uint64_t a5, bool a6) {
	if (g_network_player_vars[net_game_player[0x2D]].m_do_clone_crash) {
		printfnl("c1!");
		if (g_network_player_vars[net_game_player[0x2D]].m_clone_crash_entity_target != NULL) {
			printfnl("c2!");
			std::uint64_t target_net_obj = *(std::uint64_t*)(g_network_player_vars[net_game_player[0x2D]].m_clone_crash_entity_target + 0xD0);
			if (target_net_obj) {
				printfnl("spoofeddddddddddd!");
				SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), send_clone_sync_t, a1, net_game_player, target_net_obj, a4, a5, a6);
			}
		}
	}
	else {
		SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), send_clone_sync_t, a1, net_game_player, net_obj, a4, a5, a6);
	}
}

static bool(*process_net_obj_t)(std::uint64_t, std::uint64_t) = NULL;
bool process_net_obj_hook(std::uint64_t sync_tree, std::uint64_t net_obj) {
	std::uint8_t owner = *reinterpret_cast<std::uint8_t*>(net_obj + 0x49); // make sure to get correct offsets
	switch (*reinterpret_cast<std::uint16_t*>(net_obj + 0x8)) {
	case 0UI16: {
		std::uint32_t hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);  // automobile
		std::uint64_t model_info = get_model_info_ptr(hash);
		if (model_info) {
			std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
			if (model_type == 5) {
				std::int32_t vehicle_type = *(std::int32_t*)(model_info + 0x340);
				if (vehicle_type != 0 && vehicle_type != 3) {
					std::stringstream ss;
					ss << "Vehicle: " << (char*)(model_info + 0x298) << std::endl << "From: " << PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(owner)) << std::endl;
					map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Invalid Car Handling", ss.str());
					return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
				}
			}
			else {
				std::stringstream ss;
				ss << "Vehicle: " << (char*)(model_info + 0x298) << std::endl << "From: " << PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(owner)) << std::endl;
				map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Invalid Car Hash", ss.str());
				return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
			}
		}
		break;
	}
	case 1UI16: {
		std::uint32_t hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);  // bike
		std::uint64_t model_info = get_model_info_ptr(hash);
		if (model_info) {
			std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
			if (model_type == 5) {
				std::int32_t vehicle_type = *(std::int32_t*)(model_info + 0x340);
				if (vehicle_type != 11 && vehicle_type != 12) {
					std::stringstream ss;
					ss << "Vehicle: " << (char*)(model_info + 0x298) << std::endl << "From: " << PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(owner)) << std::endl;
					map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Invalid Bike Handling", ss.str());
					return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
				}
			}
			else {
				std::stringstream ss;
				ss << "Vehicle: " << (char*)(model_info + 0x298) << std::endl << "From: " << PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(owner)) << std::endl;
				map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Invalid Bike Hash", ss.str());
				return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
			}
		}
		break;
	}
	case 2UI16: {
		std::uint32_t hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);  // boat
		std::uint64_t model_info = get_model_info_ptr(hash);
		if (model_info) {
			std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
			if (model_type == 5) {
				std::int32_t vehicle_type = *(std::int32_t*)(model_info + 0x340);
				if (vehicle_type != 13) {
					std::stringstream ss;
					ss << "Vehicle: " << (char*)(model_info + 0x298) << std::endl << "From: " << PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(owner)) << std::endl;
					map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Invalid Boat Handling", ss.str());
					return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
				}
			}
			else {
				std::stringstream ss;
				ss << "Vehicle: " << (char*)(model_info + 0x298) << std::endl << "From: " << PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(owner)) << std::endl;
				map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Invalid Boat Hash", ss.str());
				return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
			}
		}
		break;
	}
	case 4UI16: {
		std::uint32_t hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);  // heli
		std::uint64_t model_info = get_model_info_ptr(hash);
		if (model_info) {
			std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
			if (model_type == 5) {
				std::int32_t vehicle_type = *(std::int32_t*)(model_info + 0x340);
				if (vehicle_type != 8) {
					std::stringstream ss;
					ss << "Vehicle: " << (char*)(model_info + 0x298) << std::endl << "From: " << PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(owner)) << std::endl;
					map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Invalid Heli Handling", ss.str());
					return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
				}
			}
			else {
				std::stringstream ss;
				ss << "Vehicle: " << (char*)(model_info + 0x298) << std::endl << "From: " << PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(owner)) << std::endl;
				map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Invalid Heli Hash", ss.str());
				return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
			}
		}
		break;
	}
	case 9UI16: {
		std::uint32_t hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);  // plane
		std::uint64_t model_info = get_model_info_ptr(hash);
		if (model_info) {
			std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
			if (model_type == 5) {
				std::int32_t vehicle_type = *(std::int32_t*)(model_info + 0x340);
				if (vehicle_type != 1 && vehicle_type != 9) {
					std::stringstream ss;
					ss << "Vehicle: " << (char*)(model_info + 0x298) << std::endl << "From: " << PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(owner)) << std::endl;
					map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Invalid Plane Handling", ss.str());
					return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
				}
			}
			else {
				std::stringstream ss;
				ss << "Vehicle: " << (char*)(model_info + 0x298) << std::endl << "From: " << PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(owner)) << std::endl;
				map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Invalid Plane Hash", ss.str());
				return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
			}
		}
		break;
	}
	case 10UI16: {
		std::uint32_t hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);  // submarine
		std::uint64_t model_info = get_model_info_ptr(hash);
		if (model_info) {
			std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
			if (model_type == 5) {
				std::int32_t vehicle_type = *(std::int32_t*)(model_info + 0x340);
				if (vehicle_type != 15) {
					std::stringstream ss;
					ss << "Vehicle: " << (char*)(model_info + 0x298) << std::endl << "From: " << PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(owner)) << std::endl;
					map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Invalid Sub Handling", ss.str());
					return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
				}
			}
			else {
				std::stringstream ss;
				ss << "Vehicle: " << (char*)(model_info + 0x298) << std::endl << "From: " << PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(owner)) << std::endl;
				map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Invalid Sub Hash", ss.str());
				return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
			}
		}
		break;
	}
	case 12UI16: {
		std::uint32_t hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);  // trailer
		std::uint64_t model_info = get_model_info_ptr(hash);
		if (model_info) {
			std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
			if (model_type == 5) {
				std::int32_t vehicle_type = *(std::int32_t*)(model_info + 0x340);
				if (vehicle_type != 2) {
					std::stringstream ss;
					ss << "Vehicle: " << (char*)(model_info + 0x298) << std::endl << "From: " << PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(owner)) << std::endl;
					map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Invalid Trailer Handling", ss.str());
					return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
				}
			}
			else {
				std::stringstream ss;
				ss << "Vehicle: " << (char*)(model_info + 0x298) << std::endl << "From: " << PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(owner)) << std::endl;
				map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Invalid Trailer Hash", ss.str());
				return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
			}
		}
		break;
	}
	case 13UI16: {
		std::uint32_t hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);  // train
		std::uint64_t model_info = get_model_info_ptr(hash);
		if (model_info) {
			std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
			if (model_type == 5) {
				std::int32_t vehicle_type = *(std::int32_t*)(model_info + 0x340);
				if (vehicle_type != 14) {
					std::stringstream ss;
					ss << "Hash: " << std::hex << hash << std::endl << "From: " << PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(owner));
					map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Invalid Train", ss.str());
					return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
				}
			}
			else {
				std::stringstream ss;
				ss << "Vehicle: " << (char*)(model_info + 0x298) << std::endl << "From: " << PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(owner));
				map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Invalid Train Hash", ss.str());
				return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), game_patch_return_false_stub);
			}
		}
		break;
	}
	}
	return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), process_net_obj_t, sync_tree, net_obj);
}

bool translate_runtime_rvas() {
	TRANSLATE_RUNTIME_RVA(GTA_JMP_RBX); // 23 C3 C1 E0 0C (-1)
	TRANSLATE_RUNTIME_RVA(GTA_NATIVE_REGISTRATION); // 48 8D 0D ? ? ? ? 48 8B 14 FA
	TRANSLATE_RUNTIME_RVA(GTA_GET_NATIVE_HANDLER); // 48 8D 0D ? ? ? ? 48 8B 14 FA (First call)
	TRANSLATE_RUNTIME_RVA(GTA_RETURN_FALSE_SUB); // 32 C0 C3 (Any)
	TRANSLATE_RUNTIME_RVA(GTA_SET_VECTOR_RESULTS); // 83 79 18 00 48 8B D1 74 4A 
	TRANSLATE_RUNTIME_RVA(GTA_GET_SESSION_HOST_NET_GAME_PLAYER); // 40 53 48 83 EC 20 48 8B 49 20 48 8D 54 24 ? (Go back until you find call near ptr)
	TRANSLATE_RUNTIME_RVA(GTA_GET_NET_GAME_PLAYER_FROM_PHYSICAL_INDEX); // 80 F9 20 73 13 
	TRANSLATE_RUNTIME_RVA(GTA_GET_SCRIPT_INDEX_FROM_ENTITY); // 48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 8B 15 ? ? ? ? 48 8B F9 48 83 C1 10 33 DB
	TRANSLATE_RUNTIME_RVA(GTA_GET_ENTITY_FROM_SCRIPT_GUID); // 40 53 48 83 EC 20 48 63 DA E8 ? ? ? ? 48 85 C0 74 21 (First call you see)
	TRANSLATE_RUNTIME_RVA(GTA_GET_NET_OBJECT_BY_NET_ID); // 48 89 5C 24 ? 48 89 6C 24 ? 66 89 54 24 ? (Find jmp xref with 1 xref from caller)
	TRANSLATE_RUNTIME_RVA(GTA_GET_LOCAL_PLAYER_PED); // 48 8B 05 ? ? ? ? 48 8B 40 08 C3 
	TRANSLATE_RUNTIME_RVA(GTA_GET_SYNC_TREE_FROM_CLONE_TYPE); // 0F B7 CA 83 F9 07 
	TRANSLATE_RUNTIME_RVA(GTA_STREAMED_SCRIPTS); // 48 8D 0D ? ? ? ? E8 ? ? ? ? 83 38 FF 74 2D 
	TRANSLATE_RUNTIME_RVA(GTA_LOCAL_SCRIPT_HANDLERS); // 40 53 48 83 EC 20 80 79 30 00 0F 84 ? ? ? ? (Last loc -> loc then net)
	TRANSLATE_RUNTIME_RVA(GTA_NETWORKED_SCRIPT_HANDLERS); // // 40 53 48 83 EC 20 80 79 30 00 0F 84 ? ? ? ? (Last loc -> loc then net)
	TRANSLATE_RUNTIME_RVA(GTA_REMOVE_PLAYER_FROM_PLAYER_MGR); // 48 89 5C 24 ? 57 48 83 EC 20 48 8B DA 48 8B F9 E8 ? ? ? ? 84 C0 75 14 
	TRANSLATE_RUNTIME_RVA(GTA_REGISTER_GAME_FILE); // 48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 
	TRANSLATE_RUNTIME_RVA(GTA_CHANGE_NET_OBJ_OWNER); // 48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 54 41 56 41 57 48 81 EC ? ? ? ? 44 8A 62 4B 
	TRANSLATE_RUNTIME_RVA(GTA_GET_VEHICLE_PAINT_LIST_ARRAY); // 4C 8B 0D ? ? ? ? 45 33 C0 4D 85 C9
	TRANSLATE_RUNTIME_RVA(GTA_PACK_CLONE_REMOVE); // 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 30 41 80 78 ? ? 
	TRANSLATE_RUNTIME_RVA(GTA_PACK_CLONE_SYNC); // 48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 02 
	TRANSLATE_RUNTIME_RVA(GTA_MODEL_INFO_LIST_POOL); // 0F B7 05 ? ? ? ? 45 33 C9 4C 8B DA 66 85 C0 0F 84 ? ? ? ? 44 0F B7 C0 33 D2 8B C1 41 F7 F0 48 8B 05 ? ? ? ? 4C 8B 14 D0 EB 09 41 3B 0A 74 54 (Last add instr with addr)
	TRANSLATE_RUNTIME_RVA(GTA_WATER_TUNE_XML); // F3 0F 11 05 ? ? ? ? F3 0F 10 05 ? ? ? ? F3 0F 11 0D ? ? ? ? 0F 28 0D ? ? ? ? 
	TRANSLATE_RUNTIME_RVA(GTA_WATER_QUAD_XML); // 48 8D 0D ? ? ? ? 66 44 89 05 ? ? ? ? E8 ? ? ? ? 0F B7 05 ? ? ? ? 
	TRANSLATE_RUNTIME_RVA(GTA_WATER_QUAD_XML_COUNT); // 48 8D 0D ? ? ? ? 66 44 89 05 ? ? ? ? E8 ? ? ? ? 0F B7 05 ? ? ? ?  (+ 0x8)
	TRANSLATE_RUNTIME_RVA(GTA_HUD_COLOUR_POOL); // 41 8B 8C 84 ? ? ? ? 41 0F B6 C0 
	TRANSLATE_RUNTIME_RVA(GTA_PED_FACTORY); // 48 8B 05 ? ? ? ? 48 8B 40 08 C3 
	TRANSLATE_RUNTIME_RVA(GTA_ATTACHMENT_EXTENSION_INST_POOL); // 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 85 C0 74 0E 48 8B D6 48 8B C8 E8 ? ? ? ? 48 8B D8 48 89 5F 48 
	TRANSLATE_RUNTIME_RVA(GTA_GAME_GLOBALS); // 4C 8D 05 ? ? ? ? 4D 8B 08 4D 85 C9 74 11 
	TRANSLATE_RUNTIME_RVA(GTA_SUPER_GRIP_FLOAT); // F3 0F 59 15 ? ? ? ? F3 41 0F 58 D2 F3 0F 59 D0 
	TRANSLATE_RUNTIME_RVA(GTA_NETWORK_OBJECT_MGR_INTERFACE); // 48 8B 05 ? ? ? ? 44 0F B7 8C FB ? ? ? ? 4C 8D 05 ? ? ? ? 48 8B 88 ? ? ? ? 48 8D 15 ? ? ? ? 48 8B 01 FF 50 30 48 8B 05 ? ? ? ? 44 0F B7 8C FB ? ? ? ? 48 8B 88 ? ? ? ? (Any)
	TRANSLATE_RUNTIME_RVA(GTA_NETWORK_PLAYER_MGR_INTERFACE); // 48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? C3
	TRANSLATE_RUNTIME_RVA(GTA_FORCE_SCRIPT_HOST); // 48 89 5C 24 ? 57 48 83 EC 50 48 8B FA 48 8B D9 E8 ? ? ? ? 83 7B 10 08 
	TRANSLATE_RUNTIME_RVA(GTA_SMALL_HOST_TOKEN_PATCH); // C6 05 ? ? ? ? ? 48 8B CB E8 ? ? ? ? 84 C0 75 08 
	TRANSLATE_RUNTIME_RVA(GTA_NETWORK_OBJECT_MGR_TABLE);
	TRANSLATE_RUNTIME_RVA(GTA_NET_OBJ_PED_NODE_DATA_ACCESSOR_TABLE);
	TRANSLATE_RUNTIME_RVA(GTA_NET_OBJ_OBJECT_NODE_DATA_ACCESSOR_TABLE);
	TRANSLATE_RUNTIME_RVA(GTA_REMOVE_WEAPON_EVENT_TABLE);
	TRANSLATE_RUNTIME_RVA(GTA_REMOVE_ALL_WEAPONS_EVENT_TABLE);
	TRANSLATE_RUNTIME_RVA(GTA_GAME_WEATHER_EVENT_TABLE);
	TRANSLATE_RUNTIME_RVA(GTA_GAME_CLOCK_EVENT_TABLE);
	TRANSLATE_RUNTIME_RVA(GTA_SCRIPTED_GAME_EVENT_TABLE);
	TRANSLATE_RUNTIME_RVA(GTA_EXPLOSION_EVENT_TABLE);
	TRANSLATE_RUNTIME_RVA(GTA_FIRE_EVENT_TABLE);
	TRANSLATE_RUNTIME_RVA(GTA_INCREMENT_STAT_EVENT_TABLE);
	TRANSLATE_RUNTIME_RVA(GTA_PED_INST_POOL);
	TRANSLATE_RUNTIME_RVA(GTA_OBJ_INST_POOL);
	TRANSLATE_RUNTIME_RVA(GTA_VEH_LIST_POOL);
	TRANSLATE_RUNTIME_RVA(GTA_GET_CHAT_MSG_DATA);
	TRANSLATE_RUNTIME_RVA(GTA_WRITE_SYNC_DATA_STRING);
	TRANSLATE_RUNTIME_RVA(GTA_WRITE_SYNC_DATA_QWORD);
	TRANSLATE_RUNTIME_RVA(GTA_ASSIGN_PHYSICAL_INDEX);
	TRANSLATE_RUNTIME_RVA(GTA_WAYPOINT_PATH_DATA);
	TRANSLATE_RUNTIME_RVA(GTA_SEND_CLONE_SYNC_PATCH);
	TRANSLATE_RUNTIME_RVA(GTA_BUILDING_INST_POOL);
	TRANSLATE_RUNTIME_RVA(GTA_WRITE_SYNC_DATA_BOOL);
	TRANSLATE_RUNTIME_RVA(GTA_GET_MODEL_INFO);
	TRANSLATE_RUNTIME_RVA(GTA_PROCESS_NET_OBJ);
	TRANSLATE_RUNTIME_RVA(GTA_PACK_CLONE_CREATE);
	//TRANSLATE_RUNTIME_RVA(GTA_SEND_CLONE_SYNC);
	return true;
}

bool do_virtual_hooks() {
	/*if ((g_receive_clone_create_cache = hook_virtual(reinterpret_cast<std::add_pointer_t<std::uint64_t>>(GTA_NETWORK_OBJECT_MGR_TABLE), receive_clone_create_shim, 19)) == NULL) return false;
	if ((g_receive_clone_sync_cache = hook_virtual(reinterpret_cast<std::add_pointer_t<std::uint64_t>>(GTA_NETWORK_OBJECT_MGR_TABLE), receive_clone_sync_shim, 21)) == NULL) return false;
	if ((g_receive_clone_remove_cache = hook_virtual(reinterpret_cast<std::add_pointer_t<std::uint64_t>>(GTA_NETWORK_OBJECT_MGR_TABLE), receive_clone_remove_shim, 14)) == NULL) return false;
	if ((g_remove_weapon_event_read_sync_data_cache = hook_virtual(reinterpret_cast<std::add_pointer_t<std::uint64_t>>(GTA_REMOVE_WEAPON_EVENT_TABLE), remove_weapon_event_read_sync_data_shim, 6)) == NULL) return false;
	if ((g_remove_all_weapons_event_read_sync_data_cache = hook_virtual(reinterpret_cast<std::add_pointer_t<std::uint64_t>>(GTA_REMOVE_ALL_WEAPONS_EVENT_TABLE), remove_all_weapons_event_read_sync_data_shim, 6)) == NULL) return false;
	if ((g_game_weather_event_read_sync_data_cache = hook_virtual(reinterpret_cast<std::add_pointer_t<std::uint64_t>>(GTA_GAME_WEATHER_EVENT_TABLE), game_weather_event_read_sync_data_shim, 6)) == NULL) return false;
	if ((g_game_clock_event_read_sync_data_cache = hook_virtual(reinterpret_cast<std::add_pointer_t<std::uint64_t>>(GTA_GAME_CLOCK_EVENT_TABLE), game_clock_event_read_sync_data_shim, 6)) == NULL) return false;
	if ((g_scripted_game_event_callback_cache = hook_virtual(reinterpret_cast<std::add_pointer_t<std::uint64_t>>(GTA_SCRIPTED_GAME_EVENT_TABLE), scripted_game_event_callback_shim, 7)) == NULL) return false;
	if ((g_explosion_event_callback_cache = hook_virtual(reinterpret_cast<std::add_pointer_t<std::uint64_t>>(GTA_EXPLOSION_EVENT_TABLE), explosion_event_callback_shim, 7)) == NULL) return false;
	if ((g_fire_event_callback_cache = hook_virtual(reinterpret_cast<std::add_pointer_t<std::uint64_t>>(GTA_FIRE_EVENT_TABLE), fire_event_callback_shim, 7)) == NULL) return false;
	if ((g_increment_stat_event_callback_cache = hook_virtual(reinterpret_cast<std::add_pointer_t<std::uint64_t>>(GTA_INCREMENT_STAT_EVENT_TABLE), increment_stat_event_callback_shim, 7)) == NULL) return false;
	if ((g_spawn_net_obj_ped_cache = hook_virtual(reinterpret_cast<std::add_pointer_t<std::uint64_t>>(GTA_NET_OBJ_PED_NODE_DATA_ACCESSOR_TABLE), spawn_net_obj_ped_shim, 19)) == NULL) return false;
	if ((g_spawn_net_obj_object_cache = hook_virtual(reinterpret_cast<std::add_pointer_t<std::uint64_t>>(GTA_NET_OBJ_OBJECT_NODE_DATA_ACCESSOR_TABLE), spawn_net_obj_object_shim, 6)) == NULL) return false;*/
	return true;
}

bool do_engine_hooks() {
	return TRUE;
}

namespace
{
	std::uint32_t g_HookFrameCount{};
}

bool Hooks::DoesCamExist(Cam cam)
{
	if (g_HookFrameCount != *ptr.m_FC)
	{
		g_HookFrameCount = *ptr.m_FC;
		g_ScriptManager.Tick();
	}

	return static_cast<decltype(&DoesCamExist)>(hook.m_OriginalDoesCamExist)(cam);
}

LRESULT Hooks::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ptr.g_wndproc(hWnd, msg, wParam, lParam);
	return static_cast<decltype(&WndProc)>(hook.m_OriginalWndProc)(hWnd, msg, wParam, lParam);
}
HRESULT Hooks::swapchain_present(IDXGISwapChain* this_, UINT sync_interval, UINT flags)
{
	vmt_hook* m_swapchain_hook = new vmt_hook(ptr.m_SC, 18);
	if (g_running)
	{
		ptr.g_onloop();
	}
	return m_swapchain_hook->get_original<decltype(&swapchain_present)>(swapchain_present_index)(this_, sync_interval, flags);
	return NULL;
}

HRESULT Hooks::swapchain_resizebuffers(IDXGISwapChain* this_, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swapchain_flags)
{
	vmt_hook* m_swapchain_hook = new vmt_hook(ptr.m_SC, 18);
	if (g_running)
	{
		ptr.pre_reset();			
		auto result = m_swapchain_hook->get_original<decltype(&swapchain_resizebuffers)>(swapchain_resizebuffers_index)(this_, buffer_count, width, height, new_format, swapchain_flags);
		if (SUCCEEDED(result))
		{
			ptr.post_reset();
		}
		return result;
	}
	return m_swapchain_hook->get_original<decltype(&swapchain_resizebuffers)>(swapchain_resizebuffers_index)(this_, buffer_count, width, height, new_format, swapchain_flags);
	return NULL;
}

using namespace std::chrono_literals;

bool HookNatives() {
	vmt_hook* m_swapchain_hook = new vmt_hook(ptr.m_SC, 18);
	MH_Initialize();
	printf("MHI: true\n");
	MH_CreateHook(ptr.m_DCE, &Hooks::DoesCamExist, &hook.m_OriginalDoesCamExist);
	MH_CreateHook(ptr.m_WP, &Hooks::WndProc, &hook.m_OriginalWndProc);
	printf("MHCDCE 1: true\n");
	MH_EnableHook(ptr.m_DCE);
	printf("MHCDCE 2: true\n");
	MH_EnableHook(ptr.m_WP);
	m_swapchain_hook->hook(Hooks::swapchain_present_index, &Hooks::swapchain_present);
	m_swapchain_hook->hook(Hooks::swapchain_resizebuffers_index, &Hooks::swapchain_resizebuffers);
	printf("D3D Engine: true\n");
	//MH_CreateHook(reinterpret_cast<void*>(GTA_ASSIGN_PHYSICAL_INDEX), &assign_physical_index_hook, reinterpret_cast<void**>(&assign_physical_index_t));
	//MH_CreateHook(reinterpret_cast<void*>(GTA_GET_CHAT_MSG_DATA), &get_chat_msg_data_hook, reinterpret_cast<void**>(&get_chat_msg_data_t));
	//MH_CreateHook(reinterpret_cast<void*>(GTA_WRITE_SYNC_DATA_STRING), &write_sync_data_string_hook, reinterpret_cast<void**>(&write_sync_data_string_t));
	//MH_CreateHook(reinterpret_cast<void*>(GTA_PROCESS_NET_OBJ), &process_net_obj_hook, reinterpret_cast<void**>(&process_net_obj_t));
	//MH_CreateHook(reinterpret_cast<void*>(GTA_PACK_CLONE_CREATE), &pack_clone_create_hook, reinterpret_cast<void**>(&pack_clone_create_t));
	//MH_CreateHook(reinterpret_cast<void*>(GTA_SEND_CLONE_SYNC), &send_clone_sync_hook, reinterpret_cast<void**>(&send_clone_sync_t));
	//MH_EnableHook(reinterpret_cast<void*>(GTA_ASSIGN_PHYSICAL_INDEX));
	//MH_EnableHook(reinterpret_cast<void*>(GTA_GET_CHAT_MSG_DATA));
	//MH_EnableHook(reinterpret_cast<void*>(GTA_WRITE_SYNC_DATA_STRING));
	//MH_EnableHook(reinterpret_cast<void*>(GTA_PROCESS_NET_OBJ));
	//MH_EnableHook(reinterpret_cast<void*>(GTA_PACK_CLONE_CREATE));
	//MH_EnableHook(reinterpret_cast<void*>(GTA_SEND_CLONE_SYNC));
	return true;
}

void FindPatterns()
{
	PatternB MainBatch;

	MainBatch.Add("DCE", "40 53 48 83 EC 20 33 DB 85 C9 78 10", [](PManage Pointer) {
		ptr.m_DCE = Pointer.As<decltype(ptr.m_DCE)>();
	});
	printfnl("Found DCE");

	MainBatch.Add("FC", "F3 0F 10 0D ? ? ? ? 44 89 6B 08", [](PManage Pointer) {
		ptr.m_FC = Pointer.Add(4).Rip(4).Add(-8).As<std::uint64_t*>();
	});
	printfnl("Found FC");

	MainBatch.Add("GB", "48 83 EC 60 48 8D 0D ? ? ? ? E8", [](PManage Pointer) {
		ptr.m_GB = Pointer.Sub(17).Add(265 + 3).Rip().As<char*>();
	});
	printfnl("Found GB");

	MainBatch.Add("GS", "48 85 C9 74 4B 83 3D", [](PManage Pointer) {
		ptr.m_GS = Pointer.Add(7).Rip().As<eGameState*>();
	});
	printfnl("Found GS");

	MainBatch.Add("NRTGNH", "48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A", [](PManage Pointer) {
		ptr.m_NRT = Pointer.Add(3).Rip(4).As<rage::scrNativeRegistrationTable*>();
		ptr.m_GNH = Pointer.Add(12).Rip(4).As<decltype(ptr.m_GNH)>();
	});
	printfnl("Found NRTGNH");

	MainBatch.Add("FV", "83 79 18 00 48 8B D1 74 4A FF 4A 18 48 63 4A 18 48 8D 41 04 48 8B 4C CA", [](PManage Pointer) {
		ptr.m_FV = Pointer.As<decltype(ptr.m_FV)>();
	});
	printfnl("Found FV"); //Crashes when called, most likely due to spoof call (fixed)

	MainBatch.Add("FR", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 48 8B EA 4C 8B FA 48 8B D9 4D 85 C9", [](PManage Pointer) {
		ptr.m_FR = Pointer.Add(5).As<decltype(ptr.m_FR)>();
	});
	printfnl("Found FR");

	MainBatch.Add("WP", "48 8B 0D ? ? ? ? 48 8D 55 EF FF 15", [](PManage Pointer) {
		ptr.m_WP = Pointer.Sub(853).As<decltype(ptr.m_WP)>();
	});
	printfnl("Found WP");

	MainBatch.Add("GNP", "48 83 EC 28 33 C0 38 05 ? ? ? ? 74 0A", [](PManage Pointer) {
		ptr.m_GNP = Pointer.As<decltype(ptr.m_GNP)>();
	});
	printfnl("Found GNP");

	MainBatch.Add("GPN", "85 D2 7E 0E 48 8B C8", [](PManage Pointer) {
		ptr.m_GPN = Pointer.Add(28).As<decltype(ptr.m_GPN)>();
	});
	printfnl("Found GPN");

	//MainBatch.Add("SC", "48 8B 0D ? ? ? ? 48 8D 55 A0 48 8B 01", [](PManage Pointer) {
	//	ptr.m_SC = Pointer.Add(3).Rip().As<decltype(ptr.m_SC)>();
	//});
	//printfnl("Found SC");

	MainBatch.Add("SC", "48 8B 0D ? ? ? ? 48 8B 01 44 8D 43 01 33 D2 FF 50 40 8B C8", [](PManage Pointer) {
		ptr.m_SC = Pointer.Add(3).Rip().As<decltype(ptr.m_SC)>();
	});
	printfnl("Found SC");

	ptr.m_GW = FindWindowW(L"grcWindow", nullptr);
	printfnl("Found GW");
	MainBatch.Run(GetModuleHandleW(nullptr));
}

void RemovePatterns()
{
	vmt_hook* m_swapchain_hook = new vmt_hook(ptr.m_SC, 18);
	MH_Uninitialize();
	printf("MHUI: true\n");
	MH_DisableHook(ptr.m_DCE);
	printf("MHDDCE 1: true\n");
	MH_DisableHook(ptr.m_WP);
	printf("MHDWP 1: true\n");
	m_swapchain_hook->disable();
	printf("D3D Engine: true\n");
	//MH_DisableHook(reinterpret_cast<void*>(GTA_ASSIGN_PHYSICAL_INDEX));
	//MH_DisableHook(reinterpret_cast<void*>(GTA_GET_CHAT_MSG_DATA));
	//MH_DisableHook(reinterpret_cast<void*>(GTA_WRITE_SYNC_DATA_STRING));
	//MH_DisableHook(reinterpret_cast<void*>(GTA_PROCESS_NET_OBJ));
	//MH_DisableHook(reinterpret_cast<void*>(GTA_PACK_CLONE_CREATE));z
	//MH_DisableHook(reinterpret_cast<void*>(GTA_SEND_CLONE_SYNC));
	//printf("MHEHAPHI 1: true\n");
	//printf("MHEHAPHI 2: true\n");
}

BOOL APIENTRY DllMain(HMODULE hmod, DWORD reason, LPVOID reserved) {
	if (reason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hmod);

		g_hmodule = hmod;
		if (AllocConsole())
			freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
		SetConsoleTextAttribute(GetStdHandle(static_cast<DWORD>(-11)), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		SetConsoleTitleW(L"quantum.menu v1");
		g_main_thread = CreateThread(nullptr, 0, [](PVOID) -> DWORD
			{
				translate_runtime_rvas();
				printfnl("TRR: true");
				*(bool*)(GTA_SMALL_HOST_TOKEN_PATCH) = true;
				printfnl("SHTP: true");
				do_virtual_hooks();
				printfnl("VH: true");
				FindPatterns();
				if (*ptr.m_GS != eGameState::Playing)
				{
					printfnl("GL: false");
					do
					{
						std::this_thread::sleep_for(100ms);
					} while (*ptr.m_GS != eGameState::Playing);
					printfnl("GL: true");
				}
				else
				{
					printfnl("GL: true");
				}
				HookNatives();
				printfnl("HN: true");
				g_ScriptManager.AddScript(std::make_unique<Script>(&NFunc));
				vmt_hook* m_swapchain_hook = new vmt_hook(ptr.m_SC, 18);
				//m_swapchain_hook->enable(); //Causes chrash (shows up as dxgi.pdb unloadable)
				std::string GameBuildString =ptr.m_GB;
				std::string GameVerString = "Quantum Injected. | Injected into Game Version: " + GameBuildString;
				printfnl(GameVerString.c_str());
				while (g_running)
				{
					if (GetAsyncKeyState(VK_END)) g_running = false;
					std::this_thread::sleep_for(10ms);
				}
				RemovePatterns();
				std::this_thread::sleep_for(1000ms);
				g_ScriptManager.RemoveAllScripts();
				printfnl("Goodbye!");
				fclose(stdout);
				FreeConsole();
				CloseHandle(g_main_thread);
				FreeLibraryAndExitThread(g_hmodule, 0);
			}, nullptr, 0, nullptr);
	}
	return TRUE;
}