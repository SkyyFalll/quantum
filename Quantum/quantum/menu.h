#pragma once
#include <algorithm>
#include "functions.h"
#include "rage/Script.hpp"

void menu_protection() {
	add_toggle_option(&g_notify_attacks, OBFUSCATE("Notify Attacks"));
	add_break_option(OBFUSCATE("Toggleables"));
	add_toggle_option(&g_object_protection, OBFUSCATE("Object Attachment"));
	add_toggle_option(&g_protection_redirect_bullets, OBFUSCATE("Redirect Bullets"));
	//add_toggle_option(&g_spam_protection, OBFUSCATE("Spam Protection"));
	add_toggle_option(&g_protection_remove_weapon, OBFUSCATE("Remove Single Weapon"));
	add_toggle_option(&g_protection_remove_all_weapons, OBFUSCATE("Remove All Weapons"));
	add_toggle_option(&g_protection_weather_change, OBFUSCATE("Weather"));
	add_toggle_option(&g_protection_explosion, OBFUSCATE("Explosion"));
	add_toggle_option(&g_protection_fire, OBFUSCATE("Fire"));
	add_toggle_option(&g_protection_stat_increment, OBFUSCATE("Stats/Reports"));
	if (add_toggle_option(&g_fake_position, OBFUSCATE("Fake Position")))
		g_fake_position ? *(std::uint8_t*)(GTA_SEND_CLONE_SYNC_PATCH) = 0xC3 : *(std::uint8_t*)(GTA_SEND_CLONE_SYNC_PATCH) = 0x48;
}

void menu_self_outfit_editor_manage_component() {
	if (add_editor_option(true, g_self_outfit_current_drawable_id[g_self_outfit_selected_component_id], &g_self_outfit_current_drawable_id[g_self_outfit_selected_component_id], 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), g_self_outfit_selected_component_id), 1, OBFUSCATE("Drawable ID"))) {
		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), g_self_outfit_selected_component_id, g_self_outfit_current_drawable_id[g_self_outfit_selected_component_id], g_self_outfit_current_texture_id[g_self_outfit_selected_component_id], g_self_outfit_current_pallette_id[g_self_outfit_selected_component_id]);
	}
	if (add_editor_option(true, g_self_outfit_current_texture_id[g_self_outfit_selected_component_id], &g_self_outfit_current_texture_id[g_self_outfit_selected_component_id], 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), g_self_outfit_selected_component_id, g_self_outfit_current_drawable_id[g_self_outfit_selected_component_id]), 1, OBFUSCATE("Texture ID"))) {
		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), g_self_outfit_selected_component_id, g_self_outfit_current_drawable_id[g_self_outfit_selected_component_id], g_self_outfit_current_texture_id[g_self_outfit_selected_component_id], g_self_outfit_current_pallette_id[g_self_outfit_selected_component_id]);
	}
	if (add_editor_option(true, g_self_outfit_current_pallette_id[g_self_outfit_selected_component_id], &g_self_outfit_current_pallette_id[g_self_outfit_selected_component_id], 0, 3, 1, OBFUSCATE("Palette ID"))) {
		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), g_self_outfit_selected_component_id, g_self_outfit_current_drawable_id[g_self_outfit_selected_component_id], g_self_outfit_current_texture_id[g_self_outfit_selected_component_id], g_self_outfit_current_pallette_id[g_self_outfit_selected_component_id]);
	}

	if (g_self_outfit_model_cam_active) {
		if (!CAM::DOES_CAM_EXIST(g_self_model_cam)) {
			g_self_model_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
			if (CAM::DOES_CAM_EXIST(g_self_model_cam)) {
				CAM::SET_CAM_ACTIVE(g_self_model_cam, true);
				CAM::RENDER_SCRIPT_CAMS(1, 1, g_self_model_cam, 1, 0);
			}
		}
		else {
			switch (g_self_outfit_selected_component_id) {
			case 0:
			case 1:
			case 2: {
				Vector3 bone_coords = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[g_self_outfit_selected_component_id], 0.0f, 1.0f, 0.0f);
				CAM::SET_CAM_COORD(g_self_model_cam, bone_coords.x, bone_coords.y, bone_coords.z);
				CAM::POINT_CAM_AT_PED_BONE(g_self_model_cam, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[g_self_outfit_selected_component_id]), 0.0f, 0.0f, 0.5f, 1);
				//head
			} break;
			case 3: {
				Vector3 bone_coords = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[g_self_outfit_selected_component_id], 0.0f, 1.0f, 0.0f);
				CAM::SET_CAM_COORD(g_self_model_cam, bone_coords.x, bone_coords.y, bone_coords.z);
				CAM::POINT_CAM_AT_PED_BONE(g_self_model_cam, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[g_self_outfit_selected_component_id]), 0.0f, 0.0f, 0.0f, 1);
				//torso 
			} break;
			case 4: {
				Vector3 bone_coords = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[g_self_outfit_selected_component_id], 0.0f, 1.0f, 0.0f);
				CAM::SET_CAM_COORD(g_self_model_cam, bone_coords.x, bone_coords.y, bone_coords.z);
				CAM::POINT_CAM_AT_PED_BONE(g_self_model_cam, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[g_self_outfit_selected_component_id]), 0.0f, 0.0f, -0.5f, 1);
				//leg
			} break;
			case 5: {
				Vector3 bone_coords = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[g_self_outfit_selected_component_id], 0.0f, -1.0f, 0.5f);
				CAM::SET_CAM_COORD(g_self_model_cam, bone_coords.x, bone_coords.y, bone_coords.z);
				CAM::POINT_CAM_AT_PED_BONE(g_self_model_cam, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[g_self_outfit_selected_component_id]), 0.0f, 0.0f, 0.0f, 1);
				//back 
			} break;
			case 6: {
				Vector3 bone_coords = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[g_self_outfit_selected_component_id], 0.5f, 1.0f, 0.0f);
				CAM::SET_CAM_COORD(g_self_model_cam, bone_coords.x, bone_coords.y, bone_coords.z);
				CAM::POINT_CAM_AT_PED_BONE(g_self_model_cam, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[g_self_outfit_selected_component_id]), 0.0f, 0.0f, -0.75f, 1);
				//shoes
			} break;
			case 7:
			case 8:
			case 9:
			case 10: {
				Vector3 bone_coords = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[g_self_outfit_selected_component_id], 0.0f, 1.0f, 0.5f);
				CAM::SET_CAM_COORD(g_self_model_cam, bone_coords.x, bone_coords.y, bone_coords.z);
				CAM::POINT_CAM_AT_PED_BONE(g_self_model_cam, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[g_self_outfit_selected_component_id]), 0.0f, 0.0f, 0.0f, 1);
				//chest
			} break;
			case 11: {
				Vector3 bone_coords = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[g_self_outfit_selected_component_id], 0.0f, 1.0f, 0.0f);
				CAM::SET_CAM_COORD(g_self_model_cam, bone_coords.x, bone_coords.y, bone_coords.z);
				CAM::POINT_CAM_AT_PED_BONE(g_self_model_cam, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[g_self_outfit_selected_component_id]), 0.0f, 0.0f, 0.0f, 1);
				//torso
			} break;
			}
		}
	}
}
void menu_self_outfit_editor() {
	add_toggle_option(&g_self_outfit_model_cam_active, OBFUSCATE("Outfit Cam"));
	if (add_text_option(OBFUSCATE("Reset Appearance"))) {
		STREAMING::REQUEST_MODEL(ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()));
		if (STREAMING::HAS_MODEL_LOADED(ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()))) {
			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()));
			for (INT i = 0; i < 13; i++) {
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), i, 0, 0, 2);
			}
			PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 0, 0, 0, 1);
			PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 1, 0, 0, 1);
			PED::CLEAR_PED_DECORATIONS(PLAYER::PLAYER_PED_ID());
			PED::CLEAR_ALL_PED_PROPS(PLAYER::PLAYER_PED_ID());
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()));
		}
	}
	if (add_submenu_option(menu_self_outfit_editor_manage_component, OBFUSCATE("Face"))) {
		g_self_outfit_selected_component_id = 0;
	}
	if (add_submenu_option(menu_self_outfit_editor_manage_component, OBFUSCATE("Mask"))) {
		g_self_outfit_selected_component_id = 1;
	}
	if (add_submenu_option(menu_self_outfit_editor_manage_component, OBFUSCATE("Hair"))) {
		g_self_outfit_selected_component_id = 2;
	}
	if (add_submenu_option(menu_self_outfit_editor_manage_component, OBFUSCATE("Torso 1"))) {
		g_self_outfit_selected_component_id = 3;
	}
	if (add_submenu_option(menu_self_outfit_editor_manage_component, OBFUSCATE("Leg"))) {
		g_self_outfit_selected_component_id = 4;
	}
	if (add_submenu_option(menu_self_outfit_editor_manage_component, OBFUSCATE("Parachute/Bag"))) {
		g_self_outfit_selected_component_id = 5;
	}
	if (add_submenu_option(menu_self_outfit_editor_manage_component, OBFUSCATE("Shoes"))) {
		g_self_outfit_selected_component_id = 6;
	}
	if (add_submenu_option(menu_self_outfit_editor_manage_component, OBFUSCATE("Accessory"))) {
		g_self_outfit_selected_component_id = 7;
	}
	if (add_submenu_option(menu_self_outfit_editor_manage_component, OBFUSCATE("Undershirt"))) {
		g_self_outfit_selected_component_id = 8;
	}
	if (add_submenu_option(menu_self_outfit_editor_manage_component, OBFUSCATE("Kevlar"))) {
		g_self_outfit_selected_component_id = 9;
	}
	if (add_submenu_option(menu_self_outfit_editor_manage_component, OBFUSCATE("Badge"))) {
		g_self_outfit_selected_component_id = 10;
	}
	if (add_submenu_option(menu_self_outfit_editor_manage_component, OBFUSCATE("Torso 2"))) {
		g_self_outfit_selected_component_id = 11;
	}

	if (g_self_outfit_model_cam_active) {
		if (!CAM::DOES_CAM_EXIST(g_self_model_cam) && CURRENT_OPTION > 2) {
			g_self_model_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
			if (CAM::DOES_CAM_EXIST(g_self_model_cam)) {
				Vector3 bone_coords = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), 0, 0.0f, 1.0f, 0.0f);
				CAM::SET_CAM_COORD(g_self_model_cam, bone_coords.x, bone_coords.y, bone_coords.z);
				CAM::POINT_CAM_AT_PED_BONE(g_self_model_cam, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), 0), 0.0f, 0.0f, 0.0f, 1);
				CAM::SET_CAM_ACTIVE(g_self_model_cam, true);
				CAM::RENDER_SCRIPT_CAMS(1, 1, 3000, 1, 0);
			}
		}
		else if (!CAM::DOES_CAM_EXIST(g_self_model_temp_cam))
			g_self_model_temp_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
		else {
			static bool g_self_model_cam_interloping_finished[7]{ false };
			switch (CURRENT_OPTION) {
			case 1:
			case 2: {
					if (CAM::DOES_CAM_EXIST(g_self_model_cam)) {
						CAM::SET_CAM_ACTIVE(g_self_model_cam, false);
						CAM::RENDER_SCRIPT_CAMS(0, 1, 3000, 1, 0);
						CAM::DESTROY_CAM(g_self_model_cam, true);
					}
					if (CAM::DOES_CAM_EXIST(g_self_model_temp_cam)) {
						CAM::SET_CAM_ACTIVE(g_self_model_temp_cam, false);
						CAM::RENDER_SCRIPT_CAMS(0, 1, 3000, 1, 0);
						CAM::DESTROY_CAM(g_self_model_temp_cam, true);
					} //delete cam
				} break;
			case 3:
			case 4:
			case 5: {
					for (auto i = 0; i < std::size(g_self_model_cam_interloping_finished); i++)
						if (i != 0) g_self_model_cam_interloping_finished[i] = false;

					bool using_temp_cam = (CAM::GET_RENDERING_CAM() == g_self_model_temp_cam);
					Vector3 bone_coords = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[CURRENT_OPTION - 3], 0.0f, 1.0f, 0.0f);
					if (!g_self_model_cam_interloping_finished[0]) {
						CAM::SET_CAM_COORD(using_temp_cam ? g_self_model_cam : g_self_model_temp_cam, bone_coords.x, bone_coords.y, bone_coords.z);
						CAM::POINT_CAM_AT_PED_BONE(using_temp_cam ? g_self_model_cam : g_self_model_temp_cam, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[CURRENT_OPTION - 3]), 0.0f, 0.0f, 0.5f, 1);
						using_temp_cam ? CAM::SET_CAM_ACTIVE_WITH_INTERP(g_self_model_cam, g_self_model_temp_cam, 1500, 1, 1) : CAM::SET_CAM_ACTIVE_WITH_INTERP(g_self_model_temp_cam, g_self_model_cam, 1500, 1, 1);
						g_self_model_cam_interloping_finished[0] = true;
					}
					else {
						while (CAM::IS_CAM_INTERPOLATING(g_self_model_cam) || CAM::IS_CAM_INTERPOLATING(g_self_model_temp_cam))
							Script::GetCurrent()->ScriptYield();

						CAM::SET_CAM_COORD(using_temp_cam ? g_self_model_temp_cam : g_self_model_cam, bone_coords.x, bone_coords.y, bone_coords.z);
						CAM::POINT_CAM_AT_PED_BONE(using_temp_cam ? g_self_model_temp_cam : g_self_model_cam, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[CURRENT_OPTION - 3]), 0.0f, 0.0f, 0.5f, 1);
					}
					//head
				} break;
			case 6: {
					for (auto i = 0; i < std::size(g_self_model_cam_interloping_finished); i++)
						if (i != 1) g_self_model_cam_interloping_finished[i] = false;

					bool using_temp_cam = (CAM::GET_RENDERING_CAM() == g_self_model_temp_cam);
					Vector3 bone_coords = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[CURRENT_OPTION - 3], 0.0f, 1.0f, 0.0f);
					if (!g_self_model_cam_interloping_finished[1]) {
						CAM::SET_CAM_COORD(using_temp_cam ? g_self_model_cam : g_self_model_temp_cam, bone_coords.x, bone_coords.y, bone_coords.z);
						CAM::POINT_CAM_AT_PED_BONE(using_temp_cam ? g_self_model_cam : g_self_model_temp_cam, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[CURRENT_OPTION - 3]), 0.0f, 0.0f, 0.0f, 1);
						using_temp_cam ? CAM::SET_CAM_ACTIVE_WITH_INTERP(g_self_model_cam, g_self_model_temp_cam, 1500, 1, 1) : CAM::SET_CAM_ACTIVE_WITH_INTERP(g_self_model_temp_cam, g_self_model_cam, 1500, 1, 1);
						g_self_model_cam_interloping_finished[1] = true;
					}
					else {
						while (CAM::IS_CAM_INTERPOLATING(g_self_model_cam) || CAM::IS_CAM_INTERPOLATING(g_self_model_temp_cam))
							Script::GetCurrent()->ScriptYield();

						CAM::SET_CAM_COORD(using_temp_cam ? g_self_model_temp_cam : g_self_model_cam, bone_coords.x, bone_coords.y, bone_coords.z);
						CAM::POINT_CAM_AT_PED_BONE(using_temp_cam ? g_self_model_temp_cam : g_self_model_cam, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[CURRENT_OPTION - 3]), 0.0f, 0.0f, 0.0f, 1);
					}
					//torso 
				} break;
			case 7: {
					for (auto i = 0; i < std::size(g_self_model_cam_interloping_finished); i++)
						if (i != 2) g_self_model_cam_interloping_finished[i] = false;

					bool using_temp_cam = (CAM::GET_RENDERING_CAM() == g_self_model_temp_cam);
					Vector3 bone_coords = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[CURRENT_OPTION - 3], 0.0f, 1.0f, 0.0f);
					if (!g_self_model_cam_interloping_finished[2]) {
						CAM::SET_CAM_COORD(using_temp_cam ? g_self_model_cam : g_self_model_temp_cam, bone_coords.x, bone_coords.y, bone_coords.z);
						CAM::POINT_CAM_AT_PED_BONE(using_temp_cam ? g_self_model_cam : g_self_model_temp_cam, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[CURRENT_OPTION - 3]), 0.0f, 0.0f, -0.5f, 1);
						using_temp_cam ? CAM::SET_CAM_ACTIVE_WITH_INTERP(g_self_model_cam, g_self_model_temp_cam, 1500, 1, 1) : CAM::SET_CAM_ACTIVE_WITH_INTERP(g_self_model_temp_cam, g_self_model_cam, 1500, 1, 1);
						g_self_model_cam_interloping_finished[2] = true;
					}
					else {
						while (CAM::IS_CAM_INTERPOLATING(g_self_model_cam) || CAM::IS_CAM_INTERPOLATING(g_self_model_temp_cam))
							Script::GetCurrent()->ScriptYield();

						CAM::SET_CAM_COORD(using_temp_cam ? g_self_model_temp_cam : g_self_model_cam, bone_coords.x, bone_coords.y, bone_coords.z);
						CAM::POINT_CAM_AT_PED_BONE(using_temp_cam ? g_self_model_temp_cam : g_self_model_cam, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[CURRENT_OPTION - 3]), 0.0f, 0.0f, -0.5f, 1);
					}
					//leg
				} break;
			case 8: {
					for (auto i = 0; i < std::size(g_self_model_cam_interloping_finished); i++)
						if (i != 3) g_self_model_cam_interloping_finished[i] = false;

					bool using_temp_cam = (CAM::GET_RENDERING_CAM() == g_self_model_temp_cam);
					Vector3 bone_coords = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[CURRENT_OPTION - 3], 0.0f, -1.0f, 0.5f);
					if (!g_self_model_cam_interloping_finished[3]) {
						CAM::SET_CAM_COORD(using_temp_cam ? g_self_model_cam : g_self_model_temp_cam, bone_coords.x, bone_coords.y, bone_coords.z);
						CAM::POINT_CAM_AT_PED_BONE(using_temp_cam ? g_self_model_cam : g_self_model_temp_cam, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[CURRENT_OPTION - 3]), 0.0f, 0.0f, 0.0f, 1);
						using_temp_cam ? CAM::SET_CAM_ACTIVE_WITH_INTERP(g_self_model_cam, g_self_model_temp_cam, 1500, 1, 1) : CAM::SET_CAM_ACTIVE_WITH_INTERP(g_self_model_temp_cam, g_self_model_cam, 1500, 1, 1);
						g_self_model_cam_interloping_finished[3] = true;
					}
					else {
						while (CAM::IS_CAM_INTERPOLATING(g_self_model_cam) || CAM::IS_CAM_INTERPOLATING(g_self_model_temp_cam))
							Script::GetCurrent()->ScriptYield();

						CAM::SET_CAM_COORD(using_temp_cam ? g_self_model_temp_cam : g_self_model_cam, bone_coords.x, bone_coords.y, bone_coords.z);
						CAM::POINT_CAM_AT_PED_BONE(using_temp_cam ? g_self_model_temp_cam : g_self_model_cam, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[CURRENT_OPTION - 3]), 0.0f, 0.0f, 0.0f, 1);
					}
					//back 
				} break;
			case 9: {
					for (auto i = 0; i < std::size(g_self_model_cam_interloping_finished); i++)
						if (i != 4) g_self_model_cam_interloping_finished[i] = false;

					bool using_temp_cam = (CAM::GET_RENDERING_CAM() == g_self_model_temp_cam);
					Vector3 bone_coords = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[CURRENT_OPTION - 3], 0.5f, 1.0f, 0.0f);
					if (!g_self_model_cam_interloping_finished[4]) {
						CAM::SET_CAM_COORD(using_temp_cam ? g_self_model_cam : g_self_model_temp_cam, bone_coords.x, bone_coords.y, bone_coords.z);
						CAM::POINT_CAM_AT_PED_BONE(using_temp_cam ? g_self_model_cam : g_self_model_temp_cam, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[CURRENT_OPTION - 3]), 0.0f, 0.0f, -0.75f, 1);
						using_temp_cam ? CAM::SET_CAM_ACTIVE_WITH_INTERP(g_self_model_cam, g_self_model_temp_cam, 1500, 1, 1) : CAM::SET_CAM_ACTIVE_WITH_INTERP(g_self_model_temp_cam, g_self_model_cam, 1500, 1, 1);
						g_self_model_cam_interloping_finished[4] = true;
					}
					else {
						while (CAM::IS_CAM_INTERPOLATING(g_self_model_cam) || CAM::IS_CAM_INTERPOLATING(g_self_model_temp_cam))
							Script::GetCurrent()->ScriptYield();

						CAM::SET_CAM_COORD(using_temp_cam ? g_self_model_temp_cam : g_self_model_cam, bone_coords.x, bone_coords.y, bone_coords.z);
						CAM::POINT_CAM_AT_PED_BONE(using_temp_cam ? g_self_model_temp_cam : g_self_model_cam, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[CURRENT_OPTION - 3]), 0.0f, 0.0f, -0.75f, 1);
					}
					//shoes
				} break;
			case 10:
			case 11:
			case 12:
			case 13: {
					for (auto i = 0; i < std::size(g_self_model_cam_interloping_finished); i++)
						if (i != 5) g_self_model_cam_interloping_finished[i] = false;

					bool using_temp_cam = (CAM::GET_RENDERING_CAM() == g_self_model_temp_cam);
					Vector3 bone_coords = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[CURRENT_OPTION - 3], 0.0f, 1.0f, 0.5f);
					if (!g_self_model_cam_interloping_finished[5]) {
						CAM::SET_CAM_COORD(using_temp_cam ? g_self_model_cam : g_self_model_temp_cam, bone_coords.x, bone_coords.y, bone_coords.z);
						CAM::POINT_CAM_AT_PED_BONE(using_temp_cam ? g_self_model_cam : g_self_model_temp_cam, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[CURRENT_OPTION - 3]), 0.0f, 0.0f, 0.0f, 1);
						using_temp_cam ? CAM::SET_CAM_ACTIVE_WITH_INTERP(g_self_model_cam, g_self_model_temp_cam, 1500, 1, 1) : CAM::SET_CAM_ACTIVE_WITH_INTERP(g_self_model_temp_cam, g_self_model_cam, 1500, 1, 1);
						g_self_model_cam_interloping_finished[5] = true;
					}
					else {
						while (CAM::IS_CAM_INTERPOLATING(g_self_model_cam) || CAM::IS_CAM_INTERPOLATING(g_self_model_temp_cam))
							Script::GetCurrent()->ScriptYield();

						CAM::SET_CAM_COORD(using_temp_cam ? g_self_model_temp_cam : g_self_model_cam, bone_coords.x, bone_coords.y, bone_coords.z);
						CAM::POINT_CAM_AT_PED_BONE(using_temp_cam ? g_self_model_temp_cam : g_self_model_cam, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[CURRENT_OPTION - 3]), 0.0f, 0.0f, 0.0f, 1);
					}
					//chest
				} break;
			case 14: {
					for (auto i = 0; i < std::size(g_self_model_cam_interloping_finished); i++)
						if (i != 6) g_self_model_cam_interloping_finished[i] = false;

					bool using_temp_cam = (CAM::GET_RENDERING_CAM() == g_self_model_temp_cam);
					Vector3 bone_coords = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[CURRENT_OPTION - 3], 0.0f, 1.0f, 0.0f);
					if (!g_self_model_cam_interloping_finished[6]) {
						CAM::SET_CAM_COORD(using_temp_cam ? g_self_model_cam : g_self_model_temp_cam, bone_coords.x, bone_coords.y, bone_coords.z);
						CAM::POINT_CAM_AT_PED_BONE(using_temp_cam ? g_self_model_cam : g_self_model_temp_cam, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[CURRENT_OPTION - 3]), 0.0f, 0.0f, 0.0f, 1);
						using_temp_cam ? CAM::SET_CAM_ACTIVE_WITH_INTERP(g_self_model_cam, g_self_model_temp_cam, 1500, 1, 1) : CAM::SET_CAM_ACTIVE_WITH_INTERP(g_self_model_temp_cam, g_self_model_cam, 1500, 1, 1);
						g_self_model_cam_interloping_finished[6] = true;
					}
					else {
						while (CAM::IS_CAM_INTERPOLATING(g_self_model_cam) || CAM::IS_CAM_INTERPOLATING(g_self_model_temp_cam))
							Script::GetCurrent()->ScriptYield();

						CAM::SET_CAM_COORD(using_temp_cam ? g_self_model_temp_cam : g_self_model_cam, bone_coords.x, bone_coords.y, bone_coords.z);
						CAM::POINT_CAM_AT_PED_BONE(using_temp_cam ? g_self_model_temp_cam : g_self_model_cam, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[CURRENT_OPTION - 3]), 0.0f, 0.0f, 0.0f, 1);
					}
					//torso
				} break;
			}
		}
	}
}
void menu_self_character_movement_type() {
	if (add_text_option(OBFUSCATE("Male"))) {
		PED::SET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), "move_m@generic", 1.0f);
		print_notification(7000, "~g~Success:~s~ Character Movement Male.");
	}
	if (add_text_option(OBFUSCATE("Female"))) {
		PED::SET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), "move_f@generic", 1.0f);
		print_notification(7000, "~g~Success:~s~ Character Movement Female.");
	}
}
void menu_self_handling() {
	add_submenu_option(menu_self_character_movement_type, OBFUSCATE("Character Movement Type"));
	add_toggle_option(&g_self_super_run, OBFUSCATE("Super Run"));
	if (g_self_super_run)
		add_editor_option(false, g_self_super_run_modifier, &g_self_super_run_modifier, 0.5f, 20.0f, 0.05f, OBFUSCATE("Multiplier"));
	add_toggle_option(&g_self_super_jump, OBFUSCATE("Super Jump"));
	if (add_toggle_option(&g_self_super_swim, OBFUSCATE("Super Swim")))
		if (!g_self_super_swim)
			PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), 1.0f);
	add_toggle_option(&g_self_superman, OBFUSCATE("Superman Mode"));
	if (add_toggle_option(&g_self_slow_motion, OBFUSCATE("Slow Motion")))
		if (!g_self_slow_motion)
			GAMEPLAY::SET_TIME_SCALE(1.0f);
	if (add_text_option(OBFUSCATE("Sky Diving"))) {
		Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, 0.0f, 2500.0f);
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PLAYER::PLAYER_PED_ID(), coords.x, coords.y, coords.z, FALSE, FALSE, TRUE);
		if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(PLAYER::PLAYER_PED_ID()) > 5.0f)
			AI::TASK_SKY_DIVE(PLAYER::PLAYER_PED_ID());
		print_notification(7000, "~g~Success:~s~ Player Task Sky Diving.");
	}
}
void menu_self_editor() {
	if (add_toggle_option(&g_self_shrink, OBFUSCATE("Shrink"))) {
		if (!g_self_shrink)
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 223, FALSE);
	}
	add_editor_toggle_option(&g_self_menu_ped_lean_active, g_self_menu_ped_lean, &g_self_menu_ped_lean, -2.0f, 2.0f, 0.1f, "Character Lean");
	add_editor_toggle_option(&g_self_menu_ped_width_active, g_self_menu_ped_width, &g_self_menu_ped_width, -2.0f, 2.0f, 0.1f, "Character Width");
	add_editor_toggle_option(&g_self_menu_ped_height_active, g_self_menu_ped_height, &g_self_menu_ped_height, -2.0f, 2.0f, 0.1f, "Character Height");
}
void menu_self_sport_anim() {
	for (std::int32_t i = 0; i < ARRAYSIZE(g_sport_anims); i++) {
		if (add_text_option(g_sport_anims[i].local_name)) {

			const char* dict = g_sport_anims[i].anim_dict.c_str();
			const char* name = g_sport_anims[i].anim_name.c_str();

			if (STREAMING::DOES_ANIM_DICT_EXIST(dict)) {
				STREAMING::REQUEST_ANIM_DICT(dict);
				while (!STREAMING::HAS_ANIM_DICT_LOADED(dict))
					Script::GetCurrent()->ScriptYield();
				AI::TASK_PLAY_ANIM(PLAYER::PLAYER_PED_ID(), dict, name, 8.0f, 0.0f, -1, 9, 0.0f, false, false, false);
				AI::SET_ANIM_RATE(PLAYER::PLAYER_PED_ID(), g_animation_speed, 0.0f, 0.0f);
			}

		}
	}
}
void menu_self_sex_anim() {
	for (std::int32_t i = 0; i < ARRAYSIZE(g_sex_anims); i++) {
		if (add_text_option(g_sex_anims[i].local_name)) {
			const char* dict = g_sex_anims[i].anim_dict.c_str();
			const char* name = g_sex_anims[i].anim_name.c_str();

			if (STREAMING::DOES_ANIM_DICT_EXIST(dict)) {
				STREAMING::REQUEST_ANIM_DICT(dict);
				while (!STREAMING::HAS_ANIM_DICT_LOADED(dict))
					Script::GetCurrent()->ScriptYield();
				AI::TASK_PLAY_ANIM(PLAYER::PLAYER_PED_ID(), dict, name, 8.0f, 0.0f, -1, 9, 0.0f, false, false, false);
				AI::SET_ANIM_RATE(0, g_animation_speed, 0.0f, 0.0f);
			}
		}
	}
}
void menu_self_dance_anim() {
	for (std::int32_t i = 0; i < ARRAYSIZE(g_dance_anims); i++) {
		if (add_text_option(g_dance_anims[i].local_name)) {
			const char* dict = g_dance_anims[i].anim_dict.c_str();
			const char* name = g_dance_anims[i].anim_name.c_str();

			if (STREAMING::DOES_ANIM_DICT_EXIST(dict)) {
				STREAMING::REQUEST_ANIM_DICT(dict);
				while (!STREAMING::HAS_ANIM_DICT_LOADED(dict))
					Script::GetCurrent()->ScriptYield();
				AI::TASK_PLAY_ANIM(PLAYER::PLAYER_PED_ID(), dict, name, 8.0f, 0.0f, -1, 9, 0.0f, false, false, false);
				AI::SET_ANIM_RATE(PLAYER::PLAYER_PED_ID(), g_animation_speed, 0.0f, 0.0f);
			}
		}
	}
}
void menu_self_superhero_anim() {
	for (std::int32_t i = 0; i < ARRAYSIZE(g_super_hero_anims); i++) {
		if (add_text_option(g_super_hero_anims[i].local_name)) {
			const char* dict = g_super_hero_anims[i].anim_dict.c_str();
			const char* name = g_super_hero_anims[i].anim_name.c_str();

			if (STREAMING::DOES_ANIM_DICT_EXIST(dict)) {
				STREAMING::REQUEST_ANIM_DICT(dict);
				while (!STREAMING::HAS_ANIM_DICT_LOADED(dict))
					Script::GetCurrent()->ScriptYield();
				AI::TASK_PLAY_ANIM(PLAYER::PLAYER_PED_ID(), dict, name, 8.0f, 0.0f, -1, 9, 0.0f, false, false, false);
				AI::SET_ANIM_RATE(PLAYER::PLAYER_PED_ID(), g_animation_speed, 0.0f, 0.0f);
			}
		}
	}
}
void menu_self_misc_anim() {
	for (std::int32_t i = 0; i < ARRAYSIZE(g_misc_anims); i++) {
		if (add_text_option(g_misc_anims[i].local_name)) {
			const char* dict = g_misc_anims[i].anim_dict.c_str();
			const char* name = g_misc_anims[i].anim_name.c_str();

			if (STREAMING::DOES_ANIM_DICT_EXIST(dict)) {
				STREAMING::REQUEST_ANIM_DICT(dict);
				while (!STREAMING::HAS_ANIM_DICT_LOADED(dict))
					Script::GetCurrent()->ScriptYield();
				AI::TASK_PLAY_ANIM(PLAYER::PLAYER_PED_ID(), dict, name, 8.0f, 0.0f, -1, 9, 0.0f, false, false, false);
				AI::SET_ANIM_RATE(PLAYER::PLAYER_PED_ID(), g_animation_speed, 0.0f, 0.0f);
			}
		}
	}
}
void menu_self_animation_editor() {
	if (add_editor_option(true, g_animation_speed, &g_animation_speed, 0.00f, 20.0f, 0.05f, OBFUSCATE("Playback Speed")))
		AI::SET_ANIM_RATE(PLAYER::PLAYER_PED_ID(), g_animation_speed, 0.0f, 0.0f);
	add_break_option(OBFUSCATE("Catagories"));
	add_submenu_option(menu_self_sport_anim, OBFUSCATE("Sport"));
	add_submenu_option(menu_self_sex_anim, OBFUSCATE("Sex"));
	add_submenu_option(menu_self_dance_anim, OBFUSCATE("Dance"));
	add_submenu_option(menu_self_superhero_anim, OBFUSCATE("Superhero"));
	add_submenu_option(menu_self_misc_anim, OBFUSCATE("Misc"));
	if (add_text_option(OBFUSCATE("Clear Current Animation"))) {
		AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
		print_notification(7000, "~g~Success:~s~ Cleared Player Current Animation.");
	}
}
void menu_self_scenario_editor() {
	if (add_text_option(OBFUSCATE("Clear Current Scenario"))) {
		AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
		print_notification(7000, "~g~Success:~s~ Cleared Player Current Scenario.");
	}
	add_break_option(OBFUSCATE("Scenarios"));
	for (std::int32_t i = 0; i < ARRAYSIZE(g_scenario_name); i++) {
		if (add_text_option(g_scenario_name[i])) {
			AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
			AI::CLEAR_PED_SECONDARY_TASK(PLAYER::PLAYER_PED_ID());
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), g_scenario_to_do[i].c_str(), 1, true);
		}
	}
}
void menu_self() {
	if (add_submenu_option(menu_self_outfit_editor, OBFUSCATE("Outfit Editor"))) {
		g_self_outfit_current_texture_id[0] = PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(), 0);
		g_self_outfit_current_texture_id[1] = PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(), 1);
		g_self_outfit_current_texture_id[2] = PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(), 2);
		g_self_outfit_current_texture_id[3] = PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(), 3);
		g_self_outfit_current_texture_id[4] = PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(), 4);
		g_self_outfit_current_texture_id[5] = PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(), 5);
		g_self_outfit_current_texture_id[6] = PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(), 6);
		g_self_outfit_current_texture_id[7] = PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(), 7);
		g_self_outfit_current_texture_id[8] = PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(), 8);
		g_self_outfit_current_texture_id[9] = PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(), 9);
		g_self_outfit_current_texture_id[10] = PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(), 10);
		g_self_outfit_current_texture_id[11] = PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(), 11);
		g_self_outfit_current_drawable_id[0] = PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(), 0);
		g_self_outfit_current_drawable_id[1] = PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(), 1);
		g_self_outfit_current_drawable_id[2] = PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(), 2);
		g_self_outfit_current_drawable_id[3] = PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(), 3);
		g_self_outfit_current_drawable_id[4] = PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(), 4);
		g_self_outfit_current_drawable_id[5] = PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(), 5);
		g_self_outfit_current_drawable_id[6] = PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(), 6);
		g_self_outfit_current_drawable_id[7] = PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(), 7);
		g_self_outfit_current_drawable_id[8] = PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(), 8);
		g_self_outfit_current_drawable_id[9] = PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(), 9);
		g_self_outfit_current_drawable_id[10] = PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(), 10);
		g_self_outfit_current_drawable_id[11] = PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(), 11);
		g_self_outfit_current_pallette_id[0] = PED::GET_PED_PALETTE_VARIATION(PLAYER::PLAYER_PED_ID(), 0);
		g_self_outfit_current_pallette_id[1] = PED::GET_PED_PALETTE_VARIATION(PLAYER::PLAYER_PED_ID(), 1);
		g_self_outfit_current_pallette_id[2] = PED::GET_PED_PALETTE_VARIATION(PLAYER::PLAYER_PED_ID(), 2);
		g_self_outfit_current_pallette_id[3] = PED::GET_PED_PALETTE_VARIATION(PLAYER::PLAYER_PED_ID(), 3);
		g_self_outfit_current_pallette_id[4] = PED::GET_PED_PALETTE_VARIATION(PLAYER::PLAYER_PED_ID(), 4);
		g_self_outfit_current_pallette_id[5] = PED::GET_PED_PALETTE_VARIATION(PLAYER::PLAYER_PED_ID(), 5);
		g_self_outfit_current_pallette_id[6] = PED::GET_PED_PALETTE_VARIATION(PLAYER::PLAYER_PED_ID(), 6);
		g_self_outfit_current_pallette_id[7] = PED::GET_PED_PALETTE_VARIATION(PLAYER::PLAYER_PED_ID(), 7);
		g_self_outfit_current_pallette_id[8] = PED::GET_PED_PALETTE_VARIATION(PLAYER::PLAYER_PED_ID(), 8);
		g_self_outfit_current_pallette_id[9] = PED::GET_PED_PALETTE_VARIATION(PLAYER::PLAYER_PED_ID(), 9);
		g_self_outfit_current_pallette_id[10] = PED::GET_PED_PALETTE_VARIATION(PLAYER::PLAYER_PED_ID(), 10);
		g_self_outfit_current_pallette_id[11] = PED::GET_PED_PALETTE_VARIATION(PLAYER::PLAYER_PED_ID(), 11);
	}
	add_submenu_option(menu_self_handling, OBFUSCATE("Self Handling"));
	add_submenu_option(menu_self_editor, OBFUSCATE("Self Editor"));
	add_submenu_option(menu_self_animation_editor, OBFUSCATE("Animations"));
	add_submenu_option(menu_self_scenario_editor, OBFUSCATE("Scenarios"));
	if (add_text_option(OBFUSCATE("Clean Your Ped"))) {
		PED::CLEAR_PED_BLOOD_DAMAGE(PLAYER::PLAYER_PED_ID());
		PED::RESET_PED_VISIBLE_DAMAGE(PLAYER::PLAYER_PED_ID());
		PED::SET_PED_SWEAT(PLAYER::PLAYER_PED_ID(), 0.0f);
		print_notification(7000, "~g~Success:~s~ Cleaned Your Ped.");
	}
	if (add_toggle_option(&g_self_god_mode, OBFUSCATE("God Mode"))) {
		if (!g_self_god_mode) {
			ENTITY::SET_ENTITY_PROOFS(PLAYER::PLAYER_PED_ID(), FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE);
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 32, FALSE);
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 33, FALSE);
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 281, FALSE);
		}
	}
	if (add_toggle_option(&g_self_invisibility, OBFUSCATE("Invisibility"))) {
		if (!g_self_invisibility) 
			ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), TRUE, 0);
	}
	if (add_toggle_option(&g_self_no_ragdoll, OBFUSCATE("No Ragdoll"))) {
		if (!g_self_no_ragdoll) 
			PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), TRUE);
	}
	add_toggle_option(&g_self_no_cops, OBFUSCATE("No Cops"));
	if (add_editor_option(true, g_self_wanted_level, &g_self_wanted_level, 0, 5, 1, OBFUSCATE("Wanted Level"))) {
		PLAYER::SET_MAX_WANTED_LEVEL(g_self_wanted_level);
		PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), g_self_wanted_level, FALSE);
		PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), FALSE);

		std::stringstream ss;
		ss << "~g~Success:~s~ Wanted Level Set to ~c~" << g_self_wanted_level;
		print_notification(7000, ss.str());
	}
	if (add_toggle_option(&g_self_night_vision, OBFUSCATE("Night Vision"))) {
		if (!g_self_night_vision) 
			GRAPHICS::SET_NIGHTVISION(FALSE);
	}
	if (add_toggle_option(&g_self_heat_vision, OBFUSCATE("Heat Vision"))) {
		if (!g_self_heat_vision) 
			GRAPHICS::SET_SEETHROUGH(FALSE);
	}
	//add_toggle_option(&g_self_cops_turn_blind_eye, OBFUSCATE("Cops Turn Blind Eye"));
	//add_toggle_option(&g_self_reveal_players, OBFUSCATE("Reveal Players"));
	//add_toggle_option(&g_self_off_the_radar, OBFUSCATE("Off The Radar"));
	//if (add_text_option(OBFUSCATE("BST"))) {
	//	*scr_global(2437549).at(3880).as<std::int32_t*>() = 1;
	//	print_notification(7000, "~g~Success:~s~ Bull Shark Testosterone Enabled.");
	//}
	add_toggle_option(&g_self_forcefield, OBFUSCATE("Forcefield"));
	if (add_toggle_option(&g_self_mobile_radio, OBFUSCATE("Mobile Radio"))) {
		if (!g_self_mobile_radio) 
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(FALSE);
	}
	if (add_text_option(OBFUSCATE("Clone"))) {
		PED::CLONE_PED(PLAYER::PLAYER_PED_ID(), 0.0f, TRUE, FALSE);
		print_notification(7000, "~g~Success:~s~ Cloned Player Ped.");
	}

	//if (CAM::DOES_CAM_EXIST(g_self_model_cam)) {
	//	CAM::SET_CAM_ACTIVE(g_self_model_cam, false);
	//	CAM::RENDER_SCRIPT_CAMS(0, 1, 1500, 1, 0);
	//	CAM::DESTROY_CAM(g_self_model_cam, true);
	//}
}

void menu_weapon_xml_editor() {
	std::uint64_t ped_factory = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(GTA_PED_FACTORY);
	if (ped_factory != NULL) {

		std::uint64_t entity = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(ped_factory + 0x8);
		if (entity != NULL) {

			std::add_pointer_t<CPedWeaponManager> ped_weapon_mgr = *reinterpret_cast<std::add_pointer_t<std::add_pointer_t<CPedWeaponManager>>>(entity + 0x10C8);
			if (ped_weapon_mgr != nullptr) {
				if (ped_weapon_mgr->WeaponInfo != nullptr) {
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AccuracySpread, &ped_weapon_mgr->WeaponInfo->AccuracySpread, -1000.0f, 1000.0f, 0.5f, "Accuracy Spread");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AccurateModeAccuracyModifier, &ped_weapon_mgr->WeaponInfo->AccurateModeAccuracyModifier, -1000.0f, 1000.0f, 0.5f, "Accurate Mode Accuracy Modifier");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimingBreathingAdditiveWeight, &ped_weapon_mgr->WeaponInfo->AimingBreathingAdditiveWeight, -1000.0f, 1000.0f, 0.5f, "Aiming Breathing Additive Weight");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimingLeanAdditiveWeight, &ped_weapon_mgr->WeaponInfo->AimingLeanAdditiveWeight, -1000.0f, 1000.0f, 0.5f, "Aiming Lean Additive Weight");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMaxFPSIdle.x, &ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMaxFPSIdle.x, -1000.0f, 1000.0f, 0.5f, "Aim Offset End Pos Max FPS Idle ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMaxFPSIdle.y, &ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMaxFPSIdle.y, -1000.0f, 1000.0f, 0.5f, "Aim Offset End Pos Max FPS Idle ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMaxFPSIdle.z, &ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMaxFPSIdle.z, -1000.0f, 1000.0f, 0.5f, "Aim Offset End Pos Max FPS Idle ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMaxFPSLT.x, &ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMaxFPSLT.x, -1000.0f, 1000.0f, 0.5f, "Aim Offset End Pos Max FPS LT ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMaxFPSLT.y, &ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMaxFPSLT.y, -1000.0f, 1000.0f, 0.5f, "Aim Offset End Pos Max FPS LT ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMaxFPSLT.z, &ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMaxFPSLT.z, -1000.0f, 1000.0f, 0.5f, "Aim Offset End Pos Max FPS LT ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMedFPSIdle.x, &ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMedFPSIdle.x, -1000.0f, 1000.0f, 0.5f, "Aim Offset End Pos Med FPS Idle ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMedFPSIdle.y, &ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMedFPSIdle.y, -1000.0f, 1000.0f, 0.5f, "Aim Offset End Pos Med FPS Idle ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMedFPSIdle.z, &ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMedFPSIdle.z, -1000.0f, 1000.0f, 0.5f, "Aim Offset End Pos Med FPS Idle ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMedFPSLT.x, &ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMedFPSLT.x, -1000.0f, 1000.0f, 0.5f, "Aim Offset End Pos Med FPS LT ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMedFPSLT.y, &ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMedFPSLT.y, -1000.0f, 1000.0f, 0.5f, "Aim Offset End Pos Med FPS LT ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMedFPSLT.z, &ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMedFPSLT.z, -1000.0f, 1000.0f, 0.5f, "Aim Offset End Pos Med FPS LT ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMinFPSIdle.x, &ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMinFPSIdle.x, -1000.0f, 1000.0f, 0.5f, "Aim Offset End Pos Min FPS Idle ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMinFPSIdle.y, &ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMinFPSIdle.y, -1000.0f, 1000.0f, 0.5f, "Aim Offset End Pos Min FPS Idle ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMinFPSIdle.z, &ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMinFPSIdle.z, -1000.0f, 1000.0f, 0.5f, "Aim Offset End Pos Min FPS Idle ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMinFPSLT.x, &ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMinFPSLT.x, -1000.0f, 1000.0f, 0.5f, "Aim Offset End Pos Min FPS LT ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMinFPSLT.y, &ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMinFPSLT.y, -1000.0f, 1000.0f, 0.5f, "Aim Offset End Pos Min FPS LT ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMinFPSLT.z, &ped_weapon_mgr->WeaponInfo->AimOffsetEndPosMinFPSLT.z, -1000.0f, 1000.0f, 0.5f, "Aim Offset End Pos Min FPS LT ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMax.x, &ped_weapon_mgr->WeaponInfo->AimOffsetMax.x, -1000.0f, 1000.0f, 0.5f, "Aim Offset Max ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMax.y, &ped_weapon_mgr->WeaponInfo->AimOffsetMax.y, -1000.0f, 1000.0f, 0.5f, "Aim Offset Max ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMax.z, &ped_weapon_mgr->WeaponInfo->AimOffsetMax.z, -1000.0f, 1000.0f, 0.5f, "Aim Offset Max ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMaxFPSIdle.x, &ped_weapon_mgr->WeaponInfo->AimOffsetMaxFPSIdle.x, -1000.0f, 1000.0f, 0.5f, "Aim Offset Max FPS Idle ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMaxFPSIdle.y, &ped_weapon_mgr->WeaponInfo->AimOffsetMaxFPSIdle.y, -1000.0f, 1000.0f, 0.5f, "Aim Offset Max FPS Idle ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMaxFPSIdle.z, &ped_weapon_mgr->WeaponInfo->AimOffsetMaxFPSIdle.z, -1000.0f, 1000.0f, 0.5f, "Aim Offset Max FPS Idle ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMaxFPSLT.x, &ped_weapon_mgr->WeaponInfo->AimOffsetMaxFPSLT.x, -1000.0f, 1000.0f, 0.5f, "Aim Offset Max FPS LT ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMaxFPSLT.y, &ped_weapon_mgr->WeaponInfo->AimOffsetMaxFPSLT.y, -1000.0f, 1000.0f, 0.5f, "Aim Offset Max FPS LT ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMaxFPSLT.z, &ped_weapon_mgr->WeaponInfo->AimOffsetMaxFPSLT.z, -1000.0f, 1000.0f, 0.5f, "Aim Offset Max FPS LT ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMaxFPSRNG.x, &ped_weapon_mgr->WeaponInfo->AimOffsetMaxFPSRNG.x, -1000.0f, 1000.0f, 0.5f, "Aim Offset Max FPS RNG ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMaxFPSRNG.y, &ped_weapon_mgr->WeaponInfo->AimOffsetMaxFPSRNG.y, -1000.0f, 1000.0f, 0.5f, "Aim Offset Max FPS RNG ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMaxFPSRNG.z, &ped_weapon_mgr->WeaponInfo->AimOffsetMaxFPSRNG.z, -1000.0f, 1000.0f, 0.5f, "Aim Offset Max FPS RNG ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMaxFPSScope.x, &ped_weapon_mgr->WeaponInfo->AimOffsetMaxFPSScope.x, -1000.0f, 1000.0f, 0.5f, "Aim Offset Max FPS Scope ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMaxFPSScope.y, &ped_weapon_mgr->WeaponInfo->AimOffsetMaxFPSScope.y, -1000.0f, 1000.0f, 0.5f, "Aim Offset Max FPS Scope ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMaxFPSScope.z, &ped_weapon_mgr->WeaponInfo->AimOffsetMaxFPSScope.z, -1000.0f, 1000.0f, 0.5f, "Aim Offset Max FPS Scope ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMedFPSIdle.x, &ped_weapon_mgr->WeaponInfo->AimOffsetMedFPSIdle.x, -1000.0f, 1000.0f, 0.5f, "Aim Offset Med FPS Idle ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMedFPSIdle.y, &ped_weapon_mgr->WeaponInfo->AimOffsetMedFPSIdle.y, -1000.0f, 1000.0f, 0.5f, "Aim Offset Med FPS Idle ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMedFPSIdle.z, &ped_weapon_mgr->WeaponInfo->AimOffsetMedFPSIdle.z, -1000.0f, 1000.0f, 0.5f, "Aim Offset Med FPS Idle ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMin.x, &ped_weapon_mgr->WeaponInfo->AimOffsetMin.x, -1000.0f, 1000.0f, 0.5f, "Aim Offset Min ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMin.y, &ped_weapon_mgr->WeaponInfo->AimOffsetMin.y, -1000.0f, 1000.0f, 0.5f, "Aim Offset Min ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMin.z, &ped_weapon_mgr->WeaponInfo->AimOffsetMin.z, -1000.0f, 1000.0f, 0.5f, "Aim Offset Min ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMinFPSIdle.x, &ped_weapon_mgr->WeaponInfo->AimOffsetMinFPSIdle.x, -1000.0f, 1000.0f, 0.5f, "Aim Offset Min FPS Idle ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMinFPSIdle.y, &ped_weapon_mgr->WeaponInfo->AimOffsetMinFPSIdle.y, -1000.0f, 1000.0f, 0.5f, "Aim Offset Min FPS Idle ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMinFPSIdle.z, &ped_weapon_mgr->WeaponInfo->AimOffsetMinFPSIdle.z, -1000.0f, 1000.0f, 0.5f, "Aim Offset Min FPS Idle ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMinFPSLT.x, &ped_weapon_mgr->WeaponInfo->AimOffsetMinFPSLT.x, -1000.0f, 1000.0f, 0.5f, "Aim Offset Min FPS LT ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMinFPSLT.y, &ped_weapon_mgr->WeaponInfo->AimOffsetMinFPSLT.y, -1000.0f, 1000.0f, 0.5f, "Aim Offset Min FPS LT ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMinFPSLT.z, &ped_weapon_mgr->WeaponInfo->AimOffsetMinFPSLT.z, -1000.0f, 1000.0f, 0.5f, "Aim Offset Min FPS LT ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMinFPSRNG.x, &ped_weapon_mgr->WeaponInfo->AimOffsetMinFPSRNG.x, -1000.0f, 1000.0f, 0.5f, "Aim Offset Min FPS RNG ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMinFPSRNG.y, &ped_weapon_mgr->WeaponInfo->AimOffsetMinFPSRNG.y, -1000.0f, 1000.0f, 0.5f, "Aim Offset Min FPS RNG ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMinFPSRNG.z, &ped_weapon_mgr->WeaponInfo->AimOffsetMinFPSRNG.z, -1000.0f, 1000.0f, 0.5f, "Aim Offset Min FPS RNG ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMinFPSScope.x, &ped_weapon_mgr->WeaponInfo->AimOffsetMinFPSScope.x, -1000.0f, 1000.0f, 0.5f, "Aim Offset Min FPS Scope ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMinFPSScope.y, &ped_weapon_mgr->WeaponInfo->AimOffsetMinFPSScope.y, -1000.0f, 1000.0f, 0.5f, "Aim Offset Min FPS Scope ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimOffsetMinFPSScope.z, &ped_weapon_mgr->WeaponInfo->AimOffsetMinFPSScope.z, -1000.0f, 1000.0f, 0.5f, "Aim Offset Min FPS Scope ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimProbeLengthMax, &ped_weapon_mgr->WeaponInfo->AimProbeLengthMax, -1000.0f, 1000.0f, 0.5f, "Aim Probe Length Max");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AimProbeLengthMin, &ped_weapon_mgr->WeaponInfo->AimProbeLengthMin, -1000.0f, 1000.0f, 0.5f, "Aim Probe Length Min");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AiPotentialBlastEventRange, &ped_weapon_mgr->WeaponInfo->AiPotentialBlastEventRange, -1000.0f, 1000.0f, 0.5f, "Ai Potential Blast Event Range");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AiSoundRange, &ped_weapon_mgr->WeaponInfo->AiSoundRange, -1000.0f, 1000.0f, 0.5f, "Ai Sound Range");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AlternateWaitTime, &ped_weapon_mgr->WeaponInfo->AlternateWaitTime, -1000.0f, 1000.0f, 0.5f, "Alternate Wait Time");
					add_editor_option(true, static_cast<std::int32_t>(ped_weapon_mgr->WeaponInfo->AmmoDiminishingRate), &ped_weapon_mgr->WeaponInfo->AmmoDiminishingRate, static_cast<std::int8_t>(0), static_cast<std::int8_t>(500), static_cast<std::int8_t>(1), "Ammo Diminishing Rate");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->AnimReloadRate, &ped_weapon_mgr->WeaponInfo->AnimReloadRate, -1000.0f, 1000.0f, 0.5f, "Anim Reload Rate");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->BatchSpread, &ped_weapon_mgr->WeaponInfo->BatchSpread, -1000.0f, 1000.0f, 0.5f, "Batch Spread");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->BulletBendingFarRadius, &ped_weapon_mgr->WeaponInfo->BulletBendingFarRadius, -1000.0f, 1000.0f, 0.5f, "Bullet Bending Far Radius");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->BulletBendingNearRadius, &ped_weapon_mgr->WeaponInfo->BulletBendingNearRadius, -1000.0f, 1000.0f, 0.5f, "Bullet Bending Near Radius");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->BulletBendingZoomedRadius, &ped_weapon_mgr->WeaponInfo->BulletBendingZoomedRadius, -1000.0f, 1000.0f, 0.5f, "Bullet Bending Zoomed Radius");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->BulletsInBatch, &ped_weapon_mgr->WeaponInfo->BulletsInBatch, 1, 1000, 1, "Bullets In Batch");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->BulletsPerAnimLoop, &ped_weapon_mgr->WeaponInfo->BulletsPerAnimLoop, 1, 1000, 1, "Bullets Per Anim Loop");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->CameraFov, &ped_weapon_mgr->WeaponInfo->CameraFov, -1000.0f, 1000.0f, 0.5f, "Camera Fov");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->Damage, &ped_weapon_mgr->WeaponInfo->Damage, -1000.0f, 1000.0f, 0.5f, "Damage");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->DamageFallOffModifier, &ped_weapon_mgr->WeaponInfo->DamageFallOffModifier, -1000.0f, 1000.0f, 0.5f, "Damage Fall Off Modifier");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->DamageFallOffRangeMax, &ped_weapon_mgr->WeaponInfo->DamageFallOffRangeMax, -1000.0f, 1000.0f, 0.5f, "Damage Fall Off Range Max");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->DamageFallOffRangeMin, &ped_weapon_mgr->WeaponInfo->DamageFallOffRangeMin, -1000.0f, 1000.0f, 0.5f, "Damage Fall Off Range Min");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->DamageTime, &ped_weapon_mgr->WeaponInfo->DamageTime, -1000.0f, 1000.0f, 0.5f, "Damage Time");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->DamageTimeInVehicle, &ped_weapon_mgr->WeaponInfo->DamageTimeInVehicle, -1000.0f, 1000.0f, 0.5f, "Damage Time In Vehicle");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->DamageTimeInVehicleHeadShot, &ped_weapon_mgr->WeaponInfo->DamageTimeInVehicleHeadShot, -1000.0f, 1000.0f, 0.5f, "Damage Time In Vehicle Head Shot");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->DropForwardVelocity, &ped_weapon_mgr->WeaponInfo->DropForwardVelocity, -1000.0f, 1000.0f, 0.5f, "Drop Forward Velocity");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->ExpandPedCapsuleRadius, &ped_weapon_mgr->WeaponInfo->ExpandPedCapsuleRadius, -1000.0f, 1000.0f, 0.5f, "Expand Ped Capsule Radius");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->ExplosionShakeAmplitude, &ped_weapon_mgr->WeaponInfo->ExplosionShakeAmplitude, -1000.0f, 1000.0f, 0.5f, "Explosion Shake Amplitude");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FiringBreathingAdditiveWeight, &ped_weapon_mgr->WeaponInfo->FiringBreathingAdditiveWeight, -1000.0f, 1000.0f, 0.5f, "Firing Breathing Additive Weight");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FiringLeanAdditiveWeight, &ped_weapon_mgr->WeaponInfo->FiringLeanAdditiveWeight, -1000.0f, 1000.0f, 0.5f, "Firing Lean Additive Weight");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonAimFovMax, &ped_weapon_mgr->WeaponInfo->FirstPersonAimFovMax, -1000.0f, 1000.0f, 0.5f, "First Person Aim Fov Max");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonAimFovMin, &ped_weapon_mgr->WeaponInfo->FirstPersonAimFovMin, -1000.0f, 1000.0f, 0.5f, "First Person Aim Fov Min");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonIdleOffset.x, &ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonIdleOffset.x, -1000.0f, 1000.0f, 0.5f, "First Person As Third Person Idle Offset ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonIdleOffset.y, &ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonIdleOffset.y, -1000.0f, 1000.0f, 0.5f, "First Person As Third Person Idle Offset ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonIdleOffset.z, &ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonIdleOffset.z, -1000.0f, 1000.0f, 0.5f, "First Person As Third Person Idle Offset ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonLTOffset.x, &ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonLTOffset.x, -1000.0f, 1000.0f, 0.5f, "First Person As Third Person LT Offset ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonLTOffset.y, &ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonLTOffset.y, -1000.0f, 1000.0f, 0.5f, "First Person As Third Person LT Offset ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonLTOffset.z, &ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonLTOffset.z, -1000.0f, 1000.0f, 0.5f, "First Person As Third Person LT Offset ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonRNGOffset.x, &ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonRNGOffset.x, -1000.0f, 1000.0f, 0.5f, "First Person As Third Person RNG Offset ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonRNGOffset.y, &ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonRNGOffset.y, -1000.0f, 1000.0f, 0.5f, "First Person As Third Person RNG Offset ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonRNGOffset.z, &ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonRNGOffset.z, -1000.0f, 1000.0f, 0.5f, "First Person As Third Person RNG Offset ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonScopeOffset.x, &ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonScopeOffset.x, -1000.0f, 1000.0f, 0.5f, "First Person As Third Person Scope Offset ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonScopeOffset.y, &ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonScopeOffset.y, -1000.0f, 1000.0f, 0.5f, "First Person As Third Person Scope Offset ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonScopeOffset.z, &ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonScopeOffset.z, -1000.0f, 1000.0f, 0.5f, "First Person As Third Person Scope Offset ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonWeaponBlockedOffset.x, &ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonWeaponBlockedOffset.x, -1000.0f, 1000.0f, 0.5f, "First Person As Third Person Weapon Blocked Offset ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonWeaponBlockedOffset.y, &ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonWeaponBlockedOffset.y, -1000.0f, 1000.0f, 0.5f, "First Person As Third Person Weapon Blocked Offset ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonWeaponBlockedOffset.z, &ped_weapon_mgr->WeaponInfo->FirstPersonAsThirdPersonWeaponBlockedOffset.z, -1000.0f, 1000.0f, 0.5f, "First Person As Third Person Weapon Blocked Offset ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonBulletBendingFarRadius, &ped_weapon_mgr->WeaponInfo->FirstPersonBulletBendingFarRadius, -1000.0f, 1000.0f, 0.5f, "First Person Bullet Bending Far Radius");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonBulletBendingNearRadius, &ped_weapon_mgr->WeaponInfo->FirstPersonBulletBendingNearRadius, -1000.0f, 1000.0f, 0.5f, "First Person Bullet Bending Near Radius");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonBulletBendingZoomedRadius, &ped_weapon_mgr->WeaponInfo->FirstPersonBulletBendingZoomedRadius, -1000.0f, 1000.0f, 0.5f, "First Person Bullet Bending Zoomed Radius");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonDofSubjectMagnificationPowerFactorNear.x, &ped_weapon_mgr->WeaponInfo->FirstPersonDofSubjectMagnificationPowerFactorNear.x, -1000.0f, 1000.0f, 0.5f, "First Person Dof Subject Magnification Power Factor Near ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonDofSubjectMagnificationPowerFactorNear.y, &ped_weapon_mgr->WeaponInfo->FirstPersonDofSubjectMagnificationPowerFactorNear.y, -1000.0f, 1000.0f, 0.5f, "First Person Dof Subject Magnification Power Factor Near ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonDofSubjectMagnificationPowerFactorNear.z, &ped_weapon_mgr->WeaponInfo->FirstPersonDofSubjectMagnificationPowerFactorNear.z, -1000.0f, 1000.0f, 0.5f, "First Person Dof Subject Magnification Power Factor Near ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonLTOffset.x, &ped_weapon_mgr->WeaponInfo->FirstPersonLTOffset.x, -1000.0f, 1000.0f, 0.5f, "First Person LT Offset ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonLTOffset.y, &ped_weapon_mgr->WeaponInfo->FirstPersonLTOffset.y, -1000.0f, 1000.0f, 0.5f, "First Person LT Offset ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonLTOffset.z, &ped_weapon_mgr->WeaponInfo->FirstPersonLTOffset.z, -1000.0f, 1000.0f, 0.5f, "First Person LT Offset ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonLTRotationOffset.x, &ped_weapon_mgr->WeaponInfo->FirstPersonLTRotationOffset.x, -1000.0f, 1000.0f, 0.5f, "First Person LT Rotation Offset ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonLTRotationOffset.y, &ped_weapon_mgr->WeaponInfo->FirstPersonLTRotationOffset.y, -1000.0f, 1000.0f, 0.5f, "First Person LT Rotation Offset ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonLTRotationOffset.z, &ped_weapon_mgr->WeaponInfo->FirstPersonLTRotationOffset.z, -1000.0f, 1000.0f, 0.5f, "First Person LT Rotation Offset ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonRNGOffset.x, &ped_weapon_mgr->WeaponInfo->FirstPersonRNGOffset.x, -1000.0f, 1000.0f, 0.5f, "First Person RNG Offset ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonRNGOffset.y, &ped_weapon_mgr->WeaponInfo->FirstPersonRNGOffset.y, -1000.0f, 1000.0f, 0.5f, "First Person RNG Offset ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonRNGOffset.z, &ped_weapon_mgr->WeaponInfo->FirstPersonRNGOffset.z, -1000.0f, 1000.0f, 0.5f, "First Person RNG Offset ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonRNGRotationOffset.x, &ped_weapon_mgr->WeaponInfo->FirstPersonRNGRotationOffset.x, -1000.0f, 1000.0f, 0.5f, "First Person RNG Rotation Offset ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonRNGRotationOffset.y, &ped_weapon_mgr->WeaponInfo->FirstPersonRNGRotationOffset.y, -1000.0f, 1000.0f, 0.5f, "First Person RNG Rotation Offset ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonRNGRotationOffset.z, &ped_weapon_mgr->WeaponInfo->FirstPersonRNGRotationOffset.z, -1000.0f, 1000.0f, 0.5f, "First Person RNG Rotation Offset ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonScopeAttachmentOffset.x, &ped_weapon_mgr->WeaponInfo->FirstPersonScopeAttachmentOffset.x, -1000.0f, 1000.0f, 0.5f, "First Person Scope Attachment Offset ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonScopeAttachmentOffset.y, &ped_weapon_mgr->WeaponInfo->FirstPersonScopeAttachmentOffset.y, -1000.0f, 1000.0f, 0.5f, "First Person Scope Attachment Offset ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonScopeAttachmentOffset.z, &ped_weapon_mgr->WeaponInfo->FirstPersonScopeAttachmentOffset.z, -1000.0f, 1000.0f, 0.5f, "First Person Scope Attachment Offset ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonScopeAttachmentRotationOffset.x, &ped_weapon_mgr->WeaponInfo->FirstPersonScopeAttachmentRotationOffset.x, -1000.0f, 1000.0f, 0.5f, "First Person Scope Attachment Rotation Offset ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonScopeAttachmentRotationOffset.y, &ped_weapon_mgr->WeaponInfo->FirstPersonScopeAttachmentRotationOffset.y, -1000.0f, 1000.0f, 0.5f, "First Person Scope Attachment Rotation Offset ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonScopeAttachmentRotationOffset.z, &ped_weapon_mgr->WeaponInfo->FirstPersonScopeAttachmentRotationOffset.z, -1000.0f, 1000.0f, 0.5f, "First Person Scope Attachment Rotation Offset ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonScopeFov, &ped_weapon_mgr->WeaponInfo->FirstPersonScopeFov, -1000.0f, 1000.0f, 0.5f, "First Person Scope Fov");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonScopeOffset.x, &ped_weapon_mgr->WeaponInfo->FirstPersonScopeOffset.x, -1000.0f, 1000.0f, 0.5f, "First Person Scope Offset ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonScopeOffset.y, &ped_weapon_mgr->WeaponInfo->FirstPersonScopeOffset.y, -1000.0f, 1000.0f, 0.5f, "First Person Scope Offset ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonScopeOffset.z, &ped_weapon_mgr->WeaponInfo->FirstPersonScopeOffset.z, -1000.0f, 1000.0f, 0.5f, "First Person Scope Offset ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonScopeRotationOffset.x, &ped_weapon_mgr->WeaponInfo->FirstPersonScopeRotationOffset.x, -1000.0f, 1000.0f, 0.5f, "First Person Scope Rotation Offset ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonScopeRotationOffset.y, &ped_weapon_mgr->WeaponInfo->FirstPersonScopeRotationOffset.y, -1000.0f, 1000.0f, 0.5f, "First Person Scope Rotation Offset ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FirstPersonScopeRotationOffset.z, &ped_weapon_mgr->WeaponInfo->FirstPersonScopeRotationOffset.z, -1000.0f, 1000.0f, 0.5f, "First Person Scope Rotation Offset ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FlashFxAltChance, &ped_weapon_mgr->WeaponInfo->FlashFxAltChance, -1000.0f, 1000.0f, 0.5f, "Flash Fx Alt Chance");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FlashFxChanceMP, &ped_weapon_mgr->WeaponInfo->FlashFxChanceMP, -1000.0f, 1000.0f, 0.5f, "Flash Fx Chance MP");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FlashFxChanceSP, &ped_weapon_mgr->WeaponInfo->FlashFxChanceSP, -1000.0f, 1000.0f, 0.5f, "Flash Fx Chance SP");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FlashFxLightOffsetDist, &ped_weapon_mgr->WeaponInfo->FlashFxLightOffsetDist, -1000.0f, 1000.0f, 0.5f, "Flash Fx Light Offset Dist");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FlashFxScale, &ped_weapon_mgr->WeaponInfo->FlashFxScale, -1000.0f, 1000.0f, 0.5f, "Flash Fx Scale");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->Force, &ped_weapon_mgr->WeaponInfo->Force, -1000.0f, 1000.0f, 0.5f, "Force");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->ForceFalloffMin, &ped_weapon_mgr->WeaponInfo->ForceFalloffMin, -1000.0f, 1000.0f, 0.5f, "Force Falloff Min");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->ForceFalloffRangeEnd, &ped_weapon_mgr->WeaponInfo->ForceFalloffRangeEnd, -1000.0f, 1000.0f, 0.5f, "Force Falloff Range End");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->ForceFalloffRangeStart, &ped_weapon_mgr->WeaponInfo->ForceFalloffRangeStart, -1000.0f, 1000.0f, 0.5f, "Force Falloff Range Start");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->ForceHitFlyingHeli, &ped_weapon_mgr->WeaponInfo->ForceHitFlyingHeli, -1000.0f, 1000.0f, 0.5f, "Force Hit Flying Heli");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->ForceHitPed, &ped_weapon_mgr->WeaponInfo->ForceHitPed, -1000.0f, 1000.0f, 0.5f, "Force Hit Ped");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->ForceHitVehicle, &ped_weapon_mgr->WeaponInfo->ForceHitVehicle, -1000.0f, 1000.0f, 0.5f, "Force Hit Vehicle");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->ForceMaxStrengthMult, &ped_weapon_mgr->WeaponInfo->ForceMaxStrengthMult, -1000.0f, 1000.0f, 0.5f, "Force Max Strength Mult");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->FragImpulse, &ped_weapon_mgr->WeaponInfo->FragImpulse, -1000.0f, 1000.0f, 0.5f, "Frag Impulse");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->GroundDisturbFxDist, &ped_weapon_mgr->WeaponInfo->GroundDisturbFxDist, -1000.0f, 1000.0f, 0.5f, "Ground Disturb Fx Dist");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->HeadShotDamageModifierAI, &ped_weapon_mgr->WeaponInfo->HeadShotDamageModifierAI, -1000.0f, 1000.0f, 0.5f, "Head Shot Damage Modifier AI");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->HeadShotDamageModifierPlayer, &ped_weapon_mgr->WeaponInfo->HeadShotDamageModifierPlayer, -1000.0f, 1000.0f, 0.5f, "Head Shot Damage Modifier Player");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->HitLimbsDamageModifier, &ped_weapon_mgr->WeaponInfo->HitLimbsDamageModifier, -1000.0f, 1000.0f, 0.5f, "Hit Limbs Damage Modifier");
					add_editor_option(true, static_cast<std::int32_t>(ped_weapon_mgr->WeaponInfo->HudAccuracy), &ped_weapon_mgr->WeaponInfo->HudAccuracy, static_cast<std::int8_t>(0), static_cast<std::int8_t>(500), static_cast<std::int8_t>(1), "Hud Accuracy");
					add_editor_option(true, static_cast<std::int32_t>(ped_weapon_mgr->WeaponInfo->HudCapacity), &ped_weapon_mgr->WeaponInfo->HudCapacity, static_cast<std::int8_t>(0), static_cast<std::int8_t>(500), static_cast<std::int8_t>(1), "Hud Capacity");
					add_editor_option(true, static_cast<std::int32_t>(ped_weapon_mgr->WeaponInfo->HudDamage), &ped_weapon_mgr->WeaponInfo->HudDamage, static_cast<std::int8_t>(0), static_cast<std::int8_t>(500), static_cast<std::int8_t>(1), "Hud Damage");
					add_editor_option(true, static_cast<std::int32_t>(ped_weapon_mgr->WeaponInfo->HudRange), &ped_weapon_mgr->WeaponInfo->HudRange, static_cast<std::int8_t>(0), static_cast<std::int8_t>(500), static_cast<std::int8_t>(1), "Hud Range");
					add_editor_option(true, static_cast<std::int32_t>(ped_weapon_mgr->WeaponInfo->HudSpeed), &ped_weapon_mgr->WeaponInfo->HudSpeed, static_cast<std::int8_t>(0), static_cast<std::int8_t>(500), static_cast<std::int8_t>(1), "Hud Speed");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->IkRecoilDisplacementScaleBackward, &ped_weapon_mgr->WeaponInfo->IkRecoilDisplacementScaleBackward, -1000.0f, 1000.0f, 0.5f, "Ik Recoil Displacement Scale Backward");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->IkRecoilDisplacementScaleVertical, &ped_weapon_mgr->WeaponInfo->IkRecoilDisplacementScaleVertical, -1000.0f, 1000.0f, 0.5f, "Ik Recoil Displacement Scale Vertical");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->InitialRumbleDuration, &ped_weapon_mgr->WeaponInfo->InitialRumbleDuration, 1, 1000, 1, "Initial Rumble Duration");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->InitialRumbleDurationFps, &ped_weapon_mgr->WeaponInfo->InitialRumbleDurationFps, 1, 1000, 1, "Initial Rumble Duration Fps");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->InitialRumbleIntensity, &ped_weapon_mgr->WeaponInfo->InitialRumbleIntensity, -1000.0f, 1000.0f, 0.5f, "Initial Rumble Intensity");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->InitialRumbleIntensityFps, &ped_weapon_mgr->WeaponInfo->InitialRumbleIntensityFps, -1000.0f, 1000.0f, 0.5f, "Initial Rumble Intensity Fps");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->InitialRumbleIntensityTrigger, &ped_weapon_mgr->WeaponInfo->InitialRumbleIntensityTrigger, -1000.0f, 1000.0f, 0.5f, "Initial Rumble Intensity Trigger");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->KillshotImpulseScale, &ped_weapon_mgr->WeaponInfo->KillshotImpulseScale, -1000.0f, 1000.0f, 0.5f, "Killshot Impulse Scale");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->KnockdownCount, &ped_weapon_mgr->WeaponInfo->KnockdownCount, 1, 1000, 1, "Knockdown Count");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->LeftHandIkOffset.x, &ped_weapon_mgr->WeaponInfo->LeftHandIkOffset.x, -1000.0f, 1000.0f, 0.5f, "Left Hand Ik Offset ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->LeftHandIkOffset.y, &ped_weapon_mgr->WeaponInfo->LeftHandIkOffset.y, -1000.0f, 1000.0f, 0.5f, "Left Hand Ik Offset ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->LeftHandIkOffset.z, &ped_weapon_mgr->WeaponInfo->LeftHandIkOffset.z, -1000.0f, 1000.0f, 0.5f, "Left Hand Ik Offset ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->LightlyArmouredDamageModifier, &ped_weapon_mgr->WeaponInfo->LightlyArmouredDamageModifier, -1000.0f, 1000.0f, 0.5f, "Lightly Armoured Damage Modifier");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->LockOnRange, &ped_weapon_mgr->WeaponInfo->LockOnRange, -1000.0f, 1000.0f, 0.5f, "Lock On Range");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->MaxHeadShotDistanceAI, &ped_weapon_mgr->WeaponInfo->MaxHeadShotDistanceAI, -1000.0f, 1000.0f, 0.5f, "Max Head Shot Distance AI");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->MaxHeadShotDistancePlayer, &ped_weapon_mgr->WeaponInfo->MaxHeadShotDistancePlayer, -1000.0f, 1000.0f, 0.5f, "Max Head Shot Distance Player");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->MinHeadShotDistanceAI, &ped_weapon_mgr->WeaponInfo->MinHeadShotDistanceAI, -1000.0f, 1000.0f, 0.5f, "Min Head Shot Distance AI");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->MinHeadShotDistancePlayer, &ped_weapon_mgr->WeaponInfo->MinHeadShotDistancePlayer, -1000.0f, 1000.0f, 0.5f, "Min Head Shot Distance Player");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->MinTimeBetweenRecoilShakes, &ped_weapon_mgr->WeaponInfo->MinTimeBetweenRecoilShakes, 1, 1000, 1, "Min Time Between Recoil Shakes");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->MuzzleOverrideOffset.x, &ped_weapon_mgr->WeaponInfo->MuzzleOverrideOffset.x, -1000.0f, 1000.0f, 0.5f, "Muzzle Override Offset ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->MuzzleOverrideOffset.y, &ped_weapon_mgr->WeaponInfo->MuzzleOverrideOffset.y, -1000.0f, 1000.0f, 0.5f, "Muzzle Override Offset ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->MuzzleOverrideOffset.z, &ped_weapon_mgr->WeaponInfo->MuzzleOverrideOffset.z, -1000.0f, 1000.0f, 0.5f, "Muzzle Override Offset ~c~(Z)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->NetworkHeadShotPlayerDamageModifier, &ped_weapon_mgr->WeaponInfo->NetworkHeadShotPlayerDamageModifier, -1000.0f, 1000.0f, 0.5f, "Network Head Shot Player Damage Modifier");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->NetworkHitLimbsDamageModifier, &ped_weapon_mgr->WeaponInfo->NetworkHitLimbsDamageModifier, -1000.0f, 1000.0f, 0.5f, "Network Hit Limbs Damage Modifier");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->NetworkPedDamageModifier, &ped_weapon_mgr->WeaponInfo->NetworkPedDamageModifier, -1000.0f, 1000.0f, 0.5f, "Network Ped Damage Modifier");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->NetworkPlayerDamageModifier, &ped_weapon_mgr->WeaponInfo->NetworkPlayerDamageModifier, -1000.0f, 1000.0f, 0.5f, "Network Player Damage Modifier");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->Penetration, &ped_weapon_mgr->WeaponInfo->Penetration, -1000.0f, 1000.0f, 0.5f, "Penetration");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->ProjectileForce, &ped_weapon_mgr->WeaponInfo->ProjectileForce, -1000.0f, 1000.0f, 0.5f, "Projectile Force");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->RecoilAccuracyMax, &ped_weapon_mgr->WeaponInfo->RecoilAccuracyMax, -1000.0f, 1000.0f, 0.5f, "Recoil Accuracy Max");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->RecoilAccuracyToAllowHeadShotAI, &ped_weapon_mgr->WeaponInfo->RecoilAccuracyToAllowHeadShotAI, -1000.0f, 1000.0f, 0.5f, "Recoil Accuracy To Allow Head Shot AI");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->RecoilAccuracyToAllowHeadShotPlayer, &ped_weapon_mgr->WeaponInfo->RecoilAccuracyToAllowHeadShotPlayer, -1000.0f, 1000.0f, 0.5f, "Recoil Accuracy To Allow Head Shot Player");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->RecoilErrorTime, &ped_weapon_mgr->WeaponInfo->RecoilErrorTime, -1000.0f, 1000.0f, 0.5f, "Recoil Error Time");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->RecoilRecoveryRate, &ped_weapon_mgr->WeaponInfo->RecoilRecoveryRate, -1000.0f, 1000.0f, 0.5f, "Recoil Recovery Rate");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->RecoilShakeAmplitude, &ped_weapon_mgr->WeaponInfo->RecoilShakeAmplitude, -1000.0f, 1000.0f, 0.5f, "Recoil Shake Amplitude");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->ReloadTimeMP, &ped_weapon_mgr->WeaponInfo->ReloadTimeMP, -1000.0f, 1000.0f, 0.5f, "Reload Time MP");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->ReloadTimeSP, &ped_weapon_mgr->WeaponInfo->ReloadTimeSP, -1000.0f, 1000.0f, 0.5f, "Reload Time SP");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->ReticuleMinSizeCrouched, &ped_weapon_mgr->WeaponInfo->ReticuleMinSizeCrouched, -1000.0f, 1000.0f, 0.5f, "Reticule Min Size Crouched");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->ReticuleMinSizeStanding, &ped_weapon_mgr->WeaponInfo->ReticuleMinSizeStanding, -1000.0f, 1000.0f, 0.5f, "Reticule Min Size Standing");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->ReticuleScale, &ped_weapon_mgr->WeaponInfo->ReticuleScale, -1000.0f, 1000.0f, 0.5f, "Reticule Scale");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->RumbleDamageIntensity, &ped_weapon_mgr->WeaponInfo->RumbleDamageIntensity, -1000.0f, 1000.0f, 0.5f, "Rumble Damage Intensity");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->RumbleDuration, &ped_weapon_mgr->WeaponInfo->RumbleDuration, 1, 1000, 1, "Rumble Duration");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->RumbleDurationFps, &ped_weapon_mgr->WeaponInfo->RumbleDurationFps, 1, 1000, 1, "Rumble Duration Fps");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->RumbleIntensity, &ped_weapon_mgr->WeaponInfo->RumbleIntensity, -1000.0f, 1000.0f, 0.5f, "Rumble Intensity");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->RumbleIntensityFps, &ped_weapon_mgr->WeaponInfo->RumbleIntensityFps, -1000.0f, 1000.0f, 0.5f, "Rumble Intensity Fps");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->RumbleIntensityTrigger, &ped_weapon_mgr->WeaponInfo->RumbleIntensityTrigger, -1000.0f, 1000.0f, 0.5f, "Rumble Intensity Trigger");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->RunAndGunAccuracyMinOverride, &ped_weapon_mgr->WeaponInfo->RunAndGunAccuracyMinOverride, -1000.0f, 1000.0f, 0.5f, "Run & Gun Accuracy Min Override");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->RunAndGunAccuracyModifier, &ped_weapon_mgr->WeaponInfo->RunAndGunAccuracyModifier, -1000.0f, 1000.0f, 0.5f, "Run & Gun Accuracy Modifier");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->Speed, &ped_weapon_mgr->WeaponInfo->Speed, -1000.0f, 1000.0f, 0.5f, "Speed");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->SpinDownTime, &ped_weapon_mgr->WeaponInfo->SpinDownTime, -1000.0f, 1000.0f, 0.5f, "Spin Down Time");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->SpinTime, &ped_weapon_mgr->WeaponInfo->SpinTime, -1000.0f, 1000.0f, 0.5f, "Spin Time");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->SpinUpTime, &ped_weapon_mgr->WeaponInfo->SpinUpTime, -1000.0f, 1000.0f, 0.5f, "Spin Up Time");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->StealthAimingBreathingAdditiveWeight, &ped_weapon_mgr->WeaponInfo->StealthAimingBreathingAdditiveWeight, -1000.0f, 1000.0f, 0.5f, "Stealth Aiming Breathing Additive Weight");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->StealthAimingLeanAdditiveWeight, &ped_weapon_mgr->WeaponInfo->StealthAimingLeanAdditiveWeight, -1000.0f, 1000.0f, 0.5f, "Stealth Aiming Lean Additive Weight");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->StealthFiringBreathingAdditiveWeight, &ped_weapon_mgr->WeaponInfo->StealthFiringBreathingAdditiveWeight, -1000.0f, 1000.0f, 0.5f, "Stealth Firing Breathing Additive Weight");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->StealthFiringLeanAdditiveWeight, &ped_weapon_mgr->WeaponInfo->StealthFiringLeanAdditiveWeight, -1000.0f, 1000.0f, 0.5f, "Stealth Firing Lean Additive Weight");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->TimeBetweenShots, &ped_weapon_mgr->WeaponInfo->TimeBetweenShots, -1000.0f, 1000.0f, 0.5f, "Time Between Shots");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->TimeLeftBetweenShotsWhereShouldFireIsCached, &ped_weapon_mgr->WeaponInfo->TimeLeftBetweenShotsWhereShouldFireIsCached, -1000.0f, 1000.0f, 0.5f, "Time Left Between Shots Where Should Fire Is Cached");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->TorsoAimOffset.x, &ped_weapon_mgr->WeaponInfo->TorsoAimOffset.x, -1000.0f, 1000.0f, 0.5f, "Torso Aim Offset ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->TorsoAimOffset.y, &ped_weapon_mgr->WeaponInfo->TorsoAimOffset.y, -1000.0f, 1000.0f, 0.5f, "Torso Aim Offset ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->TorsoCrouchedAimOffset.x, &ped_weapon_mgr->WeaponInfo->TorsoCrouchedAimOffset.x, -1000.0f, 1000.0f, 0.5f, "Torso Crouched Aim Offset ~c~(X)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->TorsoCrouchedAimOffset.y, &ped_weapon_mgr->WeaponInfo->TorsoCrouchedAimOffset.y, -1000.0f, 1000.0f, 0.5f, "Torso Crouched Aim Offset ~c~(Y)");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->TorsoIKAngleLimit, &ped_weapon_mgr->WeaponInfo->TorsoIKAngleLimit, -1000.0f, 1000.0f, 0.5f, "Torso IK Angle Limit");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->TracerFxChanceMP, &ped_weapon_mgr->WeaponInfo->TracerFxChanceMP, -1000.0f, 1000.0f, 0.5f, "Tracer Fx Chance MP");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->TracerFxChanceSP, &ped_weapon_mgr->WeaponInfo->TracerFxChanceSP, -1000.0f, 1000.0f, 0.5f, "Tracer Fx Chance SP");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->VehicleAttackAngle, &ped_weapon_mgr->WeaponInfo->VehicleAttackAngle, -1000.0f, 1000.0f, 0.5f, "Vehicle Attack Angle");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->VehicleDamageModifier, &ped_weapon_mgr->WeaponInfo->VehicleDamageModifier, -1000.0f, 1000.0f, 0.5f, "Vehicle Damage Modifier");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->VehicleReloadTime, &ped_weapon_mgr->WeaponInfo->VehicleReloadTime, -1000.0f, 1000.0f, 0.5f, "Vehicle Reload Time");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->VerticalLaunchAdjustment, &ped_weapon_mgr->WeaponInfo->VerticalLaunchAdjustment, -1000.0f, 1000.0f, 0.5f, "Vertical Launch Adjustment");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->WeaponRange, &ped_weapon_mgr->WeaponInfo->WeaponRange, -1000.0f, 1000.0f, 0.5f, "Weapon Range");
					add_editor_option(true, ped_weapon_mgr->WeaponInfo->ZoomFactorForAccurateMode, &ped_weapon_mgr->WeaponInfo->ZoomFactorForAccurateMode, -1000.0f, 1000.0f, 0.5f, "Zoom Factor For Accurate Mode");
				}
				else {
					// info fail
				}
			}
			else {
				// mgr fail
			}
		}
		else {
			// ped fail
		}
	}
	else {
		// factory fail
	}
}
void menu_weapon_bullet_changer() {
	add_string_array_option(true, g_weapon_bullet_types, ARRAYSIZE(g_weapon_bullet_types), &g_weapon_bullet_changer_selected_arr_index, OBFUSCATE("Type"));
	add_editor_option(true, g_weapon_bullet_changer_speed, &g_weapon_bullet_changer_speed, 1.0f, 10000.0f, 1.0f, OBFUSCATE("Speed"));
	add_toggle_option(&g_weapon_bullet_changer_audible, OBFUSCATE("Audible"));
	add_toggle_option(&g_weapon_bullet_changer_invisible, OBFUSCATE("Invisible"));
	add_toggle_option(&g_weapon_bullet_changer, OBFUSCATE("Active"));
}
void menu_weapon_bullet_gravity() {
	add_toggle_option(&g_weapon_special_gravity, OBFUSCATE("Gravity Gun"));
	add_string_array_option(true, g_weapon_gravity_entity_type, ARRAYSIZE(g_weapon_gravity_entity_type), &g_weapon_gravity_entity, OBFUSCATE("Entity Type"));
	add_break_option(OBFUSCATE("Configuration"));
	add_editor_option(true, g_weapon_gravity_distance, &g_weapon_gravity_distance, 10.0f, 1000.0f, 1.0f, OBFUSCATE("Distance"));
	add_editor_option(true, g_weapon_gravity_sling_force, &g_weapon_gravity_sling_force, 100.0f, 1000.0f, 1.0f, OBFUSCATE("Shoot Force"));
}
void menu_weapon_bullet_vortex() {
	add_toggle_option(&g_vortex_gun_active, OBFUSCATE("Vortex Gun"));
	add_editor_toggle_option(&g_vortex_gun_grab_objects, g_vortex_gun_object_capacity, &g_vortex_gun_object_capacity, 5, 15, 1, OBFUSCATE("Grab Objects"));
	add_editor_toggle_option(&g_vortex_gun_grab_vehicles, g_vortex_gun_vehicle_capacity, &g_vortex_gun_vehicle_capacity, 5, 15, 1, OBFUSCATE("Grab Vehicles"));
	add_editor_toggle_option(&g_vortex_gun_grab_peds, g_vortex_gun_ped_capacity, &g_vortex_gun_ped_capacity, 5, 15, 1, OBFUSCATE("Grab Peds"));
	add_break_option(OBFUSCATE("Configuration"));
	add_editor_option(true, g_vortex_gun_distance, &g_vortex_gun_distance, 10.0f, 100.0f, 1.0f, OBFUSCATE("Distance"));
	add_editor_option(true, g_vortex_gun_force, &g_vortex_gun_force, 100.0f, 1000.0f, 10.0f, OBFUSCATE("Shoot Force"));
}
void menu_weapon_totem_gun() {
	add_toggle_option(&g_weapon_totem_gun, "Totem Gun");
	add_break_option(OBFUSCATE("Configuration"));
	add_editor_option(true, g_weapon_totem_gun_distance, &g_weapon_totem_gun_distance, 1.0f, 100.0f, 1.0f, OBFUSCATE("Distance"));
	add_editor_option(true, g_weapon_totem_gun_spacing, &g_weapon_totem_gun_spacing, 1.0f, 50.0f, 1.0f, OBFUSCATE("Spacing"));
}
void menu_weapon_special() {
	add_submenu_option(menu_weapon_bullet_gravity, OBFUSCATE("Gravity Gun"));
	add_submenu_option(menu_weapon_bullet_vortex, OBFUSCATE("Vortex Gun"));
	add_submenu_option(menu_weapon_totem_gun, OBFUSCATE("Totem Gun"));
	add_toggle_option(&g_weapon_special_grapple, "Fly Gun");
	add_toggle_option(&g_weapon_special_teleport, OBFUSCATE("Teleport Gun"));
	add_toggle_option(&g_weapon_special_delete, OBFUSCATE("Delete Gun"));
	add_toggle_option(&g_weapon_special_vehicle, OBFUSCATE("Vehicle Gun"));
	add_toggle_option(&g_weapon_special_shotgun, OBFUSCATE("Shotgun Weapon"));
	add_toggle_option(&g_weapon_special_rubber_bullets, OBFUSCATE("Rubber Bullets"));
}
void menu_weapon_tints_mk2() {
	if (add_text_option(OBFUSCATE("Classic Black"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 0);
	if (add_text_option(OBFUSCATE("Classic Gray"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 1);
	if (add_text_option(OBFUSCATE("Classic Two-Tone"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 2);
	if (add_text_option(OBFUSCATE("Classic White"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 3);
	if (add_text_option(OBFUSCATE("Classic Beige"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 4);
	if (add_text_option(OBFUSCATE("Classic Green"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 5);
	if (add_text_option(OBFUSCATE("Classic Blue"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 6);
	if (add_text_option(OBFUSCATE("Classic Earth"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 7);
	if (add_text_option(OBFUSCATE("Classic Brown & Black"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 8);
	if (add_text_option(OBFUSCATE("Contrast Red"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 9);
	if (add_text_option(OBFUSCATE("Contrast Blue"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 10);
	if (add_text_option(OBFUSCATE("Contrast Yellow"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 11);
	if (add_text_option(OBFUSCATE("Contrast Orange"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 12);
	if (add_text_option(OBFUSCATE("Bold Pink"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 13);
	if (add_text_option(OBFUSCATE("Bold Purple & Yellow"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 14);
	if (add_text_option(OBFUSCATE("Bold Orange"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 15);
	if (add_text_option(OBFUSCATE("Bold Green & Purple"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 16);
	if (add_text_option(OBFUSCATE("Bold Red Features"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 17);
	if (add_text_option(OBFUSCATE("Bold Green Features"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 18);
	if (add_text_option(OBFUSCATE("Bold Cyan Features"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 19);
	if (add_text_option(OBFUSCATE("Bold Yellow Features"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 20);
	if (add_text_option(OBFUSCATE("Bold Red & White"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 21);
	if (add_text_option(OBFUSCATE("Bold Blue & White"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 22);
	if (add_text_option(OBFUSCATE("Metallic Gold"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 23);
	if (add_text_option(OBFUSCATE("Metallic Platinum"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 24);
	if (add_text_option(OBFUSCATE("Metallic Gray & Lilac"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 25);
	if (add_text_option(OBFUSCATE("Metallic Purple & Lime"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 26);
	if (add_text_option(OBFUSCATE("Metallic Red"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 27);
	if (add_text_option(OBFUSCATE("Metallic Green"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 28);
	if (add_text_option(OBFUSCATE("Metallic Blue"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 29);
	if (add_text_option(OBFUSCATE("Metallic White & Aqua"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 30);
	if (add_text_option(OBFUSCATE("Metallic Red & Yellow"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 31);
}
void menu_weapon_tints() {
	if (add_text_option(OBFUSCATE("Default"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 0);
	if (add_text_option(OBFUSCATE("Green"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 1);
	if (add_text_option(OBFUSCATE("Gold"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 2);
	if (add_text_option(OBFUSCATE("Pink"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 3);
	if (add_text_option(OBFUSCATE("Army"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 4);
	if (add_text_option(OBFUSCATE("LSPD"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 5);
	if (add_text_option(OBFUSCATE("Orange"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 6);
	if (add_text_option(OBFUSCATE("Platinum"))) WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), 7);
	add_submenu_option(menu_weapon_tints_mk2, "MK2 Tints");
}
void menu_weapon() {
	if (add_text_option(OBFUSCATE("Give All Weapons"))) {
		give_all_weapons(PLAYER::PLAYER_PED_ID());
		print_notification(7000, "~g~Success:~s~ Gave All Weapons to Player Ped.");
	}
	if (add_toggle_option(&g_weapon_unlimited_ammo, OBFUSCATE("Unlimited Ammo")))
		if (!g_weapon_unlimited_ammo)
			WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), FALSE);
	add_submenu_option(menu_weapon_xml_editor, OBFUSCATE("Weapon Editor"));
	add_submenu_option(menu_weapon_bullet_changer, OBFUSCATE("Bullet Changer"));
	add_submenu_option(menu_weapon_special, OBFUSCATE("Special Weapons"));
	add_submenu_option(menu_weapon_tints, OBFUSCATE("Tints"));
	add_string_array_toggle_option(&g_weapon_explosive_impact, explosion_types, ARRAYSIZE(explosion_types), &g_weapon_explosive_impact_type, OBFUSCATE("Exp. Impact"));
	add_toggle_option(&g_weapon_no_reload, OBFUSCATE("No Reload"));
	add_toggle_option(&g_weapon_quick_reload, OBFUSCATE("Quick Reload"));
	add_toggle_option(&g_weapon_laser_sight, OBFUSCATE("Laser Sight"));
	add_toggle_option(&g_weapon_no_recoil, OBFUSCATE("No Recoil"));
	if (add_text_option(OBFUSCATE("No Stun Gun Cooldown")))
		g_weapon_no_stun_gun_cooldown = true;
	if (add_toggle_option(&g_weapon_dead_eye, OBFUSCATE("Dead Eye"))){
		if (!g_weapon_dead_eye)
			GAMEPLAY::SET_TIME_SCALE(1.00f);
	}
}

void menu_network_streamer_mode() {
	add_keyboard_option(true, &g_network_streamer_mode_prefix, 10, OBFUSCATE("Prefix"));
	add_toggle_option(&g_network_streamer_mode_self_included, OBFUSCATE("Self Included"));
	add_toggle_option(&g_network_streamer_mode_display_as_hex, OBFUSCATE("Display As Hex"));
	add_toggle_option(&g_network_streamer_mode_active, OBFUSCATE("Active"));
}
void menu_network_spoofing_name() {
	add_keyboard_option(true, &g_menu_network_spoofing_name, 16, OBFUSCATE("Set Name"));
	add_toggle_option(&g_menu_network_spoofing_name_active, OBFUSCATE("Active"));
}
void menu_network_spoofing_rid() {
	add_keyboard_option(true, &g_menu_network_spoofing_rid, 19, OBFUSCATE("Set RID"));
	add_toggle_option(&g_menu_network_spoofing_rid_active, OBFUSCATE("Active"));
}
void menu_network_spoof_network_info() {
	add_submenu_option(menu_network_spoofing_name, OBFUSCATE("Name Spoofer"));
	//add_submenu_option(menu_network_spoofing_rid, OBFUSCATE("RID Spoofer"));
}
void menu_network_lobby_options() {
	//if (NETWORK::NETWORK_IS_IN_SESSION()) {
	//	g_network_lobby_host_migration_queue.clear();
	//	for (auto i = 0; i < 32; i++) {
	//		if (!NETWORK::NETWORK_IS_PLAYER_ACTIVE(i))
	//			continue;
	//		if (is_player_session_host(i))
	//			continue;
	//		const char* name_ptr = PLAYER::GET_PLAYER_NAME(i);
	//		if (name_ptr == nullptr)
	//			continue;
	//		std::uint64_t player_key = *(std::uint64_t*)(name_ptr - 0x24);
	//		if (player_key == NULL)
	//			continue;
	//		g_network_lobby_host_migration_queue.push_back(std::make_pair(player_key, i));
	//	}
	//	std::sort(g_network_lobby_host_migration_queue.begin(), g_network_lobby_host_migration_queue.end());
	//	add_info_box_title("Host Migration Queue");
	//	for (auto i = 0; i < g_network_lobby_host_migration_queue.size(); i++) {
	//		std::stringstream ss;
	//		ss << "Pos. " << i + 1;
	//		add_data_to_info_box(ss.str(), PLAYER::GET_PLAYER_NAME(g_network_lobby_host_migration_queue.at(i).second));
	//	}
	//	draw_rect((g_menu_banner_pos_x >= 0.5f) ? (g_menu_banner_pos_x - (g_menu_banner_size_x / 2) - (g_info_box_title_width / 2)) : (g_menu_banner_pos_x + (g_menu_banner_size_x / 2) + (g_info_box_title_width / 2)), ((g_menu_banner_pos_y - ((g_menu_banner_size_y / 2)) + (g_info_box_title_length / 2)) + (g_info_box_title_length / 2)) + ((g_info_box_count * (g_info_box_title_length / 2)) / 2) + 0.0035f, g_info_box_title_width, (g_info_box_count * (g_info_box_title_length / 2)) + 0.007f, g_menu_background_colour);
	//	g_info_box_count = NULL;
	//}
}
void menu_network_friends_list() {
	std::int32_t friend_count = NETWORK::NETWORK_GET_FRIEND_COUNT();
	for (std::int32_t i = 0; i < friend_count; i++) {
		const char* raw_name = NETWORK::NETWORK_GET_FRIEND_NAME(i);
		if (raw_name != nullptr) {
			std::string name(raw_name);
			if (NETWORK::NETWORK_IS_FRIEND_INDEX_ONLINE(i)) {
				name += " ~g~[ONLINE]";
				if (NETWORK::NETWORK_IS_FRIEND_IN_SAME_TITLE(raw_name)) {
					name += " ~p~[GTA V]";
					if (NETWORK::NETWORK_IS_FRIEND_IN_MULTIPLAYER(raw_name)) {
						name += " ~b~[MP]";
					}
					else {
						name += " ~y~[SP]";
					}
				}
			}
			else {
				name += " ~c~[OFFLINE]";
			}
			if (add_text_option(name)) {
				//std::uint64_t* buffer = std::make_unique<std::uint64_t[]>(13).get();
				//NETWORK::NETWORK_HANDLE_FROM_FRIEND(i, reinterpret_cast<std::int32_t*>(buffer), 13);
				//NETWORK::NETWORK_SHOW_PROFILE_UI(reinterpret_cast<std::int32_t*>(buffer));
			}
		}
	}
}
void menu_network_player_chat_commands() {
	if (add_toggle_option(&g_chat_command_clients[g_network_selected_player].m_has_access, OBFUSCATE("Privileges"))) {
		if (g_chat_command_clients[g_network_selected_player].m_has_access) {
			std::string s = "~r~Chat Cmd~s~\nFor commands, type ~b~help~s~ in chat.";
			std::int32_t handle[26];
			NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_network_selected_player, &handle[0], 13);
			NETWORK::NETWORK_SEND_TEXT_MESSAGE(s.c_str(), &handle[0]);
		}
		else {
			std::string s = "~r~Chat Cmd~s~\nYour privileges have been revoked.";
			std::int32_t handle[26];
			NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_network_selected_player, &handle[0], 13);
			NETWORK::NETWORK_SEND_TEXT_MESSAGE(s.c_str(), &handle[0]);
		}
	}
	add_break_option(OBFUSCATE("Override"));
	for (INT i = 0; i < ARRAYSIZE(g_chat_commands); i++) {
		if (add_toggle_option(&g_chat_command_clients[g_network_selected_player].m_mod_active[i], g_chat_commands[i]))
		{
			if (g_chat_commands[i] == "/help") {
				std::stringstream ss;
				std::int32_t handle[26];
				ss << "~b~Chat Cmd:~s~ You sent /help, listing all usable commands: /help and /semigod";
				NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_network_selected_player, &handle[0], 13);
				NETWORK::NETWORK_SEND_TEXT_MESSAGE(ss.str().c_str(), &handle[0]);
				ss.str("");
				ss.clear();
				ss << "~b~Chat Cmd: " << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << " sent /help, sending message with all usable commands to said player.";
				print_notification(7000, ss.str());
			}
			if (g_chat_commands[i] == "/semigod") {
				std::uint32_t hash = GAMEPLAY::GET_HASH_KEY("prop_juicestand");
				std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, 0.0f, 0.0f, 0.0f);
				std::int32_t object = spawn_object("prop_juicestand", coords, FALSE);
				if (ENTITY::DOES_ENTITY_EXIST(object)) {
					ENTITY::ATTACH_ENTITY_TO_ENTITY(object, ped, PED::GET_PED_BONE_INDEX(ped, 31086), 0.1f, 0.02f, 0.0f, 0.0f, 90.0f, 0.0f, FALSE, FALSE, FALSE, FALSE, 2, TRUE);
					ENTITY::SET_ENTITY_VISIBLE(object, FALSE, 0);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
					std::stringstream ss;
					ss << "~g~Success:~s~ ~b~Semi-God Mode~s~ given to ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~.";
					print_notification(7000, ss.str());
				}
			}
		}
	}
}
void menu_network_player_explosions_looped() {
	add_string_array_option(true, explosion_types, ARRAYSIZE(explosion_types), &g_network_player_vars[g_network_selected_player].m_looped_explosion_selected_arr_index, OBFUSCATE("Type"));
	add_editor_option(true, g_network_player_vars[g_network_selected_player].m_looped_explosion_offset.x, &g_network_player_vars[g_network_selected_player].m_looped_explosion_offset.x, -10000.0f, 10000.0f, 0.05f, OBFUSCATE("Offset ~c~(X)"));
	add_editor_option(true, g_network_player_vars[g_network_selected_player].m_looped_explosion_offset.y, &g_network_player_vars[g_network_selected_player].m_looped_explosion_offset.y, -10000.0f, 10000.0f, 0.05f, OBFUSCATE("Offset ~c~(Y)"));
	add_editor_option(true, g_network_player_vars[g_network_selected_player].m_looped_explosion_offset.z, &g_network_player_vars[g_network_selected_player].m_looped_explosion_offset.z, -10000.0f, 10000.0f, 0.05f, OBFUSCATE("Offset ~c~(Z)"));
	add_toggle_option(&g_network_player_vars[g_network_selected_player].m_looped_explosion_audible, OBFUSCATE("Audible"));
	add_toggle_option(&g_network_player_vars[g_network_selected_player].m_looped_explosion_invisible, OBFUSCATE("Invisible"));
	add_toggle_option(&g_network_player_vars[g_network_selected_player].m_looped_explosion_active, OBFUSCATE("Active"));
}
void menu_network_player_explosions() {
	add_submenu_option(menu_network_player_explosions_looped, OBFUSCATE("Looped Explosions"));
	add_break_option(OBFUSCATE("Visible & Audible One-Shot"));
	for (std::int32_t i = 0; i < ARRAYSIZE(explosion_types); i++) {
		if (add_text_option(explosion_types[i])) {
			std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
			if (ENTITY::DOES_ENTITY_EXIST(ped)) {
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, 0.0f, 0.0f, 0.0f);
				FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, i, FLT_MAX, TRUE, FALSE, 0.2f);
			}
		}
	}
}
void menu_network_trolling_options() {
	add_submenu_option(menu_network_player_explosions, OBFUSCATE("Explosions"));
	add_toggle_option(&g_network_player_vars[g_network_selected_player].m_freeze_loop, OBFUSCATE("Freeze Loop"));
	add_toggle_option(&g_network_player_vars[g_network_selected_player].m_take_weapons, OBFUSCATE("Take Weapons Loop"));
	if (add_text_option(OBFUSCATE("Trap In Cage ~c~(Female)"))) {
		std::int32_t object = spawn_object("prop_gold_cont_01", ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player), 0.0f, 0.0f, 0.0f), false);
		if (ENTITY::DOES_ENTITY_EXIST(object))
			ENTITY::FREEZE_ENTITY_POSITION(object, true);
	}
	if (add_text_option("Infinite Load Screen")) {
		Any args[] = { -125347541, g_network_selected_player, 0, -1, 1, 115, 0, 0, 0 };
		SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, (std::size(args)), 1 << g_network_selected_player);
	}
	if (add_text_option("Black Screen")) {
		Any args[] = { -1246838892, g_network_selected_player, 4, 4566469881341411328, 4528819783743622349, 0, 1, 1, 1062333317 };
		SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, (std::int32_t)(std::size(args)), 1 << g_network_selected_player);
	}
	if (add_text_option("Force Into Mission")) {
		Any args[] = { -327286343, g_network_selected_player };
		SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, (std::int32_t)(std::size(args)), 1 << g_network_selected_player);
	}
	if (add_text_option("Teleport To Eclipse Towers")) {
		Any args[] = { -125347541, g_network_selected_player, 0, -1, 1, 1, 0, 0, 0 };
		SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, (std::int32_t)(std::size(args)), 1 << g_network_selected_player);
	}
	if (add_text_option("Teleport To Las Apartment")) {
		Any args[] = { -125347541, g_network_selected_player, 0, -1, 1, 10, 0, 0, 0 };
		SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, (std::int32_t)(std::size(args)), 1 << g_network_selected_player);
	}
	if (add_text_option("Teleport To Spanish Apartment")) {
		Any args[] = { -125347541, g_network_selected_player, 0, -1, 1, 9, 0, 0, 0 };
		SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, (std::int32_t)(std::size(args)), 1 << g_network_selected_player);
	}
	if (add_text_option("Teleport To Power Apartment")) {
		Any args[] = { -125347541, g_network_selected_player, 0, -1, 1, 8, 0, 0, 0 };
		SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, (std::int32_t)(std::size(args)), 1 << g_network_selected_player);
	}
	if (add_text_option("Teleport To Del Perro Apartment")) {
		Any args[] = { -125347541, g_network_selected_player, 0, -1, 1, 7, 0, 0, 0 };
		SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, (std::int32_t)(std::size(args)), 1 << g_network_selected_player);
	}
	if (add_text_option("Teleport To Alta St. Apartment")) {
		Any args[] = { -125347541, g_network_selected_player, 0, -1, 1, 6, 0, 0, 0 };
		SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, (std::int32_t)(std::size(args)), 1 << g_network_selected_player);
	}
}
void menu_network_vehicle_spawner_spawn() {
	ListPool* model_info_pool = (ListPool*)(GTA_MODEL_INFO_LIST_POOL);
	if (model_info_pool != nullptr) {
		for (std::int32_t i = 0; i < model_info_pool->capacity; i++) {
			std::uint64_t info = model_info_pool->get(i);
			if (info != NULL) {
				if ((*(BYTE*)(info + 157) & 0x1F) == 5) {
					char* make_ptr = (char*)(info + 0x2A4);
					char* model_ptr = (char*)(info + 0x298);
					if (VEHICLE::GET_VEHICLE_CLASS_FROM_NAME(GAMEPLAY::GET_HASH_KEY(model_ptr)) == g_vehicle_spawner_selected_class) {
						std::stringstream ss;
						std::string make(make_ptr);
						std::string model(model_ptr);

						if (make[0] || model[0]) {
							make = UI::_GET_LABEL_TEXT(make.c_str());
							model = UI::_GET_LABEL_TEXT(model.c_str());

							if (make != "NULL" && model != "NULL") {
								ss << make << " " << model;
							}
							else if (model != "NULL") {
								ss << model;
							}
							else {
								ss << "~c~Unknown";
							}
						}

						if (add_text_option(ss.str())) {
							std::int32_t vehicle = spawn_vehicle(*(std::uint32_t*)(info + 0x18), PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player));
							VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle, 0.0f);
							VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
							VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 3, 0, 0);
							VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 66, 225, 221);
							VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 10, 20, 30);
							VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 3, 5);
							VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, 24, 4);
							VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(vehicle, 0, 0, 0);
							VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle, 5);
							VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(vehicle, "QUANTUM");
							VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, 18, 1);
							VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, 22, 1);
							VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, 20, 1);
							VEHICLE::SET_VEHICLE_MOD(vehicle, 16, 5, 0);
							VEHICLE::SET_VEHICLE_MOD(vehicle, 12, 2, 0);
							VEHICLE::SET_VEHICLE_MOD(vehicle, 11, 3, 0);
							VEHICLE::SET_VEHICLE_MOD(vehicle, 14, 14, 0);
							VEHICLE::SET_VEHICLE_MOD(vehicle, 15, 3, 0);
							VEHICLE::SET_VEHICLE_MOD(vehicle, 13, 2, 0);
							VEHICLE::SET_VEHICLE_WHEEL_TYPE(vehicle, 6);
							VEHICLE::SET_VEHICLE_WINDOW_TINT(vehicle, 5);
							VEHICLE::SET_VEHICLE_MOD(vehicle, 23, 19, 1);
							VEHICLE::SET_VEHICLE_MOD(vehicle, 0, 1, 0);
							VEHICLE::SET_VEHICLE_MOD(vehicle, 1, 1, 0);
							VEHICLE::SET_VEHICLE_MOD(vehicle, 2, 1, 0);
							VEHICLE::SET_VEHICLE_MOD(vehicle, 3, 1, 0);
							VEHICLE::SET_VEHICLE_MOD(vehicle, 4, 1, 0);
							VEHICLE::SET_VEHICLE_MOD(vehicle, 5, 1, 0);
							VEHICLE::SET_VEHICLE_MOD(vehicle, 6, 1, 0);
							VEHICLE::SET_VEHICLE_MOD(vehicle, 7, 1, 0);
							VEHICLE::SET_VEHICLE_MOD(vehicle, 8, 1, 0);
							VEHICLE::SET_VEHICLE_MOD(vehicle, 9, 1, 0);
							VEHICLE::SET_VEHICLE_MOD(vehicle, 10, 1, 0);
						}
					}
				}
			}
		}
	}
}
void menu_network_vehicle_spawner() {
	for (std::int32_t i = 0; i < 22; i++) {
		if (add_submenu_option(menu_network_vehicle_spawner_spawn, get_vehicle_class_name(i))) {
			g_vehicle_spawner_selected_class = i;
		}
	}
}
void menu_network_vehicle_manager() {
	add_submenu_option(menu_network_vehicle_spawner, OBFUSCATE("Vehicle Spawner"));
	add_toggle_option(&g_network_player_vars[g_network_selected_player].m_horn_boost_active, "Horn Boost");
	add_break_option("Vehicle Manipulation");
	if (add_text_option(OBFUSCATE("Kick From Vehicle"))) {
		std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {
			if (PED::IS_PED_IN_ANY_VEHICLE(ped, TRUE)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
				if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
					if (change_net_obj_owner(vehicle, PLAYER::PLAYER_ID())) {
						AI::CLEAR_PED_TASKS_IMMEDIATELY(ped);
						std::stringstream ss;
						ss << "~g~Success:~s~ Kicked ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~ from their vehicle.";
						print_notification(7000, ss.str());
					}
				}
			}
			else {
				std::stringstream ss;
				ss << "~r~Error:~s~ ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~ is not in a vehicle.";
				print_notification(7000, ss.str());
			}
		}
	}
	if (add_text_option(OBFUSCATE("Teleport Into Vehicle"))) {
		std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {
			if (PED::IS_PED_IN_ANY_VEHICLE(ped, TRUE)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
				if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
					std::int32_t seat_index = -1;
					std::int32_t max_index = VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(vehicle);
					while (seat_index < max_index) {
						if (VEHICLE::IS_VEHICLE_SEAT_FREE(vehicle, seat_index)) {
							PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, seat_index);
							std::stringstream ss;
							ss << "~g~Success:~s~ Teleported into ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~'s vehicle.";
							print_notification(7000, ss.str());
						}
						else {
							seat_index++;
						}
					}
				}
			}
			else {
				std::stringstream ss;
				ss << "~r~Error:~s~ ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~ is not in a vehicle.";
				print_notification(7000, ss.str());
			}
		}
	}
	if (add_text_option(OBFUSCATE("Teleport Above You"))) {
		std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {
			if (PED::IS_PED_IN_ANY_VEHICLE(ped, TRUE)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
				if (change_net_obj_owner(vehicle, PLAYER::PLAYER_ID())) {
					Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, 0.0f, 12.0f);
					ENTITY::SET_ENTITY_COORDS(vehicle, coords.x, coords.y, coords.z, 0, 0, 0, 1);
					std::stringstream ss;
					ss << "~g~Success:~s~ Teleported ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~'s vehicle above you.";
					print_notification(7000, ss.str());
				}
			}
			else {
				std::stringstream ss;
				ss << "~r~Error:~s~ ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~ is not in a vehicle.";
				print_notification(7000, ss.str());
			}
		}
	}
	if (add_text_option(OBFUSCATE("Stall Engine"))) {
		std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {
			if (PED::IS_PED_IN_ANY_VEHICLE(ped, TRUE)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
				if (change_net_obj_owner(vehicle, PLAYER::PLAYER_ID())) {
					VEHICLE::SET_VEHICLE_ENGINE_HEALTH(vehicle, 0.0f);
					VEHICLE::SET_VEHICLE_UNDRIVEABLE(vehicle, TRUE);
					std::stringstream ss;
					ss << "~g~Success:~s~ Stalled ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~'s vehicle engine.";
					print_notification(7000, ss.str());
				}
			}
			else {
				std::stringstream ss;
				ss << "~r~Error:~s~ ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~ is not in a vehicle.";
				print_notification(7000, ss.str());
			}
		}
	}
	if (add_text_option(OBFUSCATE("Blow Engine"))) {
		std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {
			if (PED::IS_PED_IN_ANY_VEHICLE(ped, 1)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
				if (change_net_obj_owner(vehicle, PLAYER::PLAYER_ID())) {
					VEHICLE::SET_VEHICLE_ENGINE_HEALTH(vehicle, 0);
					VEHICLE::SET_VEHICLE_UNDRIVEABLE(vehicle, 1);
					std::stringstream ss;
					ss << "~g~Success:~s~ Blown ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~'s vehicle engine.";
					print_notification(7000, ss.str());
				}
			}
			else {
				std::stringstream ss;
				ss << "~r~Error:~s~ ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~ is not in a vehicle.";
				print_notification(7000, ss.str());
			}
		}
	}
	if (add_text_option(OBFUSCATE("Launch"))) {
		std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {
			if (PED::IS_PED_IN_ANY_VEHICLE(ped, 1)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
				if (change_net_obj_owner(vehicle, PLAYER::PLAYER_ID())) {
					ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 1, 0, 0, 1500, 0, 0, 0, 0, 1, 1, 1, false, true);
					std::stringstream ss;
					ss << "~g~Success:~s~ Launched ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~'s vehicle.";
					print_notification(7000, ss.str());
				}
			}
			else {
				std::stringstream ss;
				ss << "~r~Error:~s~ ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~ is not in a vehicle.";
				print_notification(7000, ss.str());
			}
		}
	}
	if (add_text_option(OBFUSCATE("Apply Brake"))) {
		std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {
			if (PED::IS_PED_IN_ANY_VEHICLE(ped, 1)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
				if (change_net_obj_owner(vehicle, PLAYER::PLAYER_ID())) {
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, 0);
					std::stringstream ss;
					ss << "~g~Success:~s~ Brake applied to ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~'s vehicle.";
					print_notification(7000, ss.str());
				}
			}
			else {
				std::stringstream ss;
				ss << "~r~Error:~s~ ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~ is not in a vehicle.";
				print_notification(7000, ss.str());
			}
		}
	}
	if (add_text_option(OBFUSCATE("Apply Boost"))) {
		std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {
			if (PED::IS_PED_IN_ANY_VEHICLE(ped, 1)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
				if (change_net_obj_owner(vehicle, PLAYER::PLAYER_ID())) {
					ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 1, 0, 2000, 0, 0, 0, 0, 0, 1, 1, 1, false, true);
					std::stringstream ss;
					ss << "~g~Success:~s~ Boost applied to ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~'s vehicle.";
					print_notification(7000, ss.str());
				}
			}
			else {
				std::stringstream ss;
				ss << "~r~Error:~s~ ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~ is not in a vehicle.";
				print_notification(7000, ss.str());
			}
		}
	}
	if (add_text_option(OBFUSCATE("Flip 180-Degrees"))) {
		std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {
			if (PED::IS_PED_IN_ANY_VEHICLE(ped, 1)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
				if (change_net_obj_owner(vehicle, PLAYER::PLAYER_ID())) {
					std::float_t heading = ENTITY::GET_ENTITY_HEADING(vehicle);
					if (heading > 180.0f)
						heading -= 180.0f;
					else
						heading += 180.0f;

					ENTITY::SET_ENTITY_HEADING(vehicle, heading);
					ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 1, 0.0f, 1500.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 1, 1, 1, false, true);
					std::stringstream ss;
					ss << "~g~Success:~s~ Flipped ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~'s vehicle.";
					print_notification(7000, ss.str());
				}
			}
			else {
				std::stringstream ss;
				ss << "~r~Error:~s~ ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~ is not in a vehicle.";
				print_notification(7000, ss.str());
			}
		}
	}
	if (add_text_option(OBFUSCATE("Delete"))) {
		std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {
			if (PED::IS_PED_IN_ANY_VEHICLE(ped, 1)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
				if (change_net_obj_owner(vehicle, PLAYER::PLAYER_ID())) {
					AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player));
					ENTITY::SET_ENTITY_COORDS(vehicle, 6000.0f, 6000.0f, 6000.0f, 0, 0, 0, 1);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicle, 1, 1);
					VEHICLE::DELETE_VEHICLE(&vehicle);
					std::stringstream ss;
					ss << "~g~Success:~s~ Deleted ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~'s vehicle.";
					print_notification(7000, ss.str());
				}
			}
			else {
				std::stringstream ss;
				ss << "~r~Error:~s~ ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~ is not in a vehicle.";
				print_notification(7000, ss.str());
			}
		}
	}
	if (add_text_option(OBFUSCATE("Burst Tires"))) {
		std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {
			if (PED::IS_PED_IN_ANY_VEHICLE(ped, 1)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
				if (change_net_obj_owner(vehicle, PLAYER::PLAYER_ID())) {
					VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(vehicle, 1);
					VEHICLE::SET_VEHICLE_TYRE_BURST(vehicle, 0, 1, 1148846080);
					VEHICLE::SET_VEHICLE_TYRE_BURST(vehicle, 1, 1, 1148846080);
					VEHICLE::SET_VEHICLE_TYRE_BURST(vehicle, 2, 1, 1148846080);
					VEHICLE::SET_VEHICLE_TYRE_BURST(vehicle, 3, 1, 1148846080);
					VEHICLE::SET_VEHICLE_TYRE_BURST(vehicle, 4, 1, 1148846080);
					VEHICLE::SET_VEHICLE_TYRE_BURST(vehicle, 5, 1, 1148846080);
					VEHICLE::SET_VEHICLE_TYRE_BURST(vehicle, 6, 1, 1148846080);
					VEHICLE::SET_VEHICLE_TYRE_BURST(vehicle, 7, 1, 1148846080);
					std::stringstream ss;
					ss << "~g~Success:~s~ Burst ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~'s vehicle tires.";
					print_notification(7000, ss.str());
				}
			}
			else {
				std::stringstream ss;
				ss << "~r~Error:~s~ ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~ is not in a vehicle.";
				print_notification(7000, ss.str());
			}
		}
	}
	if (add_text_option(OBFUSCATE("Lock Doors"))) {
		std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {
			if (PED::IS_PED_IN_ANY_VEHICLE(ped, 1)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
				if (change_net_obj_owner(vehicle, PLAYER::PLAYER_ID())) {
					VEHICLE::SET_VEHICLE_DOORS_LOCKED(vehicle, 2);
					std::stringstream ss;
					ss << "~g~Success:~s~ Locked ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~'s vehicle doors.";
					print_notification(7000, ss.str());
				}
			}
			else {
				std::stringstream ss;
				ss << "~r~Error:~s~ ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~ is not in a vehicle.";
				print_notification(7000, ss.str());
			}
		}
	}
	if (add_text_option(OBFUSCATE("Unlock Doors"))) {
		std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {
			if (PED::IS_PED_IN_ANY_VEHICLE(ped, 1)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
				if (change_net_obj_owner(vehicle, PLAYER::PLAYER_ID())) {
					VEHICLE::SET_VEHICLE_DOORS_LOCKED(vehicle, 1);
					std::stringstream ss;
					ss << "~g~Success:~s~ Unlocked ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~'s vehicle doors.";
					print_notification(7000, ss.str());
				}
			}
			else {
				std::stringstream ss;
				ss << "~r~Error:~s~ ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~ is not in a vehicle.";
				print_notification(7000, ss.str());
			}
		}
	}
	if (add_text_option(OBFUSCATE("Fix & Wash"))) {
		std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {
			if (PED::IS_PED_IN_ANY_VEHICLE(ped, 1)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
				if (change_net_obj_owner(vehicle, PLAYER::PLAYER_ID())) {
					VEHICLE::SET_VEHICLE_FIXED(vehicle);
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle, 0.0f);
					std::stringstream ss;
					ss << "~g~Success:~s~ Fixed & washed ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~'s vehicle.";
					print_notification(7000, ss.str());
				}
			}
			else {
				std::stringstream ss;
				ss << "~r~Error:~s~ ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~ is not in a vehicle.";
				print_notification(7000, ss.str());
			}
		}
	}
	if (add_text_option(OBFUSCATE("Install Stock Parts"))) {
		std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {
			if (PED::IS_PED_IN_ANY_VEHICLE(ped, 1)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
				if (change_net_obj_owner(vehicle, PLAYER::PLAYER_ID())) {
					VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(vehicle, "QUANTUM");
					VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, 18, 1);
					VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, 22, 1);
					VEHICLE::SET_VEHICLE_MOD(vehicle, 16, 0, 0);
					VEHICLE::SET_VEHICLE_MOD(vehicle, 12, 0, 0);
					VEHICLE::SET_VEHICLE_MOD(vehicle, 11, 0, 0);
					VEHICLE::SET_VEHICLE_MOD(vehicle, 15, 0, 0);
					VEHICLE::SET_VEHICLE_MOD(vehicle, 13, 0, 0);
					std::stringstream ss;
					ss << "~g~Success:~s~ ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~'s vehicle now has stock upgrades.";
					print_notification(7000, ss.str());
				}
			}
			else {
				std::stringstream ss;
				ss << "~r~Error:~s~ ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~ is not in a vehicle.";
				print_notification(7000, ss.str());
			}
		}
	}
	if (add_text_option(OBFUSCATE("Install Max Upgrades"))) {
		std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {
			if (PED::IS_PED_IN_ANY_VEHICLE(ped, 1)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
				if (change_net_obj_owner(vehicle, PLAYER::PLAYER_ID())) {
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle, 0.0f);
					VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
					VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 3, 0, 0);
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 66, 225, 221);
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 10, 20, 30);
					VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 3, 5);
					VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, 24, 4);
					VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(vehicle, 0, 0, 0);
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle, 5);
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(vehicle, "QUANTUM");
					VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, 18, 1);
					VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, 22, 1);
					VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, 20, 1);
					VEHICLE::SET_VEHICLE_MOD(vehicle, 16, 5, 0);
					VEHICLE::SET_VEHICLE_MOD(vehicle, 12, 2, 0);
					VEHICLE::SET_VEHICLE_MOD(vehicle, 11, 3, 0);
					VEHICLE::SET_VEHICLE_MOD(vehicle, 14, 14, 0);
					VEHICLE::SET_VEHICLE_MOD(vehicle, 15, 3, 0);
					VEHICLE::SET_VEHICLE_MOD(vehicle, 13, 2, 0);
					VEHICLE::SET_VEHICLE_WHEEL_TYPE(vehicle, 6);
					VEHICLE::SET_VEHICLE_WINDOW_TINT(vehicle, 5);
					VEHICLE::SET_VEHICLE_MOD(vehicle, 23, 19, 1);
					VEHICLE::SET_VEHICLE_MOD(vehicle, 0, 1, 0);
					VEHICLE::SET_VEHICLE_MOD(vehicle, 1, 1, 0);
					VEHICLE::SET_VEHICLE_MOD(vehicle, 2, 1, 0);
					VEHICLE::SET_VEHICLE_MOD(vehicle, 3, 1, 0);
					VEHICLE::SET_VEHICLE_MOD(vehicle, 4, 1, 0);
					VEHICLE::SET_VEHICLE_MOD(vehicle, 5, 1, 0);
					VEHICLE::SET_VEHICLE_MOD(vehicle, 6, 1, 0);
					VEHICLE::SET_VEHICLE_MOD(vehicle, 7, 1, 0);
					VEHICLE::SET_VEHICLE_MOD(vehicle, 8, 1, 0);
					VEHICLE::SET_VEHICLE_MOD(vehicle, 9, 1, 0);
					VEHICLE::SET_VEHICLE_MOD(vehicle, 10, 1, 0);
					std::stringstream ss;
					ss << "~g~Success:~s~ ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~'s vehicle now has max upgrades.";
					print_notification(7000, ss.str());
				}
			}
			else {
				std::stringstream ss;
				ss << "~r~Error:~s~ ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~ is not in a vehicle.";
				print_notification(7000, ss.str());
			}
		}
	}
	if (add_text_option(OBFUSCATE("Invincibility"))) {
		std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {
			if (PED::IS_PED_IN_ANY_VEHICLE(ped, 1)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
				if (change_net_obj_owner(vehicle, PLAYER::PLAYER_ID())) {
					ENTITY::SET_ENTITY_INVINCIBLE(vehicle, true);
					ENTITY::SET_ENTITY_PROOFS(vehicle, true, true, true, true, true, false, false, false);
					ENTITY::SET_ENTITY_CAN_BE_DAMAGED(vehicle, false);
					std::stringstream ss;
					ss << "~g~Success:~s~ ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~'s vehicle is now invincible.";
					print_notification(7000, ss.str());
				}
			}
			else {
				std::stringstream ss;
				ss << "~r~Error:~s~ ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~ is not in a vehicle.";
				print_notification(7000, ss.str());
			}
		}
	}
}
void menu_network_attachment_manager_manage_attached_manage_entity() {
	if (ENTITY::DOES_ENTITY_EXIST(g_selected_menu_network_attachment_manager_manage_attached_manage_entity)) {
		if (add_text_option("Detach")) {
			ENTITY::DETACH_ENTITY(g_selected_menu_network_attachment_manager_manage_attached_manage_entity, TRUE, TRUE);
		}
	}
	else {
		add_text_option("Entity Invalid");
	}
}
void menu_network_attachment_manager_manage_attached() {
	std::uint64_t pool = *(uint64_t*)(GTA_ATTACHMENT_EXTENSION_INST_POOL);
	if (pool) {
		std::uint32_t pool_size = *(uint32_t*)(pool + 0x10);
		g_network_attachment_manager_manage_attached_count = NULL;
		for (std::uint32_t i = 0; i < pool_size; i++) {
			std::uint64_t extension = get_element_from_pool(pool, i);
			if (extension) {
				std::uint64_t parent_entity = *(std::uint64_t*)(extension);
				if (parent_entity == NULL)
					continue;
				g_network_attachment_manager_manage_attached_count++;
			}
		}
		if (g_network_attachment_manager_manage_attached_count == NULL) {
			add_text_option(OBFUSCATE("No Attachments Found"));
		}
	}
	else {
		add_text_option(OBFUSCATE("Failed To Grab Attachments"));
	}
}
void menu_network_attachment_manager() {
	add_submenu_option(menu_network_attachment_manager_manage_attached, "Manage Attached");
	/*add_break_option("Attach");*/
}
void menu_network_spoofing_options_name() {
	add_keyboard_option(true, &g_network_player_vars[g_network_selected_player].m_spoofing_name, 16, OBFUSCATE("Set Name"));
	if (add_toggle_option(&g_network_player_vars[g_network_selected_player].m_spoofing_name_active, OBFUSCATE("Active"))) {
		if (g_network_player_vars[g_network_selected_player].m_spoofing_name_active) {
			std::stringstream ss;
			ss << "~g~Success:~s~ Anyone who joins will now see ~b~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~'s name as \"~y~" << g_network_player_vars[g_network_selected_player].m_spoofing_name << "~s~\".";
			print_notification(7000, ss.str());
		}
	}
}
void menu_network_spoofing_options() {
	add_submenu_option(menu_network_spoofing_options_name, OBFUSCATE("Name Spoofer"));
}
void menu_network_player() {
	draw_player_info_box(g_network_selected_player);
	if (add_text_option("Set Waypoint To Player")) {
		std::int32_t their_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
		if (ENTITY::DOES_ENTITY_EXIST(their_ped)) {
			Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(their_ped, 0.0f, 0.0f, 0.0f);
			UI::SET_NEW_WAYPOINT(coords.x, coords.y);
			std::stringstream ss;
			ss << "~g~Success:~s~ Set waypoint at ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~'s coordinates.";
			print_notification(7000, ss.str());
		}
	}
	if (add_text_option(OBFUSCATE("Teleport To Player"))) {
		std::int32_t their_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
		if (ENTITY::DOES_ENTITY_EXIST(their_ped)) {
			Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(their_ped, 0.0f, 0.0f, 0.0f);
			teleport_to_position(coords.x, coords.y, coords.z);
			std::stringstream ss;
			ss << "~g~Success:~s~ Teleporting you to ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~...";
			print_notification(7000, ss.str());
		}
	}
	if (add_text_option(OBFUSCATE("Teleport Into Vehicle"))) {
		std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {
			if (PED::IS_PED_IN_ANY_VEHICLE(ped, TRUE)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
				if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
					std::int32_t seat_index = -1;
					std::int32_t max_index = VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(vehicle);
					while (seat_index < max_index) {
						if (VEHICLE::IS_VEHICLE_SEAT_FREE(vehicle, seat_index)) {
							PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, seat_index);
							std::stringstream ss;
							ss << "~g~Success:~s~ Teleported into ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~'s vehicle.";
							print_notification(7000, ss.str());
						}
						else {
							seat_index++;
						}
					}
				}
			}
			else {
				std::stringstream ss;
				ss << "~r~Error:~s~ ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~ is not in a vehicle.";
				print_notification(7000, ss.str());
			}
		}
	}
	if (add_text_option(OBFUSCATE("Kick Player"))) {
		kick_player_disconnect(g_network_selected_player);
	}
	if (add_text_option("Scr Crash")) {
		// TODO: make them host here
		// script event
		Any args[] = { -1256990787, g_network_selected_player, 0 };
		SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, (std::int32_t)(std::size(args)), 1 << g_network_selected_player);
	}
	if (add_text_option("Veh Crash")) {
		crash_online_player_rwea(g_network_selected_player);
	}
	if (add_text_option("Spam Crash")) {
		simple_timer spam_crash_timer;
		{
			spam_crash_timer.start(1500);
			std::int32_t their_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
			if (ENTITY::DOES_ENTITY_EXIST(their_ped)) {
				std::int32_t vehicle = spawn_vehicle(GAMEPLAY::GET_HASH_KEY("jet"), their_ped);
				if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
					VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(vehicle);
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, 100.0f);
					VEHICLE::SET_VEHICLE_CAN_BREAK(vehicle, TRUE);
					VEHICLE::SET_VEHICLE_ENGINE_HEALTH(vehicle, 0.5f);
					ENTITY::SET_ENTITY_HEALTH(vehicle, 0);
					g_network_player_vars[g_network_selected_player].m_spam_crash_entity = vehicle;
					g_network_player_vars[g_network_selected_player].m_do_spam_crash = true;
					while (!spam_crash_timer.is_ready()) {
						Script::GetCurrent()->ScriptYield();
					}
					spam_crash_timer.reset();
				}
			}
		}
		{
			spam_crash_timer.start(1500);
			std::int32_t their_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
			if (ENTITY::DOES_ENTITY_EXIST(their_ped)) {
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(their_ped, 0.0f, 0.0f, 0.0f);
				std::int32_t ped = spawn_ped(GAMEPLAY::GET_HASH_KEY("s_m_m_movalien_01"), coords, 0.0f);
				if (ENTITY::DOES_ENTITY_EXIST(ped)) {
					g_network_player_vars[g_network_selected_player].m_spam_crash_entity = ped;
					g_network_player_vars[g_network_selected_player].m_do_spam_crash = true;
					while (!spam_crash_timer.is_ready()) {
						Script::GetCurrent()->ScriptYield();
					}
					spam_crash_timer.reset();
				}
			}
		}
		{
			spam_crash_timer.start(1500);
			std::int32_t their_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
			if (ENTITY::DOES_ENTITY_EXIST(their_ped)) {
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(their_ped, 0.0f, 0.0f, 0.0f);
				std::int32_t object = spawn_object("prop_juicestand", coords, FALSE);
				if (ENTITY::DOES_ENTITY_EXIST(object)) {
					g_network_player_vars[g_network_selected_player].m_spam_crash_entity = object;
					g_network_player_vars[g_network_selected_player].m_do_spam_crash = true;
					while (!spam_crash_timer.is_ready()) {
						Script::GetCurrent()->ScriptYield();
					}
					spam_crash_timer.reset();
				}
			}
		}
	}
	if (add_toggle_option(&g_network_player_vars[g_network_selected_player].m_spectate_player, "Spectate Player")) {
		for (auto i = 0; i < 32; i++) {
			if (i != g_network_selected_player) {
				g_network_player_vars[i].m_spectate_player = false;
			}
		}
		std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {
			NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(g_network_player_vars[g_network_selected_player].m_spectate_player, ped);
		}
	}
	add_toggle_option(&g_network_player_vars[g_network_selected_player].m_esp_line, "ESP ~c~(Line)");
	add_toggle_option(&g_network_player_vars[g_network_selected_player].m_esp_box, "ESP ~c~(Box)");
	add_toggle_option(&g_network_player_vars[g_network_selected_player].m_esp_name, "ESP ~c~(Name)");
	add_submenu_option(menu_network_trolling_options, OBFUSCATE("Trolling Options"));
	add_submenu_option(menu_network_vehicle_manager, OBFUSCATE("Vehicle Manager"));
	add_submenu_option(menu_network_attachment_manager, OBFUSCATE("Attachment Manager")); // TODO
	//if (is_player_session_host(PLAYER::PLAYER_ID()))
	//	add_submenu_option(menu_network_spoofing_options, OBFUSCATE("Spoofing Options"));
	add_submenu_option(menu_network_player_chat_commands, OBFUSCATE("Chat Commands"));
	if (add_text_option(OBFUSCATE("Copy Their Outfit"))) {
		std::int32_t my_ped = PLAYER::PLAYER_PED_ID();
		std::int32_t their_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
		if (ENTITY::DOES_ENTITY_EXIST(my_ped) && ENTITY::DOES_ENTITY_EXIST(their_ped)) {
			PED::CLONE_PED_TO_TARGET(their_ped, my_ped);
			std::stringstream ss;
			ss << "~g~Success:~s~ Copied ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~'s outfit.";
			print_notification(7000, ss.str());
		}
	}
	if (add_text_option("Give Semi-God Mode")) {
		std::uint32_t hash = GAMEPLAY::GET_HASH_KEY("prop_juicestand");
		std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player);
		Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, 0.0f, 0.0f, 0.0f);
		std::int32_t object = spawn_object("prop_juicestand", coords, FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(object)) {
			ENTITY::ATTACH_ENTITY_TO_ENTITY(object, ped, PED::GET_PED_BONE_INDEX(ped, 31086), 0.1f, 0.02f, 0.0f, 0.0f, 90.0f, 0.0f, FALSE, FALSE, FALSE, FALSE, 2, TRUE);
			ENTITY::SET_ENTITY_VISIBLE(object, FALSE, 0);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
			std::stringstream ss;
			ss << "~g~Success:~s~ ~b~Semi-God Mode~s~ given to ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~.";
			print_notification(7000, ss.str());
		}
	}
	if (add_text_option(OBFUSCATE("Give All Weapons"))) {
		give_all_weapons(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player));
		std::stringstream ss;
		ss << "~g~Success:~s~ ~b~All Weapons~s~ given to ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~.";
		print_notification(7000, ss.str());
	}
	if (add_text_option(OBFUSCATE("Give Ammo"))) {
		if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player), 1)) {
			Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player), 0.0f, 0.0f, 0.0f);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_BULLET_MP"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_MISSILE_MP"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_GRENADELAUNCHER_MP"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_PISTOL"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_SMG"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_RIFLE"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_MG"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_SHOTGUN"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_SNIPER"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_GRENADELAUNCHER"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_RPG"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_MINIGUN"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_FIREWORK_MP"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_HOMINGLAUNCHER"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_FLAREGUN"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
			std::stringstream ss;
			ss << "~g~Success:~s~ ~b~Ammo~s~ given to ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~.";
			print_notification(7000, ss.str());
		}
		else {
			std::stringstream ss;
			ss << "~r~Error:~s~ ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~ is not on foot.";
			print_notification(7000, ss.str());
		}
	}
	if (add_text_option(OBFUSCATE("Give Health & Armour"))) {
		if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player), 1)) {
			Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_network_selected_player), 0.0f, 0.0f, 0.0f);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_ARMOUR_STANDARD"), coords.x, coords.y, coords.z, 0, 100000, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_HEALTH_STANDARD"), coords.x, coords.y, coords.z, 0, 100000, 1, 0, 1);
			std::stringstream ss;
			ss << "~g~Success:~s~ ~b~Health & Armour~s~ given to ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~.";
			print_notification(7000, ss.str());
		}
		else {
			std::stringstream ss;
			ss << "~r~Error:~s~ ~y~" << PLAYER::GET_PLAYER_NAME(g_network_selected_player) << "~s~ is not on foot.";
			print_notification(7000, ss.str());
		}
	}
	//if (add_text_option("Give ~italic~\"Cops Turn Blind Eye\"")) {
	//	std::uint32_t time_end = NETWORK::GET_NETWORK_TIME() + (60000 * 59);
	//	std::uint32_t check_1 = *scr_global(1628955).at(g_network_selected_player, 614).at(532).as<std::uint32_t*>();
	//	std::uint32_t check_2 = *scr_global(2531497).at(4558).as<std::uint32_t*>();
	//	Any args[] = { -1961284186, g_network_selected_player, check_2, 0, time_end, 0, check_1 };
	//	SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, (std::int32_t)(std::size(args)), 1 << g_network_selected_player);
	//}
	//if (add_text_option("Give ~italic~\"Off The Radar\"")) {
	//	std::uint32_t time_start = NETWORK::GET_NETWORK_TIME();
	//	std::uint32_t time_end = NETWORK::GET_NETWORK_TIME() + (60000 * 59);
	//	std::uint32_t check_1 = *scr_global(1628955).at(g_network_selected_player, 614).at(532).as<std::uint32_t*>();
	//	Any args[] = { -615431083, g_network_selected_player, time_start, time_start, 1, 1, check_1 };
	//	SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, (std::int32_t)(std::size(args)), 1 << g_network_selected_player);
	//}
}
void menu_network() {
	add_submenu_option(menu_network_streamer_mode, OBFUSCATE("Streamer Mode"));
	add_submenu_option(menu_network_spoof_network_info, OBFUSCATE("Spoofing"));
	add_submenu_option(menu_network_lobby_options, OBFUSCATE("Lobby Options")); // TODO
	add_submenu_option(menu_network_friends_list, OBFUSCATE("Friends List"));
	add_break_option(OBFUSCATE("Connected Players"));
	for (std::uint32_t i = 0; i < 32; ++i)
	{
		if (ptr.m_GNP)
		{
			std::string s = ptr.m_GPN(i);
			if (strcmp(s.c_str(), "**Invalid**"))
			{
				if (PLAYER::PLAYER_ID() == i)
					s += " ~g~[ME]";
				if (is_player_freemode_host(i))
					s += " ~y~[FREE-HOST]";
				if (NETWORK::NETWORK_PLAYER_IS_ROCKSTAR_DEV(i))
					s += " ~y~[ROCKSTAR]";
				if (NETWORK::_NETWORK_PLAYER_IS_CHEATER(i))
					s += " ~b~[CHEATER]";
				if (is_player_friend(i))
					s += " ~g~[FRIEND]";
				if (is_player_in_passive_mode(i))
					s += " ~c~[PASSIVE]";
				if (is_player_quantum_user(i))
					s += " ~r~[QTM]";
				if (is_player_using_oppressor(i))
					s += " ~o~[OPPRESSOR]";
				if (is_player_using_tank(i))
					s += " ~o~[TANK]";
				if (add_submenu_option(menu_network_player, s))
					g_network_selected_player = i;
				if (i == CURRENT_OPTION - 6)
					draw_player_info_box(i);
			}
		}
	}
	/*for (std::int32_t i = 0; i < 32; i++) {
		if (NETWORK::NETWORK_IS_PLAYER_ACTIVE(i)) {
			std::string s = PLAYER::GET_PLAYER_NAME(i);
			if (PLAYER::PLAYER_ID() == i)
				s += " ~g~[ME]";
			//if (is_player_session_host(i) && is_player_freemode_host(i))
			//	s += " ~y~[SF-HOST]";
			//else {
			//	if (is_player_session_host(i))
			//		s += " ~y~[S-HOST]";
			//	if (is_player_freemode_host(i))
			//		s += " ~r~[F-HOST]";
			//}
			//if (is_player_next_session_host(i))
			//	s += " ~r~[NS-HOST]";
			if (NETWORK::NETWORK_PLAYER_IS_ROCKSTAR_DEV(i))
				s += " ~y~[ROCKSTAR]";
			if (NETWORK::_NETWORK_PLAYER_IS_CHEATER(i))
				s += " ~b~[CHEATER]";
			//if (NETWORK::NETWORK_IS_IN_SESSION()) {
			//	if (get_player_cash(i) >= 10000000)
			//		s += " ~g~[RICH]";
			//	if (get_player_cash(i) < 10000000)
			//		s += " ~b~[POOR]";
			//}
			if (is_player_friend(i))
				s += " ~g~[FRIEND]";
			if (is_player_in_passive_mode(i))
				s += " ~c~[PASSIVE]";
			if (is_player_quantum_user(i))
				s += " ~r~[QTM]";
			if (is_player_using_oppressor(i))
				s += " ~o~[OPPRESSOR]";
			if (is_player_using_tank(i))
				s += " ~o~[TANK]";
			if (add_submenu_option(menu_network_player, s)) {
				std::locale loc;
				std::stringstream ss;
				g_network_selected_player = i;
				std::string temp = PLAYER::GET_PLAYER_NAME(g_network_selected_player);
				for (std::string::size_type i = 0; i < temp.length(); ++i)
					ss << std::toupper(temp[i], loc);
				g_menu_cxt_to_push.m_title = ss.str();
			}
			if (i == CURRENT_OPTION - 6) {
				draw_player_info_box(i);
			}
		}
		else {
			add_text_option(OBFUSCATE("~c~Free Slot"));
		}
	}*/
}

void menu_all_pedestrian_sport_anim() {
	for (std::int32_t i = 0; i < ARRAYSIZE(g_sport_anims); i++) {
		if (add_text_option(g_sport_anims[i].local_name)) {

			const char* dict = g_sport_anims[i].anim_dict.c_str();
			const char* name = g_sport_anims[i].anim_name.c_str();

			if (STREAMING::DOES_ANIM_DICT_EXIST(dict)) {
				STREAMING::REQUEST_ANIM_DICT(dict);
				while (!STREAMING::HAS_ANIM_DICT_LOADED(dict))
					Script::GetCurrent()->ScriptYield();

				for (auto i = 0; i < std::size(g_pedestrian_peds); i++) {
					if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[i].handle)) {
						if (!PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[i].handle, 1)) {
							AI::TASK_PLAY_ANIM(g_pedestrian_peds[i].handle, dict, name, 8.0f, 0.0f, -1, 9, 0.0f, false, false, false);
							AI::SET_ANIM_RATE(g_pedestrian_peds[i].handle, g_animation_speed, 0.0f, 0.0f);
						}
					}
				}
			}
		}
	}
}
void menu_all_pedestrian_sex_anim() {
	for (std::int32_t i = 0; i < ARRAYSIZE(g_sex_anims); i++) {
		if (add_text_option(g_sex_anims[i].local_name)) {
			const char* dict = g_sex_anims[i].anim_dict.c_str();
			const char* name = g_sex_anims[i].anim_name.c_str();

			if (STREAMING::DOES_ANIM_DICT_EXIST(dict)) {
				STREAMING::REQUEST_ANIM_DICT(dict);
				while (!STREAMING::HAS_ANIM_DICT_LOADED(dict))
					Script::GetCurrent()->ScriptYield();

				for (auto i = 0; i < std::size(g_pedestrian_peds); i++) {
					if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[i].handle)) {
						if (!PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[i].handle, 1)) {
							AI::TASK_PLAY_ANIM(g_pedestrian_peds[i].handle, dict, name, 8.0f, 0.0f, -1, 9, 0.0f, false, false, false);
							AI::SET_ANIM_RATE(g_pedestrian_peds[i].handle, g_animation_speed, 0.0f, 0.0f);
						}
					}
				}
			}
		}
	}
}
void menu_all_pedestrian_dance_anim() {
	for (std::int32_t i = 0; i < ARRAYSIZE(g_dance_anims); i++) {
		if (add_text_option(g_dance_anims[i].local_name)) {
			const char* dict = g_dance_anims[i].anim_dict.c_str();
			const char* name = g_dance_anims[i].anim_name.c_str();

			if (STREAMING::DOES_ANIM_DICT_EXIST(dict)) {
				STREAMING::REQUEST_ANIM_DICT(dict);
				while (!STREAMING::HAS_ANIM_DICT_LOADED(dict))
					Script::GetCurrent()->ScriptYield();

				for (auto i = 0; i < std::size(g_pedestrian_peds); i++) {
					if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[i].handle)) {
						if (!PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[i].handle, 1)) {
							AI::TASK_PLAY_ANIM(g_pedestrian_peds[i].handle, dict, name, 8.0f, 0.0f, -1, 9, 0.0f, false, false, false);
							AI::SET_ANIM_RATE(g_pedestrian_peds[i].handle, g_animation_speed, 0.0f, 0.0f);
						}
					}
				}
			}
		}
	}
}
void menu_all_pedestrian_superhero_anim() {
	for (std::int32_t i = 0; i < ARRAYSIZE(g_super_hero_anims); i++) {
		if (add_text_option(g_super_hero_anims[i].local_name)) {
			const char* dict = g_super_hero_anims[i].anim_dict.c_str();
			const char* name = g_super_hero_anims[i].anim_name.c_str();

			if (STREAMING::DOES_ANIM_DICT_EXIST(dict)) {
				STREAMING::REQUEST_ANIM_DICT(dict);
				while (!STREAMING::HAS_ANIM_DICT_LOADED(dict))
					Script::GetCurrent()->ScriptYield();

				for (auto i = 0; i < std::size(g_pedestrian_peds); i++) {
					if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[i].handle)) {
						if (!PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[i].handle, 1)) {
							AI::TASK_PLAY_ANIM(g_pedestrian_peds[i].handle, dict, name, 8.0f, 0.0f, -1, 9, 0.0f, false, false, false);
							AI::SET_ANIM_RATE(g_pedestrian_peds[i].handle, g_animation_speed, 0.0f, 0.0f);
						}
					}
				}
			}
		}
	}
}
void menu_all_pedestrian_misc_anim() {
	for (std::int32_t i = 0; i < ARRAYSIZE(g_misc_anims); i++) {
		if (add_text_option(g_misc_anims[i].local_name)) {
			const char* dict = g_misc_anims[i].anim_dict.c_str();
			const char* name = g_misc_anims[i].anim_name.c_str();

			if (STREAMING::DOES_ANIM_DICT_EXIST(dict)) {
				STREAMING::REQUEST_ANIM_DICT(dict);
				while (!STREAMING::HAS_ANIM_DICT_LOADED(dict))
					Script::GetCurrent()->ScriptYield();

				for (auto i = 0; i < std::size(g_pedestrian_peds); i++) {
					if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[i].handle)) {
						if (!PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[i].handle, 1)) {
							AI::TASK_PLAY_ANIM(g_pedestrian_peds[i].handle, dict, name, 8.0f, 0.0f, -1, 9, 0.0f, false, false, false);
							AI::SET_ANIM_RATE(g_pedestrian_peds[i].handle, g_animation_speed, 0.0f, 0.0f);
						}
					}
				}
			}
		}
	}
}
void menu_pedestrian_all_animation() {
	if (add_editor_option(true, g_animation_speed, &g_animation_speed, 0.00f, 20.0f, 0.05f, OBFUSCATE("Playback Speed"))) {
		for (auto i = 0; i < std::size(g_pedestrian_peds); i++) {
			if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[i].handle))
				if (!PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[i].handle, 1))
					AI::SET_ANIM_RATE(g_pedestrian_peds[i].handle, g_animation_speed, 0.0f, 0.0f);
		}
		
		std::stringstream ss;
		ss << "~g~Success:~s~ Set all pedestrians animation playback speed to ~b~" << g_animation_speed << "~s~.";
		print_notification(7000, ss.str());
	}
	add_break_option(OBFUSCATE("Catagories"));
	add_submenu_option(menu_all_pedestrian_sport_anim, OBFUSCATE("Sport"));
	add_submenu_option(menu_all_pedestrian_sex_anim, OBFUSCATE("Sex"));
	add_submenu_option(menu_all_pedestrian_dance_anim, OBFUSCATE("Dance"));
	add_submenu_option(menu_all_pedestrian_superhero_anim, OBFUSCATE("Superhero"));
	add_submenu_option(menu_all_pedestrian_misc_anim, OBFUSCATE("Misc"));
	if (add_text_option(OBFUSCATE("Clear Current Animations"))) {
		for (auto i = 0; i < std::size(g_pedestrian_peds); i++) {
			if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[i].handle))
				if (!PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[i].handle, 1))
					AI::CLEAR_PED_TASKS_IMMEDIATELY(g_pedestrian_peds[i].handle);
		}
		print_notification(7000, "~g~Success:~s~ Cleared all pedestrians current animations.");
	}
}
void menu_pedestrian_all_manager() {
	add_submenu_option(menu_pedestrian_all_animation, OBFUSCATE("Animations"));
	if (add_string_array_option(true, g_pedestrian_all_group_formation, (std::int32_t)std::size(g_pedestrian_all_group_formation), &g_pedestrian_all_group_formation_type, OBFUSCATE("Group Formation"))) {
		PED::SET_GROUP_FORMATION(PED::GET_PED_GROUP_INDEX(PLAYER::PLAYER_PED_ID()), g_pedestrian_all_group_formation_type);

		std::stringstream ss;
		ss << "~g~Success:~s~ All pedestrians group formation set to ~b~" << g_pedestrian_all_group_formation[g_pedestrian_all_group_formation_type] << "~s~.";
		print_notification(7000, ss.str());
	}
	if (add_text_option(OBFUSCATE("Teleport To Me"))) {
		for (auto i = 0; i < std::size(g_pedestrian_peds); i++) {
			if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[i].handle)) {
				if (!PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[i].handle, 1)) {
					Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, 0.0f, 0.0f);
					ENTITY::SET_ENTITY_COORDS(g_pedestrian_peds[i].handle, coords.x, coords.y, coords.z, 1, 0, 0, 1);
				}
			}
		}
		print_notification(7000, "~g~Success:~s~ All pedestrians teleported to me.");
	}
	add_toggle_option(&g_all_pedestrian_draw_esp, OBFUSCATE("ESP"));
	if (add_text_option(OBFUSCATE("Commit Suicide"))) {
		for (auto i = 0; i < std::size(g_pedestrian_peds); i++) {
			if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[i].handle)) {
				if (!PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[i].handle, 1))
					suicide_ped(g_pedestrian_peds[i].handle);
			}
		}
		print_notification(7000, "~g~Success:~s~ All pedestrians commited suicide.");
	}
	if (add_text_option(OBFUSCATE("Drop Dead"))) {
		for (auto i = 0; i < std::size(g_pedestrian_peds); i++) {
			if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[i].handle)) {
				if (!PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[i].handle, 1)) {
					ENTITY::SET_ENTITY_HEALTH(g_pedestrian_peds[i].handle, 0);
					g_pedestrian_peds[i].is_bodyguard = false;
				}
			}
		}
		print_notification(7000, "~g~Success:~s~ All pedestrians dropped dead.");
	}
}
void menu_pedestrian_editor_manage_component() {
	if (add_editor_option(true, g_pedestrian_peds[g_selected_pedestrian].current_drawable_id[g_pedestrian_peds[g_selected_pedestrian].selected_component_id], &g_pedestrian_peds[g_selected_pedestrian].current_drawable_id[g_pedestrian_peds[g_selected_pedestrian].selected_component_id], 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), g_pedestrian_peds[g_selected_pedestrian].selected_component_id), 1, OBFUSCATE("Drawable ID"))) {
		PED::SET_PED_COMPONENT_VARIATION(g_pedestrian_peds[g_selected_pedestrian].handle, g_pedestrian_peds[g_selected_pedestrian].selected_component_id, g_pedestrian_peds[g_selected_pedestrian].current_drawable_id[g_pedestrian_peds[g_selected_pedestrian].selected_component_id], g_pedestrian_peds[g_selected_pedestrian].current_texture_id[g_pedestrian_peds[g_selected_pedestrian].selected_component_id], g_pedestrian_peds[g_selected_pedestrian].current_pallette_id[g_pedestrian_peds[g_selected_pedestrian].selected_component_id]);
	}
	if (add_editor_option(true, g_pedestrian_peds[g_selected_pedestrian].current_texture_id[g_pedestrian_peds[g_selected_pedestrian].selected_component_id], &g_pedestrian_peds[g_selected_pedestrian].current_texture_id[g_pedestrian_peds[g_selected_pedestrian].selected_component_id], 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), g_pedestrian_peds[g_selected_pedestrian].selected_component_id, g_pedestrian_peds[g_selected_pedestrian].current_drawable_id[g_pedestrian_peds[g_selected_pedestrian].selected_component_id]), 1, OBFUSCATE("Texture ID"))) {
		PED::SET_PED_COMPONENT_VARIATION(g_pedestrian_peds[g_selected_pedestrian].handle, g_pedestrian_peds[g_selected_pedestrian].selected_component_id, g_pedestrian_peds[g_selected_pedestrian].current_drawable_id[g_pedestrian_peds[g_selected_pedestrian].selected_component_id], g_pedestrian_peds[g_selected_pedestrian].current_texture_id[g_pedestrian_peds[g_selected_pedestrian].selected_component_id], g_pedestrian_peds[g_selected_pedestrian].current_pallette_id[g_pedestrian_peds[g_selected_pedestrian].selected_component_id]);
	}
	if (add_editor_option(true, g_pedestrian_peds[g_selected_pedestrian].current_pallette_id[g_pedestrian_peds[g_selected_pedestrian].selected_component_id], &g_pedestrian_peds[g_selected_pedestrian].current_pallette_id[g_pedestrian_peds[g_selected_pedestrian].selected_component_id], 0, 3, 1, OBFUSCATE("Palette ID"))) {
		PED::SET_PED_COMPONENT_VARIATION(g_pedestrian_peds[g_selected_pedestrian].handle, g_pedestrian_peds[g_selected_pedestrian].selected_component_id, g_pedestrian_peds[g_selected_pedestrian].current_drawable_id[g_pedestrian_peds[g_selected_pedestrian].selected_component_id], g_pedestrian_peds[g_selected_pedestrian].current_texture_id[g_pedestrian_peds[g_selected_pedestrian].selected_component_id], g_pedestrian_peds[g_selected_pedestrian].current_pallette_id[g_pedestrian_peds[g_selected_pedestrian].selected_component_id]);
	}
	
	if (g_selected_pedestrian_camera) {
		if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle) && !PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[g_selected_pedestrian].handle, 1)) {
			if (!CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				g_selected_pedestrian_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
				if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
					CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, true);
					CAM::RENDER_SCRIPT_CAMS(1, 1, 1500, 1, 0);
				}
			}
			else {
				std::int32_t analog_x_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_LR);
				std::int32_t analog_y_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_UD);
				g_pedestrian_right_angle1 -= (0.001f * (analog_x_right - 127));
				g_pedestrian_right_angle2 += (0.001f * (analog_y_right - 127));
				CAM::DETACH_CAM(g_selected_pedestrian_cam);
				CAM::ATTACH_CAM_TO_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 3.0f * cos(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 3.0f * sin(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 3.0f * sin(g_pedestrian_right_angle2), 0);
				CAM::POINT_CAM_AT_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 0, 0, 0, 1);
				if (g_pedestrian_right_angle1 <= -6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle1 >= 6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle2 > 1.2f)
					g_pedestrian_right_angle2 = 1.2f;
				if (g_pedestrian_right_angle2 < -1.2f)
					g_pedestrian_right_angle2 = -1.2f;
			}
		}
		else {
			if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, false);
				CAM::RENDER_SCRIPT_CAMS(0, 1, 1500, 1, 0);
				CAM::DESTROY_CAM(g_selected_pedestrian_cam, true);
			}
		}
	}
}
void menu_pedestrian_outfit_editor() {
	if (add_text_option(OBFUSCATE("Reset Appearance"))) {
		for (INT i = 0; i < 13; i++)
			PED::SET_PED_COMPONENT_VARIATION(g_pedestrian_peds[g_selected_pedestrian].handle, i, 0, 0, 2);
		PED::SET_PED_PROP_INDEX(g_pedestrian_peds[g_selected_pedestrian].handle, 0, 0, 0, 1);
		PED::SET_PED_PROP_INDEX(g_pedestrian_peds[g_selected_pedestrian].handle, 1, 0, 0, 1);
		PED::CLEAR_PED_DECORATIONS(g_pedestrian_peds[g_selected_pedestrian].handle);
		PED::CLEAR_ALL_PED_PROPS(g_pedestrian_peds[g_selected_pedestrian].handle);
	}
	if (add_submenu_option(menu_pedestrian_editor_manage_component, OBFUSCATE("Face"))) {
		g_pedestrian_peds[g_selected_pedestrian].selected_component_id = 0;
	}
	if (add_submenu_option(menu_pedestrian_editor_manage_component, OBFUSCATE("Mask"))) {
		g_pedestrian_peds[g_selected_pedestrian].selected_component_id = 1;
	}
	if (add_submenu_option(menu_pedestrian_editor_manage_component, OBFUSCATE("Hair"))) {
		g_pedestrian_peds[g_selected_pedestrian].selected_component_id = 2;
	}
	if (add_submenu_option(menu_pedestrian_editor_manage_component, OBFUSCATE("Torso 1"))) {
		g_pedestrian_peds[g_selected_pedestrian].selected_component_id = 3;
	}
	if (add_submenu_option(menu_pedestrian_editor_manage_component, OBFUSCATE("Leg"))) {
		g_pedestrian_peds[g_selected_pedestrian].selected_component_id = 4;
	}
	if (add_submenu_option(menu_pedestrian_editor_manage_component, OBFUSCATE("Parachute/Bag"))) {
		g_pedestrian_peds[g_selected_pedestrian].selected_component_id = 5;
	}
	if (add_submenu_option(menu_pedestrian_editor_manage_component, OBFUSCATE("Shoes"))) {
		g_pedestrian_peds[g_selected_pedestrian].selected_component_id = 6;
	}
	if (add_submenu_option(menu_pedestrian_editor_manage_component, OBFUSCATE("Accessory"))) {
		g_pedestrian_peds[g_selected_pedestrian].selected_component_id = 7;
	}
	if (add_submenu_option(menu_pedestrian_editor_manage_component, OBFUSCATE("Undershirt"))) {
		g_pedestrian_peds[g_selected_pedestrian].selected_component_id = 8;
	}
	if (add_submenu_option(menu_pedestrian_editor_manage_component, OBFUSCATE("Kevlar"))) {
		g_pedestrian_peds[g_selected_pedestrian].selected_component_id = 9;
	}
	if (add_submenu_option(menu_pedestrian_editor_manage_component, OBFUSCATE("Badge"))) {
		g_pedestrian_peds[g_selected_pedestrian].selected_component_id = 10;
	}
	if (add_submenu_option(menu_pedestrian_editor_manage_component, OBFUSCATE("Torso 2"))) {
		g_pedestrian_peds[g_selected_pedestrian].selected_component_id = 11;
	}

	if (g_selected_pedestrian_camera) {
		if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle) && !PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[g_selected_pedestrian].handle, 1)) {
			if (!CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				g_selected_pedestrian_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
				if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
					CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, true);
					CAM::RENDER_SCRIPT_CAMS(1, 1, 1500, 1, 0);
				}
			}
			else {
				std::int32_t analog_x_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_LR);
				std::int32_t analog_y_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_UD);
				g_pedestrian_right_angle1 -= (0.001f * (analog_x_right - 127));
				g_pedestrian_right_angle2 += (0.001f * (analog_y_right - 127));
				CAM::DETACH_CAM(g_selected_pedestrian_cam);
				CAM::ATTACH_CAM_TO_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 3.0f * cos(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 3.0f * sin(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 3.0f * sin(g_pedestrian_right_angle2), 0);
				CAM::POINT_CAM_AT_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 0, 0, 0, 1);
				if (g_pedestrian_right_angle1 <= -6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle1 >= 6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle2 > 1.2f)
					g_pedestrian_right_angle2 = 1.2f;
				if (g_pedestrian_right_angle2 < -1.2f)
					g_pedestrian_right_angle2 = -1.2f;
			}
		}
		else {
			if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, false);
				CAM::RENDER_SCRIPT_CAMS(0, 1, 1500, 1, 0);
				CAM::DESTROY_CAM(g_selected_pedestrian_cam, true);
			}
		}
	}
}
void menu_pedestrian_sport_anim() {
	for (std::int32_t i = 0; i < ARRAYSIZE(g_sport_anims); i++) {
		if (add_text_option(g_sport_anims[i].local_name)) {

			const char* dict = g_sport_anims[i].anim_dict.c_str();
			const char* name = g_sport_anims[i].anim_name.c_str();

			if (STREAMING::DOES_ANIM_DICT_EXIST(dict)) {
				STREAMING::REQUEST_ANIM_DICT(dict);
				while (!STREAMING::HAS_ANIM_DICT_LOADED(dict))
					Script::GetCurrent()->ScriptYield();
				AI::TASK_PLAY_ANIM(g_pedestrian_peds[g_selected_pedestrian].handle, dict, name, 8.0f, 0.0f, -1, 9, 0.0f, false, false, false);
				AI::SET_ANIM_RATE(g_pedestrian_peds[g_selected_pedestrian].handle, g_animation_speed, 0.0f, 0.0f);
			}

		}
	}

	if (g_selected_pedestrian_camera) {
		if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle) && !PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[g_selected_pedestrian].handle, 1)) {
			if (!CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				g_selected_pedestrian_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
				if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
					CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, true);
					CAM::RENDER_SCRIPT_CAMS(1, 1, 1500, 1, 0);
				}
			}
			else {
				std::int32_t analog_x_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_LR);
				std::int32_t analog_y_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_UD);
				g_pedestrian_right_angle1 -= (0.001f * (analog_x_right - 127));
				g_pedestrian_right_angle2 += (0.001f * (analog_y_right - 127));
				CAM::DETACH_CAM(g_selected_pedestrian_cam);
				CAM::ATTACH_CAM_TO_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 5.0f * cos(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 5.0f * sin(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 5.0f * sin(g_pedestrian_right_angle2), 0);
				CAM::POINT_CAM_AT_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 0, 0, 0, 1);
				if (g_pedestrian_right_angle1 <= -6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle1 >= 6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle2 > 1.2f)
					g_pedestrian_right_angle2 = 1.2f;
				if (g_pedestrian_right_angle2 < -1.2f)
					g_pedestrian_right_angle2 = -1.2f;
			}
		}
		else {
			if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, false);
				CAM::RENDER_SCRIPT_CAMS(0, 1, 1500, 1, 0);
				CAM::DESTROY_CAM(g_selected_pedestrian_cam, true);
			}
		}
	}
}
void menu_pedestrian_sex_anim() {
	for (std::int32_t i = 0; i < ARRAYSIZE(g_sex_anims); i++) {
		if (add_text_option(g_sex_anims[i].local_name)) {
			const char* dict = g_sex_anims[i].anim_dict.c_str();
			const char* name = g_sex_anims[i].anim_name.c_str();

			if (STREAMING::DOES_ANIM_DICT_EXIST(dict)) {
				STREAMING::REQUEST_ANIM_DICT(dict);
				while (!STREAMING::HAS_ANIM_DICT_LOADED(dict))
					Script::GetCurrent()->ScriptYield();
				AI::TASK_PLAY_ANIM(g_pedestrian_peds[g_selected_pedestrian].handle, dict, name, 8.0f, 0.0f, -1, 9, 0.0f, false, false, false);
				AI::SET_ANIM_RATE(g_pedestrian_peds[g_selected_pedestrian].handle, g_animation_speed, 0.0f, 0.0f);
			}
		}
	}

	if (g_selected_pedestrian_camera) {
		if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle) && !PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[g_selected_pedestrian].handle, 1)) {
			if (!CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				g_selected_pedestrian_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
				if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
					CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, true);
					CAM::RENDER_SCRIPT_CAMS(1, 1, 1500, 1, 0);
				}
			}
			else {
				std::int32_t analog_x_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_LR);
				std::int32_t analog_y_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_UD);
				g_pedestrian_right_angle1 -= (0.001f * (analog_x_right - 127));
				g_pedestrian_right_angle2 += (0.001f * (analog_y_right - 127));
				CAM::DETACH_CAM(g_selected_pedestrian_cam);
				CAM::ATTACH_CAM_TO_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 5.0f * cos(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 5.0f * sin(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 5.0f * sin(g_pedestrian_right_angle2), 0);
				CAM::POINT_CAM_AT_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 0, 0, 0, 1);
				if (g_pedestrian_right_angle1 <= -6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle1 >= 6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle2 > 1.2f)
					g_pedestrian_right_angle2 = 1.2f;
				if (g_pedestrian_right_angle2 < -1.2f)
					g_pedestrian_right_angle2 = -1.2f;
			}
		}
		else {
			if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, false);
				CAM::RENDER_SCRIPT_CAMS(0, 1, 1500, 1, 0);
				CAM::DESTROY_CAM(g_selected_pedestrian_cam, true);
			}
		}
	}
}
void menu_pedestrian_dance_anim() {
	for (std::int32_t i = 0; i < ARRAYSIZE(g_dance_anims); i++) {
		if (add_text_option(g_dance_anims[i].local_name)) {
			const char* dict = g_dance_anims[i].anim_dict.c_str();
			const char* name = g_dance_anims[i].anim_name.c_str();

			if (STREAMING::DOES_ANIM_DICT_EXIST(dict)) {
				STREAMING::REQUEST_ANIM_DICT(dict);
				while (!STREAMING::HAS_ANIM_DICT_LOADED(dict))
					Script::GetCurrent()->ScriptYield();
				AI::TASK_PLAY_ANIM(g_pedestrian_peds[g_selected_pedestrian].handle, dict, name, 8.0f, 0.0f, -1, 9, 0.0f, false, false, false);
				AI::SET_ANIM_RATE(g_pedestrian_peds[g_selected_pedestrian].handle, g_animation_speed, 0.0f, 0.0f);
			}
		}
	}

	if (g_selected_pedestrian_camera) {
		if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle) && !PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[g_selected_pedestrian].handle, 1)) {
			if (!CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				g_selected_pedestrian_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
				if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
					CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, true);
					CAM::RENDER_SCRIPT_CAMS(1, 1, 1500, 1, 0);
				}
			}
			else {
				std::int32_t analog_x_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_LR);
				std::int32_t analog_y_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_UD);
				g_pedestrian_right_angle1 -= (0.001f * (analog_x_right - 127));
				g_pedestrian_right_angle2 += (0.001f * (analog_y_right - 127));
				CAM::DETACH_CAM(g_selected_pedestrian_cam);
				CAM::ATTACH_CAM_TO_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 5.0f * cos(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 5.0f * sin(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 5.0f * sin(g_pedestrian_right_angle2), 0);
				CAM::POINT_CAM_AT_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 0, 0, 0, 1);
				if (g_pedestrian_right_angle1 <= -6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle1 >= 6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle2 > 1.2f)
					g_pedestrian_right_angle2 = 1.2f;
				if (g_pedestrian_right_angle2 < -1.2f)
					g_pedestrian_right_angle2 = -1.2f;
			}
		}
		else {
			if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, false);
				CAM::RENDER_SCRIPT_CAMS(0, 1, 1500, 1, 0);
				CAM::DESTROY_CAM(g_selected_pedestrian_cam, true);
			}
		}
	}
}
void menu_pedestrian_superhero_anim() {
	for (std::int32_t i = 0; i < ARRAYSIZE(g_super_hero_anims); i++) {
		if (add_text_option(g_super_hero_anims[i].local_name)) {
			const char* dict = g_super_hero_anims[i].anim_dict.c_str();
			const char* name = g_super_hero_anims[i].anim_name.c_str();

			if (STREAMING::DOES_ANIM_DICT_EXIST(dict)) {
				STREAMING::REQUEST_ANIM_DICT(dict);
				while (!STREAMING::HAS_ANIM_DICT_LOADED(dict))
					Script::GetCurrent()->ScriptYield();
				AI::TASK_PLAY_ANIM(g_pedestrian_peds[g_selected_pedestrian].handle, dict, name, 8.0f, 0.0f, -1, 9, 0.0f, false, false, false);
				AI::SET_ANIM_RATE(g_pedestrian_peds[g_selected_pedestrian].handle, g_animation_speed, 0.0f, 0.0f);
			}
		}
	}

	if (g_selected_pedestrian_camera) {
		if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle) && !PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[g_selected_pedestrian].handle, 1)) {
			if (!CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				g_selected_pedestrian_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
				if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
					CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, true);
					CAM::RENDER_SCRIPT_CAMS(1, 1, 1500, 1, 0);
				}
			}
			else {
				std::int32_t analog_x_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_LR);
				std::int32_t analog_y_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_UD);
				g_pedestrian_right_angle1 -= (0.001f * (analog_x_right - 127));
				g_pedestrian_right_angle2 += (0.001f * (analog_y_right - 127));
				CAM::DETACH_CAM(g_selected_pedestrian_cam);
				CAM::ATTACH_CAM_TO_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 5.0f * cos(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 5.0f * sin(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 5.0f * sin(g_pedestrian_right_angle2), 0);
				CAM::POINT_CAM_AT_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 0, 0, 0, 1);
				if (g_pedestrian_right_angle1 <= -6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle1 >= 6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle2 > 1.2f)
					g_pedestrian_right_angle2 = 1.2f;
				if (g_pedestrian_right_angle2 < -1.2f)
					g_pedestrian_right_angle2 = -1.2f;
			}
		}
		else {
			if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, false);
				CAM::RENDER_SCRIPT_CAMS(0, 1, 1500, 1, 0);
				CAM::DESTROY_CAM(g_selected_pedestrian_cam, true);
			}
		}
	}
}
void menu_pedestrian_misc_anim() {
	for (std::int32_t i = 0; i < ARRAYSIZE(g_misc_anims); i++) {
		if (add_text_option(g_misc_anims[i].local_name)) {
			const char* dict = g_misc_anims[i].anim_dict.c_str();
			const char* name = g_misc_anims[i].anim_name.c_str();

			if (STREAMING::DOES_ANIM_DICT_EXIST(dict)) {
				STREAMING::REQUEST_ANIM_DICT(dict);
				while (!STREAMING::HAS_ANIM_DICT_LOADED(dict))
					Script::GetCurrent()->ScriptYield();
				AI::TASK_PLAY_ANIM(g_pedestrian_peds[g_selected_pedestrian].handle, dict, name, 8.0f, 0.0f, -1, 9, 0.0f, false, false, false);
				AI::SET_ANIM_RATE(g_pedestrian_peds[g_selected_pedestrian].handle, g_animation_speed, 0.0f, 0.0f);
			}
		}
	}

	if (g_selected_pedestrian_camera) {
		if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle) && !PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[g_selected_pedestrian].handle, 1)) {
			if (!CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				g_selected_pedestrian_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
				if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
					CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, true);
					CAM::RENDER_SCRIPT_CAMS(1, 1, 1500, 1, 0);
				}
			}
			else {
				std::int32_t analog_x_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_LR);
				std::int32_t analog_y_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_UD);
				g_pedestrian_right_angle1 -= (0.001f * (analog_x_right - 127));
				g_pedestrian_right_angle2 += (0.001f * (analog_y_right - 127));
				CAM::DETACH_CAM(g_selected_pedestrian_cam);
				CAM::ATTACH_CAM_TO_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 5.0f * cos(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 5.0f * sin(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 5.0f * sin(g_pedestrian_right_angle2), 0);
				CAM::POINT_CAM_AT_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 0, 0, 0, 1);
				if (g_pedestrian_right_angle1 <= -6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle1 >= 6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle2 > 1.2f)
					g_pedestrian_right_angle2 = 1.2f;
				if (g_pedestrian_right_angle2 < -1.2f)
					g_pedestrian_right_angle2 = -1.2f;
			}
		}
		else {
			if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, false);
				CAM::RENDER_SCRIPT_CAMS(0, 1, 1500, 1, 0);
				CAM::DESTROY_CAM(g_selected_pedestrian_cam, true);
			}
		}
	}
}
void menu_pedestrian_animation() {
	if (add_editor_option(true, g_animation_speed, &g_animation_speed, 0.00f, 20.0f, 0.05f, OBFUSCATE("Playback Speed"))) {
		AI::SET_ANIM_RATE(g_pedestrian_peds[g_selected_pedestrian].handle, g_animation_speed, 0.0f, 0.0f);

		std::stringstream ss;
		ss << "~g~Success:~s~ Set pedestrian ~y~" << g_pedestrian_peds[g_selected_pedestrian].name << " ~s~animation playback speed to ~b~" << g_animation_speed << "~s~.";
		print_notification(7000, ss.str());
	}
	add_break_option(OBFUSCATE("Catagories"));
	add_submenu_option(menu_pedestrian_sport_anim, OBFUSCATE("Sport"));
	add_submenu_option(menu_pedestrian_sex_anim, OBFUSCATE("Sex"));
	add_submenu_option(menu_pedestrian_dance_anim, OBFUSCATE("Dance"));
	add_submenu_option(menu_pedestrian_superhero_anim, OBFUSCATE("Superhero"));
	add_submenu_option(menu_pedestrian_misc_anim, OBFUSCATE("Misc"));
	if (add_text_option(OBFUSCATE("Clear Current Animation"))) {
		AI::CLEAR_PED_TASKS_IMMEDIATELY(g_pedestrian_peds[g_selected_pedestrian].handle);

		std::stringstream ss;
		ss << "~g~Success:~s~ Cleared pedestrian ~y~" << g_pedestrian_peds[g_selected_pedestrian].name << " ~s~current animation.";
		print_notification(7000, ss.str());
	}

	if (g_selected_pedestrian_camera) {
		if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle) && !PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[g_selected_pedestrian].handle, 1)) {
			if (!CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				g_selected_pedestrian_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
				if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
					CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, true);
					CAM::RENDER_SCRIPT_CAMS(1, 1, 1500, 1, 0);
				}
			}
			else {
				std::int32_t analog_x_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_LR);
				std::int32_t analog_y_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_UD);
				g_pedestrian_right_angle1 -= (0.001f * (analog_x_right - 127));
				g_pedestrian_right_angle2 += (0.001f * (analog_y_right - 127));
				CAM::DETACH_CAM(g_selected_pedestrian_cam);
				CAM::ATTACH_CAM_TO_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 5.0f * cos(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 5.0f * sin(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 5.0f * sin(g_pedestrian_right_angle2), 0);
				CAM::POINT_CAM_AT_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 0, 0, 0, 1);
				if (g_pedestrian_right_angle1 <= -6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle1 >= 6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle2 > 1.2f)
					g_pedestrian_right_angle2 = 1.2f;
				if (g_pedestrian_right_angle2 < -1.2f)
					g_pedestrian_right_angle2 = -1.2f;
			}
		}
		else {
			if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, false);
				CAM::RENDER_SCRIPT_CAMS(0, 1, 1500, 1, 0);
				CAM::DESTROY_CAM(g_selected_pedestrian_cam, true);
			}
		}
	}
}
void menu_pedestrian_scenarios() {
	if (add_text_option(OBFUSCATE("Clear Current Scenario"))) {
		AI::CLEAR_PED_TASKS_IMMEDIATELY(g_pedestrian_peds[g_selected_pedestrian].handle);

		std::stringstream ss;
		ss << "~g~Success:~s~ Cleared pedestrian ~y~" << g_pedestrian_peds[g_selected_pedestrian].name << "~s~ current scenario.";
		print_notification(7000, ss.str());
	}
	add_break_option(OBFUSCATE("Scenarios"));
	for (std::int32_t i = 0; i < ARRAYSIZE(g_scenario_name); i++) {
		if (add_text_option(g_scenario_name[i])) {
			AI::CLEAR_PED_TASKS_IMMEDIATELY(g_pedestrian_peds[g_selected_pedestrian].handle);
			AI::CLEAR_PED_SECONDARY_TASK(g_pedestrian_peds[g_selected_pedestrian].handle);
			AI::TASK_START_SCENARIO_IN_PLACE(g_pedestrian_peds[g_selected_pedestrian].handle, g_scenario_to_do[i].c_str(), 1, true);
		}
	}

	if (g_selected_pedestrian_camera) {
		if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle) && !PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[g_selected_pedestrian].handle, 1)) {
			if (!CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				g_selected_pedestrian_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
				if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
					CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, true);
					CAM::RENDER_SCRIPT_CAMS(1, 1, 1500, 1, 0);
				}
			}
			else {
				std::int32_t analog_x_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_LR);
				std::int32_t analog_y_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_UD);
				g_pedestrian_right_angle1 -= (0.001f * (analog_x_right - 127));
				g_pedestrian_right_angle2 += (0.001f * (analog_y_right - 127));
				CAM::DETACH_CAM(g_selected_pedestrian_cam);
				CAM::ATTACH_CAM_TO_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 5.0f * cos(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 5.0f * sin(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 5.0f * sin(g_pedestrian_right_angle2), 0);
				CAM::POINT_CAM_AT_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 0, 0, 0, 1);
				if (g_pedestrian_right_angle1 <= -6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle1 >= 6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle2 > 1.2f)
					g_pedestrian_right_angle2 = 1.2f;
				if (g_pedestrian_right_angle2 < -1.2f)
					g_pedestrian_right_angle2 = -1.2f;
			}
		}
		else {
			if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, false);
				CAM::RENDER_SCRIPT_CAMS(0, 1, 1500, 1, 0);
				CAM::DESTROY_CAM(g_selected_pedestrian_cam, true);
			}
		}
	}
}
void menu_pedestrian_task_sequence_add_sequence_manager() {
	switch (g_pedestrian_task_sequence_add) {
	case 1: {
			add_editor_option(true, weapon_hashs[g_pedestrian_task_weapon].name, &g_pedestrian_task_weapon, 0, (std::int32_t)std::size(weapon_hashs), 1, OBFUSCATE("Give Weapon"));
			if (add_text_option(OBFUSCATE("Add Event To Sequence"))) {
				if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle)) {
					for (std::int32_t i = 0; i < sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence) / sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence[0]); i++) {
						if (g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][0] == NULL) {
							g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][0] = g_pedestrian_task_sequence_add;
							g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][1] = g_pedestrian_task_weapon;

							std::stringstream ss;
							ss << "~g~Success: ~s~Added give weapon ~b~" << weapon_hashs[g_pedestrian_task_weapon].name << " to ~y~" << g_pedestrian_peds[g_selected_pedestrian].name << "~s~.";
							print_notification(7000, ss.str());
							pop_menu();
							break;
						}
					}
				}
			}
		} break;
	case 2: {
			if (add_string_array_option(true, g_pedestrian_hated_targets, (std::int32_t)std::size(g_pedestrian_hated_targets), &g_pedestrian_hated_target, OBFUSCATE("Hated Target Type"))) {
				Hash ped_relationship_hash;
				PED::ADD_RELATIONSHIP_GROUP("hated", &ped_relationship_hash);
				PED::SET_PED_RELATIONSHIP_GROUP_HASH(g_pedestrian_peds[g_selected_pedestrian].handle, ped_relationship_hash);

				PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, ped_relationship_hash, GAMEPLAY::GET_HASH_KEY(g_pedestrian_hated_targets[g_pedestrian_hated_target].c_str()));
				PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, GAMEPLAY::GET_HASH_KEY(g_pedestrian_hated_targets[g_pedestrian_hated_target].c_str()), ped_relationship_hash);
			}
			add_editor_option(true, temp_hated_targets_radius, &temp_hated_targets_radius, 5.0f, 25.0f, 0.5f, OBFUSCATE("Radius"));
			if (add_text_option(OBFUSCATE("Add Event To Sequence"))) {
				if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle)) {
					for (std::int32_t i = 0; i < sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence) / sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence[0]); i++) {
						if (g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][0] == NULL) {
							g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][0] = g_pedestrian_task_sequence_add;
							g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][1] = (std::int32_t)std::floor(temp_hated_targets_radius);

							std::stringstream ss;
							ss << "~g~Success: ~s~Added fight hated targets to ~y~" << g_pedestrian_peds[g_selected_pedestrian].name << "~s~.";
							print_notification(7000, ss.str());
							pop_menu();
							break;
						}
					}
				}
			}
		} break;
	case 3: {
			for (std::int32_t i = 0; i < 32; i++) {
				if (NETWORK::NETWORK_IS_PLAYER_ACTIVE(i)) {
					std::string s = PLAYER::GET_PLAYER_NAME(i);
					if (PLAYER::PLAYER_ID() == i)
						s += " ~g~[ME]";
					//if (is_player_session_host(i) && is_player_freemode_host(i))
					//	s += " ~y~[SF-HOST]";
					//else {
					//	if (is_player_session_host(i))
					//		s += " ~y~[S-HOST]";
					//	if (is_player_freemode_host(i))
					//		s += " ~r~[F-HOST]";
					//}
					//if (is_player_next_session_host(i))
						//s += " ~r~[NS-HOST]";
					if (NETWORK::NETWORK_PLAYER_IS_ROCKSTAR_DEV(i))
						s += " ~y~[ROCKSTAR]";
					if (NETWORK::_NETWORK_PLAYER_IS_CHEATER(i))
						s += " ~b~[CHEATER]";
					//if (NETWORK::NETWORK_IS_IN_SESSION()) {
					//	if (get_player_cash(i) >= 10000000)
					//		s += " ~g~[RICH]";
					//	if (get_player_cash(i) < 10000000)
					//		s += " ~b~[POOR]";
					//}
					if (is_player_friend(i))
						s += " ~g~[FRIEND]";
					if (is_player_in_passive_mode(i))
						s += " ~c~[PASSIVE]";
					if (is_player_quantum_user(i))
						s += " ~r~[QTM]";
					if (is_player_using_oppressor(i))
						s += " ~o~[OPPRESSOR]";
					if (is_player_using_tank(i))
						s += " ~o~[TANK]";
					//if (add_text_option(s)) {
					//	if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle)) {
					//		for (std::int32_t j = 0; j < sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence) / sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence[0]); j++) {
					//			if (g_pedestrian_peds[g_selected_pedestrian].task_sequence[j][0] == NULL) {
					//				g_pedestrian_peds[g_selected_pedestrian].task_sequence[j][0] = g_pedestrian_task_sequence_add;
					//				g_pedestrian_peds[g_selected_pedestrian].task_sequence[j][1] = i;

					//				std::stringstream ss;
					//				ss << "~g~Success: ~s~Added fight ~b~" << PLAYER::GET_PLAYER_NAME(i) << " ~s~to ~y~" << g_pedestrian_peds[g_selected_pedestrian].name << "~s~.";
					//				print_notification(7000, ss.str());
					//				pop_menu();
					//				break;
					//			}
					//		}
					//	}
					//}
					//if (i == CURRENT_OPTION - 1)
					//	draw_player_info_box(i);
				}
				else {
					add_text_option(OBFUSCATE("~c~Free Slot"));
				}
			}
		} break;
	case 4: {
			for (std::int32_t i = 0; i < 32; i++) {
				if (NETWORK::NETWORK_IS_PLAYER_ACTIVE(i)) {
					std::string s = PLAYER::GET_PLAYER_NAME(i);
					if (PLAYER::PLAYER_ID() == i)
						s += " ~g~[ME]";
					if (is_player_session_host(i) && is_player_freemode_host(i))
						s += " ~y~[SF-HOST]";
					else {
						if (is_player_session_host(i))
							s += " ~y~[S-HOST]";
						if (is_player_freemode_host(i))
							s += " ~r~[F-HOST]";
					}
					//if (is_player_next_session_host(i))
					//	s += " ~r~[NS-HOST]";
					if (NETWORK::NETWORK_PLAYER_IS_ROCKSTAR_DEV(i))
						s += " ~y~[ROCKSTAR]";
					if (NETWORK::_NETWORK_PLAYER_IS_CHEATER(i))
						s += " ~b~[CHEATER]";
					//if (NETWORK::NETWORK_IS_IN_SESSION()) {
					//	if (get_player_cash(i) >= 10000000)
					//		s += " ~g~[RICH]";
					//	if (get_player_cash(i) < 10000000)
					//		s += " ~b~[POOR]";
					//}
					if (is_player_friend(i))
						s += " ~g~[FRIEND]";
					if (is_player_in_passive_mode(i))
						s += " ~c~[PASSIVE]";
					if (is_player_quantum_user(i))
						s += " ~r~[QTM]";
					if (is_player_using_oppressor(i))
						s += " ~o~[OPPRESSOR]";
					if (is_player_using_tank(i))
						s += " ~o~[TANK]";
					//if (add_text_option(s)) {
					//	if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle)) {
					//		for (std::int32_t j = 0; j < sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence) / sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence[0]); j++) {
					//			if (g_pedestrian_peds[g_selected_pedestrian].task_sequence[j][0] == NULL) {
					//				g_pedestrian_peds[g_selected_pedestrian].task_sequence[j][0] = g_pedestrian_task_sequence_add;
					//				g_pedestrian_peds[g_selected_pedestrian].task_sequence[j][1] = i;

					//				std::stringstream ss;
					//				ss << "~g~Success: ~s~Added teleport to ~b~" << PLAYER::GET_PLAYER_NAME(i) << " ~s~from ~y~" << g_pedestrian_peds[g_selected_pedestrian].name << "~s~.";
					//				print_notification(7000, ss.str());
					//				pop_menu();
					//				break;
					//			}
					//		}
					//	}
					//}
					//if (i == CURRENT_OPTION - 1)
					//	draw_player_info_box(i);
				}
				else {
					add_text_option(OBFUSCATE("~c~Free Slot"));
				}
			}
		} break;
	case 5: {
			for (std::int32_t i = 0; i < 32; i++) {
				if (NETWORK::NETWORK_IS_PLAYER_ACTIVE(i)) {
					std::string s = PLAYER::GET_PLAYER_NAME(i);
					if (PLAYER::PLAYER_ID() == i)
						s += " ~g~[ME]";
					//if (is_player_session_host(i) && is_player_freemode_host(i))
					//	s += " ~y~[SF-HOST]";
					//else {
					//	if (is_player_session_host(i))
					//		s += " ~y~[S-HOST]";
					//	if (is_player_freemode_host(i))
					//		s += " ~r~[F-HOST]";
					//}
					//if (is_player_next_session_host(i))
					//	s += " ~r~[NS-HOST]";
					if (NETWORK::NETWORK_PLAYER_IS_ROCKSTAR_DEV(i))
						s += " ~y~[ROCKSTAR]";
					if (NETWORK::_NETWORK_PLAYER_IS_CHEATER(i))
						s += " ~b~[CHEATER]";
					//if (NETWORK::NETWORK_IS_IN_SESSION()) {
					//	if (get_player_cash(i) >= 10000000)
					//		s += " ~g~[RICH]";
					//	if (get_player_cash(i) < 10000000)
					//		s += " ~b~[POOR]";
					//}
					if (is_player_friend(i))
						s += " ~g~[FRIEND]";
					if (is_player_in_passive_mode(i))
						s += " ~c~[PASSIVE]";
					if (is_player_quantum_user(i))
						s += " ~r~[QTM]";
					if (is_player_using_oppressor(i))
						s += " ~o~[OPPRESSOR]";
					if (is_player_using_tank(i))
						s += " ~o~[TANK]";
					//if (add_text_option(s)) {
					//	if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle)) {
					//		for (std::int32_t j = 0; j < sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence) / sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence[0]); j++) {
					//			if (g_pedestrian_peds[g_selected_pedestrian].task_sequence[j][0] == NULL) {
					//				g_pedestrian_peds[g_selected_pedestrian].task_sequence[j][0] = g_pedestrian_task_sequence_add;
					//				g_pedestrian_peds[g_selected_pedestrian].task_sequence[j][1] = i;

					//				std::stringstream ss;
					//				ss << "~g~Success: ~s~Added follow ~b~" << PLAYER::GET_PLAYER_NAME(i) << " ~s~from ~y~" << g_pedestrian_peds[g_selected_pedestrian].name << "~s~.";
					//				print_notification(7000, ss.str());
					//				pop_menu();
					//				break;
					//			}
					//		}
					//	}
					//}
					//if (i == CURRENT_OPTION - 1)
					//	draw_player_info_box(i);
				}
				else {
					add_text_option(OBFUSCATE("~c~Free Slot"));
				}
			}
		} break;
	case 6: {
			add_editor_option(true, g_pedestrian_enter_vehicle_radius, &g_pedestrian_enter_vehicle_radius, 10.0f, 50.0f, 1.0f, OBFUSCATE("Radius"));
			add_string_array_option(true, g_pedestrian_enter_vehicle, (std::int32_t)std::size(g_pedestrian_enter_vehicle), &g_pedestrian_enter_vehicle_seat, OBFUSCATE("Seat Index"));
			ListPool* vehicle_pool = *(ListPool**)(GTA_VEH_LIST_POOL);
			if (vehicle_pool != nullptr) {

				std::uint32_t found_vehicles = NULL;
				for (std::int32_t i = 0; i < vehicle_pool->capacity; i++) {

					std::uint64_t vehicle_entity = vehicle_pool->get(i);
					if (vehicle_entity == NULL)
						continue;

					//if (!ENTITY::IS_ENTITY_AT_ENTITY(g_pedestrian_peds[g_selected_pedestrian].handle, vehicle, g_pedestrian_enter_vehicle_radius, g_pedestrian_enter_vehicle_radius, g_pedestrian_enter_vehicle_radius, 0, 1, 0))
					//	continue;

					//if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle)) {
					//	Vector3 ped_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_pedestrian_peds[g_selected_pedestrian].handle, 0.0f, 0.0f, 0.0f);
					//	Vector3 vehicle_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(vehicle, 0.0f, 0.0f, 0.0f);
					//	GRAPHICS::DRAW_LINE(ped_coords.x, ped_coords.y, ped_coords.z, vehicle_coords.x, vehicle_coords.y, vehicle_coords.z, g_menu_header_text_colour.r, g_menu_header_text_colour.g, g_menu_header_text_colour.b, g_menu_header_text_colour.a);
					//}
				}
			}
		} break;
	case 8: {
			for (std::int32_t i = 0; i < 32; i++) {
				if (NETWORK::NETWORK_IS_PLAYER_ACTIVE(i)) {
					std::string s = PLAYER::GET_PLAYER_NAME(i);
					if (PLAYER::PLAYER_ID() == i)
						s += " ~g~[ME]";
/*					if (is_player_session_host(i) && is_player_freemode_host(i))
						s += " ~y~[SF-HOST]";
					else {
						if (is_player_session_host(i))
							s += " ~y~[S-HOST]";
						if (is_player_freemode_host(i))
							s += " ~r~[F-HOST]";
					}
					if (is_player_next_session_host(i))
						s += " ~r~[NS-HOST]";*/
					if (NETWORK::NETWORK_PLAYER_IS_ROCKSTAR_DEV(i))
						s += " ~y~[ROCKSTAR]";
					if (NETWORK::_NETWORK_PLAYER_IS_CHEATER(i))
						s += " ~b~[CHEATER]";
					//if (NETWORK::NETWORK_IS_IN_SESSION()) {
					//	if (get_player_cash(i) >= 10000000)
					//		s += " ~g~[RICH]";
					//	if (get_player_cash(i) < 10000000)
					//		s += " ~b~[POOR]";
					//}
					if (is_player_friend(i))
						s += " ~g~[FRIEND]";
					if (is_player_in_passive_mode(i))
						s += " ~c~[PASSIVE]";
					if (is_player_quantum_user(i))
						s += " ~r~[QTM]";
					if (is_player_using_oppressor(i))
						s += " ~o~[OPPRESSOR]";
					if (is_player_using_tank(i))
						s += " ~o~[TANK]";
					//if (add_text_option(s)) {
					//	if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle)) {
					//		for (std::int32_t j = 0; j < sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence) / sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence[0]); j++) {
					//			if (g_pedestrian_peds[g_selected_pedestrian].task_sequence[j][0] == NULL) {
					//				g_pedestrian_peds[g_selected_pedestrian].task_sequence[j][0] = g_pedestrian_task_sequence_add;
					//				g_pedestrian_peds[g_selected_pedestrian].task_sequence[j][1] = i;

					//				std::stringstream ss;
					//				ss << "~g~Success: ~s~Added vehicle chase ~b~" << PLAYER::GET_PLAYER_NAME(i) << " ~s~from ~y~" << g_pedestrian_peds[g_selected_pedestrian].name << "~s~.";
					//				print_notification(7000, ss.str());
					//				pop_menu();
					//				break;
					//			}
					//		}
					//	}
					//}
					//if (i == CURRENT_OPTION - 1)
					//	draw_player_info_box(i);
				}
				else {
					add_text_option(OBFUSCATE("~c~Free Slot"));
				}
			}
		} break;
	case 9: {
			for (std::int32_t i = 0; i < 32; i++) {
				if (NETWORK::NETWORK_IS_PLAYER_ACTIVE(i)) {
					std::string s = PLAYER::GET_PLAYER_NAME(i);
					if (PLAYER::PLAYER_ID() == i)
						s += " ~g~[ME]";
					//if (is_player_session_host(i) && is_player_freemode_host(i))
					//	s += " ~y~[SF-HOST]";
					//else {
					//	if (is_player_session_host(i))
					//		s += " ~y~[S-HOST]";
					//	if (is_player_freemode_host(i))
					//		s += " ~r~[F-HOST]";
					//}
					//if (is_player_next_session_host(i))
						//s += " ~r~[NS-HOST]";
					if (NETWORK::NETWORK_PLAYER_IS_ROCKSTAR_DEV(i))
						s += " ~y~[ROCKSTAR]";
					if (NETWORK::_NETWORK_PLAYER_IS_CHEATER(i))
						s += " ~b~[CHEATER]";
					//if (NETWORK::NETWORK_IS_IN_SESSION()) {
					//	if (get_player_cash(i) >= 10000000)
					//		s += " ~g~[RICH]";
					//	if (get_player_cash(i) < 10000000)
					//		s += " ~b~[POOR]";
					//}
					if (is_player_friend(i))
						s += " ~g~[FRIEND]";
					if (is_player_in_passive_mode(i))
						s += " ~c~[PASSIVE]";
					if (is_player_quantum_user(i))
						s += " ~r~[QTM]";
					if (is_player_using_oppressor(i))
						s += " ~o~[OPPRESSOR]";
					if (is_player_using_tank(i))
						s += " ~o~[TANK]";
					if (add_text_option(s)) {
						if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle)) {
							for (std::int32_t j = 0; j < sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence) / sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence[0]); j++) {
								if (g_pedestrian_peds[g_selected_pedestrian].task_sequence[j][0] == NULL) {
									g_pedestrian_peds[g_selected_pedestrian].task_sequence[j][0] = g_pedestrian_task_sequence_add;
									g_pedestrian_peds[g_selected_pedestrian].task_sequence[j][1] = i;

									std::stringstream ss;
									ss << "~g~Success: ~s~Added heli chase ~b~" << PLAYER::GET_PLAYER_NAME(i) << " ~s~from ~y~" << g_pedestrian_peds[g_selected_pedestrian].name << "~s~.";
									print_notification(7000, ss.str());
									pop_menu();
									break;
								}
							}
						}
					}
					if (i == CURRENT_OPTION - 1)
						draw_player_info_box(i);
				}
				else {
					add_text_option(OBFUSCATE("~c~Free Slot"));
				}
			}
		} break;
	case 10: {
			for (std::int32_t i = 0; i < 32; i++) {
				if (NETWORK::NETWORK_IS_PLAYER_ACTIVE(i)) {
					std::string s = PLAYER::GET_PLAYER_NAME(i);
					if (PLAYER::PLAYER_ID() == i)
						s += " ~g~[ME]";
					//if (is_player_session_host(i) && is_player_freemode_host(i))
					//	s += " ~y~[SF-HOST]";
					//else {
					//	if (is_player_session_host(i))
					//		s += " ~y~[S-HOST]";
					//	if (is_player_freemode_host(i))
					//		s += " ~r~[F-HOST]";
					//}
					//if (is_player_next_session_host(i))
					//	s += " ~r~[NS-HOST]";
					if (NETWORK::NETWORK_PLAYER_IS_ROCKSTAR_DEV(i))
						s += " ~y~[ROCKSTAR]";
					if (NETWORK::_NETWORK_PLAYER_IS_CHEATER(i))
						s += " ~b~[CHEATER]";
					//if (NETWORK::NETWORK_IS_IN_SESSION()) {
					//	if (get_player_cash(i) >= 10000000)
					//		s += " ~g~[RICH]";
					//	if (get_player_cash(i) < 10000000)
					//		s += " ~b~[POOR]";
					//}
					if (is_player_friend(i))
						s += " ~g~[FRIEND]";
					if (is_player_in_passive_mode(i))
						s += " ~c~[PASSIVE]";
					if (is_player_quantum_user(i))
						s += " ~r~[QTM]";
					if (is_player_using_oppressor(i))
						s += " ~o~[OPPRESSOR]";
					if (is_player_using_tank(i))
						s += " ~o~[TANK]";
					//if (add_text_option(s)) {
					//	if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle)) {
					//		for (std::int32_t j = 0; j < sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence) / sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence[0]); j++) {
					//			if (g_pedestrian_peds[g_selected_pedestrian].task_sequence[j][0] == NULL) {
					//				g_pedestrian_peds[g_selected_pedestrian].task_sequence[j][0] = g_pedestrian_task_sequence_add;
					//				g_pedestrian_peds[g_selected_pedestrian].task_sequence[j][1] = i;

					//				std::stringstream ss;
					//				ss << "~g~Success: ~s~Added plane chase ~b~" << PLAYER::GET_PLAYER_NAME(i) << " ~s~from ~y~" << g_pedestrian_peds[g_selected_pedestrian].name << "~s~.";
					//				print_notification(7000, ss.str());
					//				pop_menu();
					//				break;
					//			}
					//		}
					//	}
					//}
					//if (i == CURRENT_OPTION - 1)
					//	draw_player_info_box(i);
				}
				else {
					add_text_option(OBFUSCATE("~c~Free Slot"));
				}
			}
		} break;
	case 11: {
			for (std::int32_t i = 0; i < 32; i++) {
				if (NETWORK::NETWORK_IS_PLAYER_ACTIVE(i)) {
					std::string s = PLAYER::GET_PLAYER_NAME(i);
					if (PLAYER::PLAYER_ID() == i)
						s += " ~g~[ME]";
					//if (is_player_session_host(i) && is_player_freemode_host(i))
					//	s += " ~y~[SF-HOST]";
					//else {
					//	if (is_player_session_host(i))
					//		s += " ~y~[S-HOST]";
					//	if (is_player_freemode_host(i))
					//		s += " ~r~[F-HOST]";
					//}
					//if (is_player_next_session_host(i))
					//	s += " ~r~[NS-HOST]";
					if (NETWORK::NETWORK_PLAYER_IS_ROCKSTAR_DEV(i))
						s += " ~y~[ROCKSTAR]";
					if (NETWORK::_NETWORK_PLAYER_IS_CHEATER(i))
						s += " ~b~[CHEATER]";
					//if (NETWORK::NETWORK_IS_IN_SESSION()) {
					//	if (get_player_cash(i) >= 10000000)
					//		s += " ~g~[RICH]";
					//	if (get_player_cash(i) < 10000000)
					//		s += " ~b~[POOR]";
					//}
					if (is_player_friend(i))
						s += " ~g~[FRIEND]";
					if (is_player_in_passive_mode(i))
						s += " ~c~[PASSIVE]";
					if (is_player_quantum_user(i))
						s += " ~r~[QTM]";
					if (is_player_using_oppressor(i))
						s += " ~o~[OPPRESSOR]";
					if (is_player_using_tank(i))
						s += " ~o~[TANK]";
					//if (add_text_option(s)) {
					//	if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle)) {
					//		for (std::int32_t j = 0; j < sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence) / sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence[0]); j++) {
					//			if (g_pedestrian_peds[g_selected_pedestrian].task_sequence[j][0] == NULL) {
					//				g_pedestrian_peds[g_selected_pedestrian].task_sequence[j][0] = g_pedestrian_task_sequence_add;
					//				g_pedestrian_peds[g_selected_pedestrian].task_sequence[j][1] = i;

					//				std::stringstream ss;
					//				ss << "~g~Success: ~s~Added shoot at ~b~" << PLAYER::GET_PLAYER_NAME(i) << " ~s~from ~y~" << g_pedestrian_peds[g_selected_pedestrian].name << "~s~.";
					//				print_notification(7000, ss.str());
					//				pop_menu();
					//				break;
					//			}
					//		}
					//	}
					//}
					//if (i == CURRENT_OPTION - 1)
					//	draw_player_info_box(i);
				}
				else {
					add_text_option(OBFUSCATE("~c~Free Slot"));
				}
			}
		} break;
	case 12: {
			for (std::int32_t i = 0; i < 32; i++) {
				if (NETWORK::NETWORK_IS_PLAYER_ACTIVE(i)) {
					std::string s = PLAYER::GET_PLAYER_NAME(i);
					if (PLAYER::PLAYER_ID() == i)
						s += " ~g~[ME]";
					//if (is_player_session_host(i) && is_player_freemode_host(i))
					//	s += " ~y~[SF-HOST]";
					//else {
					//	if (is_player_session_host(i))
					//		s += " ~y~[S-HOST]";
					//	if (is_player_freemode_host(i))
					//		s += " ~r~[F-HOST]";
					//}
					//if (is_player_next_session_host(i))
					//	s += " ~r~[NS-HOST]";
					if (NETWORK::NETWORK_PLAYER_IS_ROCKSTAR_DEV(i))
						s += " ~y~[ROCKSTAR]";
					if (NETWORK::_NETWORK_PLAYER_IS_CHEATER(i))
						s += " ~b~[CHEATER]";
					//if (NETWORK::NETWORK_IS_IN_SESSION()) {
					//	if (get_player_cash(i) >= 10000000)
					//		s += " ~g~[RICH]";
					//	if (get_player_cash(i) < 10000000)
					//		s += " ~b~[POOR]";
					//}
					if (is_player_friend(i))
						s += " ~g~[FRIEND]";
					if (is_player_in_passive_mode(i))
						s += " ~c~[PASSIVE]";
					if (is_player_quantum_user(i))
						s += " ~r~[QTM]";
					if (is_player_using_oppressor(i))
						s += " ~o~[OPPRESSOR]";
					if (is_player_using_tank(i))
						s += " ~o~[TANK]";
					//if (add_text_option(s)) {
					//	if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle)) {
					//		for (std::int32_t j = 0; j < sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence) / sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence[0]); j++) {
					//			if (g_pedestrian_peds[g_selected_pedestrian].task_sequence[j][0] == NULL) {
					//				g_pedestrian_peds[g_selected_pedestrian].task_sequence[j][0] = g_pedestrian_task_sequence_add;
					//				g_pedestrian_peds[g_selected_pedestrian].task_sequence[j][1] = i;

					//				std::stringstream ss;
					//				ss << "~g~Success: ~s~Added aim at ~b~" << PLAYER::GET_PLAYER_NAME(i) << " ~s~from ~y~" << g_pedestrian_peds[g_selected_pedestrian].name << "~s~.";
					//				print_notification(7000, ss.str());
					//				pop_menu();
					//				break;
					//			}
					//		}
					//	}
					//}
					if (i == CURRENT_OPTION - 1)
						draw_player_info_box(i);
				}
				else {
					add_text_option(OBFUSCATE("~c~Free Slot"));
				}
			}
		} break;
	}

	if (g_selected_pedestrian_camera) {
		if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle) && !PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[g_selected_pedestrian].handle, 1)) {
			if (!CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				g_selected_pedestrian_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
				if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
					CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, true);
					CAM::RENDER_SCRIPT_CAMS(1, 1, 1500, 1, 0);
				}
			}
			else {
				std::int32_t analog_x_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_LR);
				std::int32_t analog_y_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_UD);
				g_pedestrian_right_angle1 -= (0.001f * (analog_x_right - 127));
				g_pedestrian_right_angle2 += (0.001f * (analog_y_right - 127));
				CAM::DETACH_CAM(g_selected_pedestrian_cam);
				CAM::ATTACH_CAM_TO_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 5.0f * cos(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 5.0f * sin(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 5.0f * sin(g_pedestrian_right_angle2), 0);
				CAM::POINT_CAM_AT_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 0, 0, 0, 1);
				if (g_pedestrian_right_angle1 <= -6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle1 >= 6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle2 > 1.2f)
					g_pedestrian_right_angle2 = 1.2f;
				if (g_pedestrian_right_angle2 < -1.2f)
					g_pedestrian_right_angle2 = -1.2f;
			}
		}
		else {
			if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, false);
				CAM::RENDER_SCRIPT_CAMS(0, 1, 1500, 1, 0);
				CAM::DESTROY_CAM(g_selected_pedestrian_cam, true);
			}
		}
	}
}
void menu_pedestrian_task_sequence_add_sequence() {
	if (add_submenu_option(menu_pedestrian_task_sequence_add_sequence_manager, OBFUSCATE("Give Weapon")))
		g_pedestrian_task_sequence_add = 1;
	if (add_submenu_option(menu_pedestrian_task_sequence_add_sequence_manager, OBFUSCATE("Fight Hated Targets")))
		g_pedestrian_task_sequence_add = 2;
	if (add_submenu_option(menu_pedestrian_task_sequence_add_sequence_manager, OBFUSCATE("Fight Ped")))
		g_pedestrian_task_sequence_add = 3;
	if (add_submenu_option(menu_pedestrian_task_sequence_add_sequence_manager, OBFUSCATE("Teleport To Entity")))
		g_pedestrian_task_sequence_add = 4;
	if (add_submenu_option(menu_pedestrian_task_sequence_add_sequence_manager, OBFUSCATE("Follow Entity")))
		g_pedestrian_task_sequence_add = 5;
	if (add_submenu_option(menu_pedestrian_task_sequence_add_sequence_manager, OBFUSCATE("Enter Vehicle")))
		g_pedestrian_task_sequence_add = 6;
	if (add_text_option(OBFUSCATE("Exit Vehicle"))) {
		g_pedestrian_task_sequence_add = 7;
		if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle)) {
			for (std::int32_t i = 0; i < sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence) / sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence[0]); i++) {
				if (g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][0] == NULL) {
					g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][0] = g_pedestrian_task_sequence_add;

					std::stringstream ss;
					ss << "~g~Success: ~s~Added exit vehicle ~y~" << g_pedestrian_peds[g_selected_pedestrian].name << "~s~.";
					print_notification(7000, ss.str());
					break;
				}
			}
		}
	}
	if (add_submenu_option(menu_pedestrian_task_sequence_add_sequence_manager, OBFUSCATE("Vehicle Chase Entity")))
		g_pedestrian_task_sequence_add = 8;
	if (add_submenu_option(menu_pedestrian_task_sequence_add_sequence_manager, OBFUSCATE("Heli Chase Entity")))
		g_pedestrian_task_sequence_add = 9;
	if (add_submenu_option(menu_pedestrian_task_sequence_add_sequence_manager, OBFUSCATE("Plane Chase Entity")))
		g_pedestrian_task_sequence_add = 10;
	if (add_submenu_option(menu_pedestrian_task_sequence_add_sequence_manager, OBFUSCATE("Shoot At Entity")))
		g_pedestrian_task_sequence_add = 11;
	if (add_submenu_option(menu_pedestrian_task_sequence_add_sequence_manager, OBFUSCATE("Aim At Entity")))
		g_pedestrian_task_sequence_add = 12;

	if (g_selected_pedestrian_camera) {
		if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle) && !PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[g_selected_pedestrian].handle, 1)) {
			if (!CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				g_selected_pedestrian_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
				if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
					CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, true);
					CAM::RENDER_SCRIPT_CAMS(1, 1, 1500, 1, 0);
				}
			}
			else {
				std::int32_t analog_x_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_LR);
				std::int32_t analog_y_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_UD);
				g_pedestrian_right_angle1 -= (0.001f * (analog_x_right - 127));
				g_pedestrian_right_angle2 += (0.001f * (analog_y_right - 127));
				CAM::DETACH_CAM(g_selected_pedestrian_cam);
				CAM::ATTACH_CAM_TO_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 5.0f * cos(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 5.0f * sin(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 5.0f * sin(g_pedestrian_right_angle2), 0);
				CAM::POINT_CAM_AT_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 0, 0, 0, 1);
				if (g_pedestrian_right_angle1 <= -6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle1 >= 6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle2 > 1.2f)
					g_pedestrian_right_angle2 = 1.2f;
				if (g_pedestrian_right_angle2 < -1.2f)
					g_pedestrian_right_angle2 = -1.2f;
			}
		}
		else {
			if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, false);
				CAM::RENDER_SCRIPT_CAMS(0, 1, 1500, 1, 0);
				CAM::DESTROY_CAM(g_selected_pedestrian_cam, true);
			}
		}
	}
}
void menu_pedestrian_task_sequence() {
	add_submenu_option(menu_pedestrian_task_sequence_add_sequence, OBFUSCATE("Add Sequence Event"));
	if (add_text_option(OBFUSCATE("Clear All Sequence Events"))) {
		if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle)) {
			for (std::int32_t j = 0; j < (std::int32_t)std::size(g_pedestrian_hated_targets); j++) {
				PED::CLEAR_RELATIONSHIP_BETWEEN_GROUPS(2, PED::GET_PED_RELATIONSHIP_GROUP_HASH(g_pedestrian_peds[g_selected_pedestrian].handle), GAMEPLAY::GET_HASH_KEY(g_pedestrian_hated_targets[j].c_str()));
				PED::CLEAR_RELATIONSHIP_BETWEEN_GROUPS(2, GAMEPLAY::GET_HASH_KEY(g_pedestrian_hated_targets[j].c_str()), PED::GET_PED_RELATIONSHIP_GROUP_HASH(g_pedestrian_peds[g_selected_pedestrian].handle));
			}

			for (std::int32_t r = 0; r < sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence) / sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence[0]); r++) //type, args
				for (std::int32_t c = 0; c < sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence[0]) / sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence[0][0]); c++)
					g_pedestrian_peds[g_selected_pedestrian].task_sequence[r][c] = NULL;
			AI::CLEAR_PED_TASKS_IMMEDIATELY(g_pedestrian_peds[g_selected_pedestrian].handle);

			std::stringstream ss;
			ss << "~g~Success:~s~ Cleared all pedestrian ~y~" << g_pedestrian_peds[g_selected_pedestrian].name << " ~s~sequence task events.";
			print_notification(7000, ss.str());
		}
	}
	add_break_option(OBFUSCATE("Current Sequence Events"));
	if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle)) {
		for (std::int32_t i = 0; i < sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence) / sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence[0]); i++) { //type, args
			if (g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][0] != NULL) {
				std::stringstream ss;
				switch (g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][0]) { //0 type, 1+ args
				case 1: ss << "~c~Give Weapon " << weapon_hashs[g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][1]].name; break;
				case 2: ss << "~c~Fight Hated Targets"; break;
				case 3: ss << "~c~Fight " << PLAYER::GET_PLAYER_NAME(g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][1]); break;
				case 4: ss << "~c~Teleport To " << PLAYER::GET_PLAYER_NAME(g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][1]); break;
				case 5: ss << "~c~Follow " << PLAYER::GET_PLAYER_NAME(g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][1]); break;
				case 6: ss << "~c~Enter " << UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][1]))); break;
				case 7: ss << "~c~Exit Vehicle"; break;
				case 8: ss << "~c~Vehicle Chase " << PLAYER::GET_PLAYER_NAME(g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][1]); break;
				case 9: ss << "~c~Heli Chase " << PLAYER::GET_PLAYER_NAME(g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][1]); break;
				case 10: ss << "~c~Plane Chase " << PLAYER::GET_PLAYER_NAME(g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][1]); break;
				case 11: ss << "~c~Shoot At " << PLAYER::GET_PLAYER_NAME(g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][1]); break;
				case 12: ss << "~c~Aim At " << PLAYER::GET_PLAYER_NAME(g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][1]); break;
				}
				add_text_option(ss.str());
				if (CURRENT_OPTION == OPTION_COUNT) { //delete
					if (g_option_alt_pressed) {
						switch (g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][0]) {
						case 2: {
								for (std::int32_t j = 0; j < (std::int32_t)std::size(g_pedestrian_hated_targets); j++) {
									PED::CLEAR_RELATIONSHIP_BETWEEN_GROUPS(2, PED::GET_PED_RELATIONSHIP_GROUP_HASH(g_pedestrian_peds[g_selected_pedestrian].handle), GAMEPLAY::GET_HASH_KEY(g_pedestrian_hated_targets[j].c_str()));
									PED::CLEAR_RELATIONSHIP_BETWEEN_GROUPS(2, GAMEPLAY::GET_HASH_KEY(g_pedestrian_hated_targets[j].c_str()), PED::GET_PED_RELATIONSHIP_GROUP_HASH(g_pedestrian_peds[g_selected_pedestrian].handle));
								}
								AI::CLEAR_PED_TASKS_IMMEDIATELY(g_pedestrian_peds[g_selected_pedestrian].handle);
							} break;
						case 3:
						case 5:
						case 8:
						case 9:
						case 10:
						case 11:
						case 12: {
								AI::CLEAR_PED_TASKS_IMMEDIATELY(g_pedestrian_peds[g_selected_pedestrian].handle);
							} break;
						}
						for (std::int32_t c = 0; c < sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence[0]) / sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence[0][0]); c++)
							g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][c] = NULL;
					}
				}
			}
		}
		if (add_text_option(OBFUSCATE("Activate Sequence Events"))) {
			//BRAIN::OPEN_SEQUENCE_TASK(&g_pedestrian_peds[g_selected_pedestrian].task_sequence_active);
			for (std::int32_t i = 0; i < sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence) / sizeof(g_pedestrian_peds[g_selected_pedestrian].task_sequence[0]); i++) { //type, args
				if (g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][0] != NULL) {
					switch (g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][0]) {
					case 1: {
							WEAPON::GIVE_DELAYED_WEAPON_TO_PED(g_pedestrian_peds[g_selected_pedestrian].handle, weapon_hashs[g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][1]].hash, 1337, TRUE);
							WEAPON::SET_CURRENT_PED_WEAPON(g_pedestrian_peds[g_selected_pedestrian].handle, weapon_hashs[g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][1]].hash, TRUE);
						} break;
					case 2: {
							AI::TASK_COMBAT_HATED_TARGETS_AROUND_PED(g_pedestrian_peds[g_selected_pedestrian].handle, (std::float_t)g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][1], 0);
						} break;
					case 3: {
							AI::TASK_COMBAT_PED(g_pedestrian_peds[g_selected_pedestrian].handle, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][1]), 0, 16);
						} break;
					case 4: {
							Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][1]), 0.0f, 0.0f, 0.0f);
							ENTITY::SET_ENTITY_COORDS(g_pedestrian_peds[g_selected_pedestrian].handle, coords.x, coords.y, coords.z, 1, 0, 0, 1);
						} break;
					case 5: {
							AI::TASK_FOLLOW_TO_OFFSET_OF_ENTITY(g_pedestrian_peds[g_selected_pedestrian].handle, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][1]), 0.0f, 0.0f, 0.0f, 100.0f, -1, 2.0f, TRUE);
						} break;
					case 6: {
							PED::SET_PED_INTO_VEHICLE(g_pedestrian_peds[g_selected_pedestrian].handle, g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][1], (g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][2] - 1));
						} break;
					case 7: {
							if (PED::IS_PED_IN_ANY_VEHICLE(g_pedestrian_peds[g_selected_pedestrian].handle, FALSE))
								AI::TASK_LEAVE_VEHICLE(g_pedestrian_peds[g_selected_pedestrian].handle, PED::GET_VEHICLE_PED_IS_IN(g_pedestrian_peds[g_selected_pedestrian].handle, FALSE), 0);
						} break;
					case 8: {
							if (PED::IS_PED_IN_ANY_VEHICLE(g_pedestrian_peds[g_selected_pedestrian].handle, FALSE))
								AI::TASK_VEHICLE_CHASE(g_pedestrian_peds[g_selected_pedestrian].handle, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][1]));
						} break;
					case 9: {
							if (PED::IS_PED_IN_ANY_HELI(g_pedestrian_peds[g_selected_pedestrian].handle)) {
								Hash ped_relationship_hash;
								PED::ADD_RELATIONSHIP_GROUP("hated", &ped_relationship_hash);
								PED::SET_PED_RELATIONSHIP_GROUP_HASH(g_pedestrian_peds[g_selected_pedestrian].handle, ped_relationship_hash);

								PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, ped_relationship_hash, GAMEPLAY::GET_HASH_KEY("PLAYER"));
								PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, GAMEPLAY::GET_HASH_KEY("PLAYER"), ped_relationship_hash);
								AI::TASK_HELI_CHASE(g_pedestrian_peds[g_selected_pedestrian].handle, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][1]), 0.0f, 0.0f, 10.0f);
							}
						} break;
					case 10: {
							if (PED::IS_PED_IN_ANY_PLANE(g_pedestrian_peds[g_selected_pedestrian].handle)) {
								Hash ped_relationship_hash;
								PED::ADD_RELATIONSHIP_GROUP("hated", &ped_relationship_hash);
								PED::SET_PED_RELATIONSHIP_GROUP_HASH(g_pedestrian_peds[g_selected_pedestrian].handle, ped_relationship_hash);

								PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, ped_relationship_hash, GAMEPLAY::GET_HASH_KEY("PLAYER"));
								PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, GAMEPLAY::GET_HASH_KEY("PLAYER"), ped_relationship_hash);
								AI::TASK_PLANE_CHASE(g_pedestrian_peds[g_selected_pedestrian].handle, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][1]), 0.0f, 0.0f, 40.0f);
							}
						} break;
					case 11: {
							AI::TASK_SHOOT_AT_ENTITY(g_pedestrian_peds[g_selected_pedestrian].handle, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][1]), -1, GAMEPLAY::GET_HASH_KEY("FIRING_PATTERN_FULL_AUTO"));
						} break;
					case 12: {
							AI::TASK_AIM_GUN_AT_ENTITY(g_pedestrian_peds[g_selected_pedestrian].handle, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_pedestrian_peds[g_selected_pedestrian].task_sequence[i][1]), -1, true);
						} break;
					}
				}
			}
			//BRAIN::CLOSE_SEQUENCE_TASK(g_pedestrian_peds[g_selected_pedestrian].task_sequence_active);
			//BRAIN::SET_SEQUENCE_TO_REPEAT(g_pedestrian_peds[g_selected_pedestrian].task_sequence_active, TRUE);
            //BRAIN::TASK_PERFORM_SEQUENCE(g_pedestrian_peds[g_selected_pedestrian].handle, g_pedestrian_peds[g_selected_pedestrian].task_sequence_active);
			//BRAIN::CLEAR_SEQUENCE_TASK(&g_pedestrian_peds[g_selected_pedestrian].task_sequence_active);
			
			std::stringstream ss;
			ss << "~g~Success:~s~ Activated all pedestrian ~y~" << g_pedestrian_peds[g_selected_pedestrian].name << " ~s~sequence task events.";
			print_notification(7000, ss.str());
		}
	}

	if (g_selected_pedestrian_camera) {
		if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle) && !PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[g_selected_pedestrian].handle, 1)) {
			if (!CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				g_selected_pedestrian_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
				if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
					CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, true);
					CAM::RENDER_SCRIPT_CAMS(1, 1, 1500, 1, 0);
				}
			}
			else {
				std::int32_t analog_x_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_LR);
				std::int32_t analog_y_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_UD);
				g_pedestrian_right_angle1 -= (0.001f * (analog_x_right - 127));
				g_pedestrian_right_angle2 += (0.001f * (analog_y_right - 127));
				CAM::DETACH_CAM(g_selected_pedestrian_cam);
				CAM::ATTACH_CAM_TO_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 5.0f * cos(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 5.0f * sin(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 5.0f * sin(g_pedestrian_right_angle2), 0);
				CAM::POINT_CAM_AT_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 0, 0, 0, 1);
				if (g_pedestrian_right_angle1 <= -6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle1 >= 6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle2 > 1.2f)
					g_pedestrian_right_angle2 = 1.2f;
				if (g_pedestrian_right_angle2 < -1.2f)
					g_pedestrian_right_angle2 = -1.2f;
			}
		}
		else {
			if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, false);
				CAM::RENDER_SCRIPT_CAMS(0, 1, 1500, 1, 0);
				CAM::DESTROY_CAM(g_selected_pedestrian_cam, true);
			}
		}
	}
}
void menu_pedestrian_select_manager() {
	add_keyboard_option(true, &g_pedestrian_peds[g_selected_pedestrian].name, 64, "Change Pedestrian Name");
	add_submenu_option(menu_pedestrian_outfit_editor, OBFUSCATE("Outfit Editor"));
	add_submenu_option(menu_pedestrian_animation, OBFUSCATE("Animations"));
	add_submenu_option(menu_pedestrian_scenarios, OBFUSCATE("Scenarios"));
	add_submenu_option(menu_pedestrian_task_sequence, OBFUSCATE("Task Sequence"));
	if (add_text_option(OBFUSCATE("Teleport To Me"))) {
		Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, 0.0f, 0.0f);
		ENTITY::SET_ENTITY_COORDS(g_pedestrian_peds[g_selected_pedestrian].handle, coords.x, coords.y, coords.z, 1, 0, 0, 1);

		std::stringstream ss;
		ss << "~g~Success:~s~ Teleported Pedestrian ~y~" << g_pedestrian_peds[g_selected_pedestrian].name << " ~s~To Me.";
		print_notification(7000, ss.str());
	}
	if (add_toggle_option(&g_pedestrian_peds[g_selected_pedestrian].is_invincible, "Invincible")) {
		if (!g_pedestrian_peds[g_selected_pedestrian].is_invincible)
			ENTITY::SET_ENTITY_PROOFS(g_pedestrian_peds[g_selected_pedestrian].handle, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE);
	}
	if (add_toggle_option(&g_pedestrian_peds[g_selected_pedestrian].is_invisible, OBFUSCATE("Invisible"))) {
		if (!g_pedestrian_peds[g_selected_pedestrian].is_invisible)
			ENTITY::SET_ENTITY_VISIBLE(g_pedestrian_peds[g_selected_pedestrian].handle, TRUE, 0);
	}
	if (add_text_option(OBFUSCATE("Set As Bodyguard"))) {
		std::int32_t count = NULL;
		for (auto ped : g_pedestrian_peds)
			if (ped.is_bodyguard)
				count++;
		if (count < 9) {
			if (!g_pedestrian_peds[g_selected_pedestrian].is_bodyguard) {
				std::int32_t group = PED::GET_PED_GROUP_INDEX(PLAYER::PLAYER_PED_ID());
				if (PED::DOES_GROUP_EXIST(group)) {
					AI::CLEAR_PED_TASKS_IMMEDIATELY(g_pedestrian_peds[g_selected_pedestrian].handle);
					PED::REMOVE_PED_FROM_GROUP(g_pedestrian_peds[g_selected_pedestrian].handle);
					PED::SET_PED_AS_GROUP_MEMBER(g_pedestrian_peds[g_selected_pedestrian].handle, group);
					PED::SET_PED_NEVER_LEAVES_GROUP(g_pedestrian_peds[g_selected_pedestrian].handle, true);

					Hash my_relationship_hash = PED::GET_PED_RELATIONSHIP_GROUP_HASH(PLAYER::PLAYER_PED_ID());
					Hash group_relationship_hash;
					PED::ADD_RELATIONSHIP_GROUP("bodyguard", &group_relationship_hash);
					PED::SET_PED_RELATIONSHIP_GROUP_HASH(g_pedestrian_peds[g_selected_pedestrian].handle, group_relationship_hash);
					PED::SET_RELATIONSHIP_BETWEEN_GROUPS(0, my_relationship_hash, group_relationship_hash);
					PED::SET_RELATIONSHIP_BETWEEN_GROUPS(0, group_relationship_hash, my_relationship_hash);
				}
				g_pedestrian_peds[g_selected_pedestrian].is_bodyguard = true;

				std::stringstream ss;
				ss << "~g~Success:~s~ ~y~" << g_pedestrian_peds[g_selected_pedestrian].name << "~s~ is now a bodyguard.";
				print_notification(7000, ss.str());
			}
			else print_notification(7000, "~r~Error:~s~ This ped is already a bodyguard.");
		}
		else print_notification(7000, "~r~Error:~s~ The max amount of bodyguards has been reached.");
	}
	if (add_text_option(OBFUSCATE("Remove Bodyguard"))) {
		if (g_pedestrian_peds[g_selected_pedestrian].is_bodyguard) {
			PED::SET_PED_NEVER_LEAVES_GROUP(g_pedestrian_peds[g_selected_pedestrian].handle, false);
			PED::REMOVE_PED_FROM_GROUP(g_pedestrian_peds[g_selected_pedestrian].handle);
			g_pedestrian_peds[g_selected_pedestrian].is_bodyguard = false;

			std::stringstream ss;
			ss << "~g~Success:~s~ ~y~" << g_pedestrian_peds[g_selected_pedestrian].name << "~s~ is no longer a bodyguard.";
			print_notification(7000, ss.str());
		}
		else print_notification(7000, "~r~Error:~s~ This ped is not a bodyguard.");
	}
	add_toggle_option(&g_pedestrian_peds[g_selected_pedestrian].draw_esp, OBFUSCATE("ESP"));
	if (add_text_option(OBFUSCATE("Commit Suicide"))) {
		suicide_ped(g_pedestrian_peds[g_selected_pedestrian].handle);

		std::stringstream ss;
		ss << "~g~Success:~s~ Pedestrian ~y~" << g_pedestrian_peds[g_selected_pedestrian].name << " ~s~Commited Suicide.";
		print_notification(7000, ss.str());
	}
	if (add_text_option(OBFUSCATE("Drop Dead"))) {
		ENTITY::SET_ENTITY_HEALTH(g_pedestrian_peds[g_selected_pedestrian].handle, 0);
		g_pedestrian_peds[g_selected_pedestrian].is_bodyguard = false;

		std::stringstream ss;
		ss << "~g~Success:~s~ Pedestrian ~y~" << g_pedestrian_peds[g_selected_pedestrian].name << " ~s~Dropped Dead.";
		print_notification(7000, ss.str());
	}

	if (g_selected_pedestrian_camera) {
		if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[g_selected_pedestrian].handle) && !PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[g_selected_pedestrian].handle, 1)) {
			if (!CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				g_selected_pedestrian_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
				if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
					CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, true);
					CAM::RENDER_SCRIPT_CAMS(1, 1, 1500, 1, 0);
				}
			}
			else {
				std::int32_t analog_x_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_LR);
				std::int32_t analog_y_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_UD);
				g_pedestrian_right_angle1 -= (0.001f * (analog_x_right - 127));
				g_pedestrian_right_angle2 += (0.001f * (analog_y_right - 127));
				CAM::DETACH_CAM(g_selected_pedestrian_cam);
				CAM::ATTACH_CAM_TO_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 5.0f * cos(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 5.0f * sin(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 5.0f * sin(g_pedestrian_right_angle2), 0);
				CAM::POINT_CAM_AT_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[g_selected_pedestrian].handle, 0, 0, 0, 1);
				if (g_pedestrian_right_angle1 <= -6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle1 >= 6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle2 > 1.2f)
					g_pedestrian_right_angle2 = 1.2f;
				if (g_pedestrian_right_angle2 < -1.2f)
					g_pedestrian_right_angle2 = -1.2f;
			}
		}
		else {
			if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, false);
				CAM::RENDER_SCRIPT_CAMS(0, 1, 1500, 1, 0);
				CAM::DESTROY_CAM(g_selected_pedestrian_cam, true);
			}
		}
	}
}
void menu_pedestrian_manage() {
	add_toggle_option(&g_selected_pedestrian_camera, "Pedestrian Camera");
	add_submenu_option(menu_pedestrian_all_manager, OBFUSCATE("Manage All Pedestrians"));
	for (auto i = 0; i < std::size(g_pedestrian_peds); i++) {
		if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[i].handle)) {
			if (!PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[i].handle, 1)) {
				if (i == CURRENT_OPTION - 3) {
					draw_pedestrian_info_box(g_pedestrian_peds[i]);

					Vector3 ped_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_pedestrian_peds[i].handle, 0.0f, 0.0f, 0.0f);
					GRAPHICS::DRAW_MARKER(0, ped_coords.x, ped_coords.y, ped_coords.z + 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.8f, 0.8f, 0.8f, g_menu_header_text_colour.r, g_menu_header_text_colour.g, g_menu_header_text_colour.b, g_menu_header_text_colour.a, false, false, 2, true, false, false, false);
				}
				if (add_submenu_option(menu_pedestrian_select_manager, g_pedestrian_peds[i].name))
					g_selected_pedestrian = i;
			}
			else { 
				std::stringstream ss;
				ss << g_pedestrian_peds[i].name << " ~c~[DEAD]";
				add_text_option(ss.str());

				//reset sequence events
				for (std::int32_t r = 0; r < sizeof(g_pedestrian_peds[i].task_sequence) / sizeof(g_pedestrian_peds[i].task_sequence[0]); r++) //type, args
					for (std::int32_t c = 0; c < sizeof(g_pedestrian_peds[i].task_sequence[0]) / sizeof(g_pedestrian_peds[i].task_sequence[0][0]); c++)
						g_pedestrian_peds[i].task_sequence[r][c] = NULL;
			}
		}
		else { 
			add_text_option("~c~Free Slot");

			//reset sequence events
			for (std::int32_t r = 0; r < sizeof(g_pedestrian_peds[i].task_sequence) / sizeof(g_pedestrian_peds[i].task_sequence[0]); r++) //type, args
				for (std::int32_t c = 0; c < sizeof(g_pedestrian_peds[i].task_sequence[0]) / sizeof(g_pedestrian_peds[i].task_sequence[0][0]); c++)
					g_pedestrian_peds[i].task_sequence[r][c] = NULL;
		}
	}

	//create cam
	if (g_selected_pedestrian_camera) {
		if (CURRENT_OPTION > 2 && ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[CURRENT_OPTION - 3].handle) && !PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[CURRENT_OPTION - 3].handle, 1)) {
			if (!CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				g_selected_pedestrian_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
				if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
					CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, true);
					CAM::RENDER_SCRIPT_CAMS(1, 1, 1500, 1, 0);
				}
			}
			else {
				std::int32_t analog_x_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_LR);
				std::int32_t analog_y_right = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_UD);
				g_pedestrian_right_angle1 -= (0.001f * (analog_x_right - 127));
				g_pedestrian_right_angle2 += (0.001f * (analog_y_right - 127));
				CAM::DETACH_CAM(g_selected_pedestrian_cam);
				CAM::ATTACH_CAM_TO_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[CURRENT_OPTION - 3].handle, 5.0f * cos(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 5.0f * sin(g_pedestrian_right_angle1) * cos(g_pedestrian_right_angle2), 5.0f * sin(g_pedestrian_right_angle2), 0);
				CAM::POINT_CAM_AT_ENTITY(g_selected_pedestrian_cam, g_pedestrian_peds[CURRENT_OPTION - 3].handle, 0, 0, 0, 1);
				if (g_pedestrian_right_angle1 <= -6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle1 >= 6.25f)
					g_pedestrian_right_angle1 = 0.00f;
				if (g_pedestrian_right_angle2 > 1.2f)
					g_pedestrian_right_angle2 = 1.2f;
				if (g_pedestrian_right_angle2 < -1.2f)
					g_pedestrian_right_angle2 = -1.2f;
			}
		}
		else {
			if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
				CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, false);
				CAM::RENDER_SCRIPT_CAMS(0, 1, 1500, 1, 0);
				CAM::DESTROY_CAM(g_selected_pedestrian_cam, true);
			}
		}
	}
}
void menu_pedestrian() {
	add_submenu_option(menu_pedestrian_manage, OBFUSCATE("Manage Pedestrians"));
	add_keyboard_option(true, &g_loaded_list_file_peds_filter, 32, OBFUSCATE("Search For Model"));
	add_break_option(OBFUSCATE("Loaded Models"));
	if (g_loaded_list_file_peds_did_load) {
		for (auto model : g_loaded_list_file_peds) {
			if (!g_loaded_list_file_peds_filter.empty()) {
				if (model.find(g_loaded_list_file_peds_filter) != std::string::npos)
					if (add_text_option(model)) {
						std::int32_t count = NULL;
						for (auto i = 0; i < std::size(g_pedestrian_peds); i++) {
							count++;
							if (count != std::size(g_pedestrian_peds)) {
								if (!ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[i].handle) || PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[i].handle, 1)) {
									std::int32_t ped = spawn_ped(GAMEPLAY::GET_HASH_KEY(model.c_str()), ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, 0.0f, 0.0f), ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
									if (ENTITY::DOES_ENTITY_EXIST(ped)) {
										g_pedestrian_peds[i].handle = ped;
										g_pedestrian_peds[i].name = model;
										break;
									}
									else print_notification(7000, "~r~Error:~s~ Failed to spawn ped.");
								}
							}
							else { print_notification(7000, "~r~Error:~s~ Maximum spawned peds reached."); }
						}
					}
			}
			else if (add_text_option(model)) {
				std::int32_t count = NULL;
				for (auto i = 0; i < std::size(g_pedestrian_peds); i++) {
					count++;
					if (count != std::size(g_pedestrian_peds)) {
						if (!ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[i].handle) || PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[i].handle, 1)) {
							std::int32_t ped = spawn_ped(GAMEPLAY::GET_HASH_KEY(model.c_str()), ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, 0.0f, 0.0f), ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
							if (ENTITY::DOES_ENTITY_EXIST(ped)) {
								g_pedestrian_peds[i].handle = ped;
								g_pedestrian_peds[i].name = model;
								break;
							}
							else print_notification(7000, "~r~Error:~s~ Failed to spawn ped.");
						}
					}
					else { print_notification(7000, "~r~Error:~s~ Maximum spawned peds reached."); }
				}
			}
		}
	}
	else { add_text_option(OBFUSCATE("\"ped_models.txt\" failed to load")); }

	if (CAM::DOES_CAM_EXIST(g_selected_pedestrian_cam)) {
		CAM::SET_CAM_ACTIVE(g_selected_pedestrian_cam, false);
		CAM::RENDER_SCRIPT_CAMS(0, 1, 1500, 1, 0);
		CAM::DESTROY_CAM(g_selected_pedestrian_cam, true);
	}
}

/*
lsc camera
fly vehicle
vehicle trails
vehicle speedometer
NiNJA:
preset handling
container rider
heli bomber
RPM
Torque
Headlight Brightness
Rim Scale
drive types
custom vehicle textures (Quantum)
fuel mod
manual transmission
hover mode -> name different redo
super handling
vehicle hydraulics
tow truck mode
paint display rect
*/

void menu_vehicle_spawner_spawn() {
	ListPool* model_info_pool = (ListPool*)(GTA_MODEL_INFO_LIST_POOL);
	if (model_info_pool != nullptr) {
		for (std::int32_t i = 0; i < model_info_pool->capacity; i++) {
			std::uint64_t info = model_info_pool->get(i);
			if (info != NULL) {
				if ((*(BYTE*)(info + 157) & 0x1F) == 5) {
					char* make_ptr = (char*)(info + 0x2A4);
					char* model_ptr = (char*)(info + 0x298);
					if (VEHICLE::GET_VEHICLE_CLASS_FROM_NAME(GAMEPLAY::GET_HASH_KEY(model_ptr)) == g_vehicle_spawner_selected_class) {
						std::stringstream ss;
						std::string make(make_ptr);
						std::string model(model_ptr);

						if (make[0] || model[0]) {
							make = UI::_GET_LABEL_TEXT(make.c_str());
							model = UI::_GET_LABEL_TEXT(model.c_str());

							if (make != "NULL" && model != "NULL") {
								ss << make << " " << model;
							}
							else if (model != "NULL") {
								ss << model;
							}
							else {
								ss << "~c~Unknown";
							}
						}

						if (add_text_option(ss.str())) {
							if (!g_vehicle_spawn_options_spawn_in_a_line) {
								std::int32_t vehicle = spawn_vehicle(*(std::uint32_t*)(info + 0x18), PLAYER::PLAYER_PED_ID());
								VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle, 0.0f);
								VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
								VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 3, 0, 0);
								VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 66, 225, 221);
								VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 10, 20, 30);
								VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 3, 5);
								VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, 24, 4);
								VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(vehicle, 0, 0, 0);
								VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle, 5);
								VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(vehicle, OBFUSCATE("QUANTUM"));
								if (g_vehicle_spawn_options_max_upgrades) {
									VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, 18, 1);
									VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, 22, 1);
									VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, 20, 1);
									VEHICLE::SET_VEHICLE_MOD(vehicle, 16, 5, 0);
									VEHICLE::SET_VEHICLE_MOD(vehicle, 12, 2, 0);
									VEHICLE::SET_VEHICLE_MOD(vehicle, 11, 3, 0);
									VEHICLE::SET_VEHICLE_MOD(vehicle, 14, 14, 0);
									VEHICLE::SET_VEHICLE_MOD(vehicle, 15, 3, 0);
									VEHICLE::SET_VEHICLE_MOD(vehicle, 13, 2, 0);
									VEHICLE::SET_VEHICLE_WHEEL_TYPE(vehicle, 6);
									VEHICLE::SET_VEHICLE_WINDOW_TINT(vehicle, 5);
									VEHICLE::SET_VEHICLE_MOD(vehicle, 23, 19, 1);
									VEHICLE::SET_VEHICLE_MOD(vehicle, 0, 1, 0);
									VEHICLE::SET_VEHICLE_MOD(vehicle, 1, 1, 0);
									VEHICLE::SET_VEHICLE_MOD(vehicle, 2, 1, 0);
									VEHICLE::SET_VEHICLE_MOD(vehicle, 3, 1, 0);
									VEHICLE::SET_VEHICLE_MOD(vehicle, 4, 1, 0);
									VEHICLE::SET_VEHICLE_MOD(vehicle, 5, 1, 0);
									VEHICLE::SET_VEHICLE_MOD(vehicle, 6, 1, 0);
									VEHICLE::SET_VEHICLE_MOD(vehicle, 7, 1, 0);
									VEHICLE::SET_VEHICLE_MOD(vehicle, 8, 1, 0);
									VEHICLE::SET_VEHICLE_MOD(vehicle, 9, 1, 0);
									VEHICLE::SET_VEHICLE_MOD(vehicle, 10, 1, 0);
								}
							}
							else if (g_vehicle_spawn_options_spawn_in_a_line) {

								std::uint32_t hash = *(std::uint32_t*)(info + 0x18);
								for (std::int32_t i = 0; i < g_vehicle_spawn_options_spawn_amount; i++) {

									if (STREAMING::IS_MODEL_VALID(hash)) {

										STREAMING::REQUEST_MODEL(hash);
										while (!STREAMING::HAS_MODEL_LOADED(hash))
											Script::GetCurrent()->ScriptYield();

										Vector3 model_min, model_max;
										GAMEPLAY::GET_MODEL_DIMENSIONS(hash, &model_min, &model_max);

										Vector3 l_coords;
										if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE))
											l_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE), 0.0f, ((i + 1) * ((model_max.y * 2.0f) + 3.0f)), 0.0f);
										else 
											l_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, ((i + 1) * ((model_max.y * 2.0f) + 3.0f)), 0.0f);
										std::int32_t net_id = NETWORK::VEH_TO_NET(VEHICLE::CREATE_VEHICLE(hash, l_coords.x, l_coords.y, l_coords.z, (ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()) - 90.0f), TRUE, FALSE));
										NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(net_id, TRUE);
										if (ENTITY::IS_ENTITY_VISIBLE_TO_SCRIPT(NETWORK::NET_TO_VEH(net_id))) {
											VEHICLE::SET_VEHICLE_ENGINE_ON(NETWORK::NET_TO_VEH(net_id), TRUE, TRUE, TRUE);
											DECORATOR::DECOR_SET_INT(NETWORK::NET_TO_VEH(net_id), "MPBitset", (1 << 10));

											std::int32_t vehicle = NETWORK::NET_TO_VEH(net_id);
											VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle, 0.0f);
											VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
											VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, 3, 0, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, 66, 225, 221);
											VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, 10, 20, 30);
											VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, 3, 5);
											VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, 24, 4);
											VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(vehicle, 0, 0, 0);
											VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle, 5);
											VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(vehicle, OBFUSCATE("QUANTUM"));
											if (g_vehicle_spawn_options_max_upgrades) {
												VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, 18, 1);
												VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, 22, 1);
												VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, 20, 1);
												VEHICLE::SET_VEHICLE_MOD(vehicle, 16, 5, 0);
												VEHICLE::SET_VEHICLE_MOD(vehicle, 12, 2, 0);
												VEHICLE::SET_VEHICLE_MOD(vehicle, 11, 3, 0);
												VEHICLE::SET_VEHICLE_MOD(vehicle, 14, 14, 0);
												VEHICLE::SET_VEHICLE_MOD(vehicle, 15, 3, 0);
												VEHICLE::SET_VEHICLE_MOD(vehicle, 13, 2, 0);
												VEHICLE::SET_VEHICLE_WHEEL_TYPE(vehicle, 6);
												VEHICLE::SET_VEHICLE_WINDOW_TINT(vehicle, 5);
												VEHICLE::SET_VEHICLE_MOD(vehicle, 23, 19, 1);
												VEHICLE::SET_VEHICLE_MOD(vehicle, 0, 1, 0);
												VEHICLE::SET_VEHICLE_MOD(vehicle, 1, 1, 0);
												VEHICLE::SET_VEHICLE_MOD(vehicle, 2, 1, 0);
												VEHICLE::SET_VEHICLE_MOD(vehicle, 3, 1, 0);
												VEHICLE::SET_VEHICLE_MOD(vehicle, 4, 1, 0);
												VEHICLE::SET_VEHICLE_MOD(vehicle, 5, 1, 0);
												VEHICLE::SET_VEHICLE_MOD(vehicle, 6, 1, 0);
												VEHICLE::SET_VEHICLE_MOD(vehicle, 7, 1, 0);
												VEHICLE::SET_VEHICLE_MOD(vehicle, 8, 1, 0);
												VEHICLE::SET_VEHICLE_MOD(vehicle, 9, 1, 0);
												VEHICLE::SET_VEHICLE_MOD(vehicle, 10, 1, 0);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
void menu_vehicle_spawner_spawn_options() {
	if (add_toggle_option(&g_vehicle_spawn_options_spawn_inside, OBFUSCATE("Spawn Inside"))) {
		if (g_vehicle_spawn_options_spawn_in_a_line && g_vehicle_spawn_options_spawn_inside)
			g_vehicle_spawn_options_spawn_in_a_line = false;
	}
	add_toggle_option(&g_vehicle_spawn_options_max_upgrades, OBFUSCATE("Max Upgrades"));
	if (add_editor_toggle_option(&g_vehicle_spawn_options_spawn_in_a_line, g_vehicle_spawn_options_spawn_amount, &g_vehicle_spawn_options_spawn_amount, 1, 5, 1, OBFUSCATE("Spawn In A Line"))) {
		if (g_vehicle_spawn_options_spawn_in_a_line && g_vehicle_spawn_options_spawn_inside)
			g_vehicle_spawn_options_spawn_inside = false;
	}
}
void menu_vehicle_spawner() {
	add_submenu_option(menu_vehicle_spawner_spawn_options, OBFUSCATE("Spawn Options"));
	for (std::int32_t i = 0; i < 22; i++) {
		if (add_submenu_option(menu_vehicle_spawner_spawn, get_vehicle_class_name(i)))
			g_vehicle_spawner_selected_class = i;
	}
}
void menu_vehicle_lsc_respray_custom_primary() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			if (add_editor_option(true, g_vehicle_lsc_respray_custom_primary[0], &g_vehicle_lsc_respray_custom_primary[0], 0, 255, 1, OBFUSCATE("Red"))) {
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle,
					g_vehicle_lsc_respray_custom_primary[0],
					g_vehicle_lsc_respray_custom_primary[1],
					g_vehicle_lsc_respray_custom_primary[2]);
			}
			if (add_editor_option(true, g_vehicle_lsc_respray_custom_primary[1], &g_vehicle_lsc_respray_custom_primary[1], 0, 255, 1, OBFUSCATE("Green"))) {
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle,
					g_vehicle_lsc_respray_custom_primary[0],
					g_vehicle_lsc_respray_custom_primary[1],
					g_vehicle_lsc_respray_custom_primary[2]);
			}
			if (add_editor_option(true, g_vehicle_lsc_respray_custom_primary[2], &g_vehicle_lsc_respray_custom_primary[2], 0, 255, 1, OBFUSCATE("Blue"))) {
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle,
					g_vehicle_lsc_respray_custom_primary[0],
					g_vehicle_lsc_respray_custom_primary[1],
					g_vehicle_lsc_respray_custom_primary[2]);
			}
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_respray_custom_secondary() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			if (add_editor_option(true, g_vehicle_lsc_respray_custom_secondary[0], &g_vehicle_lsc_respray_custom_secondary[0], 0, 255, 1, OBFUSCATE("Red"))) {
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle,
					g_vehicle_lsc_respray_custom_secondary[0],
					g_vehicle_lsc_respray_custom_secondary[1],
					g_vehicle_lsc_respray_custom_secondary[2]);
			}
			if (add_editor_option(true, g_vehicle_lsc_respray_custom_secondary[1], &g_vehicle_lsc_respray_custom_secondary[1], 0, 255, 1, OBFUSCATE("Green"))) {
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle,
					g_vehicle_lsc_respray_custom_secondary[0],
					g_vehicle_lsc_respray_custom_secondary[1],
					g_vehicle_lsc_respray_custom_secondary[2]);
			}
			if (add_editor_option(true, g_vehicle_lsc_respray_custom_secondary[2], &g_vehicle_lsc_respray_custom_secondary[2], 0, 255, 1, OBFUSCATE("Blue"))) {
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle,
					g_vehicle_lsc_respray_custom_secondary[0],
					g_vehicle_lsc_respray_custom_secondary[1],
					g_vehicle_lsc_respray_custom_secondary[2]);
			}
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_respray_category() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			if (g_vehicle_lsc_respray_type == 0) {
				if (add_submenu_option(menu_vehicle_lsc_respray_custom_primary, OBFUSCATE("Custom Primary"))) {
					if (VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(vehicle)) {
						VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle,
							&g_vehicle_lsc_respray_custom_primary[0],
							&g_vehicle_lsc_respray_custom_primary[1],
							&g_vehicle_lsc_respray_custom_primary[2]);
					}
				}
				add_break_option(OBFUSCATE("Categories"));
			}
			if (g_vehicle_lsc_respray_type == 1) {
				if (add_submenu_option(menu_vehicle_lsc_respray_custom_secondary, OBFUSCATE("Custom Secondary"))) {
					if (VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(vehicle)) {
						VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle,
							&g_vehicle_lsc_respray_custom_secondary[0],
							&g_vehicle_lsc_respray_custom_secondary[1],
							&g_vehicle_lsc_respray_custom_secondary[2]);
					}
				}
				add_break_option(OBFUSCATE("Categories"));
			}
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_respray() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			// Load Custom Paint
			if (add_submenu_option(menu_vehicle_lsc_respray_category, OBFUSCATE("Primary"))) { g_vehicle_lsc_respray_type = 0; }
			if (add_submenu_option(menu_vehicle_lsc_respray_category, OBFUSCATE("Secondary"))) { g_vehicle_lsc_respray_type = 1; }
			if (add_submenu_option(menu_vehicle_lsc_respray_category, OBFUSCATE("Pearlescent"))) { g_vehicle_lsc_respray_type = 2; }
			if (add_submenu_option(menu_vehicle_lsc_respray_category, OBFUSCATE("Wheels"))) { g_vehicle_lsc_respray_type = 3; }
			if (add_toggle_option(&g_vehicle_rainbow_paint_fade, OBFUSCATE("Rainbow Paint ~c~(Fade)"))) {
				if (g_vehicle_rainbow_paint_fade) {
					g_vehicle_rainbow_paint_fade_colour.r = 255;
					g_vehicle_rainbow_paint_fade_colour.g = 0;
					g_vehicle_rainbow_paint_fade_colour.b = 0;
				}
			}
			// Save Current Paint
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_engine() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			for (std::int32_t i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_ENGINE); i++) {
				std::stringstream ss; ss << "CMOD_ENG_" << i + 2;
				if (add_text_option(UI::_GET_LABEL_TEXT(ss.str().c_str()))) {
					VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_ENGINE, i, FALSE);
				}
			}
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_transmission() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			for (std::int32_t i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_TRANSMISSION); i++) {
				std::stringstream ss; ss << "CMOD_GBX_" << i + 1;
				if (add_text_option(UI::_GET_LABEL_TEXT(ss.str().c_str()))) {
					VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_TRANSMISSION, i, FALSE);
				}
			}
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_brakes() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			for (std::int32_t i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_BRAKES); i++) {
				std::stringstream ss; ss << "CMOD_BRA_" << i + 1;
				if (add_text_option(UI::_GET_LABEL_TEXT(ss.str().c_str()))) {
					VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_BRAKES, i, FALSE);
				}
			}
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_suspension() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			for (std::int32_t i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_SUSPENSION); i++) {
				std::stringstream ss; ss << "CMOD_SUS_" << i + 1;
				if (add_text_option(UI::_GET_LABEL_TEXT(ss.str().c_str()))) {
					VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_SUSPENSION, i, FALSE);
				}
			}
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_armour() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			for (std::int32_t i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_ARMOR); i++) {
				std::stringstream ss; ss << "CMOD_ARM_" << i + 1;
				if (add_text_option(UI::_GET_LABEL_TEXT(ss.str().c_str()))) {
					VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_ARMOR, i, FALSE);
				}
			}
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_exhaust() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			for (std::int32_t i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_EXHAUST); i++) {
				const char* label = UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, MOD_EXHAUST, i));
				if (add_text_option(!strcmp(label, "NULL") ? "Stock" : label)) {
					VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_EXHAUST, i, FALSE);
				}
			}
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_spoiler() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			for (std::int32_t i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_SPOILER); i++) {
				const char* label = UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, MOD_SPOILER, i));
				if (add_text_option(!strcmp(label, "NULL") ? "Stock" : label)) {
					VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_SPOILER, i, FALSE);
				}
			}
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_front_bumper() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			for (std::int32_t i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_FRONTBUMPER); i++) {
				const char* label = UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, MOD_FRONTBUMPER, i));
				if (add_text_option(!strcmp(label, "NULL") ? "Stock" : label)) {
					VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_FRONTBUMPER, i, FALSE);
				}
			}
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_rear_bumper() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			for (std::int32_t i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_REARBUMPER); i++) {
				const char* label = UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, MOD_REARBUMPER, i));
				if (add_text_option(!strcmp(label, "NULL") ? "Stock" : label)) {
					VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_REARBUMPER, i, FALSE);
				}
			}
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_bumpers() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			if (VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_FRONTBUMPER) > NULL)
				add_submenu_option(menu_vehicle_lsc_front_bumper, OBFUSCATE("Front Bumpers"));
			if (VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_REARBUMPER) > NULL)
				add_submenu_option(menu_vehicle_lsc_rear_bumper, OBFUSCATE("Rear Bumpers"));
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_grille() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			for (std::int32_t i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_GRILLE); i++) {
				const char* label = UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, MOD_GRILLE, i));
				if (add_text_option(!strcmp(label, "NULL") ? "Stock" : label)) {
					VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_GRILLE, i, FALSE);
				}
			}
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_hood() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			for (std::int32_t i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_HOOD); i++) {
				const char* label = UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, MOD_HOOD, i));
				if (add_text_option(!strcmp(label, "NULL") ? "Stock" : label)) {
					VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HOOD, i, FALSE);
				}
			}
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_roll_cage() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			for (std::int32_t i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_CHASSIS); i++) {
				const char* label = UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, MOD_CHASSIS, i));
				if (add_text_option(!strcmp(label, "NULL") ? "Stock" : label)) {
					VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_CHASSIS, i, FALSE);
				}
			}
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_fenders() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			for (std::int32_t i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_FENDER); i++) {
				const char* label = UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, MOD_FENDER, i));
				if (add_text_option(!strcmp(label, "NULL") ? "Stock" : label)) {
					VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_FENDER, i, FALSE);
				}
			}
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_roof() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			for (std::int32_t i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_ROOF); i++) {
				const char* label = UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, MOD_ROOF, i));
				if (add_text_option(!strcmp(label, "NULL") ? "Stock" : label)) {
					VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_ROOF, i, FALSE);
				}
			}
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_skirts() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			for (std::int32_t i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_SIDESKIRT); i++) {
				const char* label = UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, MOD_SIDESKIRT, i));
				if (add_text_option(!strcmp(label, "NULL") ? "Stock" : label)) {
					VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_SIDESKIRT, i, FALSE);
				}
			}
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_horn() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("CMOD_HRN_0"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, CMOD_HRN_0, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("CMOD_HRN_TRK"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, CMOD_HRN_TRK, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("CMOD_HRN_COP"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, CMOD_HRN_COP, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("CMOD_HRN_CLO"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, CMOD_HRN_CLO, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("CMOD_HRN_MUS1"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, CMOD_HRN_MUS1, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("CMOD_HRN_MUS2"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, CMOD_HRN_MUS2, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("CMOD_HRN_MUS3"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, CMOD_HRN_MUS3, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("CMOD_HRN_MUS4"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, CMOD_HRN_MUS4, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("CMOD_HRN_MUS5"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, CMOD_HRN_MUS5, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("CMOD_HRN_SAD"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, CMOD_HRN_SAD, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_CLAS1"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_CLAS1, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_CLAS2"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_CLAS2, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_CLAS3"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_CLAS3, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_CLAS4"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_CLAS4, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_CLAS5"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_CLAS5, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_CLAS6"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_CLAS6, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_CLAS7"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_CLAS7, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_CNOTE_C0"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_CNOTE_C0, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_CNOTE_D0"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_CNOTE_D0, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_CNOTE_E0"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_CNOTE_E0, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_CNOTE_F0"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_CNOTE_F0, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_CNOTE_G0"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_CNOTE_G0, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_CNOTE_A0"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_CNOTE_A0, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_CNOTE_B0"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_CNOTE_B0, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_CNOTE_C1"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_CNOTE_C1, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_HIPS1"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_HIPS1, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_HIPS2"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_HIPS2, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_HIPS3"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_HIPS3, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_HIPS4"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_HIPS4, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_INDI_1"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_INDI_1, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_INDI_2"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_INDI_2, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_INDI_3"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_INDI_3, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_INDI_4"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_INDI_4, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_LUXE2"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_LUXE2, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_LUXE1"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_LUXE1, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_LUXE3"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_LUXE3, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_HWEEN1"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_HWEEN1, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_HWEEN2"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_HWEEN2, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_LOWRDER1"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_LOWRDER1, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_LOWRDER2"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_LOWRDER2, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_XM15_1"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_XM15_1, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_XM15_2"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_XM15_2, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("HORN_XM15_3"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, HORN_XM15_3, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("CMOD_AIRHORN_01"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, CMOD_AIRHORN_01, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("CMOD_AIRHORN_02"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, CMOD_AIRHORN_02, FALSE);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("CMOD_AIRHORN_03"))))
				VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HORN, CMOD_AIRHORN_03, FALSE);
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_headlights_colour() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			for (std::int32_t i = 0; i < 14; i++) {
				std::stringstream ss; ss << "CMOD_NEONCOL_" << i;
				const char* label = UI::_GET_LABEL_TEXT(ss.str().c_str());
				if (add_text_option(!strcmp(label, "NULL") ? "Stock" : label)) {
					//VEHICLE::_SET_VEHICLE_XENON_LIGHTS_COLOUR(vehicle, i);
				}
			}
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_headlights() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			if (add_text_option(UI::_GET_LABEL_TEXT("CMOD_LGT_0"))) {
				VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, MOD_XENONLIGHTS, FALSE);
			}
			if (add_text_option(UI::_GET_LABEL_TEXT("CMOD_LGT_1"))) {
				VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, MOD_XENONLIGHTS, TRUE);
			}
			if (VEHICLE::IS_TOGGLE_MOD_ON(vehicle, MOD_XENONLIGHTS))
				add_submenu_option(menu_vehicle_lsc_headlights_colour, OBFUSCATE("Xenon Headlight Colour"));
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_lights_neon_layout() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {

			bool left_neon = VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 0);
			bool right_neon = VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 1);
			bool front_neon = VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 2);
			bool back_neon = VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 3);

			if (add_toggle_option(&left_neon, "Left")) {
				if (g_vehicle_lsc_neon_rgb[0] == NULL || g_vehicle_lsc_neon_rgb[1] == NULL || g_vehicle_lsc_neon_rgb[2] == NULL)
					VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(vehicle, 66, 225, 221);
				VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 0, left_neon);
			}
			if (add_toggle_option(&right_neon, "Right")) {
				if (g_vehicle_lsc_neon_rgb[0] == NULL || g_vehicle_lsc_neon_rgb[1] == NULL || g_vehicle_lsc_neon_rgb[2] == NULL)
					VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(vehicle, 66, 225, 221);
				VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 1, right_neon);
			}
			if (add_toggle_option(&front_neon, "Front")) {
				if (g_vehicle_lsc_neon_rgb[0] == NULL || g_vehicle_lsc_neon_rgb[1] == NULL || g_vehicle_lsc_neon_rgb[2] == NULL)
					VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(vehicle, 66, 225, 221);
				VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 2, front_neon);
			}
			if (add_toggle_option(&back_neon, "Back")) {
				if (g_vehicle_lsc_neon_rgb[0] == NULL || g_vehicle_lsc_neon_rgb[1] == NULL || g_vehicle_lsc_neon_rgb[2] == NULL)
					VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(vehicle, 66, 225, 221);
				VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 3, back_neon);
			}
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_lights_neon_colour() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			for (std::int32_t i = 0; i < 14; i++) {
				std::stringstream ss; ss << "CMOD_NEONCOL_" << i;
				const char* label = UI::_GET_LABEL_TEXT(ss.str().c_str());
				if (add_text_option(!strcmp(label, "NULL") ? "Stock" : label)) {
					switch (CURRENT_OPTION - 1) {
					case 0: g_vehicle_lsc_neon_rgb[0] = 222; g_vehicle_lsc_neon_rgb[1] = 222; g_vehicle_lsc_neon_rgb[2] = 255; break;
					case 1: g_vehicle_lsc_neon_rgb[0] = 2; g_vehicle_lsc_neon_rgb[1] = 21; g_vehicle_lsc_neon_rgb[2] = 255; break;
					case 2: g_vehicle_lsc_neon_rgb[0] = 3; g_vehicle_lsc_neon_rgb[1] = 83; g_vehicle_lsc_neon_rgb[2] = 255; break;
					case 3: g_vehicle_lsc_neon_rgb[0] = 0; g_vehicle_lsc_neon_rgb[1] = 255; g_vehicle_lsc_neon_rgb[2] = 140; break;
					case 4: g_vehicle_lsc_neon_rgb[0] = 94; g_vehicle_lsc_neon_rgb[1] = 255; g_vehicle_lsc_neon_rgb[2] = 1; break;
					case 5: g_vehicle_lsc_neon_rgb[0] = 255; g_vehicle_lsc_neon_rgb[1] = 255; g_vehicle_lsc_neon_rgb[2] = 0; break;
					case 6: g_vehicle_lsc_neon_rgb[0] = 255; g_vehicle_lsc_neon_rgb[1] = 150; g_vehicle_lsc_neon_rgb[2] = 5; break;
					case 7: g_vehicle_lsc_neon_rgb[0] = 255; g_vehicle_lsc_neon_rgb[1] = 62; g_vehicle_lsc_neon_rgb[2] = 0; break;
					case 8: g_vehicle_lsc_neon_rgb[0] = 255; g_vehicle_lsc_neon_rgb[1] = 1; g_vehicle_lsc_neon_rgb[2] = 1; break;
					case 9: g_vehicle_lsc_neon_rgb[0] = 255; g_vehicle_lsc_neon_rgb[1] = 50; g_vehicle_lsc_neon_rgb[2] = 100; break;
					case 10: g_vehicle_lsc_neon_rgb[0] = 255; g_vehicle_lsc_neon_rgb[1] = 5; g_vehicle_lsc_neon_rgb[2] = 190; break;
					case 11: g_vehicle_lsc_neon_rgb[0] = 35; g_vehicle_lsc_neon_rgb[1] = 1; g_vehicle_lsc_neon_rgb[2] = 255; break;
					case 12: g_vehicle_lsc_neon_rgb[0] = 15; g_vehicle_lsc_neon_rgb[1] = 3; g_vehicle_lsc_neon_rgb[2] = 255; break;
					case 13: {
							if (NETWORK::NETWORK_IS_GAME_IN_PROGRESS()) {
								g_vehicle_lsc_neon_rgb[0] = *scr_global(1314030).as<std::int32_t*>();
								g_vehicle_lsc_neon_rgb[1] = *scr_global(1314031).as<std::int32_t*>();
								g_vehicle_lsc_neon_rgb[2] = *scr_global(1314032).as<std::int32_t*>();
							}
						} break;
					}
					VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(vehicle, g_vehicle_lsc_neon_rgb[0], g_vehicle_lsc_neon_rgb[1], g_vehicle_lsc_neon_rgb[2]);
				}
			}
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_lights_neon() {
	add_submenu_option(menu_vehicle_lsc_lights_neon_layout, UI::_GET_LABEL_TEXT(OBFUSCATE("CMOD_NEON_0")));
	add_submenu_option(menu_vehicle_lsc_lights_neon_colour, UI::_GET_LABEL_TEXT(OBFUSCATE("CMOD_NEON_1")));
}
void menu_vehicle_lsc_lights() {
	add_submenu_option(menu_vehicle_lsc_headlights, OBFUSCATE("Headlights"));
	add_submenu_option(menu_vehicle_lsc_lights_neon, OBFUSCATE("Neon Kits"));
}
void menu_vehicle_lsc_plate() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("CMOD_PLA_0"))))
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle, 0);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("CMOD_PLA_4"))))
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle, 1);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("CMOD_PLA_3"))))
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle, 2);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("CMOD_PLA_1"))))
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle, 3);
			if (add_text_option(UI::_GET_LABEL_TEXT(OBFUSCATE("CMOD_PLA_2"))))
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle, 4);
			if (add_text_option(OBFUSCATE("North Yankton")))
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle, 5);
			if (add_keyboard_option(false, &g_vehicle_lsc_plate_text, 8, OBFUSCATE("Edit Plate Text")))
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(vehicle, g_vehicle_lsc_plate_text.c_str());
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_turbo() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			if (add_text_option(OBFUSCATE("Stock")))
				VEHICLE::REMOVE_VEHICLE_MOD(vehicle, MOD_TURBO);
			if (add_text_option(OBFUSCATE("Turbo Tuning")))
				VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, MOD_TURBO, 0);
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc_wheels() {

	//make sure vehicle has custom wheels!!!
	
}
void menu_vehicle_lsc_windows() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			if (add_text_option(UI::_GET_LABEL_TEXT("CMOD_WIN_0")))
				VEHICLE::SET_VEHICLE_WINDOW_TINT(vehicle, 0);
			if (add_text_option(UI::_GET_LABEL_TEXT("CMOD_WIN_1")))
				VEHICLE::SET_VEHICLE_WINDOW_TINT(vehicle, 2);
			if (add_text_option(UI::_GET_LABEL_TEXT("CMOD_WIN_2")))
				VEHICLE::SET_VEHICLE_WINDOW_TINT(vehicle, 1);
			if (add_text_option(UI::_GET_LABEL_TEXT("CMOD_WIN_3")))
				VEHICLE::SET_VEHICLE_WINDOW_TINT(vehicle, 3);
			if (add_text_option(UI::_GET_LABEL_TEXT("FMMC_COL1_11")))
				VEHICLE::SET_VEHICLE_WINDOW_TINT(vehicle, 7);
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_lsc() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			if (VEHICLE::GET_VEHICLE_MOD_KIT(vehicle) != 0)
				VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);

			add_toggle_option(&g_vehicle_lsc_cam_active, OBFUSCATE("LSC Camera"));

			if (VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_ARMOR) > NULL)
				add_submenu_option(menu_vehicle_lsc_armour, OBFUSCATE("Armour"));

			if (VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_BRAKES) > NULL)
				add_submenu_option(menu_vehicle_lsc_brakes, OBFUSCATE("Brakes"));

			if (VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_FRONTBUMPER) > NULL
				|| VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_REARBUMPER) > NULL)
				add_submenu_option(menu_vehicle_lsc_bumpers, OBFUSCATE("Bumpers"));

			if (VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_ENGINE) > NULL)
				add_submenu_option(menu_vehicle_lsc_engine, OBFUSCATE("Engine"));

			if (VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_EXHAUST) > NULL)
				add_submenu_option(menu_vehicle_lsc_exhaust, OBFUSCATE("Exhaust"));

			if (VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_FENDER) > NULL)
				add_submenu_option(menu_vehicle_lsc_fenders, OBFUSCATE("Fenders"));

			if (VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_GRILLE) > NULL)
				add_submenu_option(menu_vehicle_lsc_grille, OBFUSCATE("Grille"));

			if (VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_HOOD) > NULL)
				add_submenu_option(menu_vehicle_lsc_hood, OBFUSCATE("Hood"));

			add_submenu_option(menu_vehicle_lsc_horn, OBFUSCATE("Horn"));

			add_submenu_option(menu_vehicle_lsc_lights, OBFUSCATE("Lights"));

			add_submenu_option(menu_vehicle_lsc_plate, OBFUSCATE("Plate"));

			add_submenu_option(menu_vehicle_lsc_respray, OBFUSCATE("Respray"));

			if (VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_CHASSIS) > NULL)
				add_submenu_option(menu_vehicle_lsc_roll_cage, OBFUSCATE("Roll Cage"));

			if (VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_ROOF) > NULL)
				add_submenu_option(menu_vehicle_lsc_roof, OBFUSCATE("Roof"));

			if (VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_SIDESKIRT) > NULL)
				add_submenu_option(menu_vehicle_lsc_skirts, OBFUSCATE("Skirts"));

			if (VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_SPOILER) > NULL)
				add_submenu_option(menu_vehicle_lsc_spoiler, OBFUSCATE("Spoiler"));

			if (VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_SUSPENSION) > NULL)
				add_submenu_option(menu_vehicle_lsc_suspension, OBFUSCATE("Suspension"));

			if (VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_TRANSMISSION) > NULL)
				add_submenu_option(menu_vehicle_lsc_transmission, OBFUSCATE("Transmission"));

			add_submenu_option(menu_vehicle_lsc_turbo, OBFUSCATE("Turbo"));
			
			add_submenu_option(menu_vehicle_lsc_wheels, OBFUSCATE("Wheels")); //need to do

			add_submenu_option(menu_vehicle_lsc_windows, OBFUSCATE("Windows"));
		}
		else {
			add_text_option(OBFUSCATE("No Vehicle Found"));
			CURRENT_OPTION = 1;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}

	//if (g_vehicle_lsc_cam_active) {
	//	if (!CAM::DOES_CAM_EXIST(g_vehicle_lsc_cam) && CURRENT_OPTION != 1) {
	//		g_vehicle_lsc_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
	//		if (CAM::DOES_CAM_EXIST(g_vehicle_lsc_cam)) {
	//			

	//			CAM::SET_CAM_ACTIVE(g_self_model_cam, true);
	//			CAM::RENDER_SCRIPT_CAMS(1, 1, 3000, 1, 0);
	//		}
	//	}
	//	else if (!CAM::DOES_CAM_EXIST(g_vehicle_lsc_cam_temp))
	//		g_vehicle_lsc_cam_temp = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
	//	else {
	//		static bool g_vehicle_lsc_cam_interloping_finished[21]{ false };
	//		switch (CURRENT_OPTION) {
	//		case 1: { //delete cam
	//				if (CAM::DOES_CAM_EXIST(g_vehicle_lsc_cam)) {
	//					CAM::SET_CAM_ACTIVE(g_vehicle_lsc_cam, false);
	//					CAM::RENDER_SCRIPT_CAMS(0, 1, 3000, 1, 0);
	//					CAM::DESTROY_CAM(g_vehicle_lsc_cam, true);
	//				}
	//				if (CAM::DOES_CAM_EXIST(g_vehicle_lsc_cam_temp)) {
	//					CAM::SET_CAM_ACTIVE(g_vehicle_lsc_cam_temp, false);
	//					CAM::RENDER_SCRIPT_CAMS(0, 1, 3000, 1, 0);
	//					CAM::DESTROY_CAM(g_vehicle_lsc_cam_temp, true);
	//				}
	//			} break;
	//		case 2: { //Armour
	//				for (auto i = 0; i < std::size(g_vehicle_lsc_cam_interloping_finished); i++)
	//					if (i != 0) g_vehicle_lsc_cam_interloping_finished[i] = false;

	//				bool using_temp_cam = (CAM::GET_RENDERING_CAM() == g_vehicle_lsc_cam_temp);

	//				Vector3 bone_coords = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[CURRENT_OPTION - 2], 0.0f, 1.0f, 0.0f);

	//				if (!g_vehicle_lsc_cam_interloping_finished[0]) {
	//					CAM::SET_CAM_COORD(using_temp_cam ? g_vehicle_lsc_cam : g_vehicle_lsc_cam_temp, bone_coords.x, bone_coords.y, bone_coords.z);
	//					CAM::POINT_CAM_AT_PED_BONE(using_temp_cam ? g_vehicle_lsc_cam : g_vehicle_lsc_cam_temp, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[CURRENT_OPTION - 2]), 0.0f, 0.0f, 0.5f, 1);
	//					using_temp_cam ? CAM::SET_CAM_ACTIVE_WITH_INTERP(g_vehicle_lsc_cam, g_vehicle_lsc_cam_temp, 1500, 1, 1) : CAM::SET_CAM_ACTIVE_WITH_INTERP(g_vehicle_lsc_cam_temp, g_vehicle_lsc_cam, 1500, 1, 1);
	//					g_vehicle_lsc_cam_interloping_finished[0] = true;
	//				}
	//				else {
	//					while (CAM::IS_CAM_INTERPOLATING(g_vehicle_lsc_cam) || CAM::IS_CAM_INTERPOLATING(g_vehicle_lsc_cam_temp))
	//						Script::GetCurrent()->ScriptYield();

	//					CAM::SET_CAM_COORD(using_temp_cam ? g_vehicle_lsc_cam_temp : g_vehicle_lsc_cam, bone_coords.x, bone_coords.y, bone_coords.z);
	//					CAM::POINT_CAM_AT_PED_BONE(using_temp_cam ? g_vehicle_lsc_cam_temp : g_vehicle_lsc_cam, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), g_ped_bone_list[CURRENT_OPTION - 2]), 0.0f, 0.0f, 0.5f, 1);
	//				}
	//			} break;
	//		case 3: { //Brakes
	//				
	//			} break;
	//		case 4: { //Bumpers
	//				
	//			} break;
	//		case 5: { //Engine
	//				
	//			} break;
	//		case 6: { //Exhaust
	//				
	//			} break;
	//		case 7: { //Fenders
	//				
	//			} break;
	//		case 8: { //Grille
	//				
	//			} break;
	//		case 9: { //Hood
	//				
	//			} break;
	//		case 10: { //Horn
	//				
	//			} break;
	//		case 11: { //Lights
	//				
	//			} break;
	//		case 12: { //Plate
	//				
	//			} break;
	//		case 13: { //Respray
	//				
	//			} break;
	//		case 14: { //Roll Cage
	//				
	//			} break;
	//		case 15: { //Roof
	//				
	//			} break;
	//		case 16: { //Skirts
	//				
	//			} break;
	//		case 17: { //Spoiler
	//				
	//			} break;
	//		case 18: { //Suspension
	//				
	//			} break;
	//		case 19: { //Transmission
	//				
	//			} break;
	//		case 20: { //Turbo
	//				
	//			} break;
	//		case 21: { //Wheels
	//				
	//			} break;
	//		case 22: { //Windows
	//				
	//			} break;
	//		}
	//	}
	//}
}
void menu_vehicle_nitrous_config() {
	add_editor_option(false, g_vehicle_nitrous_exponent, &g_vehicle_nitrous_exponent, 1.0f, 1.1f, 0.001f, OBFUSCATE("Exponent"));
	add_toggle_option(&g_vehicle_nitrous_play_sound, OBFUSCATE("Play Sound"));
	add_toggle_option(&g_vehicle_nitrous_screen_effect, OBFUSCATE("Show Screen Effect"));
	add_toggle_option(&g_vehicle_nitrous_active, OBFUSCATE("Active"));
}
void menu_vehicle_handling_meta_editor() {
	std::uint64_t ped_factory = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(GTA_PED_FACTORY);
	if (ped_factory != NULL) {
		std::uint64_t entity = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(ped_factory + 0x8);
		if (entity != NULL) {
			std::uint64_t vehicle = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(entity + 0xD28);
			if (vehicle != NULL) {
				std::add_pointer_t<CHandlingData> handling = *reinterpret_cast<std::add_pointer_t<std::add_pointer_t<CHandlingData>>>(vehicle + 0x918);
				if (handling != NULL) {
					if (add_text_option("Reload Current Vehicle")) {
						std::int32_t ped = PLAYER::PLAYER_PED_ID();
						if (ENTITY::DOES_ENTITY_EXIST(ped)) {
							std::int32_t veh = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
							if (ENTITY::DOES_ENTITY_EXIST(veh)) {
								spawn_vehicle(ENTITY::GET_ENTITY_MODEL(veh), ped);
							}
						}
					}
					add_break_option("Editor");
					add_editor_option(true, handling->fAntiRollBarBiasFront, &handling->fAntiRollBarBiasFront, -1000.0f, 1000.0f, 0.1f, "Anti Roll Bar Bias Front");
					add_editor_option(true, handling->fAntiRollBarBiasRear, &handling->fAntiRollBarBiasRear, -1000.0f, 1000.0f, 0.1f, "Anti Roll Bar Bias Rear");
					add_editor_option(true, handling->fAntiRollBarForce, &handling->fAntiRollBarForce, -1000.0f, 1000.0f, 0.1f, "Anti Roll Bar Force");
					add_editor_option(true, handling->fBrakeBiasFront, &handling->fBrakeBiasFront, -1000.0f, 1000.0f, 0.1f, "Brake Bias Front");
					add_editor_option(true, handling->fBrakeBiasRear, &handling->fBrakeBiasRear, -1000.0f, 1000.0f, 0.1f, "Brake Bias Rear");
					add_editor_option(true, handling->fBrakeForce, &handling->fBrakeForce, -1000.0f, 1000.0f, 0.1f, "Brake Force");
					add_editor_option(true, handling->fCamberStiffness, &handling->fCamberStiffness, -1000.0f, 1000.0f, 0.1f, "Camber Stiffness");
					add_editor_option(true, handling->fClutchChangeRateScaleDownShift, &handling->fClutchChangeRateScaleDownShift, -1000.0f, 1000.0f, 0.1f, "Clutch Change Rate Scale Down Shift");
					add_editor_option(true, handling->fClutchChangeRateScaleUpShift, &handling->fClutchChangeRateScaleUpShift, -1000.0f, 1000.0f, 0.1f, "Clutch Change Rate Scale Up Shift");
					add_editor_option(true, handling->fCollisionDamageMult, &handling->fCollisionDamageMult, -1000.0f, 1000.0f, 0.1f, "Collision Damage Multiplier");
					add_editor_option(true, handling->fDeformationDamageMult, &handling->fDeformationDamageMult, -1000.0f, 1000.0f, 0.1f, "Deformation Damage Multiplier");
					add_editor_option(true, handling->fDownforceModifier, &handling->fDownforceModifier, -1000.0f, 1000.0f, 0.1f, "Downforce Modifier");
					add_editor_option(true, handling->fDriveBiasFront, &handling->fDriveBiasFront, -1000.0f, 1000.0f, 0.1f, "Drive Bias Front");
					add_editor_option(true, handling->fDriveBiasRear, &handling->fDriveBiasRear, -1000.0f, 1000.0f, 0.1f, "Drive Bias Rear");
					add_editor_option(true, handling->fDriveInertia, &handling->fDriveInertia, -1000.0f, 1000.0f, 0.1f, "Drive Inertia");
					add_editor_option(true, handling->fDriveMaxFlatVel, &handling->fDriveMaxFlatVel, -1000.0f, 1000.0f, 0.1f, "Drive Max Flat Velocity");
					add_editor_option(true, handling->fEngineDamageMult, &handling->fEngineDamageMult, -1000.0f, 1000.0f, 0.1f, "Engine Damage Multiplier");
					add_editor_option(true, handling->fInitialDragCoeff, &handling->fInitialDragCoeff, -1000.0f, 1000.0f, 0.1f, "Initial Drag Coefficient");
					add_editor_option(true, handling->fInitialDriveForce, &handling->fInitialDriveForce, -1000.0f, 1000.0f, 0.1f, "Initial Drive Force");
					add_editor_option(true, handling->fInitialDriveMaxFlatVel, &handling->fInitialDriveMaxFlatVel, -1000.0f, 1000.0f, 0.1f, "Initial Drive Max Flat Velocity");
					add_editor_option(true, handling->fLowSpeedTractionLossMult, &handling->fLowSpeedTractionLossMult, -1000.0f, 1000.0f, 0.1f, "Low Speed Traction Loss Multiplier");
					add_editor_option(true, handling->fMass, &handling->fMass, -100000.0f, 100000.0f, 10.0f, "Mass");
					add_editor_option(true, handling->fOilVolume, &handling->fOilVolume, -1000.0f, 1000.0f, 0.1f, "Oil Volume");
					add_editor_option(true, handling->fPercentSubmerged, &handling->fPercentSubmerged, -1000.0f, 1000.0f, 0.1f, "Percent Submerged");
					add_editor_option(true, handling->fPetrolTankVolume, &handling->fPetrolTankVolume, -1000.0f, 1000.0f, 0.1f, "Petrol Tank Volume");
					add_editor_option(true, handling->fRollCentreHeightFront, &handling->fRollCentreHeightFront, -1000.0f, 1000.0f, 0.1f, "Roll Centre Height Front");
					add_editor_option(true, handling->fRollCentreHeightRear, &handling->fRollCentreHeightRear, -1000.0f, 1000.0f, 0.1f, "Roll Centre Height Rear");
					add_editor_option(true, handling->fSeatOffsetDistX, &handling->fSeatOffsetDistX, -1000.0f, 1000.0f, 0.1f, "Seat Offset Distance ~c~(X)");
					add_editor_option(true, handling->fSeatOffsetDistY, &handling->fSeatOffsetDistY, -1000.0f, 1000.0f, 0.1f, "Seat Offset Distance ~c~(Y)");
					add_editor_option(true, handling->fSeatOffsetDistZ, &handling->fSeatOffsetDistZ, -1000.0f, 1000.0f, 0.1f, "Seat Offset Distance ~c~(Z)");
					add_editor_option(true, handling->fSteeringLock, &handling->fSteeringLock, -1000.0f, 1000.0f, 0.1f, "Steering Lock");
					add_editor_option(true, handling->fSteeringLockRatio, &handling->fSteeringLockRatio, -1000.0f, 1000.0f, 0.1f, "Steering Lock Ratio");
					add_editor_option(true, handling->fSubmergedRatio, &handling->fSubmergedRatio, -1000.0f, 1000.0f, 0.1f, "Submerged Ratio");
					add_editor_option(true, handling->fSuspensionBiasFront, &handling->fSuspensionBiasFront, -1000.0f, 1000.0f, 0.1f, "Suspension Bias Front");
					add_editor_option(true, handling->fSuspensionBiasRear, &handling->fSuspensionBiasRear, -1000.0f, 1000.0f, 0.1f, "Suspension Bias Rear");
					add_editor_option(true, handling->fSuspensionCompDamp, &handling->fSuspensionCompDamp, -1000.0f, 1000.0f, 0.1f, "Suspension Comp Damp");
					add_editor_option(true, handling->fSuspensionForce, &handling->fSuspensionForce, -1000.0f, 1000.0f, 0.1f, "Suspension Force");
					add_editor_option(true, handling->fSuspensionLowerLimit, &handling->fSuspensionLowerLimit, -1000.0f, 1000.0f, 0.1f, "Suspension Lower Limit");
					add_editor_option(true, handling->fSuspensionRaise, &handling->fSuspensionRaise, -1000.0f, 1000.0f, 0.1f, "Suspension Raise");
					add_editor_option(true, handling->fSuspensionReboundDamp, &handling->fSuspensionReboundDamp, -1000.0f, 1000.0f, 0.1f, "Suspension Rebound Damp");
					add_editor_option(true, handling->fSuspensionUpperLimit, &handling->fSuspensionUpperLimit, -1000.0f, 1000.0f, 0.1f, "Suspension Upper Limit");
					add_editor_option(true, handling->fTractionBiasFront, &handling->fTractionBiasFront, -1000.0f, 1000.0f, 0.1f, "Traction Bias Front");
					add_editor_option(true, handling->fTractionBiasRear, &handling->fTractionBiasRear, -1000.0f, 1000.0f, 0.1f, "Traction Bias Rear");
					add_editor_option(true, handling->fTractionCurveLateral, &handling->fTractionCurveLateral, -1000.0f, 1000.0f, 0.1f, "Traction Curve Lateral");
					add_editor_option(true, handling->fTractionCurveLateralRatio, &handling->fTractionCurveLateralRatio, -1000.0f, 1000.0f, 0.1f, "Traction Curve Lateral Ratio");
					add_editor_option(true, handling->fTractionCurveMax, &handling->fTractionCurveMax, -1000.0f, 1000.0f, 0.1f, "Traction Curve Max");
					add_editor_option(true, handling->fTractionCurveMaxRatio, &handling->fTractionCurveMaxRatio, -1000.0f, 1000.0f, 0.1f, "Traction Curve Max Ratio");
					add_editor_option(true, handling->fTractionCurveMin, &handling->fTractionCurveMin, -1000.0f, 1000.0f, 0.1f, "Traction Curve Min");
					add_editor_option(true, handling->fTractionCurveRatio, &handling->fTractionCurveRatio, -1000.0f, 1000.0f, 0.1f, "Traction Curve Ratio");
					add_editor_option(true, handling->fTractionLossMult, &handling->fTractionLossMult, -1000.0f, 1000.0f, 0.1f, "Traction Loss Multiplier");
					add_editor_option(true, handling->fTractionSpringDeltaMax, &handling->fTractionSpringDeltaMax, -1000.0f, 1000.0f, 0.1f, "Traction Spring Delta Max");
					add_editor_option(true, handling->fTractionSpringDeltaMaxRatio, &handling->fTractionSpringDeltaMaxRatio, -1000.0f, 1000.0f, 0.1f, "Traction Spring Delta Max Ratio");
					add_editor_option(true, handling->fWeaponDamageMult, &handling->fWeaponDamageMult, -1000.0f, 1000.0f, 0.1f, "Weapon Damage Multiplier");
					add_editor_option(true, handling->vecCentreOfMassOffset.x, &handling->vecCentreOfMassOffset.x, -1000.0f, 1000.0f, 0.1f, "Centre Of Mass Offset ~c~(X)");
					add_editor_option(true, handling->vecCentreOfMassOffset.y, &handling->vecCentreOfMassOffset.y, -1000.0f, 1000.0f, 0.1f, "Centre Of Mass Offset ~c~(Y)");
					add_editor_option(true, handling->vecCentreOfMassOffset.z, &handling->vecCentreOfMassOffset.z, -1000.0f, 1000.0f, 0.1f, "Centre Of Mass Offset ~c~(Z)");
					add_editor_option(true, handling->vecInertiaMultiplier.x, &handling->vecInertiaMultiplier.x, -1000.0f, 1000.0f, 0.1f, "Inertia Multiplier ~c~(X)");
					add_editor_option(true, handling->vecInertiaMultiplier.y, &handling->vecInertiaMultiplier.y, -1000.0f, 1000.0f, 0.1f, "Inertia Multiplier ~c~(Y)");
					add_editor_option(true, handling->vecInertiaMultiplier.z, &handling->vecInertiaMultiplier.z, -1000.0f, 1000.0f, 0.1f, "Inertia Multiplier ~c~(Z)");
				}
				else {
					add_text_option("Failed to get handling data");
				}
			}
			else {
				add_text_option("Failed to get handling data");
			}
		}
		else {
			add_text_option("Failed to get handling data");
		}
	}
	else {
		add_text_option("Failed to get handling data");
	}
}
void menu_vehicle_handling() {
	add_submenu_option(menu_vehicle_handling_meta_editor, OBFUSCATE("Handling Editor"));
	std::uint64_t ped_factory = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(GTA_PED_FACTORY);
	if (ped_factory != NULL) {
		std::uint64_t entity = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(ped_factory + 0x8);
		if (entity != NULL) {
			std::uint64_t vehicle = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(entity + 0xD28);
			if (vehicle != NULL) {
				std::uint64_t model_info = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(vehicle + 0x20);
				if (model_info != NULL) {
					if (add_editor_option(false, vehicle_base_model[g_vehicle_base_model].name, &g_vehicle_base_model, 0, (std::int32_t)std::size(vehicle_base_model), 1, OBFUSCATE("Vehicle Type"))) {
						*(std::int32_t*)(model_info + 0x340) = vehicle_base_model[g_vehicle_base_model].type;
					}
				}
			}
		}
	}
	add_toggle_option(&g_vehicle_fly_vehicle, OBFUSCATE("Fly Vehicle"));
	if (add_toggle_option(&g_vehicle_gravity, OBFUSCATE("Gravity"))) {
		if (!g_vehicle_gravity) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
				if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
					VEHICLE::SET_VEHICLE_GRAVITY(vehicle, TRUE);
				}
			}
		}
	}
	add_toggle_option(&g_vehicle_tumble_dryer, OBFUSCATE("Tumble Dryer"));
	add_toggle_option(&g_vehicle_sticky_tires, OBFUSCATE("Sticky Tires"));
	if (add_toggle_option(&g_vehicle_drive_in_air, OBFUSCATE("Drive In Air"))) {
		if (g_vehicle_drive_in_air) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
				if (!ENTITY::DOES_ENTITY_EXIST(g_drive_wheel_object)) {
					Vector3 l_position = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0.0f, 0.0f, -5.0f);
					g_drive_wheel_object = spawn_object("prop_ld_ferris_wheel", l_position, FALSE);
					if (ENTITY::DOES_ENTITY_EXIST(g_drive_wheel_object)) {
						ENTITY::SET_ENTITY_COORDS(g_drive_wheel_object, l_position.x, l_position.y, l_position.z - 25.0f, 1, 0, 0, 1);
						ENTITY::SET_ENTITY_ROTATION(g_drive_wheel_object, 180, 90, 180, 2, 1);
						ENTITY::FREEZE_ENTITY_POSITION(g_drive_wheel_object, true);
					}
				}
				Vector3 l_position = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0.0f, 0.0f, 370.0f);
				ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), l_position.x, l_position.y, l_position.z, 1, 0, 0, 1);
			}
			else {
				print_notification(7000, "~r~Error:~s~ You must be in a vehicle.");
				g_vehicle_drive_in_air = false;
			}
		}
	}
	if (add_toggle_option(&g_vehicle_drive_on_water, OBFUSCATE("Drive On Water"))) {
		if (g_vehicle_drive_on_water) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
				if (!ENTITY::DOES_ENTITY_EXIST(g_drive_wheel_object)) {
					Vector3 l_position = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0.0f, 0.0f, -5.0f);
					g_drive_wheel_object = spawn_object("prop_ld_ferris_wheel", l_position, FALSE);
					if (ENTITY::DOES_ENTITY_EXIST(g_drive_wheel_object)) {
						ENTITY::SET_ENTITY_COORDS(g_drive_wheel_object, l_position.x, l_position.y, l_position.z - 25.0f, 1, 0, 0, 1);
						ENTITY::SET_ENTITY_ROTATION(g_drive_wheel_object, 180, 90, 180, 2, 1);
						ENTITY::FREEZE_ENTITY_POSITION(g_drive_wheel_object, true);
					}
				}
			}
			else {
				print_notification(7000, "~r~Error:~s~ You must be in a vehicle.");
				g_vehicle_drive_on_water = false;
			}
		}
	}
	if (add_toggle_option(&g_vehicle_drive_through_walls, OBFUSCATE("Drive Through Walls"))) {
		if (g_vehicle_drive_through_walls) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
				if (ENTITY::DOES_ENTITY_EXIST(vehicle))
					ENTITY::SET_ENTITY_COLLISION(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), false, 0);
			}
		}
		else if (!g_vehicle_drive_through_walls) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
				if (ENTITY::DOES_ENTITY_EXIST(vehicle))
					ENTITY::SET_ENTITY_COLLISION(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true, 0);
			}
		}
	}
	add_submenu_option(menu_vehicle_nitrous_config, OBFUSCATE("Nitrous Config"));
	if (add_toggle_option(&g_vehicle_drift_mode, OBFUSCATE("Drift Mode"))) {
		if (!g_vehicle_drift_mode) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
				if (ENTITY::DOES_ENTITY_EXIST(vehicle))
					VEHICLE::SET_VEHICLE_REDUCE_GRIP(vehicle, false);
			}
		}
	}
	if (add_toggle_option(&g_vehicle_super_grip, OBFUSCATE("Super Grip"))) {
		if (g_vehicle_super_grip) *(std::float_t*)(GTA_SUPER_GRIP_FLOAT) = 0.50f;
		else if (!g_vehicle_super_grip) *(std::float_t*)(GTA_SUPER_GRIP_FLOAT) = 0.16666667f;
	}
}
void menu_vehicle_radio_manager_change_station() {
	if (add_toggle_option(&g_vehicle_radio_manager_music_only, "Play Music Only")) {
		const char* name = AUDIO::GET_PLAYER_RADIO_STATION_NAME();
		if (name != nullptr) {
		}
	}
	add_break_option("Stations");
	for (auto s : g_radio_stations) {
		const char* name = s.c_str();
		if (add_text_option(name)) {
			std::int32_t ped = PLAYER::PLAYER_PED_ID();
			if (ENTITY::DOES_ENTITY_EXIST(ped)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
				if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
					AUDIO::SET_VEH_RADIO_STATION(vehicle, name);
					//AUDIO::SET_RADIO_STATION_MUSIC_ONLY(name, g_vehicle_radio_manager_music_only);
				}
			}
		}
	}
}
void menu_vehicle_radio_manager() {
	if (add_text_option("Turn On")) {
		std::int32_t ped = PLAYER::PLAYER_PED_ID();
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {
			std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
			if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
				AUDIO::SET_VEHICLE_RADIO_ENABLED(vehicle, TRUE);
			}
		}
	}
	if (add_text_option("Turn Off")) {
		std::int32_t ped = PLAYER::PLAYER_PED_ID();
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {
			std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
			if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
				AUDIO::SET_VEHICLE_RADIO_ENABLED(vehicle, FALSE);
			}
		}
	}
	add_submenu_option(menu_vehicle_radio_manager_change_station, "Change Station");
}
void menu_vehicle_funny_car_creator_load() {

}
void menu_vehicle_funny_car_spawner_object() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
		if (g_loaded_list_file_objects_did_load) {
			for (auto model : g_loaded_list_file_objects) {
				if (!g_loaded_list_file_objects_filter.empty()) {
					if (model.find(g_loaded_list_file_objects_filter) != std::string::npos) {
						if (add_text_option(model)) {
							Vector3 l_object_dim_min, g_object_dim_max;
							GAMEPLAY::GET_MODEL_DIMENSIONS(GAMEPLAY::GET_HASH_KEY(model.c_str()), &l_object_dim_min, &g_object_dim_max);

							Vector3 l_offset;
							if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
								l_offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0.0f, ((g_object_dim_max.y * 2) + 3.0f), 0.0f);
							else
								l_offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, ((g_object_dim_max.y * 2) + 3.0f), 0.0f);
							g_vehicle_funny_car_temp_object = spawn_object(model.c_str(), l_offset, FALSE);
						}
					}
				}
				else if (add_text_option(model)) {
					Vector3 l_object_dim_min, g_object_dim_max;
					GAMEPLAY::GET_MODEL_DIMENSIONS(GAMEPLAY::GET_HASH_KEY(model.c_str()), &l_object_dim_min, &g_object_dim_max);

					Vector3 l_offset;
					if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
						l_offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0.0f, ((g_object_dim_max.y * 2) + 3.0f), 0.0f);
					else
						l_offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, ((g_object_dim_max.y * 2) + 3.0f), 0.0f);
					g_vehicle_funny_car_temp_object = spawn_object(model.c_str(), l_offset, FALSE);
				}
			}
		}
		else { add_text_option(OBFUSCATE("\"obj_models.txt\" failed to load")); }
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_funny_car_spawner_vehicle_spawn() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
		ListPool* model_info_pool = (ListPool*)(GTA_MODEL_INFO_LIST_POOL);
		if (model_info_pool != nullptr) {
			for (std::int32_t i = 0; i < model_info_pool->capacity; i++) {
				std::uint64_t info = model_info_pool->get(i);
				if (info != NULL) {
					if ((*(BYTE*)(info + 157) & 0x1F) == 5) {
						char* make_ptr = (char*)(info + 0x2A4);
						char* model_ptr = (char*)(info + 0x298);
						if (VEHICLE::GET_VEHICLE_CLASS_FROM_NAME(GAMEPLAY::GET_HASH_KEY(model_ptr)) == g_vehicle_spawner_selected_class) {
							std::stringstream ss;
							std::string make(make_ptr);
							std::string model(model_ptr);

							if (make[0] || model[0]) {
								make = UI::_GET_LABEL_TEXT(make.c_str());
								model = UI::_GET_LABEL_TEXT(model.c_str());

								if (make != "NULL" && model != "NULL") {
									ss << make << " " << model;
								}
								else if (model != "NULL") {
									ss << model;
								}
								else {
									ss << "~c~Unknown";
								}
							}

							if (add_text_option(ss.str())) {
								g_vehicle_funny_car_temp_object = spawn_funny_vehicle(*(std::uint32_t*)(info + 0x18));
								VEHICLE::SET_VEHICLE_DIRT_LEVEL(g_vehicle_funny_car_temp_object, 0.0f);
								VEHICLE::SET_VEHICLE_MOD_KIT(g_vehicle_funny_car_temp_object, 0);
								VEHICLE::SET_VEHICLE_MOD_COLOR_1(g_vehicle_funny_car_temp_object, 3, 0, 0);
								VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(g_vehicle_funny_car_temp_object, 66, 225, 221);
								VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(g_vehicle_funny_car_temp_object, 10, 20, 30);
								VEHICLE::SET_VEHICLE_MOD_COLOR_2(g_vehicle_funny_car_temp_object, 3, 5);
								VEHICLE::SET_VEHICLE_EXTRA_COLOURS(g_vehicle_funny_car_temp_object, 24, 4);
								VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(g_vehicle_funny_car_temp_object, 0, 0, 0);
								VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(g_vehicle_funny_car_temp_object, 5);
								VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(g_vehicle_funny_car_temp_object, "QUANTUM");
								VEHICLE::TOGGLE_VEHICLE_MOD(g_vehicle_funny_car_temp_object, 18, 1);
								VEHICLE::TOGGLE_VEHICLE_MOD(g_vehicle_funny_car_temp_object, 22, 1);
								VEHICLE::TOGGLE_VEHICLE_MOD(g_vehicle_funny_car_temp_object, 20, 1);
								VEHICLE::SET_VEHICLE_MOD(g_vehicle_funny_car_temp_object, 16, 5, 0);
								VEHICLE::SET_VEHICLE_MOD(g_vehicle_funny_car_temp_object, 12, 2, 0);
								VEHICLE::SET_VEHICLE_MOD(g_vehicle_funny_car_temp_object, 11, 3, 0);
								VEHICLE::SET_VEHICLE_MOD(g_vehicle_funny_car_temp_object, 14, 14, 0);
								VEHICLE::SET_VEHICLE_MOD(g_vehicle_funny_car_temp_object, 15, 3, 0);
								VEHICLE::SET_VEHICLE_MOD(g_vehicle_funny_car_temp_object, 13, 2, 0);
								VEHICLE::SET_VEHICLE_WHEEL_TYPE(g_vehicle_funny_car_temp_object, 6);
								VEHICLE::SET_VEHICLE_WINDOW_TINT(g_vehicle_funny_car_temp_object, 5);
								VEHICLE::SET_VEHICLE_MOD(g_vehicle_funny_car_temp_object, 23, 19, 1);
								VEHICLE::SET_VEHICLE_MOD(g_vehicle_funny_car_temp_object, 0, 1, 0);
								VEHICLE::SET_VEHICLE_MOD(g_vehicle_funny_car_temp_object, 1, 1, 0);
								VEHICLE::SET_VEHICLE_MOD(g_vehicle_funny_car_temp_object, 2, 1, 0);
								VEHICLE::SET_VEHICLE_MOD(g_vehicle_funny_car_temp_object, 3, 1, 0);
								VEHICLE::SET_VEHICLE_MOD(g_vehicle_funny_car_temp_object, 4, 1, 0);
								VEHICLE::SET_VEHICLE_MOD(g_vehicle_funny_car_temp_object, 5, 1, 0);
								VEHICLE::SET_VEHICLE_MOD(g_vehicle_funny_car_temp_object, 6, 1, 0);
								VEHICLE::SET_VEHICLE_MOD(g_vehicle_funny_car_temp_object, 7, 1, 0);
								VEHICLE::SET_VEHICLE_MOD(g_vehicle_funny_car_temp_object, 8, 1, 0);
								VEHICLE::SET_VEHICLE_MOD(g_vehicle_funny_car_temp_object, 9, 1, 0);
								VEHICLE::SET_VEHICLE_MOD(g_vehicle_funny_car_temp_object, 10, 1, 0);
							}
						}
					}
				}
			}
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_funny_car_spawner_vehicle() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
		for (std::int32_t i = 0; i < 22; i++) {
			if (add_submenu_option(menu_vehicle_funny_car_spawner_vehicle_spawn, get_vehicle_class_name(i)))
				g_vehicle_spawner_selected_class = i;
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_funny_car_spawner_ped() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
		add_keyboard_option(true, &g_loaded_list_file_peds_filter, 32, OBFUSCATE("Search For Model"));
		add_break_option(OBFUSCATE("Loaded Models"));
		if (g_loaded_list_file_peds_did_load) {
			for (auto model : g_loaded_list_file_peds) {
				if (!g_loaded_list_file_peds_filter.empty()) {
					if (model.find(g_loaded_list_file_peds_filter) != std::string::npos) {
						if (add_text_option(model)) {
							Vector3 l_object_dim_min, g_object_dim_max;
							GAMEPLAY::GET_MODEL_DIMENSIONS(GAMEPLAY::GET_HASH_KEY(model.c_str()), &l_object_dim_min, &g_object_dim_max);

							Vector3 l_coords;
							if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
								l_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0.0f, ((g_object_dim_max.y * 2) + 3.0f), 0.0f);
							else
								l_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, ((g_object_dim_max.y * 2) + 3.0f), 0.0f);

							g_vehicle_funny_car_temp_object = spawn_ped(GAMEPLAY::GET_HASH_KEY(model.c_str()), l_coords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
						}
					}
				}
				else if (add_text_option(model)) {
					Vector3 l_object_dim_min, g_object_dim_max;
					GAMEPLAY::GET_MODEL_DIMENSIONS(GAMEPLAY::GET_HASH_KEY(model.c_str()), &l_object_dim_min, &g_object_dim_max);

					Vector3 l_coords;
					if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
						l_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0.0f, ((g_object_dim_max.y * 2) + 3.0f), 0.0f);
					else
						l_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, ((g_object_dim_max.y * 2) + 3.0f), 0.0f);

					g_vehicle_funny_car_temp_object = spawn_ped(GAMEPLAY::GET_HASH_KEY(model.c_str()), l_coords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
				}
			}
		}
		else { add_text_option(OBFUSCATE("\"ped_models.txt\" failed to load")); }
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_funny_car_spawner_ped_sport_anim() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
		for (std::int32_t i = 0; i < ARRAYSIZE(g_sport_anims); i++) {
			if (add_text_option(g_sport_anims[i].local_name)) {

				const char* dict = g_sport_anims[i].anim_dict.c_str();
				const char* name = g_sport_anims[i].anim_name.c_str();

				if (STREAMING::DOES_ANIM_DICT_EXIST(dict)) {
					STREAMING::REQUEST_ANIM_DICT(dict);
					while (!STREAMING::HAS_ANIM_DICT_LOADED(dict))
						Script::GetCurrent()->ScriptYield();
					if (ENTITY::GET_ENTITY_TYPE(g_object_handle) == 1) {
						AI::TASK_PLAY_ANIM(g_object_handle, dict, name, 8.0f, 0.0f, -1, 9, 0.0f, false, false, false);
						AI::SET_ANIM_RATE(g_object_handle, g_animation_speed, 0.0f, 0.0f);
					}
				}
			}
		}

		if (g_object_handle != PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())) {
			if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
				CAM::_ANIMATE_GAMEPLAY_CAM_ZOOM(1, g_vehicle_funny_car_cam_zoom);
			}
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_funny_car_spawner_ped_sex_anim() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
		for (std::int32_t i = 0; i < ARRAYSIZE(g_sex_anims); i++) {
			if (add_text_option(g_sex_anims[i].local_name)) {
				const char* dict = g_sex_anims[i].anim_dict.c_str();
				const char* name = g_sex_anims[i].anim_name.c_str();

				if (STREAMING::DOES_ANIM_DICT_EXIST(dict)) {
					STREAMING::REQUEST_ANIM_DICT(dict);
					while (!STREAMING::HAS_ANIM_DICT_LOADED(dict))
						Script::GetCurrent()->ScriptYield();
					if (ENTITY::GET_ENTITY_TYPE(g_object_handle) == 1) {
						AI::TASK_PLAY_ANIM(g_object_handle, dict, name, 8.0f, 0.0f, -1, 9, 0.0f, false, false, false);
						AI::SET_ANIM_RATE(g_object_handle, g_animation_speed, 0.0f, 0.0f);
					}
				}
			}
		}

		if (g_object_handle != PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())) {
			if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
				CAM::_ANIMATE_GAMEPLAY_CAM_ZOOM(1, g_vehicle_funny_car_cam_zoom);
			}
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_funny_car_spawner_ped_dance_anim() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
		for (std::int32_t i = 0; i < ARRAYSIZE(g_dance_anims); i++) {
			if (add_text_option(g_dance_anims[i].local_name)) {
				const char* dict = g_dance_anims[i].anim_dict.c_str();
				const char* name = g_dance_anims[i].anim_name.c_str();

				if (STREAMING::DOES_ANIM_DICT_EXIST(dict)) {
					STREAMING::REQUEST_ANIM_DICT(dict);
					while (!STREAMING::HAS_ANIM_DICT_LOADED(dict))
						Script::GetCurrent()->ScriptYield();
					if (ENTITY::GET_ENTITY_TYPE(g_object_handle) == 1) {
						AI::TASK_PLAY_ANIM(g_object_handle, dict, name, 8.0f, 0.0f, -1, 9, 0.0f, false, false, false);
						AI::SET_ANIM_RATE(g_object_handle, g_animation_speed, 0.0f, 0.0f);
					}
				}
			}
		}

		if (g_object_handle != PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())) {
			if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
				CAM::_ANIMATE_GAMEPLAY_CAM_ZOOM(1, g_vehicle_funny_car_cam_zoom);
			}
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_funny_car_spawner_ped_superhero_anim() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
		for (std::int32_t i = 0; i < ARRAYSIZE(g_super_hero_anims); i++) {
			if (add_text_option(g_super_hero_anims[i].local_name)) {
				const char* dict = g_super_hero_anims[i].anim_dict.c_str();
				const char* name = g_super_hero_anims[i].anim_name.c_str();

				if (STREAMING::DOES_ANIM_DICT_EXIST(dict)) {
					STREAMING::REQUEST_ANIM_DICT(dict);
					while (!STREAMING::HAS_ANIM_DICT_LOADED(dict))
						Script::GetCurrent()->ScriptYield();
					if (ENTITY::GET_ENTITY_TYPE(g_object_handle) == 1) {
						AI::TASK_PLAY_ANIM(g_object_handle, dict, name, 8.0f, 0.0f, -1, 9, 0.0f, false, false, false);
						AI::SET_ANIM_RATE(g_object_handle, g_animation_speed, 0.0f, 0.0f);
					}
				}
			}
		}

		if (g_object_handle != PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())) {
			if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
				CAM::_ANIMATE_GAMEPLAY_CAM_ZOOM(1, g_vehicle_funny_car_cam_zoom);
			}
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_funny_car_spawner_ped_misc_anim() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
		for (std::int32_t i = 0; i < ARRAYSIZE(g_misc_anims); i++) {
			if (add_text_option(g_misc_anims[i].local_name)) {
				const char* dict = g_misc_anims[i].anim_dict.c_str();
				const char* name = g_misc_anims[i].anim_name.c_str();

				if (STREAMING::DOES_ANIM_DICT_EXIST(dict)) {
					STREAMING::REQUEST_ANIM_DICT(dict);
					while (!STREAMING::HAS_ANIM_DICT_LOADED(dict))
						Script::GetCurrent()->ScriptYield();
					if (ENTITY::GET_ENTITY_TYPE(g_object_handle) == 1) {
						AI::TASK_PLAY_ANIM(g_object_handle, dict, name, 8.0f, 0.0f, -1, 9, 0.0f, false, false, false);
						AI::SET_ANIM_RATE(g_object_handle, g_animation_speed, 0.0f, 0.0f);
					}
				}
			}
		}

		if (g_object_handle != PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())) {
			if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
				CAM::_ANIMATE_GAMEPLAY_CAM_ZOOM(1, g_vehicle_funny_car_cam_zoom);
			}
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_funny_car_spawner_ped_anim() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
		if (add_editor_option(true, g_animation_speed, &g_animation_speed, 0.00f, 20.0f, 0.05f, OBFUSCATE("Playback Speed"))) {
			if (ENTITY::GET_ENTITY_TYPE(g_object_handle) == 1)
				AI::SET_ANIM_RATE(g_object_handle, g_animation_speed, 0.0f, 0.0f);
		}
		add_break_option(OBFUSCATE("Catagories"));
		add_submenu_option(menu_vehicle_funny_car_spawner_ped_sport_anim, OBFUSCATE("Sport"));
		add_submenu_option(menu_vehicle_funny_car_spawner_ped_sex_anim, OBFUSCATE("Sex"));
		add_submenu_option(menu_vehicle_funny_car_spawner_ped_dance_anim, OBFUSCATE("Dance"));
		add_submenu_option(menu_vehicle_funny_car_spawner_ped_superhero_anim, OBFUSCATE("Superhero"));
		add_submenu_option(menu_vehicle_funny_car_spawner_ped_misc_anim, OBFUSCATE("Misc"));
		if (add_text_option(OBFUSCATE("Clear Current Animation"))) {
			if (ENTITY::GET_ENTITY_TYPE(g_object_handle) == 1) {
				AI::CLEAR_PED_TASKS_IMMEDIATELY(g_object_handle);
				print_notification(7000, "~g~Success:~s~ Cleared Player Current Animation.");
			}
		}

		if (g_object_handle != PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())) {
			if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
				CAM::_ANIMATE_GAMEPLAY_CAM_ZOOM(1, g_vehicle_funny_car_cam_zoom);
			}
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_funny_car_spawner_attached_entities() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
		add_string_array_option(true, g_vehicle_bone_list, (std::int32_t)std::size(g_vehicle_bone_list), &g_vehicle_funny_car_bone, OBFUSCATE("Bone Index"));
		if (add_toggle_option(&g_vehicle_funny_car_invisible, OBFUSCATE("Invisible")))
			ENTITY::SET_ENTITY_VISIBLE(g_object_handle, !g_vehicle_funny_car_invisible, 0);
		if (ENTITY::GET_ENTITY_TYPE(g_object_handle) == 1)
			add_submenu_option(menu_vehicle_funny_car_spawner_ped_anim, OBFUSCATE("Animations"));
		add_editor_option(true, g_vehicle_funny_car_cam_zoom, &g_vehicle_funny_car_cam_zoom, 1.0f, 1000.0f, 0.5f, OBFUSCATE("Cam Zoom"));
		add_editor_option(true, g_vehicle_funny_car_x, &g_vehicle_funny_car_x, -180.0f, 180.0f, 0.04f, OBFUSCATE("Offset ~c~(X)"));
		add_editor_option(true, g_vehicle_funny_car_y, &g_vehicle_funny_car_y, -180.0f, 180.0f, 0.04f, OBFUSCATE("Offset ~c~(Y)"));
		add_editor_option(true, g_vehicle_funny_car_z, &g_vehicle_funny_car_z, -180.0f, 180.0f, 0.04f, OBFUSCATE("Offset ~c~(Z)"));
		add_editor_option(true, g_vehicle_funny_car_p, &g_vehicle_funny_car_p, -180.0f, 180.0f, 0.2f, OBFUSCATE("Pitch"));
		add_editor_option(true, g_vehicle_funny_car_r, &g_vehicle_funny_car_r, -180.0f, 180.0f, 0.2f, OBFUSCATE("Roll"));
		add_editor_option(true, g_vehicle_funny_car_ya, &g_vehicle_funny_car_ya, -180.0f, 180.0f, 0.2f, OBFUSCATE("Yaw"));

		if (g_object_handle != PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())) {
			if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
				//DECORATOR::DECOR_SET_FLOAT(g_object_handle, "bombdec", g_vehicle_funny_car_p);
				//DECORATOR::DECOR_SET_FLOAT(g_object_handle, "bombdec1", g_vehicle_funny_car_r);
				//DECORATOR::DECOR_SET_FLOAT(g_object_handle, "bombowner", g_vehicle_funny_car_ya);

				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);

				CAM::_ANIMATE_GAMEPLAY_CAM_ZOOM(1, g_vehicle_funny_car_cam_zoom);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(g_object_handle, vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, g_vehicle_bone_list[g_vehicle_funny_car_bone].c_str()), g_vehicle_funny_car_x, g_vehicle_funny_car_y, g_vehicle_funny_car_z, g_vehicle_funny_car_p, g_vehicle_funny_car_r, g_vehicle_funny_car_ya, false, false, false, false, 2, 1);
				ENTITY::FREEZE_ENTITY_POSITION(g_object_handle, true);
				ENTITY::SET_ENTITY_COLLISION(g_object_handle, true, 0);
				if (ENTITY::IS_ENTITY_A_VEHICLE(g_object_handle)) {
					VEHICLE::SET_VEHICLE_ALLOW_NO_PASSENGERS_LOCKON(g_object_handle, false);
					VEHICLE::SET_VEHICLE_DOORS_LOCKED(g_object_handle, 2);
				}
			}
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_funny_car_creator() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
		//add_submenu_option(menu_vehicle_funny_car_creator_load, OBFUSCATE("Load Funny Cars"));
		if (add_submenu_option(menu_vehicle_funny_car_spawner_object, OBFUSCATE("Object Spawner")))
			g_loaded_list_file_objects_did_load = load_list_file("obj_models", &g_loaded_list_file_objects);
		add_submenu_option(menu_vehicle_funny_car_spawner_vehicle, OBFUSCATE("Vehicle Spawner"));
		if (add_submenu_option(menu_vehicle_funny_car_spawner_ped, OBFUSCATE("Ped Spawner")))
			g_loaded_list_file_peds_did_load = load_list_file("ped_models", &g_loaded_list_file_peds);
		if (add_text_option(OBFUSCATE("Attach Last Spawned Entity"))) {
			if (ENTITY::DOES_ENTITY_EXIST(g_vehicle_funny_car_temp_object)) {
				g_object_handle = g_vehicle_funny_car_temp_object;
				ENTITY::ATTACH_ENTITY_TO_ENTITY(g_object_handle, PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, false, false, false, false, 2, 1);
				ENTITY::FREEZE_ENTITY_POSITION(g_object_handle, true);
				ENTITY::SET_ENTITY_COLLISION(g_object_handle, true, 0);
				if (ENTITY::IS_ENTITY_A_VEHICLE(g_object_handle)) {
					VEHICLE::SET_VEHICLE_ALLOW_NO_PASSENGERS_LOCKON(g_object_handle, false);
					VEHICLE::SET_VEHICLE_DOORS_LOCKED(g_object_handle, 2);
				}
			}
			else
				print_notification(7000, OBFUSCATE("~r~Error:~s~ Entity handle does not exist."));
		}
		if (add_text_option(OBFUSCATE("Delete Last Attached"))) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
				if (g_object_handle != PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())) {
					switch (ENTITY::GET_ENTITY_TYPE(g_object_handle)) {
					case 1: {
							if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
								ENTITY::SET_ENTITY_AS_MISSION_ENTITY(g_object_handle, 0, 1);
								PED::DELETE_PED(&g_object_handle);
							}
						} break;
					case 2: {
							if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
								ENTITY::SET_ENTITY_AS_MISSION_ENTITY(g_object_handle, 0, 1);
								VEHICLE::DELETE_VEHICLE(&g_object_handle);
							}
						} break;
					case 3: {
							if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
								ENTITY::SET_ENTITY_AS_MISSION_ENTITY(g_object_handle, 0, 1);
								OBJECT::DELETE_OBJECT(&g_object_handle);
							}
						} break;
					}
				}
				else
					print_notification(7000, OBFUSCATE("Object handle cannot be your vehicle."));
			}
			else
				print_notification(7000, OBFUSCATE("You must be in a vehicle."));
		}
		add_break_option(OBFUSCATE("Attached Entities"));

		if (GTA_ATTACHMENT_EXTENSION_INST_POOL) {
			std::uint64_t pool = *(uint64_t*)(GTA_ATTACHMENT_EXTENSION_INST_POOL);
			if (pool) {
				std::int32_t g_vehicle_funny_car_attached_entities_count = NULL;
				std::uint32_t pool_size = *(uint32_t*)(pool + 0x10);
				for (std::uint32_t i = 0; i < pool_size; i++) {
					std::uint64_t extension = get_element_from_pool(pool, i);
					if (extension) {
						std::uint64_t parent_entity = *(std::uint64_t*)(extension);
						if (parent_entity == NULL)
							continue;

						//if (parent != PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0))
						//	continue;

						//std::uint64_t child_entity = *(std::uint64_t*)(extension + 0x18);
						//if (child_entity == NULL)
						//	continue;
					}
				}
				if (g_vehicle_funny_car_attached_entities_count == NULL)
					add_text_option("No Attachments Found");
			}
		}
	}
	else {
		add_text_option(OBFUSCATE("No Vehicle Found"));
		CURRENT_OPTION = 1;
	}
}
void menu_vehicle_particle_trails() {
	add_string_array_option(true, g_particle_effect_names, (std::int32_t)std::size(g_particle_effect_names), &g_vehicle_particle_trails_selected_particle_arr_index, OBFUSCATE("Particle"));
	for (auto i = 0; i < std::size(g_vehicle_particle_trails_bone_active); i++) 
		add_toggle_option(&g_vehicle_particle_trails_bone_active[i], g_vehicle_bone_list[i].c_str());
	add_editor_option(true, g_vehicle_particle_trails_scale, &g_vehicle_particle_trails_scale, 0.0f, 10.0f, 0.01f, OBFUSCATE("Scale"));
	add_toggle_option(&g_vehicle_particle_trails_play_when_stationary, OBFUSCATE("Play When Stationary"));
	add_toggle_option(&g_vehicle_particle_trails_active, OBFUSCATE("Active"));
}
void menu_vehicle_drive_to_waypoint_driving_styles() {
	add_toggle_option(&g_vehicle_drive_to_waypoint_stop_before_vehicles, "Stop Before Vehicles");
	add_toggle_option(&g_vehicle_drive_to_waypoint_stop_before_peds, "Stop Before Peds");
	add_toggle_option(&g_vehicle_drive_to_waypoint_avoid_vehicles, "Avoid Vehicles");
	add_toggle_option(&g_vehicle_drive_to_waypoint_avoid_empty_vehicles, "Avoid Empty Vehicles");
	add_toggle_option(&g_vehicle_drive_to_waypoint_avoid_peds, "Avoid Peds");
	add_toggle_option(&g_vehicle_drive_to_waypoint_avoid_objects, "Avoid Objects");
	add_toggle_option(&g_vehicle_drive_to_waypoint_stop_at_traffic_lights, "Stop At Traffic Lights");
	add_toggle_option(&g_vehicle_drive_to_waypoint_use_blinkers, "Use Blinkers");
	add_toggle_option(&g_vehicle_drive_to_waypoint_allow_to_go_wrong_way, "Allow To Go Wrong Way");
	add_toggle_option(&g_vehicle_drive_to_waypoint_go_in_reverse_gear, "Go In Reverse Gear");
	add_toggle_option(&g_vehicle_drive_to_waypoint_take_shortest_path, "Take Shortest Path");
	add_toggle_option(&g_vehicle_drive_to_waypoint_avoid_offroad, "Avoid Going Off-Road");
	add_toggle_option(&g_vehicle_drive_to_waypoint_avoid_highways, "Avoid Using Highways");
	if (UI::DOES_BLIP_EXIST(UI::GET_FIRST_BLIP_INFO_ID(8))) {
		std::uint64_t points = *(std::uint64_t*)GTA_WAYPOINT_PATH_DATA;
		if (points) {

			std::int32_t ped = PLAYER::PLAYER_PED_ID();
			if (ENTITY::DOES_ENTITY_EXIST(ped)) {
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, 0.0f, 0.0f, 0.0f);
				GRAPHICS::DRAW_LINE(coords.x, coords.y, coords.z, *(std::float_t*)(points + 0x10), *(std::float_t*)(points + 0x14), coords.z, 100, 0, 255, 255);
			}

			add_info_box_title("Waypoint Info");
			add_data_to_info_box("GPS Nodes", *(std::int32_t*)(GTA_WAYPOINT_PATH_DATA + 0x44));
			add_data_to_info_box("Axis ~c~(X)", *(std::float_t*)(GTA_WAYPOINT_PATH_DATA + 0x20));
			add_data_to_info_box("Axis ~c~(Y)", *(std::float_t*)(GTA_WAYPOINT_PATH_DATA + 0x24));
			add_data_to_info_box("Dist. ~c~(Metres)", *(std::float_t*)(GTA_WAYPOINT_PATH_DATA + 0x68));
			draw_rect((g_menu_banner_pos_x >= 0.5f) ? (g_menu_banner_pos_x - (g_menu_banner_size_x / 2) - (g_info_box_title_width / 2)) : (g_menu_banner_pos_x + (g_menu_banner_size_x / 2) + (g_info_box_title_width / 2)), ((g_menu_banner_pos_y - ((g_menu_banner_size_y / 2)) + (g_info_box_title_length / 2)) + (g_info_box_title_length / 2)) + ((g_info_box_count * (g_info_box_title_length / 2)) / 2) + 0.0035f, g_info_box_title_width, (g_info_box_count * (g_info_box_title_length / 2)) + 0.007f, g_menu_background_colour);
			g_info_box_count = NULL;
		}
	}
}
void menu_vehicle_drive_to_waypoint() {
	add_editor_option(true, g_vehicle_drive_to_waypoint_speed, &g_vehicle_drive_to_waypoint_speed, 10.0f, 150.0f, 0.5f, "Speed");
	add_editor_option(true, g_vehicle_drive_to_waypoint_driver_ability, &g_vehicle_drive_to_waypoint_driver_ability, 0.0f, 200.0f, 0.5f, "Driving Ability");
	add_submenu_option(menu_vehicle_drive_to_waypoint_driving_styles, "Driving Styles");
	if (add_text_option(OBFUSCATE("Go"))) {
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
			std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
			if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
				std::int32_t blip = UI::GET_FIRST_BLIP_INFO_ID(8);
				if (UI::DOES_BLIP_EXIST(blip)) {
					Vector3 coords = UI::GET_BLIP_COORDS(blip);
					std::int32_t driving_style = NULL;
					if (g_vehicle_drive_to_waypoint_stop_before_vehicles)
						driving_style |= PED_DRIVE_FLAG_STOP_BEFORE_VEHICLES;
					if (g_vehicle_drive_to_waypoint_stop_before_peds)
						driving_style |= PED_DRIVE_FLAG_STOP_BEFORE_PEDS;
					if (g_vehicle_drive_to_waypoint_avoid_vehicles)
						driving_style |= PED_DRIVE_FLAG_AVOID_VEHICLES;
					if (g_vehicle_drive_to_waypoint_avoid_empty_vehicles)
						driving_style |= PED_DRIVE_FLAG_AVOID_EMPTY_VEHICLES;
					if (g_vehicle_drive_to_waypoint_avoid_peds)
						driving_style |= PED_DRIVE_FLAG_AVOID_PEDS;
					if (g_vehicle_drive_to_waypoint_avoid_objects)
						driving_style |= PED_DRIVE_FLAG_AVOID_OBJECTS;
					if (g_vehicle_drive_to_waypoint_stop_at_traffic_lights)
						driving_style |= PED_DRIVE_FLAG_STOP_AT_TRAFFIC_LIGHTS;
					if (g_vehicle_drive_to_waypoint_use_blinkers)
						driving_style |= PED_DRIVE_FLAG_USE_BLINKERS;
					if (g_vehicle_drive_to_waypoint_allow_to_go_wrong_way)
						driving_style |= PED_DRIVE_FLAG_ALLOW_TO_GO_WRONG_WAY;
					if (g_vehicle_drive_to_waypoint_go_in_reverse_gear)
						driving_style |= PED_DRIVE_FLAG_GO_IN_REVERSE_GEAR;
					if (g_vehicle_drive_to_waypoint_take_shortest_path)
						driving_style |= PED_DRIVE_FLAG_TAKE_SHORTEST_PATH;
					if (g_vehicle_drive_to_waypoint_avoid_offroad)
						driving_style |= PED_DRIVE_FLAG_AVOID_OFFROAD;
					if (g_vehicle_drive_to_waypoint_avoid_highways)
						driving_style |= PED_DRIVE_FLAG_AVOID_HIGHWAYS;
					AI::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(PLAYER::PLAYER_PED_ID(), vehicle, coords.x, coords.y, coords.z, g_vehicle_drive_to_waypoint_speed, driving_style, 20.0f);
					PED::SET_DRIVER_ABILITY(PLAYER::PLAYER_PED_ID(), g_vehicle_drive_to_waypoint_driver_ability);
					print_notification(7000, "~g~Success:~s~ Taking you to the set waypoint. Press ~y~F3~s~ to cancel.");
					while (UI::DOES_BLIP_EXIST(blip) && !KEYBOARD::IS_KEYBOARD_INPUT_PRESSED(VK_F3))
						Script::GetCurrent()->ScriptYield();
					AI::CLEAR_PED_TASKS(PLAYER::PLAYER_PED_ID());
				}
				else
					print_notification(7000, "~r~Error:~s~ No waypoint set.");
			}
		}
		else {
			std::stringstream ss;
			ss << "~r~Error:~s~ You are not in a vehicle.";
			print_notification(7000, ss.str());
		}
	}
	if (UI::DOES_BLIP_EXIST(UI::GET_FIRST_BLIP_INFO_ID(8))) {
		std::uint64_t points = *(std::uint64_t*)GTA_WAYPOINT_PATH_DATA;
		if (points) {

			std::int32_t ped = PLAYER::PLAYER_PED_ID();
			if (ENTITY::DOES_ENTITY_EXIST(ped)) {
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, 0.0f, 0.0f, 0.0f);
				GRAPHICS::DRAW_LINE(coords.x, coords.y, coords.z, *(std::float_t*)(points + 0x10), *(std::float_t*)(points + 0x14), coords.z, 100, 0, 255, 255);
			}

			add_info_box_title("Waypoint Info");
			add_data_to_info_box("GPS Nodes", *(std::int32_t*)(GTA_WAYPOINT_PATH_DATA + 0x44));
			add_data_to_info_box("Axis ~c~(X)", *(std::float_t*)(GTA_WAYPOINT_PATH_DATA + 0x20));
			add_data_to_info_box("Axis ~c~(Y)", *(std::float_t*)(GTA_WAYPOINT_PATH_DATA + 0x24));
			add_data_to_info_box("Dist. ~c~(Metres)", *(std::float_t*)(GTA_WAYPOINT_PATH_DATA + 0x68));
			draw_rect((g_menu_banner_pos_x >= 0.5f) ? (g_menu_banner_pos_x - (g_menu_banner_size_x / 2) - (g_info_box_title_width / 2)) : (g_menu_banner_pos_x + (g_menu_banner_size_x / 2) + (g_info_box_title_width / 2)), ((g_menu_banner_pos_y - ((g_menu_banner_size_y / 2)) + (g_info_box_title_length / 2)) + (g_info_box_title_length / 2)) + ((g_info_box_count * (g_info_box_title_length / 2)) / 2) + 0.0035f, g_info_box_title_width, (g_info_box_count * (g_info_box_title_length / 2)) + 0.007f, g_menu_background_colour);
			g_info_box_count = NULL;
		}
	}
}
void menu_vehicle() {
	add_submenu_option(menu_vehicle_spawner, OBFUSCATE("Vehicle Spawner"));
	add_submenu_option(menu_vehicle_lsc, OBFUSCATE("Los Santos Customs"));
	add_submenu_option(menu_vehicle_handling, OBFUSCATE("Vehicle Handling"));
	add_submenu_option(menu_vehicle_radio_manager, "Radio Manager");
	add_string_array_toggle_option(&g_vehicle_weapon_active, g_vehicle_weapon_hash, ARRAYSIZE(g_vehicle_weapon_hash), &g_vehicle_weapon, OBFUSCATE("Vehicle Weapon"));
	add_submenu_option(menu_vehicle_funny_car_creator, OBFUSCATE("Funny Car Creator"));
	add_submenu_option(menu_vehicle_particle_trails, OBFUSCATE("Vehicle Particle Trails"));
	add_toggle_option(&g_vehicle_plate_speedo, OBFUSCATE("Plate Speedo"));
	add_submenu_option(menu_vehicle_drive_to_waypoint, OBFUSCATE("Drive To Waypoint"));
	if (add_text_option(OBFUSCATE("Fix & Wash"))) {
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
			std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
			if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
				VEHICLE::SET_VEHICLE_FIXED(vehicle);
				VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle, 0.0f);
				ENTITY::SET_ENTITY_RENDER_SCORCHED(vehicle, FALSE);
			}
		}
	}
	if (add_text_option(OBFUSCATE("Scorch Vehicle"))) {
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
			std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
			if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
				ENTITY::SET_ENTITY_RENDER_SCORCHED(vehicle, TRUE);
			}
		}
	}
	if (add_toggle_option(&g_vehicle_seatbelt, OBFUSCATE("Seatbelt"))) {
		if (!g_vehicle_seatbelt) {
			PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), TRUE);
			PED::SET_PED_RAGDOLL_ON_COLLISION(PLAYER::PLAYER_PED_ID(), TRUE);
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), TRUE);
		}
	}
	if (add_toggle_option(&g_vehicle_invincible, OBFUSCATE("Vehicle Invincible"))) {
		if (!g_vehicle_invincible) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
				VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true);
				ENTITY::SET_ENTITY_INVINCIBLE(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), false);
				ENTITY::SET_ENTITY_CAN_BE_DAMAGED(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true);
				ENTITY::SET_ENTITY_PROOFS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), false, false, false, false, false, false, false, true);
				VEHICLE::SET_VEHICLE_STRONG(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), false);
				VEHICLE::SET_VEHICLE_BODY_HEALTH(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 1000);
			}
		}
	}
	if (add_toggle_option(&g_vehicle_invisible, OBFUSCATE("Vehicle Invisible"))) {
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
			if (!g_vehicle_invisible) {
				ENTITY::SET_ENTITY_VISIBLE(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true, 0);
			}
		}
	}
	add_toggle_option(&g_vehicle_auto_flip, OBFUSCATE("Auto Flip"));
	std::uint64_t ped_factory = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(GTA_PED_FACTORY);
	if (ped_factory != NULL) {
		std::uint64_t entity = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(ped_factory + 0x8);
		if (entity != NULL) {
			std::uint64_t vehicle = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(entity + 0xD28);
			if (vehicle != NULL) {
				std::uint64_t draw_handler = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(vehicle + 0x48);
				if (draw_handler != NULL) {
					std::uint64_t stream_render_gfx = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(draw_handler + 0x370);
					if (stream_render_gfx != NULL) {
						add_editor_option(false, *(std::float_t*)(stream_render_gfx + 0x8), (std::float_t*)(stream_render_gfx + 0x8), 0.0f, 10.0f, 0.1f, "Wheel Scale");
					}
				}
			}
		}
	}
}

void menu_object_entity_movement() {
	add_editor_toggle_option(&g_object_handle_movement_x, g_object_handle_movement_value_x, &g_object_handle_movement_value_x, -10.0f, 10.0f, 0.01f, "Axis ~c~(X)~s~ Looped");
	add_editor_toggle_option(&g_object_handle_movement_y, g_object_handle_movement_value_y, &g_object_handle_movement_value_y, -10.0f, 10.0f, 0.01f, "Axis ~c~(Y)~s~ Looped");
	add_editor_toggle_option(&g_object_handle_movement_z, g_object_handle_movement_value_z, &g_object_handle_movement_value_z, -10.0f, 10.0f, 0.01f, "Axis ~c~(Z)~s~ Looped");
	add_editor_toggle_option(&g_object_handle_movement_p, g_object_handle_movement_value_p, &g_object_handle_movement_value_p, -10.0f, 10.0f, 0.01f, "Pitch Looped");
	add_editor_toggle_option(&g_object_handle_movement_ya, g_object_handle_movement_value_ya, &g_object_handle_movement_value_ya, -10.0f, 10.0f, 0.01f, "Yaw Looped");
	add_editor_toggle_option(&g_object_handle_movement_r, g_object_handle_movement_value_r, &g_object_handle_movement_value_r, -10.0f, 10.0f, 0.01f, "Roll Looped");
	add_break_option("Manual");
	if (add_text_option("Axis ~c~(X+)")) {
		if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(g_object_handle);
			Vector3 l_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_object_handle, 0.0f, 0.0f, 0.0f);
			ENTITY::SET_ENTITY_COORDS(g_object_handle, l_coords.x + 0.1f, l_coords.y, l_coords.z, 1, 0, 0, 1);
			ENTITY::FREEZE_ENTITY_POSITION(g_object_handle, true);
			ENTITY::SET_ENTITY_COLLISION(g_object_handle, true, 0);
		}
	}
	if (add_text_option("Axis ~c~(X-)")) {
		if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(g_object_handle);
			Vector3 l_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_object_handle, 0.0f, 0.0f, 0.0f);
			ENTITY::SET_ENTITY_COORDS(g_object_handle, l_coords.x - 0.1f, l_coords.y, l_coords.z, 1, 0, 0, 1);
			ENTITY::FREEZE_ENTITY_POSITION(g_object_handle, true);
			ENTITY::SET_ENTITY_COLLISION(g_object_handle, true, 0);
		}
	}
	if (add_text_option("Axis ~c~(Y+)")) {
		if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(g_object_handle);
			Vector3 l_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_object_handle, 0.0f, 0.0f, 0.0f);
			ENTITY::SET_ENTITY_COORDS(g_object_handle, l_coords.x, l_coords.y + 0.1f, l_coords.z, 1, 0, 0, 1);
			ENTITY::FREEZE_ENTITY_POSITION(g_object_handle, true);
			ENTITY::SET_ENTITY_COLLISION(g_object_handle, true, 0);
		}
	}
	if (add_text_option("Axis ~c~(Y-)")) {
		if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(g_object_handle);
			Vector3 l_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_object_handle, 0.0f, 0.0f, 0.0f);
			ENTITY::SET_ENTITY_COORDS(g_object_handle, l_coords.x, l_coords.y - 0.1f, l_coords.z, 1, 0, 0, 1);
			ENTITY::FREEZE_ENTITY_POSITION(g_object_handle, true);
			ENTITY::SET_ENTITY_COLLISION(g_object_handle, true, 0);
		}
	}
	if (add_text_option("Axis ~c~(Z+)")) {
		if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(g_object_handle);
			Vector3 l_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_object_handle, 0.0f, 0.0f, 0.0f);
			ENTITY::SET_ENTITY_COORDS(g_object_handle, l_coords.x, l_coords.y, l_coords.z + 0.1f, 1, 0, 0, 1);
			ENTITY::FREEZE_ENTITY_POSITION(g_object_handle, true);
			ENTITY::SET_ENTITY_COLLISION(g_object_handle, true, 0);
		}
	}
	if (add_text_option("Axis ~c~(Z-)")) {
		if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(g_object_handle);
			Vector3 l_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_object_handle, 0.0f, 0.0f, 0.0f);
			ENTITY::SET_ENTITY_COORDS(g_object_handle, l_coords.x, l_coords.y, l_coords.z - 0.1f, 1, 0, 0, 1);
			ENTITY::FREEZE_ENTITY_POSITION(g_object_handle, true);
			ENTITY::SET_ENTITY_COLLISION(g_object_handle, true, 0);
		}
	}
	if (add_text_option("Pitch ~c~(Up)")) {
		if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(g_object_handle);
			Vector3 fRot = ENTITY::GET_ENTITY_ROTATION(g_object_handle, 2);
			std::float_t l_p = fRot.x;
			l_p += 1.5f;
			ENTITY::SET_ENTITY_ROTATION(g_object_handle, l_p, fRot.y, fRot.z, 2, 1);
		}
	}
	if (add_text_option("Pitch ~c~(Down)")) {
		if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(g_object_handle);
			Vector3 fRot = ENTITY::GET_ENTITY_ROTATION(g_object_handle, 2);
			std::float_t l_p = fRot.x;
			l_p -= 1.5f;
			ENTITY::SET_ENTITY_ROTATION(g_object_handle, l_p, fRot.y, fRot.z, 2, 1);
		}
	}
	if (add_text_option("Yaw ~c~(Right)")) {
		if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(g_object_handle);
			Vector3 fRot = ENTITY::GET_ENTITY_ROTATION(g_object_handle, 2);
			std::float_t l_y = fRot.z;
			l_y += 1.5f;
			ENTITY::SET_ENTITY_ROTATION(g_object_handle, fRot.x, fRot.y, l_y, 2, 1);
		}
	}
	if (add_text_option("Yaw ~c~(Left)")) {
		if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(g_object_handle);
			Vector3 fRot = ENTITY::GET_ENTITY_ROTATION(g_object_handle, 2);
			std::float_t l_y = fRot.z;
			l_y -= 1.5f;
			ENTITY::SET_ENTITY_ROTATION(g_object_handle, fRot.x, fRot.y, l_y, 2, 1);
		}
	}
	if (add_text_option("Roll ~c~(Right)")) {
		if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(g_object_handle);
			Vector3 fRot = ENTITY::GET_ENTITY_ROTATION(g_object_handle, 2);
			std::float_t l_r = fRot.y;
			l_r += 1.5f;
			ENTITY::SET_ENTITY_ROTATION(g_object_handle, fRot.x, l_r, fRot.z, 2, 1);
		}
	}
	if (add_text_option("Roll ~c~(Left)")) {
		if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(g_object_handle);
			Vector3 fRot = ENTITY::GET_ENTITY_ROTATION(g_object_handle, 2);
			std::float_t l_r = fRot.y;
			l_r -= 1.5f;
			ENTITY::SET_ENTITY_ROTATION(g_object_handle, fRot.x, l_r, fRot.z, 2, 1);
		}
	}
}
void menu_object_entity_management() {
	add_submenu_option(menu_object_entity_movement, OBFUSCATE("Movement"));
	add_toggle_option(&g_object_creator_mode, OBFUSCATE("Creator Mode"));
	if (add_toggle_option(&g_object_snap_mode, OBFUSCATE("Snap Object")))
		if (g_object_snap_mode)
			g_object_incrment_snap_mode = 0;
	if (g_object_snap_mode) {
		if (add_string_array_option(true, g_object_smap_mode_text, ARRAYSIZE(g_object_smap_mode_text), &g_object_snap, OBFUSCATE("Spawn")))
			g_spawn_object_snap_mode = true;
		add_editor_option(true, g_object_snap_mode_cam_zoom, &g_object_snap_mode_cam_zoom, 0.0f, 40.0f, 0.1f, OBFUSCATE("Cam Distance"));
		add_editor_option(true, g_object_forward_snap_mode, &g_object_forward_snap_mode, -10.0f, 10.0f, 0.1f, OBFUSCATE("Forward Distance"));
		add_editor_option(true, g_object_backward_snap_mode, &g_object_backward_snap_mode, -10.0f, 10.0f, 0.1f, OBFUSCATE("Backward Distance"));
		add_editor_option(true, g_object_right_snap_mode, &g_object_right_snap_mode, -10.0f, 10.0f, 0.1f, OBFUSCATE("Right Distance"));
		add_editor_option(true, g_object_left_snap_mode, &g_object_left_snap_mode, -10.0f, 10.0f, 0.1f, OBFUSCATE("Left Distance"));
	}
	if (add_text_option(OBFUSCATE("Teleport To Object"))) {
		Vector3 l_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_object_handle, 0.0f, 0.0f, 0.0f);
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PLAYER::PLAYER_PED_ID(), l_coords.x, l_coords.y, l_coords.z, 0, 0, 0);
	}
	if (add_text_option(OBFUSCATE("Teleport Into Vehicle"))) {
		if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
			if (ENTITY::GET_ENTITY_TYPE(g_object_handle) == 2) {
				Vector3 l_fCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_object_handle, 0.0f, 0.0f, 0.0f);
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PLAYER::PLAYER_PED_ID(), l_fCoords.x, l_fCoords.y, l_fCoords.z, 0, 0, 0);
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), g_object_handle, -1);
			}
			else
				print_notification(7000, OBFUSCATE("Entity handle is not a vehicle."));
		}
	}
	if (add_toggle_option(&g_object_handle_invisibility, OBFUSCATE("Invisibility")))
		if (!g_object_handle_invisibility)
			if (ENTITY::DOES_ENTITY_EXIST(g_object_handle))
				ENTITY::SET_ENTITY_VISIBLE(g_object_handle, true, 0);
	add_toggle_option(&g_object_handle_forcefield, OBFUSCATE("Forcefield"));

	if (add_toggle_option(&g_object_handle_invisibility, OBFUSCATE("Freeze Position")))
		ENTITY::FREEZE_ENTITY_POSITION(g_object_handle, true);
	if (add_toggle_option(&g_object_handle_invisibility, OBFUSCATE("Unfreeze Position")))
		ENTITY::FREEZE_ENTITY_POSITION(g_object_handle, false);
	if (add_text_option(OBFUSCATE("Delete"))) {
		if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
			switch (ENTITY::GET_ENTITY_TYPE(g_object_handle)) {
			case 1: {
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(g_object_handle, 0, 1);
					PED::DELETE_PED(&g_object_handle);
				} break;
			case 2: {
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(g_object_handle, 0, 1);
					VEHICLE::DELETE_VEHICLE(&g_object_handle);
				} break;
			case 3: {
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(g_object_handle, 0, 1);
					OBJECT::DELETE_OBJECT(&g_object_handle);
				} break;
			}
		}
	}

	if (g_object_snap_mode && CURRENT_OPTION >= 4 && CURRENT_OPTION <= 9) {
		if (!g_object_spawn_snap_mode_cam) {
			if (!CAM::DOES_CAM_EXIST(g_object_snap_mode_cam))
				g_object_snap_mode_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
			else {
				CAM::SET_CAM_ACTIVE(g_object_snap_mode_cam, true);
				CAM::RENDER_SCRIPT_CAMS(1, 1, g_object_snap_mode_cam, 1, 0);
				g_object_spawn_snap_mode_cam = true;
			}
		}
		else {
			if (ENTITY::DOES_ENTITY_EXIST(g_object_spam_snap_mode)) {

				std::int32_t l_object_snap_mode_analog_x = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_LR);
				std::int32_t l_object_snap_mode_analog_y = CONTROLS::GET_CONTROL_VALUE(0, INPUT_LOOK_UD);

				g_object_snap_mode_angle_1 -= (0.001f * (l_object_snap_mode_analog_x - 127));
				g_object_snap_mode_angle_2 += (0.001f * (l_object_snap_mode_analog_y - 127));
				CAM::DETACH_CAM(g_object_snap_mode_cam);
				CAM::ATTACH_CAM_TO_ENTITY(g_object_snap_mode_cam, g_object_spam_snap_mode, g_object_snap_mode_cam_zoom * cos(g_object_snap_mode_angle_1) * cos(g_object_snap_mode_angle_2), g_object_snap_mode_cam_zoom * sin(g_object_snap_mode_angle_1) * cos(g_object_snap_mode_angle_2), g_object_snap_mode_cam_zoom * sin(g_object_snap_mode_angle_2), 0);
				CAM::POINT_CAM_AT_ENTITY(g_object_snap_mode_cam, g_object_spam_snap_mode, 0, 0, 0, 1);
				if (g_object_snap_mode_angle_1 <= -6.25f)
					g_object_snap_mode_angle_1 = 0.00f;
				if (g_object_snap_mode_angle_1 >= 6.25f)
					g_object_snap_mode_angle_1 = 0.00f;
				if (g_object_snap_mode_angle_2 > 1.2f)
					g_object_snap_mode_angle_2 = 1.2f;
				if (g_object_snap_mode_angle_2 < -1.2f)
					g_object_snap_mode_angle_2 = -1.2f;
			}
			if (ENTITY::IS_ENTITY_AN_OBJECT(g_object_handle)) {
				if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
					Vector3 l_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_object_handle, 0.0f, 0.0f, 0.0f);
					INT l_object_snap_mode_model = ENTITY::GET_ENTITY_MODEL(g_object_handle);

					Vector3 l_object_handle_dim_min, l_object_handle_dim_max;
					GAMEPLAY::GET_MODEL_DIMENSIONS(l_object_snap_mode_model, &l_object_handle_dim_min, &l_object_handle_dim_max);
					Vector3 l_rotation = ENTITY::GET_ENTITY_ROTATION(g_object_handle, 2);
					if (g_object_incrment_snap_mode <= 255) {
						switch (g_object_snap) {
						case 0: { /*FORWARD*/
								Vector3 l_relative = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_object_handle, 0.0f, (l_object_handle_dim_max.y * 2), 0.0f);
								if (!g_spawn_object_snap_mode) {
									if (!ENTITY::DOES_ENTITY_EXIST(g_object_spam_snap_mode)) {
										if (!STREAMING::HAS_MODEL_LOADED(l_object_snap_mode_model))
											STREAMING::REQUEST_MODEL(l_object_snap_mode_model);
										else {
											Vector3 l_new_relative;
											l_new_relative.x = l_relative.x;
											l_new_relative.y = l_relative.y + g_object_forward_snap_mode;
											l_new_relative.z = l_relative.z;
											g_object_spam_snap_mode = spawn_snapped_object(l_object_snap_mode_model, l_new_relative, FALSE);
										}
									}
									else {
										ENTITY::SET_ENTITY_COORDS_NO_OFFSET(g_object_spam_snap_mode, l_relative.x, l_relative.y + g_object_forward_snap_mode, l_relative.z, 0, 0, 1);
										ENTITY::SET_ENTITY_ROTATION(g_object_spam_snap_mode, l_rotation.x, l_rotation.y, l_rotation.z, 0, 1);
										ENTITY::FREEZE_ENTITY_POSITION(g_object_spam_snap_mode, true);
										ENTITY::SET_ENTITY_ALPHA(g_object_spam_snap_mode, 150, true);
									}
								}
								else {
									if (!ENTITY::DOES_ENTITY_EXIST(g_object_spam_snap_mode)) {
										if (!STREAMING::HAS_MODEL_LOADED(l_object_snap_mode_model))
											STREAMING::REQUEST_MODEL(l_object_snap_mode_model);
										else {
											Vector3 l_new_relative;
											l_new_relative.x = l_relative.x;
											l_new_relative.y = l_relative.y + g_object_forward_snap_mode;
											l_new_relative.z = l_relative.z;
											g_object_spam_snap_mode = spawn_snapped_object(l_object_snap_mode_model, l_new_relative, FALSE);
										}
									}
									else {
										ENTITY::SET_ENTITY_COORDS_NO_OFFSET(g_object_spam_snap_mode, l_relative.x, l_relative.y + g_object_forward_snap_mode, l_relative.z, 0, 0, 1);
										ENTITY::SET_ENTITY_ROTATION(g_object_spam_snap_mode, l_rotation.x, l_rotation.y, l_rotation.z, 0, 1);
										ENTITY::FREEZE_ENTITY_POSITION(g_object_spam_snap_mode, true);
										ENTITY::SET_ENTITY_ALPHA(g_object_spam_snap_mode, 255, true);
										g_object_handle = g_object_spam_snap_mode;
										g_object_incrment_snap_mode++;
										g_object_spam_snap_mode = 0;
										g_spawn_object_snap_mode = false;
									}
								}
							} break;
						case 1: { /*BACKWARD*/
								Vector3 l_relative = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_object_handle, 0.0f, (l_object_handle_dim_min.y * 2), 0.0f);
								if (!g_spawn_object_snap_mode) {
									if (!ENTITY::DOES_ENTITY_EXIST(g_object_spam_snap_mode)) {
										if (!STREAMING::HAS_MODEL_LOADED(l_object_snap_mode_model))
											STREAMING::REQUEST_MODEL(l_object_snap_mode_model);
										else {
											Vector3 l_new_relative;
											l_new_relative.x = l_relative.x;
											l_new_relative.y = l_relative.y - g_object_backward_snap_mode;
											l_new_relative.z = l_relative.z;
											g_object_spam_snap_mode = spawn_snapped_object(l_object_snap_mode_model, l_new_relative, FALSE);
										}
									}
									else {
										ENTITY::SET_ENTITY_COORDS_NO_OFFSET(g_object_spam_snap_mode, l_relative.x, l_relative.y - g_object_backward_snap_mode, l_relative.z, 0, 0, 1);
										ENTITY::SET_ENTITY_ROTATION(g_object_spam_snap_mode, l_rotation.x, l_rotation.y, l_rotation.z, 0, 1);
										ENTITY::FREEZE_ENTITY_POSITION(g_object_spam_snap_mode, true);
										ENTITY::SET_ENTITY_ALPHA(g_object_spam_snap_mode, 150, true);
									}
								}
								else {
									if (!ENTITY::DOES_ENTITY_EXIST(g_object_spam_snap_mode)) {
										if (!STREAMING::HAS_MODEL_LOADED(l_object_snap_mode_model)) {
											STREAMING::REQUEST_MODEL(l_object_snap_mode_model);
										}
										else {
											Vector3 l_new_relative;
											l_new_relative.x = l_relative.x;
											l_new_relative.y = l_relative.y - g_object_backward_snap_mode;
											l_new_relative.z = l_relative.z;
											g_object_spam_snap_mode = spawn_snapped_object(l_object_snap_mode_model, l_new_relative, FALSE);
										}
									}
									else {
										ENTITY::SET_ENTITY_COORDS_NO_OFFSET(g_object_spam_snap_mode, l_relative.x, l_relative.y - g_object_backward_snap_mode, l_relative.z, 0, 0, 1);
										ENTITY::SET_ENTITY_ROTATION(g_object_spam_snap_mode, l_rotation.x, l_rotation.y, l_rotation.z, 0, 1);
										ENTITY::FREEZE_ENTITY_POSITION(g_object_spam_snap_mode, true);
										ENTITY::SET_ENTITY_ALPHA(g_object_spam_snap_mode, 255, true);
										g_object_handle = g_object_spam_snap_mode;
										g_object_incrment_snap_mode++;
										g_object_spam_snap_mode = 0;
										g_spawn_object_snap_mode = false;
									}
								}
							} break;
						case 2: { /*RIGHT*/
								Vector3 l_relative = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_object_handle, (l_object_handle_dim_max.x * 2), 0.0f, 0.0f);
								if (!g_spawn_object_snap_mode) {
									if (!ENTITY::DOES_ENTITY_EXIST(g_object_spam_snap_mode)) {
										if (!STREAMING::HAS_MODEL_LOADED(l_object_snap_mode_model))
											STREAMING::REQUEST_MODEL(l_object_snap_mode_model);
										else {
											Vector3 l_new_relative;
											l_new_relative.x = l_relative.x + g_object_right_snap_mode;
											l_new_relative.y = l_relative.y;
											l_new_relative.z = l_relative.z;
											g_object_spam_snap_mode = spawn_snapped_object(l_object_snap_mode_model, l_new_relative, FALSE);
										}
									}
									else {
										ENTITY::SET_ENTITY_COORDS_NO_OFFSET(g_object_spam_snap_mode, l_relative.x + g_object_right_snap_mode, l_relative.y, l_relative.z, 0, 0, 1);
										ENTITY::SET_ENTITY_ROTATION(g_object_spam_snap_mode, l_rotation.x, l_rotation.y, l_rotation.z, 0, 1);
										ENTITY::FREEZE_ENTITY_POSITION(g_object_spam_snap_mode, true);
										ENTITY::SET_ENTITY_ALPHA(g_object_spam_snap_mode, 150, true);
									}
								}
								else {
									if (!ENTITY::DOES_ENTITY_EXIST(g_object_spam_snap_mode)) {
										if (!STREAMING::HAS_MODEL_LOADED(l_object_snap_mode_model))
											STREAMING::REQUEST_MODEL(l_object_snap_mode_model);
										else {
											Vector3 l_new_relative;
											l_new_relative.x = l_relative.x + g_object_right_snap_mode;
											l_new_relative.y = l_relative.y;
											l_new_relative.z = l_relative.z;
											g_object_spam_snap_mode = spawn_snapped_object(l_object_snap_mode_model, l_new_relative, FALSE);
										}
									}
									else {
										ENTITY::SET_ENTITY_COORDS_NO_OFFSET(g_object_spam_snap_mode, l_relative.x + g_object_right_snap_mode, l_relative.y, l_relative.z, 0, 0, 1);
										ENTITY::SET_ENTITY_ROTATION(g_object_spam_snap_mode, l_rotation.x, l_rotation.y, l_rotation.z, 0, 1);
										ENTITY::FREEZE_ENTITY_POSITION(g_object_spam_snap_mode, true);
										ENTITY::SET_ENTITY_ALPHA(g_object_spam_snap_mode, 255, true);
										g_object_handle = g_object_spam_snap_mode;
										g_object_incrment_snap_mode++;
										g_object_spam_snap_mode = 0;
										g_spawn_object_snap_mode = false;
									}
								}
							} break;
						case 3: { /*LEFT*/
								Vector3 l_relative = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_object_handle, (l_object_handle_dim_min.x * 2), 0.0f, 0.0f);
								if (!g_spawn_object_snap_mode) {
									if (!ENTITY::DOES_ENTITY_EXIST(g_object_spam_snap_mode)) {
										if (!STREAMING::HAS_MODEL_LOADED(l_object_snap_mode_model))
											STREAMING::REQUEST_MODEL(l_object_snap_mode_model);
										else {
											Vector3 l_new_relative;
											l_new_relative.x = l_relative.x - g_object_left_snap_mode;
											l_new_relative.y = l_relative.y;
											l_new_relative.z = l_relative.z;
											g_object_spam_snap_mode = spawn_snapped_object(l_object_snap_mode_model, l_new_relative, FALSE);
										}
									}
									else {
										ENTITY::SET_ENTITY_COORDS_NO_OFFSET(g_object_spam_snap_mode, l_relative.x - g_object_left_snap_mode, l_relative.y, l_relative.z, 0, 0, 1);
										ENTITY::SET_ENTITY_ROTATION(g_object_spam_snap_mode, l_rotation.x, l_rotation.y, l_rotation.z, 0, 1);
										ENTITY::FREEZE_ENTITY_POSITION(g_object_spam_snap_mode, true);
										ENTITY::SET_ENTITY_ALPHA(g_object_spam_snap_mode, 150, true);
									}
								}
								else {
									if (!ENTITY::DOES_ENTITY_EXIST(g_object_spam_snap_mode)) {
										if (!STREAMING::HAS_MODEL_LOADED(l_object_snap_mode_model))
											STREAMING::REQUEST_MODEL(l_object_snap_mode_model);
										else {
											Vector3 l_new_relative;
											l_new_relative.x = l_relative.x - g_object_left_snap_mode;
											l_new_relative.y = l_relative.y;
											l_new_relative.z = l_relative.z;
											g_object_spam_snap_mode = spawn_snapped_object(l_object_snap_mode_model, l_new_relative, FALSE);
										}
									}
									else {
										ENTITY::SET_ENTITY_COORDS_NO_OFFSET(g_object_spam_snap_mode, l_relative.x - g_object_left_snap_mode, l_relative.y, l_relative.z, 0, 0, 1);
										ENTITY::SET_ENTITY_ROTATION(g_object_spam_snap_mode, l_rotation.x, l_rotation.y, l_rotation.z, 0, 1);
										ENTITY::FREEZE_ENTITY_POSITION(g_object_spam_snap_mode, true);
										ENTITY::SET_ENTITY_ALPHA(g_object_spam_snap_mode, 255, true);
										g_object_handle = g_object_spam_snap_mode;
										g_object_incrment_snap_mode++;
										g_object_spam_snap_mode = 0;
										g_spawn_object_snap_mode = false;
									}
								}
							} break;
						}
					}
				}
				else {
					print_notification(7000, "Object handle does not exist.");
					g_object_snap_mode = false;
				}
			}
		}
	}
	else {
		if (ENTITY::DOES_ENTITY_EXIST(g_object_spam_snap_mode)) {
			ENTITY::SET_ENTITY_COORDS(g_object_spam_snap_mode, 6000.0, 6000.0, 6000.0, true, false, false, true);
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(g_object_spam_snap_mode, 0, 1);
			OBJECT::DELETE_OBJECT(&g_object_spam_snap_mode);
		}
		if (g_object_spawn_snap_mode_cam) {
			CAM::SET_CAM_ACTIVE(g_object_snap_mode_cam, false);
			CAM::RENDER_SCRIPT_CAMS(0, 1, g_object_snap_mode_cam, 1, 0);
			CAM::DESTROY_CAM(g_object_snap_mode_cam, true);
			g_object_spawn_snap_mode_cam = false;
		}
	}
}
void menu_object_load_map_creation() {

}
void menu_object() {
	add_submenu_option(menu_object_entity_management, OBFUSCATE("Manage Spawned Object"));
	/*add_submenu_option(menu_object_load_map_creation, OBFUSCATE("Load Map Creation"));
	if (add_keyboard_option(true, &g_loaded_list_file_objects_filter, 32, OBFUSCATE("Save Map Creation"))) {

	}*/
	add_keyboard_option(true, &g_loaded_list_file_objects_filter, 32, OBFUSCATE("Search For Model"));
	if (g_loaded_list_file_objects_did_load) {
		for (auto model : g_loaded_list_file_objects) {
			if (!g_loaded_list_file_objects_filter.empty()) {
				if (model.find(g_loaded_list_file_objects_filter) != std::string::npos) {
					if (add_text_option(model)) {

						//spawn obj
						Vector3 l_object_dim_min, g_object_dim_max;
						GAMEPLAY::GET_MODEL_DIMENSIONS(GAMEPLAY::GET_HASH_KEY(model.c_str()), &l_object_dim_min, &g_object_dim_max);

						Vector3 l_offset;
						if (ENTITY::DOES_ENTITY_EXIST(g_object_handle))
							l_offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_object_handle, 0.0f, ((g_object_dim_max.y * 2) + 3.0f), 0.0f);
						else if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
							l_offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0.0f, ((g_object_dim_max.y * 2) + 3.0f), 0.0f);
						else
							l_offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, ((g_object_dim_max.y * 2) + 3.0f), 0.0f);
						g_object_handle = spawn_object(model.c_str(), l_offset, FALSE);
						ENTITY::SET_ENTITY_ALPHA(g_object_handle, 150, true);

						// create cam
						if (!CAM::DOES_CAM_EXIST(g_object_cam)) {
							create_cam_label_filtered:
							g_object_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
							if (CAM::DOES_CAM_EXIST(g_object_cam)) {
								Vector3 player_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, 0.0f, 0.0f);
								CAM::SET_CAM_COORD(g_object_cam, player_coords.x, player_coords.y + 1.0f, player_coords.z + 2.0f);
								CAM::SET_CAM_ACTIVE(g_object_cam, true);
								CAM::RENDER_SCRIPT_CAMS(1, 1, 1000, 1, 0);
							} else goto create_cam_label_filtered;
						}

						//Script::GetCurrent()->ScriptYield();

						g_do_object_spawn_preview = true;
						while (g_do_object_spawn_preview) {

							// disable controls
							if (UI::IS_PAUSE_MENU_ACTIVE())
								break;

							UI::HIDE_HUD_AND_RADAR_THIS_FRAME();

							CONTROLS::DISABLE_ALL_CONTROL_ACTIONS(0);
							CONTROLS::DISABLE_ALL_CONTROL_ACTIONS(2);
							CONTROLS::ENABLE_CONTROL_ACTION(2, INPUT_FRONTEND_PAUSE, true);
							CONTROLS::ENABLE_CONTROL_ACTION(2, INPUT_FRONTEND_PAUSE_ALTERNATE, true);

							ENTITY::SET_ENTITY_COLLISION(g_object_handle, false, false);

							// do movement
							Vector3 cam_offset;
							cam_offset.x = CONTROLS::GET_DISABLED_CONTROL_NORMAL(0, INPUT_MOVE_LR) * 2.0f;
							cam_offset.y = -CONTROLS::GET_DISABLED_CONTROL_NORMAL(0, INPUT_MOVE_UD) * 2.0f;

							Vector3 cam_rot_offset;
							cam_rot_offset.x = -CONTROLS::GET_DISABLED_CONTROL_NORMAL(0, INPUT_LOOK_UD) * 4.0f;
							cam_rot_offset.z = -CONTROLS::GET_DISABLED_CONTROL_NORMAL(0, INPUT_LOOK_LR) * 4.0f;

							Vector3 new_cam_offset = get_offset_from_camera(g_object_cam, cam_offset);
							CAM::SET_CAM_COORD(g_object_cam, new_cam_offset.x, new_cam_offset.y, new_cam_offset.z);

							Vector3 new_rot_offset = CAM::GET_CAM_ROT(g_object_cam, 2);
							new_rot_offset.x += cam_rot_offset.x;
							new_rot_offset.y += cam_rot_offset.y;
							new_rot_offset.z += cam_rot_offset.z;
							CAM::SET_CAM_ROT(g_object_cam, new_rot_offset.x, 0.0f, new_rot_offset.z, 2);

							Vector3 obj_coords = get_coords_in_front_of_cam(g_object_cam, ((g_object_dim_max.y * 2.0f) + 3.0f));
							ENTITY::SET_ENTITY_COORDS(g_object_handle, obj_coords.x, obj_coords.y, obj_coords.z, true, false, false, true);

							if (CONTROLS::_IS_INPUT_DISABLED(2) ? CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_ATTACK) : CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_ACCEPT)) {
								g_was_object_spawn_preview_finished = true;
								g_was_object_spawn_preview_exited = false;
								g_do_object_spawn_preview = false;
							}
							if (CONTROLS::_IS_INPUT_DISABLED(2) ? CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_AIM) : CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_CANCEL)) {
								g_was_object_spawn_preview_finished = false;
								g_was_object_spawn_preview_exited = true;
								g_do_object_spawn_preview = false;
							}
							//Script::GetCurrent()->ScriptYield();
						}

						if (g_was_object_spawn_preview_finished) {
							ENTITY::SET_ENTITY_COLLISION(g_object_handle, true, false);
							ENTITY::SET_ENTITY_ALPHA(g_object_handle, 255, true);
						}

						if (g_was_object_spawn_preview_exited) {
							ENTITY::SET_ENTITY_COORDS(g_object_handle, 6000.0, 6000.0, 6000.0, true, false, false, true);
							ENTITY::SET_ENTITY_AS_MISSION_ENTITY(g_object_handle, 0, 1);
							OBJECT::DELETE_OBJECT(&g_object_handle);
						}

						if (CAM::DOES_CAM_EXIST(g_object_cam)) {
							CAM::SET_CAM_ACTIVE(g_object_cam, false);
							CAM::RENDER_SCRIPT_CAMS(0, 1, g_object_cam, 1, 0);
							CAM::DESTROY_CAM(g_object_cam, true);
						}
					}
				}
			}
			else if (add_text_option(model)) {

				//spawn obj
				Vector3 l_object_dim_min, g_object_dim_max;
				GAMEPLAY::GET_MODEL_DIMENSIONS(GAMEPLAY::GET_HASH_KEY(model.c_str()), &l_object_dim_min, &g_object_dim_max);

				Vector3 l_offset;
				if (ENTITY::DOES_ENTITY_EXIST(g_object_handle))
					l_offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_object_handle, 0.0f, ((g_object_dim_max.y * 2) + 3.0f), 0.0f);
				else if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
					l_offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0.0f, ((g_object_dim_max.y * 2) + 3.0f), 0.0f);
				else
					l_offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, ((g_object_dim_max.y * 2) + 3.0f), 0.0f);
				g_object_handle = spawn_object(model.c_str(), l_offset, FALSE);
				ENTITY::SET_ENTITY_ALPHA(g_object_handle, 150, true);

				// create cam
				if (!CAM::DOES_CAM_EXIST(g_object_cam)) {
					create_cam_label:
					g_object_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
					if (CAM::DOES_CAM_EXIST(g_object_cam)) {
						Vector3 player_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, 0.0f, 0.0f);
						CAM::SET_CAM_COORD(g_object_cam, player_coords.x, player_coords.y + 1.0f, player_coords.z + 2.0f);
						CAM::SET_CAM_ACTIVE(g_object_cam, true);
						CAM::RENDER_SCRIPT_CAMS(1, 1, 1000, 1, 0);
					}
					else goto create_cam_label;
				}

				//Script::GetCurrent()->ScriptYield();

				g_do_object_spawn_preview = true;
				while (g_do_object_spawn_preview) {

					// disable controls
					if (UI::IS_PAUSE_MENU_ACTIVE())
						break;

					UI::HIDE_HUD_AND_RADAR_THIS_FRAME();

					CONTROLS::DISABLE_ALL_CONTROL_ACTIONS(0);
					CONTROLS::DISABLE_ALL_CONTROL_ACTIONS(2);
					CONTROLS::ENABLE_CONTROL_ACTION(2, INPUT_FRONTEND_PAUSE, true);
					CONTROLS::ENABLE_CONTROL_ACTION(2, INPUT_FRONTEND_PAUSE_ALTERNATE, true);

					ENTITY::SET_ENTITY_COLLISION(g_object_handle, false, false);

					// do movement
					Vector3 cam_offset;
					cam_offset.x = CONTROLS::GET_DISABLED_CONTROL_NORMAL(0, INPUT_MOVE_LR) * 2.0f;
					cam_offset.y = -CONTROLS::GET_DISABLED_CONTROL_NORMAL(0, INPUT_MOVE_UD) * 2.0f;

					Vector3 cam_rot_offset;
					cam_rot_offset.x = -CONTROLS::GET_DISABLED_CONTROL_NORMAL(0, INPUT_LOOK_UD) * 4.0f;
					cam_rot_offset.z = -CONTROLS::GET_DISABLED_CONTROL_NORMAL(0, INPUT_LOOK_LR) * 4.0f;

					Vector3 new_cam_offset = get_offset_from_camera(g_object_cam, cam_offset);
					CAM::SET_CAM_COORD(g_object_cam, new_cam_offset.x, new_cam_offset.y, new_cam_offset.z);

					Vector3 new_rot_offset = CAM::GET_CAM_ROT(g_object_cam, 2);
					new_rot_offset.x += cam_rot_offset.x;
					new_rot_offset.y += cam_rot_offset.y;
					new_rot_offset.z += cam_rot_offset.z;
					CAM::SET_CAM_ROT(g_object_cam, new_rot_offset.x, 0.0f, new_rot_offset.z, 2);

					Vector3 obj_coords = get_coords_in_front_of_cam(g_object_cam, ((g_object_dim_max.y * 2.0f) + 3.0f));
					ENTITY::SET_ENTITY_COORDS(g_object_handle, obj_coords.x, obj_coords.y, obj_coords.z, true, false, false, true);

					if (CONTROLS::_IS_INPUT_DISABLED(2) ? CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_ATTACK) : CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_ACCEPT)) {
						g_was_object_spawn_preview_finished = true;
						g_was_object_spawn_preview_exited = false;
						g_do_object_spawn_preview = false;
					}
					if (CONTROLS::_IS_INPUT_DISABLED(2) ? CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_AIM) : CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_CANCEL)) {
						g_was_object_spawn_preview_finished = false;
						g_was_object_spawn_preview_exited = true;
						g_do_object_spawn_preview = false;
					}
					//Script::GetCurrent()->ScriptYield();
				}

				if (g_was_object_spawn_preview_finished) {
					ENTITY::SET_ENTITY_COLLISION(g_object_handle, true, false);
					ENTITY::SET_ENTITY_ALPHA(g_object_handle, 255, true);
				}

				if (g_was_object_spawn_preview_exited) {
					ENTITY::SET_ENTITY_COORDS(g_object_handle, 6000.0, 6000.0, 6000.0, true, false, false, true);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(g_object_handle, 0, 1);
					OBJECT::DELETE_OBJECT(&g_object_handle);
				}

				if (CAM::DOES_CAM_EXIST(g_object_cam)) {
					CAM::SET_CAM_ACTIVE(g_object_cam, false);
					CAM::RENDER_SCRIPT_CAMS(0, 1, g_object_cam, 1, 0);
					CAM::DESTROY_CAM(g_object_cam, true);
				}
			}
		}
	}
	else { add_text_option(OBFUSCATE("\"obj_models.txt\" failed to load")); }

	std::int32_t aimed_entity = NULL;
	if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &aimed_entity)) {
		if (ENTITY::DOES_ENTITY_EXIST(aimed_entity)) {
			std::uint64_t model_info = get_model_info_ptr(ENTITY::GET_ENTITY_MODEL(aimed_entity));
			if (model_info) {
				add_info_box_title("Aimed Entity");
				add_data_to_info_box("Model Info", (void*)model_info);
				add_data_to_info_box("Model Type", (*(std::uint8_t*)(model_info + 157) & 0x1F));
				draw_rect((g_menu_banner_pos_x >= 0.5f) ? (g_menu_banner_pos_x - (g_menu_banner_size_x / 2) - (g_info_box_title_width / 2)) : (g_menu_banner_pos_x + (g_menu_banner_size_x / 2) + (g_info_box_title_width / 2)), ((g_menu_banner_pos_y - ((g_menu_banner_size_y / 2)) + (g_info_box_title_length / 2)) + (g_info_box_title_length / 2)) + ((g_info_box_count * (g_info_box_title_length / 2)) / 2) + 0.0035f, g_info_box_title_width, (g_info_box_count * (g_info_box_title_length / 2)) + 0.007f, g_menu_background_colour);
				g_info_box_count = NULL;

			}
		}
	}

	if (g_object_snap_mode) {
		if (ENTITY::DOES_ENTITY_EXIST(g_object_spam_snap_mode)) {
			ENTITY::SET_ENTITY_COORDS(g_object_spam_snap_mode, 6000.0, 6000.0, 6000.0, true, false, false, true);
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(g_object_spam_snap_mode, 0, 1);
			OBJECT::DELETE_OBJECT(&g_object_spam_snap_mode);
		}
		if (g_object_spawn_snap_mode_cam) {
			CAM::SET_CAM_ACTIVE(g_object_snap_mode_cam, false);
			CAM::RENDER_SCRIPT_CAMS(0, 1, g_object_snap_mode_cam, 1, 0);
			CAM::DESTROY_CAM(g_object_snap_mode_cam, true);
			g_object_spawn_snap_mode_cam = false;
		}
	}
}

void menu_teleport_ipl_locations_online_bunkers() {
	if (add_text_option("Zancudo Bunker")) {
		STREAMING::REQUEST_IPL("gr_case10_bunkerclosed");
		teleport_to_position(-3058.714f, 3329.19f, 12.5844f);
	}
	if (add_text_option("Route 68 Bunker")) {
		STREAMING::REQUEST_IPL("gr_case9_bunkerclosed");
		teleport_to_position(24.43542f, 2959.705f, 58.35517f);
	}
	if (add_text_option("Oilfields Bunker")) {
		STREAMING::REQUEST_IPL("gr_case3_bunkerclosed");
		teleport_to_position(481.0465f, 2995.135f, 43.96672f);
	}
	if (add_text_option("Desert Bunker")) {
		STREAMING::REQUEST_IPL("gr_case0_bunkerclosed");
		teleport_to_position(848.6175f, 2996.567f, 45.81612f);
	}
	if (add_text_option("Smoke Tree Bunker")) {
		STREAMING::REQUEST_IPL("gr_case1_bunkerclosed");
		teleport_to_position(2126.785f, 3335.04f, 48.21422f);
	}
	if (add_text_option("Scrapyard Bunker")) {
		STREAMING::REQUEST_IPL("gr_case2_bunkerclosed");
		teleport_to_position(2493.654f, 3140.399f, 51.28789f);
	}
	if (add_text_option("Grapeseed Bunker")) {
		STREAMING::REQUEST_IPL("gr_case5_bunkerclosed");
		teleport_to_position(1823.961f, 4708.14f, 42.4991f);
	}
	if (add_text_option("Palleto Bunker")) {
		STREAMING::REQUEST_IPL("gr_case7_bunkerclosed");
		teleport_to_position(-783.0755f, 5934.686f, 24.31475f);
	}
	if (add_text_option("Route 1 Bunker")) {
		STREAMING::REQUEST_IPL("gr_case11_bunkerclosed");
		teleport_to_position(-3180.466f, 1374.192f, 19.9597f);
	}
	if (add_text_option("Farmhouse Bunker")) {
		STREAMING::REQUEST_IPL("gr_case6_bunkerclosed");
		teleport_to_position(1570.372f, 2254.549f, 78.89397f);
	}
	if (add_text_option("Raton Canyon Bunker")) {
		STREAMING::REQUEST_IPL("gr_case4_bunkerclosed");
		teleport_to_position(-391.3216f, 4363.728f, 58.65862f);
	}
}
void menu_teleport_ipl_locations_online_apartments() {

}
void menu_teleport_ipl_locations_arcadius_business_centre() {

}
void menu_teleport_ipl_locations_maze_bank_building() {

}
void menu_teleport_ipl_locations_lom_bank() {

}
void menu_teleport_ipl_locations_maze_bank_west() {

}
void menu_teleport_ipl_locations_clubhouse_warehouse() {
	if (add_text_option("Clubhouse 1")) {
		STREAMING::REQUEST_IPL("vw_cbkr_biker_interior_placement_interior_0_biker_dlc_int_01_miloasino_main");
		teleport_to_position(1107.04f, -3157.399f, -37.51859f);
	}
	if (add_text_option("Clubhouse 2")) {
		STREAMING::REQUEST_IPL("bkr_biker_interior_placement_interior_1_biker_dlc_int_02_milo");
		teleport_to_position(998.4809f, -3164.711f, -38.90733f);
	}
	if (add_text_option("Meth Lab")) {
		STREAMING::REQUEST_IPL("bkr_biker_interior_placement_interior_2_biker_dlc_int_ware01_milo");
		teleport_to_position(1009.5f, -3196.6f, -38.99682f);
	}
	if (add_text_option("Weed Farm")) {
		STREAMING::REQUEST_IPL("bkr_biker_interior_placement_interior_3_biker_dlc_int_ware02_milo");
		teleport_to_position(1051.491f, -3196.536f, -39.14842f);
	}
	if (add_text_option("Cocaine Lockup")) {
		STREAMING::REQUEST_IPL("bkr_biker_interior_placement_interior_4_biker_dlc_int_ware03_milo");
		teleport_to_position(1093.6f, -3196.6f, -38.99841f);
	}
	if (add_text_option("Counterfeit Cash Factory")) {
		STREAMING::REQUEST_IPL("bkr_biker_interior_placement_interior_5_biker_dlc_int_ware04_milo");
		teleport_to_position(1121.897f, -3195.338f, -40.4025f);
	}
	if (add_text_option("Document Forgery Office")) {
		STREAMING::REQUEST_IPL("bkr_biker_interior_placement_interior_6_biker_dlc_int_ware05_milo");
		teleport_to_position(1165.0f, -3196.6f, -39.01306f);
	}
	if (add_text_option("Warehouse Small")) {
		STREAMING::REQUEST_IPL("ex_exec_warehouse_placement_interior_1_int_warehouse_s_dlc_milo");
		teleport_to_position(1094.988f, -3101.776f, -39.00363f);
	}
	if (add_text_option("Warehouse Medium")) {
		STREAMING::REQUEST_IPL("ex_exec_warehouse_placement_interior_0_int_warehouse_m_dlc_milo");
		teleport_to_position(1056.486f, -3105.724f, -39.00439f);
	}
	if (add_text_option("Warehouse Large")) {
		STREAMING::REQUEST_IPL("ex_exec_warehouse_placement_interior_2_int_warehouse_l_dlc_milo");
		teleport_to_position(1006.967f, -3102.079f, -39.0035f);
	}
	if (add_text_option("Vehicle Warehouse")) {
		STREAMING::REQUEST_IPL("imp_impexp_interior_placement_interior_1_impexp_intwaremed_milo_");
		teleport_to_position(994.5925f, -3002.594f, -39.64699f);
	}
	if (add_text_option("Lost MC Clubhouse")) {
		STREAMING::REQUEST_IPL("bkr_bi_hw1_13_int");
		teleport_to_position(982.0083f, -100.8747f, 74.84512f);
	}
}
void menu_teleport_ipl_locations_special_locations() {
	if (add_text_option("Normal Cargo Ship")) {
		STREAMING::REQUEST_IPL("cargoship");
		teleport_to_position(-163.3628f, -2385.161f, 5.999994f);
	}
	if (add_text_option("Sunken Cargo Ship")) {
		STREAMING::REQUEST_IPL("sunkcargoship");
		teleport_to_position(-163.3628f, -2385.161f, 5.999994f);
	}
	if (add_text_option("Burning Cargo Ship")) {
		STREAMING::REQUEST_IPL("SUNK_SHIP_FIRE");
		teleport_to_position(-163.3628f, -2385.161f, 5.999994f);
	}
	if (add_text_option("Red Carpet	")) {
		STREAMING::REQUEST_IPL("redCarpet");
		teleport_to_position(300.5927f, 300.5927f, 104.3776f);
	}
	if (add_text_option("Rekt Stilthouse Destroyed")) {
		STREAMING::REQUEST_IPL("DES_StiltHouse_imapend");
		teleport_to_position(-1020.518f, 663.27f, 153.5167f);
	}
	if (add_text_option("Rekt Stilthouse Rebuild")) {
		STREAMING::REQUEST_IPL("DES_stilthouse_rebuild");
		teleport_to_position(-1020.518f, 663.27f, 153.5167f);
	}
	if (add_text_option("Union Depository")) {
		STREAMING::REQUEST_IPL("FINBANK");
		teleport_to_position(2.6968f, -667.0166f, 16.13061f);
	}
	if (add_text_option("Trevors Trailer Dirty")) {
		STREAMING::REQUEST_IPL("TrevorsMP");
		teleport_to_position(1975.552f, 3820.538f, 33.44833f);
	}
	if (add_text_option("Trevors Trailer Clean")) {
		STREAMING::REQUEST_IPL("TrevorsTrailerTidy");
		teleport_to_position(1975.552f, 3820.538f, 33.44833f);
	}
	if (add_text_option("Stadium")) {
		STREAMING::REQUEST_IPL("SP1_10_real_interior");
		teleport_to_position(-248.6731f, -2010.603f, 30.14562f);
	}
	if (add_text_option("Max Renda Shop")) {
		STREAMING::REQUEST_IPL("refit_unload");
		teleport_to_position(-585.8247f, -282.72f, 35.45475f);
	}
	if (add_text_option("Jewel Store")) {
		STREAMING::REQUEST_IPL("post_hiest_unload");
		teleport_to_position(-630.07f, -236.332f, 38.05704f);
	}
	if (add_text_option("FIB Lobby")) {
		STREAMING::REQUEST_IPL("FIBlobby");
		teleport_to_position(110.4f, -744.2f, 45.7496f);
	}
	if (add_text_option("Gunrunning Heist Yacht")) {
		STREAMING::REQUEST_IPL("gr_heist_yacht2");
		STREAMING::REQUEST_IPL("gr_heist_yacht2_bar");
		STREAMING::REQUEST_IPL("gr_heist_yacht2_bedrm");
		STREAMING::REQUEST_IPL("gr_heist_yacht2_bridge");
		STREAMING::REQUEST_IPL("gr_heist_yacht2_enginrm");
		STREAMING::REQUEST_IPL("gr_heist_yacht2_lounge");
		teleport_to_position(1373.828f, 6737.393f, 6.707596f);
	}
	if (add_text_option("Dignity Heist Yacht")) {
		STREAMING::REQUEST_IPL("hei_yacht_heist");
		STREAMING::REQUEST_IPL("hei_yacht_heist_enginrm");
		STREAMING::REQUEST_IPL("hei_yacht_heist_Lounge");
		STREAMING::REQUEST_IPL("hei_yacht_heist_Bridge");
		STREAMING::REQUEST_IPL("hei_yacht_heist_Bar");
		STREAMING::REQUEST_IPL("hei_yacht_heist_Bedrm");
		STREAMING::REQUEST_IPL("hei_yacht_heist_DistantLights");
		STREAMING::REQUEST_IPL("hei_yacht_heist_LODLights");
		teleport_to_position(-2027.946f, -1036.695f, 6.707587f);
	}
	if (add_text_option("Dignity Party Yacht")) {
		STREAMING::REQUEST_IPL("smboat");
		STREAMING::REQUEST_IPL("smboat_lod");
		teleport_to_position(-2023.643f, -1038.119f, 5.576781f);
	}
	if (add_text_option("Aircraft Carrier")) {
		STREAMING::REQUEST_IPL("hei_carrier");
		STREAMING::REQUEST_IPL("hei_carrier_DistantLights");
		STREAMING::REQUEST_IPL("hei_Carrier_int1");
		STREAMING::REQUEST_IPL("hei_Carrier_int2");
		STREAMING::REQUEST_IPL("hei_Carrier_int3");
		STREAMING::REQUEST_IPL("hei_Carrier_int4");
		STREAMING::REQUEST_IPL("hei_Carrier_int5");
		STREAMING::REQUEST_IPL("hei_Carrier_int6");
		STREAMING::REQUEST_IPL("hei_carrier_LODLights");
		teleport_to_position(3084.73f, -4770.709f, 15.26167f);
	}
	if (add_text_option("Bridge Train Crash")) {
		STREAMING::REQUEST_IPL("canyonriver01_traincrash");
		STREAMING::REQUEST_IPL("railing_end");
		teleport_to_position(532.1309f, 4526.187f, 89.79387f);
	}
	if (add_text_option("Bridge Train Normal")) {
		STREAMING::REQUEST_IPL("canyonriver01");
		STREAMING::REQUEST_IPL("railing_start");
		teleport_to_position(532.1309f, 4526.187f, 89.79387f);
	}
	if (add_text_option("North Yankton")) {
		STREAMING::REQUEST_IPL("prologue01");
		STREAMING::REQUEST_IPL("prologue01c");
		STREAMING::REQUEST_IPL("prologue01d");
		STREAMING::REQUEST_IPL("prologue01e");
		STREAMING::REQUEST_IPL("prologue01f");
		STREAMING::REQUEST_IPL("prologue01g");
		STREAMING::REQUEST_IPL("prologue01h");
		STREAMING::REQUEST_IPL("prologue01i");
		STREAMING::REQUEST_IPL("prologue01j");
		STREAMING::REQUEST_IPL("prologue01k");
		STREAMING::REQUEST_IPL("prologue01z");
		STREAMING::REQUEST_IPL("prologue02");
		STREAMING::REQUEST_IPL("prologue03");
		STREAMING::REQUEST_IPL("prologue03b");
		STREAMING::REQUEST_IPL("prologue03_grv_dug");
		STREAMING::REQUEST_IPL("prologue_grv_torch");
		STREAMING::REQUEST_IPL("prologue04");
		STREAMING::REQUEST_IPL("prologue04b");
		STREAMING::REQUEST_IPL("prologue04_cover");
		STREAMING::REQUEST_IPL("des_protree_end");
		STREAMING::REQUEST_IPL("des_protree_start");
		STREAMING::REQUEST_IPL("prologue05");
		STREAMING::REQUEST_IPL("prologue05b");
		STREAMING::REQUEST_IPL("prologue06");
		STREAMING::REQUEST_IPL("prologue06b");
		STREAMING::REQUEST_IPL("prologue06_int");
		STREAMING::REQUEST_IPL("prologue06_pannel");
		STREAMING::REQUEST_IPL("plg_occl_00");
		STREAMING::REQUEST_IPL("prologue_occl");
		STREAMING::REQUEST_IPL("prologuerd");
		STREAMING::REQUEST_IPL("prologuerdb");
		teleport_to_position(3217.697f, -4834.826f, 111.8152f);
	}
	if (add_text_option("ONeils Farm Burnt")) {
		STREAMING::REQUEST_IPL("farmint");
		STREAMING::REQUEST_IPL("farm_burnt");
		STREAMING::REQUEST_IPL("farm_burnt_props");
		STREAMING::REQUEST_IPL("des_farmhs_endimap");
		STREAMING::REQUEST_IPL("des_farmhs_end_occl");
		teleport_to_position(2469.03f, 4955.278f, 45.11892f);
	}
	if (add_text_option("ONeils Farm")) {
		STREAMING::REQUEST_IPL("farm");
		STREAMING::REQUEST_IPL("farm_props");
		STREAMING::REQUEST_IPL("farm_int");
		teleport_to_position(2469.03f, 4955.278f, 45.11892f);
	}
	if (add_text_option("Morgue")) {
		STREAMING::REQUEST_IPL("coronertrash");
		STREAMING::REQUEST_IPL("Coroner_Int_On");
		teleport_to_position(275.446f, -1361.11f, 24.5378f);
	}
}
void menu_teleport_ipl_locations_diamond_casino_resort() {
	if (add_text_option("Casino")) {
		STREAMING::REQUEST_IPL("vw_casino_main");
		teleport_to_position(1100.000f, 220.000f, -50.000);
	}
	if (add_text_option("Garage")) {
		STREAMING::REQUEST_IPL("vw_casino_garage");
		teleport_to_position(1295.000, 230.000, -50.000);
	}
	if (add_text_option("Car Park")) {
		STREAMING::REQUEST_IPL("vw_casino_carpark");
		teleport_to_position(1380.000, 200.000, -50.000);
	}
	if (add_text_option("Penthouse")) {
		STREAMING::REQUEST_IPL("vw_casino_penthouse");
		teleport_to_position(976.636f, 70.295f, 115.164f);
	}
}
void menu_teleport_ipl_locations() {
	add_submenu_option(menu_teleport_ipl_locations_online_bunkers, "Online Bunkers");
	add_submenu_option(menu_teleport_ipl_locations_online_apartments, "Online Apartments");
	add_submenu_option(menu_teleport_ipl_locations_arcadius_business_centre, "Arcadius Business Centre");
	add_submenu_option(menu_teleport_ipl_locations_maze_bank_building, "Maze Bank Building");
	add_submenu_option(menu_teleport_ipl_locations_lom_bank, "Lom Bank");
	add_submenu_option(menu_teleport_ipl_locations_maze_bank_west, "Maze Bank West");
	add_submenu_option(menu_teleport_ipl_locations_clubhouse_warehouse, "Clubhouse & Warehouses");
	add_submenu_option(menu_teleport_ipl_locations_special_locations, "Special Locations");
	add_submenu_option(menu_teleport_ipl_locations_diamond_casino_resort, "Diamond Casino & Resort");
}
void menu_teleport() {
	if (add_text_option("Waypoint")) {
		if (UI::DOES_BLIP_EXIST(UI::GET_FIRST_BLIP_INFO_ID(8))) {
			Vector3 coords = UI::GET_BLIP_COORDS(UI::GET_FIRST_BLIP_INFO_ID(8));
			teleport_to_position(coords.x, coords.y, coords.z);
		}
		else
			print_notification(7000, "~r~Error:~s~ No waypoint set.");
	}
	add_submenu_option(menu_teleport_ipl_locations, "IPL Locations");
	add_break_option("Popular");
	if (add_text_option("Airport Top")) { teleport_to_position(-1030.025146f, -3015.658691f, 49.091133f); }
	if (add_text_option("Airport Bottom")) { teleport_to_position(-1500.652588f, -2858.271729f, 13.954378f); }
	if (add_text_option("Mount Chilliad")) { teleport_to_position(500.385651f, 5588.618652f, 794.612122f); }
	if (add_text_option("Ponsonbys (Clothing)")) { teleport_to_position(-159.2996f, -304.3292f, 39.7333f); }
	if (add_text_option("Suburban (Clothing)")) { teleport_to_position(129.735962f, -202.199875f, 54.511318f); }
	if (add_text_option("Maze Tower")) { teleport_to_position(-73.92588f, -818.455078f, 326.174377f); }
	if (add_text_option("The Prison")) { teleport_to_position(495.088409f, 5604.172363f, 794.877686f); }
	if (add_text_option("Eclipse Towers")) { teleport_to_position(-810.110901f, 300.467865f, 86.118515f); }
	if (add_text_option("Eclipse Towers Roof")) { teleport_to_position(-776.372864f, 332.285461f, 239.666777f); }
	if (add_text_option("Tinsel Towers")) { teleport_to_position(-641.864624f, 24.014740f, 39.351025f); }
	if (add_text_option("Alta St. Apt. Entrance")) { teleport_to_position(-266.0524f, -968.6304f, 31.2243f); }
	if (add_text_option("10 Car Garage")) { teleport_to_position(228.7188f, -989.9847f, -99.0f); }
	if (add_text_option("Airport Top")) { teleport_to_position(-1030.025146f, -3015.658691f, 49.091133f); }
	if (add_text_option("Airport Bottom")) { teleport_to_position(-1500.652588f, -2858.271729f, 13.954378f); }
	if (add_text_option("Airport Office")) { teleport_to_position(-1559.734741f, -3237.086182f, 29.634100f); }
	if (add_text_option("Trevor Airfield")) { teleport_to_position(1704.752686f, 3275.902832f, 41.157715f); }
	if (add_text_option("Grapeseed Air Field")) { teleport_to_position(2124.0330f, 4800.5860f, 41.0031f); }
	if (add_text_option("Ammunation (Morningwood)")) { teleport_to_position(-1330.267822f, -390.644684f, 36.602779f); }
	if (add_text_option("Ammunation (Desert)")) { teleport_to_position(1696.1050f, 3755.1670f, 34.7053f); }
	if (add_text_option("Ammunation (City)")) { teleport_to_position(232.832550f, -40.852272f, 69.705482f); }
	if (add_text_option("Ponsonbys (Clothing)")) { teleport_to_position(-159.2996f, -304.3292f, 39.7333f); }
	if (add_text_option("Suburban (Clothing)")) { teleport_to_position(129.735962f, -202.199875f, 54.511318f); }
	if (add_text_option("Car Wash")) { teleport_to_position(53.9397f, -1390.7710f, 29.3734f); }
	if (add_text_option("Los Santos Customs (Burton)")) { teleport_to_position(-384.217834f, -118.733658f, 38.689579f); }
	if (add_text_option("Deposit Car Insurance")) { teleport_to_position(-233.7411f, -1150.3910f, 22.5367f); }
	if (add_text_option("Hair On Hawick (Barbers)")) { teleport_to_position(-29.816093f, -140.543686f, 57.035568f); }
	if (add_text_option("The Pit (Tattoo)")) { teleport_to_position(-1156.064209f, -1422.023560f, 4.778219f); }
	if (add_text_option("Franklin's House")) { teleport_to_position(8.069606f, 537.153015f, 176.028015f); }
	if (add_text_option("Micheal's House")) { teleport_to_position(-813.176453f, 179.232452f, 72.159149f); }
	if (add_text_option("Trevor's House")) { teleport_to_position(1974.7580f, 3819.4570f, 33.4363f); }
	if (add_text_option("Lester's House")) { teleport_to_position(1248.1830f, -1728.1040f, 56.0000f); }
	if (add_text_option("Floyd's House")) { teleport_to_position(-1159.0340f, -1521.1800f, 10.6327f); }
	if (add_text_option("Franklin's Aunt's House")) { teleport_to_position(-14.9693f, -1436.4430f, 31.1185f); }
	if (add_text_option("Devin Weston's House")) { teleport_to_position(-2639.872f, 1866.812f, 160.135f); }
	if (add_text_option("Secret Army Tower")) { teleport_to_position(-2358.946045f, 3252.216797f, 101.450424f); }
	if (add_text_option("Maze Tower")) { teleport_to_position(-73.92588f, -818.455078f, 326.174377f); }
	if (add_text_option("Construction Tower")) { teleport_to_position(-143.881927f, -984.810852f, 269.134308f); }
	if (add_text_option("Clock Tower")) { teleport_to_position(-1238.675537f, -847.954590f, 85.161690f); }
	if (add_text_option("Sniper Tower")) { teleport_to_position(-550.989380f, -193.862366f, 76.499336f); }
	if (add_text_option("Creek Tower")) { teleport_to_position(2784.6060f, 6000.8770f, 357.2007f); }
	if (add_text_option("Prison Tower")) { teleport_to_position(1541.6290f, 2470.1400f, 62.8751f); }
	if (add_text_option("Military Base")) { teleport_to_position(-2150.634277f, 3234.995117f, 32.810455f); }
	if (add_text_option("Lazer Spawn 1")) { teleport_to_position(-2246.638672f, 3230.022949f, 32.810146f); }
	if (add_text_option("Lazer Spawn 2")) { teleport_to_position(-2138.139893f, 3056.729736f, 32.809875f); }
	if (add_text_option("Lazer Spawn 3")) { teleport_to_position(-2022.258423f, 2973.546875f, 33.118137f); }
	if (add_text_option("Lazer Spawn 4")) { teleport_to_position(-2007.929932f, 3098.386475f, 32.810257f); }
	if (add_text_option("Merryweather")) { teleport_to_position(568.406006f, -3125.799805f, 18.768612f); }
	if (add_text_option("Merryweather Dock")) { teleport_to_position(486.417f, -3339.692f, 6.070f); }
	if (add_text_option("Underwater Ocean")) { teleport_to_position(103.4720f, 7744.1870f, -37.974f); }
	if (add_text_option("Underwater Tank")) { teleport_to_position(4201.633f, 3643.821f, -24.656f); }
	if (add_text_option("Sea Monster")) { teleport_to_position(-3372.677002f, 504.2677002f, -22.797211f); }
	if (add_text_option("Underwater UFO")) { teleport_to_position(762.426f, 7380.371f, -111.377f); }
	if (add_text_option("Underwater Hatch")) { teleport_to_position(4273.950f, 2975.714f, -170.746f); }
	if (add_text_option("Sunken Plane")) { teleport_to_position(-942.350f, 6608.752f, -20.912f); }
	if (add_text_option("Sunken Cargo Ship")) { teleport_to_position(3199.748f, -379.018f, -22.500f); }
	if (add_text_option("Inside Building")) { teleport_to_position(-91.6870f, 33.0948f, 71.4655f); }
	if (add_text_option("Inside Store")) { teleport_to_position(-1244.1380f, -1454.9980f, 4.3478f); }
	if (add_text_option("Vesupucci House")) { teleport_to_position(-976.0147f, 2.1502f, 2.1502f); }
	if (add_text_option("City Wall")) { teleport_to_position(-254.9432f, -147.3534f, 42.7314f); }
	if (add_text_option("Under Bridge")) { teleport_to_position(721.6599f, -1000.6510f, 23.5455f); }
	if (add_text_option("Inside FIB")) { teleport_to_position(135.9541f, -749.8984f, 258.1520f); }
	if (add_text_option("Police Station")) { teleport_to_position(447.0900f, -985.5400f, 30.9600f); }
	if (add_text_option("Strip Club Bar")) { teleport_to_position(126.1211f, -1278.5130f, 29.2696f); }
	if (add_text_option("Inside Casino")) { teleport_to_position(937.4756f, 42.4248f, 80.8990f); }
	if (add_text_option("Beach House")) { teleport_to_position(-1907.3500f, -577.2352f, 20.1223f); }
	if (add_text_option("Under Roof")) { teleport_to_position(-1883.7390f, 2062.8590f, 144.8217f); }
}

void menu_recovery_view_reports() {
	std::stringstream ss;
	ss.precision(2);
	ss << "MPPLY_OVERALL_BADSPORT: " << std::fixed << g_recovery_view_reports_overall_badsport;
	if (add_text_option(ss.str())) { print_notification(7000, "This is your current badsport threshold."); }
	ss.str("");
	ss.clear();
	ss << "MPPLY_CHAR_IS_BADSPORT: " << g_recovery_view_reports_is_badsport;
	if (add_text_option(ss.str())) { print_notification(7000, "This shows whether you are in badsport or not."); }
	ss.str("");
	ss.clear();
	ss << "MPPLY_BECAME_BADSPORT_NUM: " << g_recovery_view_reports_became_badsport_num;
	if (add_text_option(ss.str())) { print_notification(7000, "This is the amount of times you have been in badsport."); }
	ss.str("");
	ss.clear();
	ss << "MPPLY_REPORT_STRENGTH: " << g_recovery_view_reports_report_strength;
	if (add_text_option(ss.str())) { print_notification(7000, "This is your report strength."); }
	ss.str("");
	ss.clear();
	ss << "MPPLY_COMMEND_STRENGTH: " << g_recovery_view_reports_commend_strength;
	if (add_text_option(ss.str())) { print_notification(7000, "This is your commend strength."); }
	ss.str("");
	ss.clear();
	ss << "MPPLY_FRIENDLY: " << g_recovery_view_reports_friendly;
	if (add_text_option(ss.str())) { print_notification(7000, "This is the amount of times you have been commended for being friendly."); }
	ss.str("");
	ss.clear();
	ss << "MPPLY_HELPFUL: " << g_recovery_view_reports_helpful;
	if (add_text_option(ss.str())) { print_notification(7000, "This is the amount of times you have been commended for being helpful."); }
	ss.str("");
	ss.clear();
	ss << "MPPLY_GRIEFING: " << g_recovery_view_reports_griefing;
	if (add_text_option(ss.str())) { print_notification(7000, "This is the amount of times you were reported for griefing."); }
	ss.str("");
	ss.clear();
	ss << "MPPLY_VC_ANNOYINGME: " << g_recovery_view_reports_vc_annoying_me;
	if (add_text_option(ss.str())) { print_notification(7000, "This is the amount of times you were reported for annoying players in voice chat."); }
	ss.str("");
	ss.clear();
	ss << "MPPLY_VC_HATE: " << g_recovery_view_reports_vc_hate;
	if (add_text_option(ss.str())) { print_notification(7000, "This is the amount of times you were reported for voice chat hate speech."); }
	ss.str("");
	ss.clear();
	ss << "MPPLY_TC_ANNOYINGME: " << g_recovery_view_reports_tc_annoying_me;
	if (add_text_option(ss.str())) { print_notification(7000, "This is the amount of times you were reported for annoying players in text chat."); }
	ss.str("");
	ss.clear();
	ss << "MPPLY_TC_HATE: " << g_recovery_view_reports_tc_hate;
	if (add_text_option(ss.str())) { print_notification(7000, "This is the amount of times you were reported for text chat hate speech."); }
	ss.str("");
	ss.clear();
	ss << "MPPLY_OFFENSIVE_LANGUAGE: " << g_recovery_view_reports_offensive_language;
	if (add_text_option(ss.str())) { print_notification(7000, "This is the amount of times you were reported for offensive language."); }
	ss.str("");
	ss.clear();
	ss << "MPPLY_OFFENSIVE_TAGPLATE: " << g_recovery_view_reports_offensive_tagplate;
	if (add_text_option(ss.str())) { print_notification(7000, "This is the amount of times you were reported for having an offensive tagplate."); }
	ss.str("");
	ss.clear();
	ss << "MPPLY_OFFENSIVE_UGC: " << g_recovery_view_reports_offensive_ugc;
	if (add_text_option(ss.str())) { print_notification(7000, "This is the amount of times you were reported for offenive content."); }
	ss.str("");
	ss.clear();
	ss << "MPPLY_BAD_CREW_NAME: " << g_recovery_view_reports_bad_crew_name;
	if (add_text_option(ss.str())) { print_notification(7000, "This is the amount of times you were reported for having a bad crew name."); }
	ss.str("");
	ss.clear();
	ss << "MPPLY_BAD_CREW_MOTTO: " << g_recovery_view_reports_bad_crew_motto;
	if (add_text_option(ss.str())) { print_notification(7000, "This is the amount of times you were reported for having a bad crew motto."); }
	ss.str("");
	ss.clear();
	ss << "MPPLY_BAD_CREW_STATUS: " << g_recovery_view_reports_bad_crew_status;
	if (add_text_option(ss.str())) { print_notification(7000, "This is the amount of times you were reported for having a bad crew status."); }
	ss.str("");
	ss.clear();
	ss << "MPPLY_BAD_CREW_EMBLEM: " << g_recovery_view_reports_bad_crew_emblem;
	if (add_text_option(ss.str())) { print_notification(7000, "This is the amount of times you were reported for having a bad crew emblem."); }
	ss.str("");
	ss.clear();
	ss << "MPPLY_GAME_EXPLOITS: " << g_recovery_view_reports_game_exploits;
	if (add_text_option(ss.str())) { print_notification(7000, "This is the amount of times you were reported for in-game exploits."); }
	ss.str("");
	ss.clear();
	ss << "MPPLY_EXPLOITS: " << g_recovery_view_reports_exploits;
	if (add_text_option(ss.str())) { print_notification(7000, "This is the amount of times you were reported for exploits."); }
	ss.str("");
	ss.clear();
	ss << "MP0_BAD_SPORT_BITSET: " << g_recovery_view_reports_char_0_badsport_bitset;
	if (add_text_option(ss.str())) { print_notification(7000, "This is your first character's badsport bitset."); }
	ss.str("");
	ss.clear();
	ss << "MP1_BAD_SPORT_BITSET: " << g_recovery_view_reports_char_1_badsport_bitset;
	if (add_text_option(ss.str())) { print_notification(7000, "This is your second character's badsport bitset."); }
	ss.str("");
	ss.clear();
	ss << "MP2_BAD_SPORT_BITSET: " << g_recovery_view_reports_char_2_badsport_bitset;
	if (add_text_option(ss.str())) { print_notification(7000, "This is your third character's badsport bitset."); }
	ss.str("");
	ss.clear();
	ss << "MP0_CHEAT_BITSET: " << g_recovery_view_reports_char_0_cheat_bitset;
	if (add_text_option(ss.str())) { print_notification(7000, "This is your first character's cheat bitset."); }
	ss.str("");
	ss.clear();
	ss << "MP1_CHEAT_BITSET: " << g_recovery_view_reports_char_1_cheat_bitset;
	if (add_text_option(ss.str())) { print_notification(7000, "This is your second character's cheat bitset."); }
	ss.str("");
	ss.clear();
	ss << "MP2_CHEAT_BITSET: " << g_recovery_view_reports_char_2_cheat_bitset;
	if (add_text_option(ss.str())) { print_notification(7000, "This is your third character's cheat bitset."); }
	ss.str("");
	ss.clear();
}
void menu_recovery_rp_increaser() {
	add_editor_option(true, g_recovery_rp_increaser_wanted_level, &g_recovery_rp_increaser_wanted_level, 1, 5, 1, "Wanted Level");
	add_editor_option(true, g_recovery_rp_increaser_delay, &g_recovery_rp_increaser_delay, 0ui64, 60000ui64, 500ui64, "Delay ~c~(ms)");
	add_toggle_option(&g_recovery_rp_increaser_active, "Active");
}
void menu_recovery() {
	add_submenu_option(menu_recovery_rp_increaser, "RP Increaser ~c~(Wanted Level)");
	if (add_submenu_option(menu_recovery_view_reports, "View Reports")) {
		STATS::STAT_GET_FLOAT(GAMEPLAY::GET_HASH_KEY("MPPLY_OVERALL_BADSPORT"), &g_recovery_view_reports_overall_badsport, TRUE);
		STATS::STAT_GET_BOOL(GAMEPLAY::GET_HASH_KEY("MPPLY_CHAR_IS_BADSPORT"), &g_recovery_view_reports_is_badsport, TRUE);
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BECAME_BADSPORT_NUM"), &g_recovery_view_reports_became_badsport_num, TRUE);
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_REPORT_STRENGTH"), &g_recovery_view_reports_report_strength, TRUE);
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_COMMEND_STRENGTH"), &g_recovery_view_reports_commend_strength, TRUE);
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_FRIENDLY"), &g_recovery_view_reports_friendly, TRUE);
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_HELPFUL"), &g_recovery_view_reports_helpful, TRUE);
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_GRIEFING"), &g_recovery_view_reports_griefing, TRUE);
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_VC_ANNOYINGME"), &g_recovery_view_reports_vc_annoying_me, TRUE);
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_VC_HATE"), &g_recovery_view_reports_vc_hate, TRUE);
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_TC_ANNOYINGME"), &g_recovery_view_reports_tc_annoying_me, TRUE);
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_TC_HATE"), &g_recovery_view_reports_tc_hate, TRUE);
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_OFFENSIVE_LANGUAGE"), &g_recovery_view_reports_offensive_language, TRUE);
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_OFFENSIVE_TAGPLATE"), &g_recovery_view_reports_offensive_tagplate, TRUE);
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_OFFENSIVE_UGC"), &g_recovery_view_reports_offensive_ugc, TRUE);
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_NAME"), &g_recovery_view_reports_bad_crew_name, TRUE);
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_MOTTO"), &g_recovery_view_reports_bad_crew_motto, TRUE);
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_STATUS"), &g_recovery_view_reports_bad_crew_status, TRUE);
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_EMBLEM"), &g_recovery_view_reports_bad_crew_emblem, TRUE);
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_GAME_EXPLOITS"), &g_recovery_view_reports_game_exploits, TRUE);
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_EXPLOITS"), &g_recovery_view_reports_exploits, TRUE);
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MP0_BAD_SPORT_BITSET"), &g_recovery_view_reports_char_0_badsport_bitset, TRUE);
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MP1_BAD_SPORT_BITSET"), &g_recovery_view_reports_char_1_badsport_bitset, TRUE);
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MP2_BAD_SPORT_BITSET"), &g_recovery_view_reports_char_2_badsport_bitset, TRUE);
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHEAT_BITSET"), &g_recovery_view_reports_char_0_cheat_bitset, TRUE);
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHEAT_BITSET"), &g_recovery_view_reports_char_1_cheat_bitset, TRUE);
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHEAT_BITSET"), &g_recovery_view_reports_char_2_cheat_bitset, TRUE);
	}
	if (add_text_option("Clear Reports")) { recovery_clear_reports(); }
	if (add_text_option("Unlock All")) { recovery_unlock_all(); }
	if (add_text_option("Remove Badsport Status")) { recovery_remove_badsport(); }
	if (add_text_option("Max Skills")) { recovery_max_skills(); }
	if (add_text_option("Infinite Ammo")) { recovery_infinite_ammo(); }
	if (add_text_option("Unlock Chrome Rims")) { recovery_unlock_chrome_rims(); }
	if (add_text_option("Max Fireworks")) { recovery_max_fireworks(); }
	if (add_text_option("Max Snacks")) { recovery_max_snacks(); }
	if (add_text_option("Max Armour")) { recovery_max_armour(); }
	if (add_text_option("Enable Character Redesign")) { recovery_enable_character_redesign(); }
}

void menu_world_time() {
	std::int32_t time[3] = { TIME::GET_CLOCK_HOURS(), TIME::GET_CLOCK_MINUTES(), TIME::GET_CLOCK_SECONDS() };
	std::stringstream ss;
	ss << std::setw(2) << std::setfill('0') << time[0] << ":" << std::setw(2) << std::setfill('0') << time[1] << ":" << std::setw(2) << std::setfill('0') << time[2];
	if (add_editor_option(true, ss.str(), &time[0], 0, 23, 1, "Current Time"))
		set_session_time(time[0], time[1], time[2]);
	if (add_toggle_option(&g_world_time_freeze, "Freeze Time ~c~(Locally)")) { if (!g_world_time_freeze) TIME::PAUSE_CLOCK(FALSE); }
	if (add_toggle_option(&g_world_time_sync, "Sync With System")) { if (!g_world_time_sync) TIME::PAUSE_CLOCK(FALSE); }
}
void menu_world_clouds() {
	if (add_text_option("Cloudy")) { GAMEPLAY::LOAD_CLOUD_HAT("Cloudy 01", 0.5f); }
	if (add_text_option("Rain")) { GAMEPLAY::LOAD_CLOUD_HAT("RAIN", 0.5f); }
	if (add_text_option("Horizon")) { GAMEPLAY::LOAD_CLOUD_HAT("Horizon", 0.5f); }
	if (add_text_option("Horizon Band 1")) { GAMEPLAY::LOAD_CLOUD_HAT("horizonband1", 0.5f); }
	if (add_text_option("Horizon Band 2")) { GAMEPLAY::LOAD_CLOUD_HAT("horizonband2", 0.5f); }
	if (add_text_option("Horizon Band 3")) { GAMEPLAY::LOAD_CLOUD_HAT("horizonband3", 0.5f); }
	if (add_text_option("Puffs")) { GAMEPLAY::LOAD_CLOUD_HAT("Puffs", 0.5f); }
	if (add_text_option("Wispy")) { GAMEPLAY::LOAD_CLOUD_HAT("Wispy", 0.5f); }
	if (add_text_option("Stormy")) { GAMEPLAY::LOAD_CLOUD_HAT("Stormy 01", 0.5f); }
	if (add_text_option("Clear")) { GAMEPLAY::LOAD_CLOUD_HAT("Clear 01", 0.5f); }
	if (add_text_option("Snowy")) { GAMEPLAY::LOAD_CLOUD_HAT("Snowy 01", 0.5f); }
	if (add_text_option("Contrails")) { GAMEPLAY::LOAD_CLOUD_HAT("Contrails", 0.5f); }
	if (add_text_option("Altostratus")) { GAMEPLAY::LOAD_CLOUD_HAT("altostratus", 0.5f); }
	if (add_text_option("Nimbus")) { GAMEPLAY::LOAD_CLOUD_HAT("Nimbus", 0.5f); }
	if (add_text_option("Cirrus")) { GAMEPLAY::LOAD_CLOUD_HAT("Cirrus", 0.5f); }
	if (add_text_option("Cirrocumulus")) { GAMEPLAY::LOAD_CLOUD_HAT("cirrocumulus", 0.5f); }
	if (add_text_option("Stratocumulus")) { GAMEPLAY::LOAD_CLOUD_HAT("stratocumulus", 0.5f); }
	if (add_text_option("Stripey")) { GAMEPLAY::LOAD_CLOUD_HAT("Stripey", 0.5f); }
	if (add_text_option("Horsey")) { GAMEPLAY::LOAD_CLOUD_HAT("horsey", 0.5f); }
	if (add_text_option("Shower")) { GAMEPLAY::LOAD_CLOUD_HAT("shower", 0.5f); }
}
void menu_world_weather() {
	if (add_text_option("Extra Sunny")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("EXTRASUNNY"); }
	if (add_text_option("Clear")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("CLEAR"); }
	if (add_text_option("Clouds")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("CLOUDS"); }
	if (add_text_option("Smog")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("SMOG"); }
	if (add_text_option("Foggy")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("FOGGY"); }
	if (add_text_option("Overcast")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("OVERCAST"); }
	if (add_text_option("Rain")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("RAIN"); }
	if (add_text_option("Thunder")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("THUNDER"); }
	if (add_text_option("Clearing")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("CLEARING"); }
	if (add_text_option("Neutral")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("NEUTRAL"); }
	if (add_text_option("Snow")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("SNOW"); }
	if (add_text_option("Blizzard")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("BLIZZARD"); }
	if (add_text_option("Snow Light")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("SNOWLIGHT"); }
	if (add_text_option("Xmas")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("XMAS"); }
	if (add_text_option("Halloween")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("HALLOWEEN"); }
}
void menu_world_water_tuning() {
	std::add_pointer_t<std::float_t> water_tune = reinterpret_cast<std::add_pointer_t<std::float_t>>(GTA_WATER_TUNE_XML);
	add_editor_option(true, water_tune[0], &water_tune[0], -10.0f, 10.0f, 0.1f, "Ripple Scale");
	add_editor_option(true, water_tune[1], &water_tune[1], -10.0f, 10.0f, 0.1f, "Ocean Foam Scale");
	add_editor_option(true, water_tune[2], &water_tune[2], 800.0f, 1200.0f, 0.5f, "Specular Falloff");
	add_editor_option(true, water_tune[3], &water_tune[3], -100.0f, 100.0f, 0.25f, "Fog Pierce Intensity");
	add_editor_option(true, water_tune[4], &water_tune[4], -10.0f, 10.0f, 0.1f, "Refraction Blend");
	add_editor_option(true, water_tune[5], &water_tune[5], -10.0f, 10.0f, 0.1f, "Refraction Exponent");
	add_editor_option(true, water_tune[6], &water_tune[6], -1000.0f, 1000.0f, 1.0f, "Water Cycle Depth");
	add_editor_option(true, water_tune[7], &water_tune[7], -1000.0f, 1000.0f, 1.0f, "Water Cycle Fade");
	add_editor_option(true, water_tune[8], &water_tune[8], -1000.0f, 1000.0f, 1.0f, "Water Lightning Depth");
	add_editor_option(true, water_tune[9], &water_tune[9], -1000.0f, 1000.0f, 1.0f, "Water Lightning Fade");
	add_editor_option(true, water_tune[10], &water_tune[10], -1000.0f, 1000.0f, 1.0f, "Deep Water Mod Depth");
	add_editor_option(true, water_tune[11], &water_tune[11], -1000.0f, 1000.0f, 1.0f, "Deep Water Mod Fade");
	add_editor_option(true, water_tune[12], &water_tune[12], -1000.0f, 1000.0f, 1.0f, "God Rays Lerp Start");
	add_editor_option(true, water_tune[13], &water_tune[13], -1000.0f, 1000.0f, 1.0f, "God Rays Lerp End");
	add_editor_option(true, water_tune[14], &water_tune[14], -10.0f, 10.0f, 0.1f, "Disturb Foam Scale");
	add_editor_option(true, water_tune[15], &water_tune[15], -8000.0f, 8000.0f, 10.0f, "Fog Min X");
	add_editor_option(true, water_tune[16], &water_tune[16], -8000.0f, 8000.0f, 10.0f, "Fog Min Y");
	add_editor_option(true, water_tune[17], &water_tune[17], -8000.0f, 8000.0f, 10.0f, "Fog Max X");
	add_editor_option(true, water_tune[18], &water_tune[18], -8000.0f, 8000.0f, 10.0f, "Fog Max Y");
}
void menu_world_water_quads() {
	if (add_text_option("Transparent Water")) {
		std::add_pointer_t<WaterQuad> water_quads = *reinterpret_cast<std::add_pointer_t<WaterQuad*>>(GTA_WATER_QUAD_XML);
		if (water_quads) {
			for (std::int16_t i = 0; i < *reinterpret_cast<std::add_pointer_t<std::int16_t>>(GTA_WATER_QUAD_XML_COUNT); i++) {
				water_quads[i].a1 = 0i8;
				water_quads[i].a2 = 0i8;
				water_quads[i].a3 = 0i8;
				water_quads[i].a4 = 0i8;
			}
		}
	}
	if (add_text_option("Opaque Water")) {
		std::add_pointer_t<WaterQuad> water_quads = *reinterpret_cast<std::add_pointer_t<WaterQuad*>>(GTA_WATER_QUAD_XML);
		if (water_quads) {
			for (std::int16_t i = 0; i < *reinterpret_cast<std::add_pointer_t<std::int16_t>>(GTA_WATER_QUAD_XML_COUNT); i++) {
				water_quads[i].a1 = 255i8;
				water_quads[i].a2 = 255i8;
				water_quads[i].a3 = 255i8;
				water_quads[i].a4 = 255i8;
			}
		}
	}
	if (add_text_option("Raise Water Height")) {
		std::add_pointer_t<WaterQuad> water_quads = *reinterpret_cast<std::add_pointer_t<WaterQuad*>>(GTA_WATER_QUAD_XML);
		if (water_quads) {
			for (std::int16_t i = 0; i < *reinterpret_cast<std::add_pointer_t<std::int16_t>>(GTA_WATER_QUAD_XML_COUNT); i++) {
				water_quads[i].z = water_quads[i].z + 1.0f;
			}
		}
	}
	if (add_text_option("Lower Water Height")) {
		std::add_pointer_t<WaterQuad> water_quads = *reinterpret_cast<std::add_pointer_t<WaterQuad*>>(GTA_WATER_QUAD_XML);
		if (water_quads) {
			for (std::int16_t i = 0; i < *reinterpret_cast<std::add_pointer_t<std::int16_t>>(GTA_WATER_QUAD_XML_COUNT); i++) {
				water_quads[i].z = water_quads[i].z - 1.0f;
			}
		}
	}
}
void menu_world_water() {
	add_submenu_option(menu_world_water_tuning, "Water Tuning");
	add_submenu_option(menu_world_water_quads, "Water Quads");
}
void menu_world_radar() {
	add_toggle_option(&g_quantum_radar_active, "Display");
	add_editor_option(true, g_quantum_radar_fov, &g_quantum_radar_fov, 0.0f, 1000.0f, 0.5f, "FOV");
	add_editor_option(true, g_quantum_radar_scale, &g_quantum_radar_scale, 0.0f, 1.0f, 0.01f, "Scale");
	add_editor_option(true, g_quantum_radar_pos_x, &g_quantum_radar_pos_x, 0.0f, 1.0f, 0.01f, "Screen Pos ~c~(X)");
	add_editor_option(true, g_quantum_radar_pos_y, &g_quantum_radar_pos_y, 0.0f, 1.0f, 0.01f, "Screen Pos ~c~(Y)");
	add_editor_option(true, g_quantum_radar_inner_line_width, &g_quantum_radar_inner_line_width, 0.0f, 1.0f, 0.001f, "Inner Line Width");
	add_editor_option(true, g_quantum_radar_outer_line_width, &g_quantum_radar_outer_line_width, 0.0f, 1.0f, 0.001f, "Outer Line Width");
	add_editor_option(true, g_quantum_radar_center_rect_scale, &g_quantum_radar_center_rect_scale, 0.0f, 1.0f, 0.001f, "Center Rect Scale");
}
void menu_world_waypoint() {
	if (add_text_option("Teleport To Waypoint")) {
		if (UI::DOES_BLIP_EXIST(UI::GET_FIRST_BLIP_INFO_ID(8))) {
			Vector3 coords = UI::GET_BLIP_COORDS(UI::GET_FIRST_BLIP_INFO_ID(8));
			teleport_to_position(coords.x, coords.y, coords.z);
		}
		else
			print_notification(7000, "~r~Error:~s~ No waypoint set.");
	}
	add_submenu_option(menu_vehicle_drive_to_waypoint, "Drive To Waypoint");
	if (UI::DOES_BLIP_EXIST(UI::GET_FIRST_BLIP_INFO_ID(8))) {
		std::uint64_t points = *(std::uint64_t*)GTA_WAYPOINT_PATH_DATA;
		if (points) {

			std::int32_t ped = PLAYER::PLAYER_PED_ID();
			if (ENTITY::DOES_ENTITY_EXIST(ped)) {
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, 0.0f, 0.0f, 0.0f);
				GRAPHICS::DRAW_LINE(coords.x, coords.y, coords.z, *(std::float_t*)(points + 0x10), *(std::float_t*)(points + 0x14), coords.z, 100, 0, 255, 255);
			}

			add_info_box_title("Waypoint Info");
			add_data_to_info_box("GPS Nodes", *(std::int32_t*)(GTA_WAYPOINT_PATH_DATA + 0x44));
			add_data_to_info_box("Axis ~c~(X)", *(std::float_t*)(GTA_WAYPOINT_PATH_DATA + 0x20));
			add_data_to_info_box("Axis ~c~(Y)", *(std::float_t*)(GTA_WAYPOINT_PATH_DATA + 0x24));
			add_data_to_info_box("Dist. ~c~(Metres)", *(std::float_t*)(GTA_WAYPOINT_PATH_DATA + 0x68));
			draw_rect((g_menu_banner_pos_x >= 0.5f) ? (g_menu_banner_pos_x - (g_menu_banner_size_x / 2) - (g_info_box_title_width / 2)) : (g_menu_banner_pos_x + (g_menu_banner_size_x / 2) + (g_info_box_title_width / 2)), ((g_menu_banner_pos_y - ((g_menu_banner_size_y / 2)) + (g_info_box_title_length / 2)) + (g_info_box_title_length / 2)) + ((g_info_box_count * (g_info_box_title_length / 2)) / 2) + 0.0035f, g_info_box_title_width, (g_info_box_count * (g_info_box_title_length / 2)) + 0.007f, g_menu_background_colour);
			g_info_box_count = NULL;
		}
	}
}
void menu_world_manage_closest_drawable() {
	add_editor_option(true, g_menu_drawable_manager_radius, &g_menu_drawable_manager_radius, 5.0f, 5000.0f, 1.0f, "Radius");
	if (add_text_option("Update Handle")) {
		update_closest_drawable_handle(g_menu_drawable_manager_radius);
	}
	add_break_option("Manipulation");
	if (g_menu_drawable_manager_current_closest_drawable) {
		Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, 0.0f, 0.0f);
		GRAPHICS::DRAW_LINE(coords.x, coords.y, coords.z, g_menu_drawable_manager_current_closest_drawable->x, g_menu_drawable_manager_current_closest_drawable->y, g_menu_drawable_manager_current_closest_drawable->z, g_menu_header_text_colour.r, g_menu_header_text_colour.g, g_menu_header_text_colour.b, g_menu_header_text_colour.a);
		add_editor_option(true, g_menu_drawable_manager_current_closest_drawable->x, &g_menu_drawable_manager_current_closest_drawable->x, -8000.0f, 8000.0f, 1.0f, "Axis ~c~(X)");
		add_editor_option(true, g_menu_drawable_manager_current_closest_drawable->y, &g_menu_drawable_manager_current_closest_drawable->y, -8000.0f, 8000.0f, 1.0f, "Axis ~c~(Y)");
		add_editor_option(true, g_menu_drawable_manager_current_closest_drawable->z, &g_menu_drawable_manager_current_closest_drawable->z, -8000.0f, 8000.0f, 1.0f, "Axis ~c~(Z)");
		add_editor_option(true, g_menu_drawable_manager_current_closest_drawable->s3, &g_menu_drawable_manager_current_closest_drawable->s3, -100.0f, 100.0f, 0.1f, "Width");
		add_editor_option(true, g_menu_drawable_manager_current_closest_drawable->s4, &g_menu_drawable_manager_current_closest_drawable->s4, -100.0f, 100.0f, 0.1f, "Height");
		std::uint64_t model_info = g_menu_drawable_manager_current_closest_drawable->model_info;
		if (model_info) {
			Vector3 min; Vector3 max;
			std::uint32_t hash = *(std::uint32_t*)(model_info + 0x18);
			add_info_box_title("Drawable Info");
			GAMEPLAY::GET_MODEL_DIMENSIONS(hash, &min, &max);
			add_data_to_info_box("Hash", hash);
			add_data_to_info_box("Axis ~c~(X)", g_menu_drawable_manager_current_closest_drawable->x);
			add_data_to_info_box("Axis ~c~(Y)", g_menu_drawable_manager_current_closest_drawable->y);
			add_data_to_info_box("Axis ~c~(Z)", g_menu_drawable_manager_current_closest_drawable->z);
			add_data_to_info_box("Width", max.x * 2.0f);
			add_data_to_info_box("Length", max.y * 2.0f);
			add_data_to_info_box("Height", max.z * 2.0f);
			draw_rect((g_menu_banner_pos_x >= 0.5f) ? (g_menu_banner_pos_x - (g_menu_banner_size_x / 2) - (g_info_box_title_width / 2)) : (g_menu_banner_pos_x + (g_menu_banner_size_x / 2) + (g_info_box_title_width / 2)), ((g_menu_banner_pos_y - ((g_menu_banner_size_y / 2)) + (g_info_box_title_length / 2)) + (g_info_box_title_length / 2)) + ((g_info_box_count * (g_info_box_title_length / 2)) / 2) + 0.0035f, g_info_box_title_width, (g_info_box_count * (g_info_box_title_length / 2)) + 0.007f, g_menu_background_colour);
			g_info_box_count = NULL;
		}
		if (CURRENT_OPTION == 1) GRAPHICS::DRAW_MARKER(28, coords.x, coords.y, coords.z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, g_menu_drawable_manager_radius, g_menu_drawable_manager_radius, g_menu_drawable_manager_radius, g_menu_header_text_colour.r, g_menu_header_text_colour.g, g_menu_header_text_colour.b, g_menu_header_text_colour.a, false, false, 2, true, false, false, false);
	}
	else {
		add_text_option("No Handle");
	}
}
void menu_world() {
	add_submenu_option(menu_world_time, "Time");
	add_submenu_option(menu_world_weather, "Weather");
	add_submenu_option(menu_world_clouds, "Clouds");
	add_submenu_option(menu_world_water, "Water");
	add_submenu_option(menu_world_radar, "Radar");
	add_submenu_option(menu_world_waypoint, "Waypoint");
	if (add_submenu_option(menu_world_manage_closest_drawable, "Manage Closest Drawable"))
		update_closest_drawable_handle(g_menu_drawable_manager_radius);
	//add_submenu_option(menu_world_black_hole, "Black Hole");
	if (add_text_option(OBFUSCATE("Disable Mission Circles")))
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("fmmc_launcher");
	if (add_toggle_option(&g_world_blackout, "Blackout"))
		GRAPHICS::SET_ARTIFICIAL_LIGHTS_STATE(g_world_blackout);
	add_toggle_option(&g_world_bypass_restricted_zones, "Bypass Restricted Zones");
}

void menu_misc_tunable_manager() {
	add_toggle_option(scr_global(262145).at(7686).as<std::add_pointer_t<bool>>(), "SET_ALL_PHONE_SERVICES_AVAILABLE");
	add_toggle_option(scr_global(262145).at(8269).as<std::add_pointer_t<bool>>(), "DISABLE_SCTV_FRIENDS_SPECTATE");
	add_toggle_option(scr_global(262145).at(8270).as<std::add_pointer_t<bool>>(), "DISABLE_SCTV_GTAO_TV");
	add_toggle_option(scr_global(262145).at(8271).as<std::add_pointer_t<bool>>(), "DISABLE_SCTV_DEV_SPECTATE");
	add_toggle_option(scr_global(262145).at(12705).as<std::add_pointer_t<bool>>(), "PROPERTYWEBSITE_SALE");
	add_toggle_option(scr_global(262145).at(4723).as<std::add_pointer_t<bool>>(), "TURN_SNOW_ON_OFF");
	add_toggle_option(scr_global(262145).at(4724).as<std::add_pointer_t<bool>>(), "TURN_SNAPMATIC_ON_OFF");
	add_toggle_option(scr_global(262145).at(4734).as<std::add_pointer_t<bool>>(), "TOGGLE_XMAS_CONTENT");
	add_toggle_option(scr_global(262145).at(8982).as<std::add_pointer_t<bool>>(), "TOGGLE_CHRISTMAS_EVE_GIFT");
	add_toggle_option(scr_global(262145).at(8983).as<std::add_pointer_t<bool>>(), "TOGGLE_NEW_YEARS_EVE_GIFT");
	add_toggle_option(scr_global(262145).at(8984).as<std::add_pointer_t<bool>>(), "TOGGLE_NEW_YEARS_DAY_GIFT");
	add_toggle_option(scr_global(262145).at(12227).as<std::add_pointer_t<bool>>(), "TURN_ON_HALLOWEEN_SOUNDS");
	add_toggle_option(scr_global(262145).at(11577).as<std::add_pointer_t<bool>>(), "TURN_ON_HALLOWEEN_WEAPONS");
	add_toggle_option(scr_global(262145).at(11584).as<std::add_pointer_t<bool>>(), "TURN_ON_HALLOWEEN_ANIMS");
	add_toggle_option(scr_global(262145).at(11555).as<std::add_pointer_t<bool>>(), "TURN_ON_VALENTINE_WEAPON");
	add_toggle_option(scr_global(262145).at(11556).as<std::add_pointer_t<bool>>(), "TURN_ON_VALENTINE_VEHICLE");
	add_toggle_option(scr_global(262145).at(11557).as<std::add_pointer_t<bool>>(), "TURN_ON_VALENTINE_MASKS");
	add_toggle_option(scr_global(262145).at(11558).as<std::add_pointer_t<bool>>(), "TURN_ON_VALENTINE_HAIR");
	add_toggle_option(scr_global(262145).at(11559).as<std::add_pointer_t<bool>>(), "TURN_ON_VALENTINE_CLOTHING");
	add_toggle_option(scr_global(262145).at(12909).as<std::add_pointer_t<bool>>(), "TURN_ON_VALENTINE_2016_CLOTHING");
	add_toggle_option(scr_global(262145).at(12910).as<std::add_pointer_t<bool>>(), "TURN_ON_VALENTINE_2016_VEHICLE");
	add_toggle_option(scr_global(262145).at(12235).as<std::add_pointer_t<bool>>(), "XMAS2015_VEHICLE");
	add_toggle_option(scr_global(262145).at(7936).as<std::add_pointer_t<bool>>(), "TURNOFFSPECIALCRATES");
	add_toggle_option(scr_global(262145).at(7805).as<std::add_pointer_t<bool>>(), "DISABLEROLLERCOASTER");
	add_toggle_option(scr_global(262145).at(7806).as<std::add_pointer_t<bool>>(), "DISABLEFERRISWHEEL");
	add_toggle_option(scr_global(262145).at(7807).as<std::add_pointer_t<bool>>(), "DISABLEFIREWORKS");
}
void menu_misc_script_manager_manage_selected_thread() {
	if (g_misc_selected_script_handler) {
		if (g_misc_selected_script_handler->Thread) {
			/*if (g_pSelectedScriptHandler->m_lpGtaThread->m_lpGameScriptHandlerNetComponent) {
				add_submenu_option(nullptr, "Manage Network Component");
			}*/
		}
		else {
			add_text_option("Thread Invalid");
		}
	}
	else {
		add_text_option("Handler Invalid");
	}
}
void menu_misc_script_manager_manage_selected() {
	if (g_misc_selected_script_handler) {
		if (g_misc_selected_script_handler->Thread) {
			add_submenu_option(menu_misc_script_manager_manage_selected_thread, "Manage Thread");
		}
	}
	else {
		add_text_option("Handler Invalid");
	}
}
void menu_misc_script_manager_networked() {
	if (GTA_NETWORKED_SCRIPT_HANDLERS) {
		std::uint64_t pool = *(std::uint64_t*)(GTA_NETWORKED_SCRIPT_HANDLERS);
		if (pool) {
			std::uint32_t pool_size = *(std::uint32_t*)(pool + 0x10);
			for (std::uint32_t i = 0; i < pool_size; i++) {
				CGameScriptHandlerNetwork* handler = (CGameScriptHandlerNetwork*)(get_element_from_pool(pool, i));
				if (handler) {
					if (add_submenu_option(menu_misc_script_manager_manage_selected, handler->GameScriptId.ScriptName)) {
						g_misc_selected_script_handler = handler;
					}
					if (i == CURRENT_OPTION - 1) {
						add_info_box_title(handler->GameScriptId.ScriptName);
						add_data_to_info_box("Handler", handler);
						add_data_to_info_box("Script Hash", handler->GameScriptId.ScriptHash);
						add_data_to_info_box("Instance Hash", handler->GameScriptId.InstanceHash);
						add_data_to_info_box("Instance ID", handler->GameScriptId.InstanceId);
						add_data_to_info_box("Timestamp", handler->GameScriptId.Timestamp);
						if (handler->Thread) {
							add_data_to_info_box("Thread", handler->Thread);
							add_data_to_info_box("Thread ID", handler->Thread->ThreadId);
							add_data_to_info_box("Thread State", handler->Thread->ThreadState);
							add_data_to_info_box("Timer A", handler->Thread->TimerA);
							add_data_to_info_box("Timer B", handler->Thread->TimerB);
							add_data_to_info_box("Wait Time", handler->Thread->WaitTime);
							if (handler->Thread->Message) {
								add_data_to_info_box("Msg", handler->Thread->Message);
							}
						}
						draw_rect((g_menu_banner_pos_x >= 0.5f) ? (g_menu_banner_pos_x - (g_menu_banner_size_x / 2) - (g_info_box_title_width / 2)) : (g_menu_banner_pos_x + (g_menu_banner_size_x / 2) + (g_info_box_title_width / 2)), ((g_menu_banner_pos_y - ((g_menu_banner_size_y / 2)) + (g_info_box_title_length / 2)) + (g_info_box_title_length / 2)) + ((g_info_box_count * (g_info_box_title_length / 2)) / 2) + 0.0035f, g_info_box_title_width, (g_info_box_count * (g_info_box_title_length / 2)) + 0.007f, g_menu_background_colour);
						g_info_box_count = NULL;
					}
				}
				else {
					add_text_option("~c~Free Slot");
				}
			}
		}
		else {
			add_text_option("No Script Handlers Found");
		}
	}
	else {
		add_text_option("No Script Handlers Found");
	}
}
void menu_misc_script_manager_local() {
	if (GTA_LOCAL_SCRIPT_HANDLERS) {
		std::uint64_t pool = *(std::uint64_t*)(GTA_LOCAL_SCRIPT_HANDLERS);
		if (pool) {
			std::uint32_t pool_size = *(std::uint32_t*)(pool + 0x10);
			for (std::uint32_t i = 0; i < pool_size; i++) {
				CGameScriptHandlerNetwork* handler = (CGameScriptHandlerNetwork*)(get_element_from_pool(pool, i));
				if (handler) {
					if (add_submenu_option(menu_misc_script_manager_manage_selected, handler->GameScriptId.ScriptName)) {
						g_misc_selected_script_handler = handler;
					}
					if (i == CURRENT_OPTION - 1) {
						add_info_box_title(handler->GameScriptId.ScriptName);
						add_data_to_info_box("Handler", handler);
						add_data_to_info_box("Script Hash", handler->GameScriptId.ScriptHash);
						add_data_to_info_box("Instance Hash", handler->GameScriptId.InstanceHash);
						add_data_to_info_box("Instance ID", handler->GameScriptId.InstanceId);
						add_data_to_info_box("Timestamp", handler->GameScriptId.Timestamp);
						if (handler->Thread) {
							add_data_to_info_box("Thread", handler->Thread);
							add_data_to_info_box("Thread ID", handler->Thread->ThreadId);
							add_data_to_info_box("Thread State", handler->Thread->ThreadState);
							add_data_to_info_box("Timer A", handler->Thread->TimerA);
							add_data_to_info_box("Timer B", handler->Thread->TimerB);
							add_data_to_info_box("Wait Time", handler->Thread->WaitTime);
							if (handler->Thread->Message) {
								add_data_to_info_box("Msg", handler->Thread->Message);
							}
						}
						draw_rect((g_menu_banner_pos_x >= 0.5f) ? (g_menu_banner_pos_x - (g_menu_banner_size_x / 2) - (g_info_box_title_width / 2)) : (g_menu_banner_pos_x + (g_menu_banner_size_x / 2) + (g_info_box_title_width / 2)), ((g_menu_banner_pos_y - ((g_menu_banner_size_y / 2)) + (g_info_box_title_length / 2)) + (g_info_box_title_length / 2)) + ((g_info_box_count * (g_info_box_title_length / 2)) / 2) + 0.0035f, g_info_box_title_width, (g_info_box_count * (g_info_box_title_length / 2)) + 0.007f, g_menu_background_colour);
						g_info_box_count = NULL;
					}
				}
				else {
					add_text_option("~c~Free Slot");
				}
			}
		}
		else {
			add_text_option("No Script Handlers Found");
		}
	}
	else {
		add_text_option("No Script Handlers Found");
	}
}
void menu_misc_virtual_tv_playlists() {
	if (add_text_option("Clear Current Playlist"))
	add_toggle_option(&g_misc_virtual_tv_playlists_restart_on_change, "Restart On Change");
	for (auto s : g_tv_playlists) {
		if (add_text_option(s))
			GRAPHICS::SET_TV_CHANNEL_PLAYLIST(0, s.c_str(), g_misc_virtual_tv_playlists_restart_on_change);
	}
}
void menu_misc_virtual_tv() {
	if (add_toggle_option(&g_misc_virtual_tv_subtitles, "Subtitles"))
		GRAPHICS::ENABLE_MOVIE_SUBTITLES(g_misc_virtual_tv_subtitles);
	add_submenu_option(menu_misc_virtual_tv_playlists, "Playlists");
	add_editor_option(true, g_misc_virtual_tv_x, &g_misc_virtual_tv_x, 0.0f, 0.5f, 0.01f, "Position ~c~(X)");
	add_editor_option(true, g_misc_virtual_tv_y, &g_misc_virtual_tv_y, 0.0f, 0.5f, 0.01f, "Position ~c~(Y)");
	add_editor_option(true, g_misc_virtual_tv_width, &g_misc_virtual_tv_width, 0.0f, 0.5f, 0.01f, "Scale ~c~(W)");
	add_editor_option(true, g_misc_virtual_tv_height, &g_misc_virtual_tv_height, 0.0f, 0.5f, 0.01f, "Scale ~c~(H)");
	add_editor_option(true, g_misc_virtual_tv_rotation, &g_misc_virtual_tv_rotation, 0.0f, 360.0f, 0.1f, "Rotation");
	if (add_toggle_option(&g_misc_virtual_tv_active, "Active")) {
		if (g_misc_virtual_tv_active)
			GRAPHICS::SET_TV_CHANNEL(2);
	}
}
void menu_misc() {
	add_submenu_option(menu_misc_tunable_manager, "Tunable Manager");
	add_submenu_option(menu_misc_virtual_tv, "Virtual TV");
	if (add_toggle_option(&g_misc_disable_minimap, "Disable Minimap")) {
		if (!g_misc_disable_minimap) {
			UI::DISPLAY_HUD(true);
			UI::DISPLAY_RADAR(true);
		}
	}
	add_toggle_option(&g_misc_disable_gameplay_phone, "Disable Gameplay Phone");
	add_toggle_option(&g_misc_weapons_in_apartment, "Weapons In Apartment");
	add_toggle_option(&g_misc_weapons_in_casino, "Weapons In Casino");
	add_toggle_option(&g_misc_player_join_leave_notify, "Notify On Player Join/Leave");
	add_toggle_option(&g_misc_global_teleport_animation, "Global Teleport Camera");
}

void menu_settings_colours_editor() {
	add_editor_option(true, g_selected_menu_colour_to_edit->r, &g_selected_menu_colour_to_edit->r, 0, 255, 1, "Red");
	add_editor_option(true, g_selected_menu_colour_to_edit->g, &g_selected_menu_colour_to_edit->g, 0, 255, 1, "Green");
	add_editor_option(true, g_selected_menu_colour_to_edit->b, &g_selected_menu_colour_to_edit->b, 0, 255, 1, "Blue");
	add_editor_option(true, g_selected_menu_colour_to_edit->a, &g_selected_menu_colour_to_edit->a, 0, 255, 1, "Alpha");
}
void menu_settings_colours() {
	if (add_submenu_option(menu_settings_colours_editor, "Header Rect")) { g_selected_menu_colour_to_edit = &g_menu_header_colour; }
	if (add_submenu_option(menu_settings_colours_editor, "Header Text")) { g_selected_menu_colour_to_edit = &g_menu_header_text_colour; }
	if (add_submenu_option(menu_settings_colours_editor, "Background Rect")) { g_selected_menu_colour_to_edit = &g_menu_background_colour; }
	if (add_submenu_option(menu_settings_colours_editor, "Option Text")) { g_selected_menu_colour_to_edit = &g_menu_option_text_colour; }
	if (add_submenu_option(menu_settings_colours_editor, "Selected Option Text")) { g_selected_menu_colour_to_edit = &g_menu_selected_option_text_colour; }
	if (add_submenu_option(menu_settings_colours_editor, "Scroll Bar Rect")) { g_selected_menu_colour_to_edit = &g_menu_scroll_bar_colour; }
	if (add_submenu_option(menu_settings_colours_editor, "Footer Rect")) { g_selected_menu_colour_to_edit = &g_menu_footer_colour; }
	if (add_submenu_option(menu_settings_colours_editor, "Footer Sprite Arrows")) { g_selected_menu_colour_to_edit = &g_menu_footer_arrows_colour; }
	if (add_submenu_option(menu_settings_colours_editor, "Footer Info Text")) { g_selected_menu_colour_to_edit = &g_menu_footer_text_colour; }
	if (add_submenu_option(menu_settings_colours_editor, "Variable Editor Sprite Arrows")) { g_selected_menu_colour_to_edit = &g_menu_variable_arrows_colour; }
	if (add_submenu_option(menu_settings_colours_editor, "Submenu Accent Rect")) { g_selected_menu_colour_to_edit = &g_menu_submenu_accent_colour; }
	if (add_submenu_option(menu_settings_colours_editor, "Toggle Sprite Circle ~c~(On)")) { g_selected_menu_colour_to_edit = &g_menu_toggle_on_colour; }
	if (add_submenu_option(menu_settings_colours_editor, "Toggle Sprite Circle ~c~(Off)")) { g_selected_menu_colour_to_edit = &g_menu_toggle_off_colour; }
	if (add_submenu_option(menu_settings_colours_editor, "Break Text")) { g_selected_menu_colour_to_edit = &g_menu_break_option_colour; }
}
void menu_settings_themes() {
	if (add_text_option("Classic ~c~(1.2 - 1.3)")) {

		g_menu_banner_texture = "quantum_header_new";
		g_menu_banner_pos_x_cache = 0.8700f;
		g_menu_banner_pos_y_cache = 0.0650f;
		g_menu_banner_size_x = 0.2000f;
		g_menu_banner_size_y = 0.0970f;
		g_menu_text_padding = 0.0035f;
		g_menu_text_offset = 0.0145f;
		g_menu_header_colour = rgba(10, 20, 30, 255);
		g_menu_header_text_colour = rgba(66, 225, 221, 255);
		g_menu_background_colour = rgba(10, 20, 30, 170);
		g_menu_option_text_colour = rgba(255, 255, 255, 255);
		g_menu_selected_option_text_colour = rgba(66, 225, 221, 255);
		g_menu_scroll_bar_colour = rgba(10, 20, 30, 255);
		g_menu_footer_colour = rgba(10, 20, 30, 255);
		g_menu_footer_arrows_colour = rgba(66, 225, 221, 255);
		g_menu_footer_text_colour = rgba(66, 225, 221, 255);
		g_menu_variable_arrows_colour = rgba(66, 225, 221, 255);
		g_menu_submenu_accent_colour = rgba(66, 225, 221, 110);
		g_menu_toggle_on_colour = rgba(66, 225, 221, 255);
		g_menu_toggle_off_colour = rgba(210, 50, 90, 255);
		g_menu_break_option_colour = rgba(140, 140, 140, 255);
	}
	if (add_text_option("Dark")) {

		g_menu_banner_texture = "quantum_header_glitch";
		g_menu_banner_pos_x_cache = 0.8700f;
		g_menu_banner_pos_y_cache = 0.0650f;
		g_menu_banner_size_x = 0.2000f;
		g_menu_banner_size_y = 0.0970f;
		g_menu_text_padding = 0.0035f;
		g_menu_text_offset = 0.0145f;

		g_menu_header_colour = rgba(0, 0, 0, 255);
		g_menu_header_text_colour = rgba(255, 255, 255, 255);
		g_menu_background_colour = rgba(0, 0, 0, 255);
		g_menu_option_text_colour = rgba(255, 255, 255, 255);
		g_menu_selected_option_text_colour = rgba(0, 0, 0, 255);
		g_menu_scroll_bar_colour = rgba(255, 255, 255, 255);
		g_menu_footer_colour = rgba(0, 0, 0, 255);
		g_menu_footer_arrows_colour = rgba(255, 255, 255, 255);
		g_menu_footer_text_colour = rgba(255, 255, 255, 255);
		g_menu_variable_arrows_colour = rgba(0, 0, 0, 255);
		g_menu_submenu_accent_colour = rgba(255, 255, 255, 110);
		g_menu_toggle_on_colour = rgba(50, 210, 90, 255);
		g_menu_toggle_off_colour = rgba(210, 50, 90, 255);
		g_menu_break_option_colour = rgba(140, 140, 140, 255);
	}
	if (add_text_option("Light Purple")) {

		g_menu_banner_texture = "quantum_header_new";
		g_menu_banner_pos_x_cache = 0.8700f;
		g_menu_banner_pos_y_cache = 0.0650f;
		g_menu_banner_size_x = 0.2000f;
		g_menu_banner_size_y = 0.0970f;
		g_menu_text_padding = 0.0035f;
		g_menu_text_offset = 0.0145f;

		g_menu_header_colour = rgba(255, 255, 255, 255);
		g_menu_header_text_colour = rgba(100, 50, 255, 255);
		g_menu_background_colour = rgba(0, 0, 0, 60);
		g_menu_option_text_colour = rgba(255, 255, 255, 255);
		g_menu_selected_option_text_colour = rgba(100, 50, 255, 255);
		g_menu_scroll_bar_colour = rgba(255, 255, 255, 255);
		g_menu_footer_colour = rgba(255, 255, 255, 255);
		g_menu_footer_arrows_colour = rgba(100, 50, 255, 255);
		g_menu_footer_text_colour = rgba(100, 50, 255, 255);
		g_menu_variable_arrows_colour = rgba(100, 50, 255, 255);
		g_menu_submenu_accent_colour = rgba(100, 50, 255, 255);
		g_menu_toggle_on_colour = rgba(100, 50, 255, 255);
		g_menu_toggle_off_colour = rgba(210, 50, 90, 255);
		g_menu_break_option_colour = rgba(140, 140, 140, 255);
	}
}
void menu_settings() {
	add_submenu_option(menu_settings_colours, "Menu Colour");
	add_submenu_option(menu_settings_themes, "Menu Themes");
	add_editor_option(true, g_menu_banner_pos_x_cache, &g_menu_banner_pos_x_cache, 0.0f, 1.0f, 0.01f, "Menu X Pos");
	add_editor_option(true, g_menu_banner_pos_y_cache, &g_menu_banner_pos_y_cache, 0.0f, 1.0f, 0.01f, "Menu Y Pos");
	add_editor_option(true, g_menu_banner_size_x, &g_menu_banner_size_x, 0.0f, 1.0f, 0.001f, "Menu Width");
	add_editor_option(true, g_menu_scroll_bar_smoothness, &g_menu_scroll_bar_smoothness, 4.0f, 20.0f, 0.01f, "Scroll Bar Smoothness");
	if (add_text_option("Unload")) 
	{
		g_running = false;
	}
}

void menu_main() {
	add_submenu_option(menu_self, "Self");
	add_submenu_option(menu_weapon, "Weapon");
	add_submenu_option(menu_protection, "Protection");
	add_submenu_option(menu_network, "Network");
	add_text_option("Pedestrian"); //g_loaded_list_file_peds_did_load = load_list_file("ped_models", &g_loaded_list_file_peds);
	add_submenu_option(menu_vehicle, "Vehicle");
	add_text_option("Object"); //g_loaded_list_file_objects_did_load = load_list_file("obj_models", &g_loaded_list_file_objects);
	add_submenu_option(menu_teleport, "Teleport");
	add_submenu_option(menu_recovery, "Recovery");
	add_submenu_option(menu_world, "World");
	add_submenu_option(menu_misc, "Miscellaneous");
	add_submenu_option(menu_settings, "Settings");
}

void update_user_input() {
	UI::HIDE_HELP_TEXT_THIS_FRAME();
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(10);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(6);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(7);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(9);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(8);
	CAM::SET_CINEMATIC_BUTTON_ACTIVE(1);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, INPUT_CURSOR_SCROLL_UP);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, INPUT_CURSOR_SCROLL_DOWN);
	CONTROLS::DISABLE_CONTROL_ACTION(0, INPUT_HUD_SPECIAL, TRUE);
	CONTROLS::DISABLE_CONTROL_ACTION(0, INPUT_LOOK_BEHIND, TRUE);
	CONTROLS::DISABLE_CONTROL_ACTION(0, INPUT_NEXT_CAMERA, TRUE);
	CONTROLS::DISABLE_CONTROL_ACTION(0, INPUT_VEH_SELECT_NEXT_WEAPON, TRUE);
	CONTROLS::DISABLE_CONTROL_ACTION(0, INPUT_VEH_CIN_CAM, TRUE);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_ACCEPT, TRUE);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_CANCEL, TRUE);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_LEFT, TRUE);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_RIGHT, TRUE);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_DOWN, TRUE);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_UP, TRUE);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_ACCEPT, TRUE);
	CONTROLS::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_FRANKLIN, TRUE);
	CONTROLS::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_MICHAEL, TRUE);
	CONTROLS::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_TREVOR, TRUE);
	CONTROLS::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_MULTIPLAYER, TRUE);
	CONTROLS::DISABLE_CONTROL_ACTION(0, INPUT_CHARACTER_WHEEL, TRUE);
	CONTROLS::DISABLE_CONTROL_ACTION(0, INPUT_PHONE, TRUE);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_CELLPHONE_CANCEL, TRUE);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_CELLPHONE_SELECT, TRUE);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_CELLPHONE_UP, TRUE);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_CELLPHONE_DOWN, TRUE);

	if (KEYBOARD::IS_KEYBOARD_INPUT_JUST_PRESSED(KeyboardMenuSelect)) // sel
		g_option_select_pressed = true;

	if (KEYBOARD::IS_KEYBOARD_INPUT_JUST_PRESSED(KeyboardMenuBack)) // back
		pop_menu();

	if (KEYBOARD::IS_KEYBOARD_INPUT_JUST_PRESSED(VK_F3)) // alt
		g_option_alt_pressed = true;

	if (KEYBOARD::IS_KEYBOARD_INPUT_JUST_PRESSED(KeyboardMenuNavLeft)) { // left
		g_option_left_pressed = true;
	}
	else if (KEYBOARD::IS_KEYBOARD_INPUT_PRESSED(KeyboardMenuNavLeft)) { // left
		g_menu_scroll_timer[3].start(500);
		if (g_menu_scroll_timer[3].is_ready()) {
			g_option_left_pressed = true;
		}
	}
	else { g_menu_scroll_timer[3].reset(); }

	if (KEYBOARD::IS_KEYBOARD_INPUT_JUST_PRESSED(KeyboardMenuNavRight)) { // right
		g_option_right_pressed = true;
	}
	else if (KEYBOARD::IS_KEYBOARD_INPUT_PRESSED(KeyboardMenuNavRight)) { // right
		g_menu_scroll_timer[4].start(500);
		if (g_menu_scroll_timer[4].is_ready()) {
			g_option_right_pressed = true;
		}
	}
	else { g_menu_scroll_timer[4].reset(); }

	if (KEYBOARD::IS_KEYBOARD_INPUT_JUST_PRESSED(KeyboardMenuNavDown) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, INPUT_CURSOR_SCROLL_DOWN)) { // down
		g_option_down_pressed = true;
		CURRENT_OPTION++;
		if (CURRENT_OPTION > OPTION_COUNT)
			CURRENT_OPTION = 1;
	}
	else if (KEYBOARD::IS_KEYBOARD_INPUT_PRESSED(KeyboardMenuNavDown)) { // down
		g_menu_scroll_timer[1].start(500);
		if (g_menu_scroll_timer[1].is_ready()) {
			g_menu_scroll_timer[0].start(40);
			if (g_menu_scroll_timer[0].is_ready()) {
				g_option_down_pressed = true;
				CURRENT_OPTION++;
				if (CURRENT_OPTION > OPTION_COUNT)
					CURRENT_OPTION = 1;
				g_menu_scroll_timer[0].reset();
			}
		}
	}
	else { g_menu_scroll_timer[1].reset(); }

	if (KEYBOARD::IS_KEYBOARD_INPUT_JUST_PRESSED(KeyboardMenuNavUp) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, INPUT_CURSOR_SCROLL_UP)) { // up
		g_option_up_pressed = true;
		CURRENT_OPTION--;
		if (CURRENT_OPTION < 1)
			CURRENT_OPTION = OPTION_COUNT;
	}
	if (KEYBOARD::IS_KEYBOARD_INPUT_PRESSED(KeyboardMenuNavUp)) { // up
		g_menu_scroll_timer[2].start(500);
		if (g_menu_scroll_timer[2].is_ready()) {
			g_menu_scroll_timer[0].start(40);
			if (g_menu_scroll_timer[0].is_ready()) {
				g_option_up_pressed = true;
				CURRENT_OPTION--;
				if (CURRENT_OPTION < 1)
					CURRENT_OPTION = OPTION_COUNT;
				g_menu_scroll_timer[0].reset();
			}
		}
	}
	else { g_menu_scroll_timer[2].reset(); }
}

void render_menu() {
	if (KEYBOARD::IS_KEYBOARD_INPUT_JUST_PRESSED(KeyboardMenuOpen))
		g_menu_is_open = !g_menu_is_open;
	if (g_push_menu_cxt) {
		g_menu_cxt_stack.push(g_menu_cxt_to_push);
		g_push_menu_cxt = false;
	}

	auto sizee = GetSpriteScale(0.65f);
	if (g_menu_is_open) {
		update_user_input();
		g_menu_banner_pos_x_cache = g_menu_banner_pos_x;
		g_menu_banner_pos_y_cache = g_menu_banner_pos_y;
		OPTION_COUNT = NULL;

		if (g_menu_cxt_stack.top().m_cxt_fn != nullptr)
			g_menu_cxt_stack.top().m_cxt_fn();

		if (g_was_texture_file_loaded) {
			draw_rect(g_menu_banner_pos_x, g_menu_banner_pos_y, g_menu_banner_size_x, g_menu_banner_size_y, g_menu_header_colour);
			draw_sprite("Evac", "Evac", g_menu_banner_pos_x, g_menu_banner_pos_y, g_menu_banner_size_x, g_menu_banner_size_y, 0.0f, g_menu_header_text_colour);
		}
		else {
			draw_rect(g_menu_banner_pos_x, g_menu_banner_pos_y, g_menu_banner_size_x, g_menu_banner_size_y, g_menu_header_colour);
			draw_text("Quantum", g_menu_banner_pos_x, g_menu_banner_pos_y - 0.025f, 1, 1.0f, g_menu_header_text_colour, true, false, false);
		}

		std::stringstream ss;
		ss << CURRENT_OPTION << " / " << OPTION_COUNT;
		auto sizee = GetSpriteScale(0.025f);
		if (OPTION_COUNT > MAX_OPTIONS) {
			draw_text(ss.str(), g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - g_menu_text_padding, g_menu_banner_pos_y + (g_menu_banner_size_y / 6.0f) + ((g_menu_banner_size_y / 3.0f) / 2.0f) + (MAX_OPTIONS + 1) * (g_menu_banner_size_y / 3.0f) - (g_menu_text_offset * 0.75f), 4, 0.275f, g_menu_footer_text_colour, false, true, false);
			draw_text(MENU_TITLE, g_menu_banner_pos_x - (g_menu_banner_size_x / 2.0f) + g_menu_text_padding, g_menu_banner_pos_y + (g_menu_banner_size_y / 6.0f) + ((g_menu_banner_size_y / 3.0f) / 2.0f) + (MAX_OPTIONS + 1) * (g_menu_banner_size_y / 3.0f) - (g_menu_text_offset * 0.75f), 4, 0.275f, g_menu_footer_text_colour, false, false, false);
			draw_rect(g_menu_banner_pos_x, g_menu_banner_pos_y + (g_menu_banner_size_y / 6.0f) + ((g_menu_banner_size_y / 3.0f) / 2.0f) + (MAX_OPTIONS + 1) * (g_menu_banner_size_y / 3.0f), g_menu_banner_size_x, (g_menu_banner_size_y / 3.0f), g_menu_footer_colour);
			draw_sprite("commonmenu", "shop_arrows_upanddown", g_menu_banner_pos_x, g_menu_banner_pos_y + (g_menu_banner_size_y / 6.0f) + ((g_menu_banner_size_y / 3.0f) / 2.0f) + (MAX_OPTIONS + 1) * (g_menu_banner_size_y / 3.0f), sizee.x, sizee.y, 0.0f, g_menu_footer_arrows_colour);
			draw_rect(g_menu_banner_pos_x, g_menu_banner_pos_y + (g_menu_banner_size_y / 6.0f) + ((MAX_OPTIONS * (g_menu_banner_size_y / 3.0f)) / 2.0f) + (g_menu_banner_size_y / 3.0f), g_menu_banner_size_x, (g_menu_banner_size_y / 3.0f) * MAX_OPTIONS, g_menu_background_colour);
		}
		else {
			draw_text(ss.str(), g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - g_menu_text_padding, g_menu_banner_pos_y + (g_menu_banner_size_y / 6.0f) + ((g_menu_banner_size_y / 3.0f) / 2.0f) + (OPTION_COUNT + 1) * (g_menu_banner_size_y / 3.0f) - (g_menu_text_offset * 0.75f), 4, 0.275f, g_menu_footer_text_colour, false, true, false);
			draw_text(MENU_TITLE, g_menu_banner_pos_x - (g_menu_banner_size_x / 2.0f) + g_menu_text_padding, g_menu_banner_pos_y + (g_menu_banner_size_y / 6.0f) + ((g_menu_banner_size_y / 3.0f) / 2.0f) + (OPTION_COUNT + 1) * (g_menu_banner_size_y / 3.0f) - (g_menu_text_offset * 0.75f), 4, 0.275f, g_menu_footer_text_colour, false, false, false);
			draw_rect(g_menu_banner_pos_x, g_menu_banner_pos_y + (g_menu_banner_size_y / 6.0f) + ((g_menu_banner_size_y / 3.0f) / 2.0f) + (OPTION_COUNT + 1) * (g_menu_banner_size_y / 3.0f), g_menu_banner_size_x, (g_menu_banner_size_y / 3.0f), g_menu_footer_colour);
			draw_sprite("commonmenu", "shop_arrows_upanddown", g_menu_banner_pos_x, g_menu_banner_pos_y + (g_menu_banner_size_y / 6.0f) + ((g_menu_banner_size_y / 3.0f) / 2.0f) + (OPTION_COUNT + 1) * (g_menu_banner_size_y / 3.0f), sizee.x, sizee.y, 0.0f, g_menu_footer_arrows_colour);
			draw_rect(g_menu_banner_pos_x, g_menu_banner_pos_y + (g_menu_banner_size_y / 6.0f) + ((OPTION_COUNT * (g_menu_banner_size_y / 3.0f)) / 2.0f) + (g_menu_banner_size_y / 3.0f), g_menu_banner_size_x, (g_menu_banner_size_y / 3.0f) * OPTION_COUNT, g_menu_background_colour);
		}

		//Selector
		g_menu_scroll_bar_dest = CURRENT_OPTION > MAX_OPTIONS ? g_menu_banner_pos_y + (g_menu_banner_size_y / 2.0f) - (g_menu_banner_size_y / 6.0f) + (MAX_OPTIONS * (g_menu_banner_size_y / 3.0f)) : g_menu_banner_pos_y + (g_menu_banner_size_y / 2.0f) - (g_menu_banner_size_y / 6.0f) + (CURRENT_OPTION * (g_menu_banner_size_y / 3.0f));
		std::float_t scroll_bar_inc = abs(g_menu_scroll_bar_pos - g_menu_scroll_bar_dest) / g_menu_scroll_bar_smoothness;
		if (g_menu_scroll_bar_pos < g_menu_scroll_bar_dest && scroll_bar_inc != 0.0f)
			g_menu_scroll_bar_pos += scroll_bar_inc;
		else if (g_menu_scroll_bar_pos > g_menu_scroll_bar_dest && scroll_bar_inc != 0.0f)
			g_menu_scroll_bar_pos -= scroll_bar_inc;
		draw_rect(g_menu_banner_pos_x, g_menu_scroll_bar_pos, g_menu_banner_size_x, (g_menu_banner_size_y / 3.0f), g_menu_scroll_bar_colour);
		g_menu_banner_pos_x = g_menu_banner_pos_x_cache;
		g_menu_banner_pos_y = g_menu_banner_pos_y_cache;
	}
	g_option_select_pressed = false;
	g_option_up_pressed = false;
	g_option_down_pressed = false;
	g_option_left_pressed = false;
	g_option_right_pressed = false;
	g_option_alt_pressed = false;
}
void Main() {
	if (!g_was_texture_file_load_attempted) {
		g_was_texture_file_loaded = register_game_file("C:\\Evac\\Evac.ytd", "Evac.ytd");
		g_was_texture_file_load_attempted = true;
	}
	if (g_push_main_menu) {
		push_menu(menu_main, "HOME");
		g_push_main_menu = false;
	}
	render_menu();
	menu_loops_handler();
}

void NTick()
{
	Main();
}

void NFunc()
{
	while (true)
	{
		NTick();
		Script::GetCurrent()->ScriptYield();
	}
}