#pragma once
#include "natives.h"
#include "rage/Script.hpp"
#include <inaddr.h>

std::uint64_t hook_virtual(std::uint64_t* table, void* destination, std::uint64_t index) {
	BOOL return_val = FALSE;
	DWORD old_protect;
	std::uint64_t dest = (std::uint64_t)(destination);
	std::uint64_t* entry = &table[index];
	std::uint64_t original = *entry;
	::VirtualProtect((void*)entry, sizeof(entry), PAGE_EXECUTE_READWRITE, &old_protect);
	return_val = ((*entry = dest) == dest);
	::VirtualProtect((void*)entry, sizeof(entry), old_protect, &old_protect);

	if (!return_val) printf("Cant virtual hook: %s\n", index);
	return return_val ? original : NULL;
}
bool hook_script_native(char* script_name, std::uint64_t native_hash, void* destination, std::uint64_t* original) {
	std::uint64_t handler = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint64_t, std::uint64_t))GTA_GET_NATIVE_HANDLER), GTA_NATIVE_REGISTRATION, native_hash);
	if (handler == NULL) return false;
	std::uint64_t table = *(std::uint64_t*)(GTA_STREAMED_SCRIPTS);
	if (table == NULL) return false;
	for (std::uint32_t i = 0; i < *(std::uint32_t*)(GTA_STREAMED_SCRIPTS + 0x48); i++) {
		std::uint64_t script_program = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint64_t, std::uint32_t))(*(std::uint64_t*)(table + 0x68))), GTA_STREAMED_SCRIPTS, i);
		if (script_program) {
			if (!strcmp(*(char**)(script_program + 0x60), script_name)) {
				for (std::uint32_t j = 0; j < *(std::uint32_t*)(script_program + 0x2C); j++) {
					std::uint64_t* script_handlers = *(std::uint64_t**)(script_program + 0x40);
					if (script_handlers[j] == handler) {
						if (original != nullptr) *original = script_handlers[j];
						script_handlers[j] = (std::uint64_t)(destination);
						return true;
					}
				}
			}
		}
	}
	return false;
}
bool register_game_file(std::string path, std::string name) {
	int texture_id;
	ptr.m_FR(&texture_id, path.c_str(), true, name.c_str(), false);
	return true;
}

void push_menu(menu_cxt_fn menu, std::string title, std::int32_t max_options = 13) {
	if (menu != nullptr) {
		std::locale loc;
		g_menu_cxt_to_push.m_current_option = 1;
		g_menu_cxt_to_push.m_max_options = max_options;
		g_menu_cxt_to_push.m_option_count = 0;
		std::stringstream ss;
		for (std::string::size_type i = 0; i < title.length(); ++i)
			ss << std::toupper(title[i], loc);
		g_menu_cxt_to_push.m_title = ss.str();
		g_menu_cxt_to_push.m_cxt_fn = menu;
		g_push_menu_cxt = true;
	}
}
void pop_menu() {
	if (g_menu_cxt_stack.size() > 1) g_menu_cxt_stack.pop();
	else g_menu_is_open = false;
}
void init_menu(menu_cxt_fn menu, std::string title) {
	push_menu(menu, title);
}
std::float_t get_text_width(const char* text, bool grotesque, std::int32_t font = -1, std::float_t scale_override = 0.0f) {
	UI::_BEGIN_TEXT_COMMAND_WIDTH("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	std::float_t scale = 0.35f;
	UI::SET_TEXT_FONT(0);
	if (grotesque) {
		scale = 0.425f;
		UI::SET_TEXT_FONT(4);
	}
	if (font != -1) {
		scale = scale_override;
		UI::SET_TEXT_FONT(font);
	}
	UI::SET_TEXT_SCALE(0.0f, scale);
	return UI::_END_TEXT_COMMAND_GET_WIDTH(TRUE);
}

Vector2 GetSpriteScale(float size)
{
	int x;
	int y;
	GRAPHICS::_GET_ACTIVE_SCREEN_RESOLUTION(&x, &y);

	return { (static_cast<float>(y) / static_cast<float>(x)) * size, size };
}

void draw_sprite(const char* dictionary, const char* texture, std::float_t x, std::float_t y, std::float_t width, std::float_t height, std::float_t rot, rgba col, std::float_t w = 1.0f, std::float_t h = 1.0f) {
	if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(dictionary))
	{
		float size = 30.f;
		auto sizee = GetSpriteScale(size);
		GRAPHICS::DRAW_SPRITE(dictionary, texture, x, y, width, height, rot, col.r, col.g, col.b, col.a);
	}
	else
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(dictionary, false);
	}

}
void map_notification(std::string image, std::string title, std::string subtitle, std::string body) {
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(body.c_str());
	if (!image.empty() && !title.empty() && !subtitle.empty())
		UI::_SET_NOTIFICATION_MESSAGE_2(image.c_str(), image.c_str(), FALSE, NULL, title.c_str(), subtitle.c_str());
	UI::_DRAW_NOTIFICATION_2(FALSE, FALSE);
}
void print_notification(int ticks, std::string text) {
	UI::CLEAR_PRINTS();
	UI::BEGIN_TEXT_COMMAND_PRINT("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
	UI::END_TEXT_COMMAND_PRINT(ticks, TRUE);
}
void draw_text(std::string text, std::float_t x, std::float_t y, std::int32_t font, std::float_t scale, rgba col, bool centered, bool right_justified, bool outlined) {
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(0.0f, scale);
	UI::SET_TEXT_COLOUR(col.r, col.g, col.b, col.a);
	if (right_justified) UI::SET_TEXT_WRAP(0.0f, x);
	else UI::SET_TEXT_WRAP(0.0f, 1.0f);
	UI::SET_TEXT_CENTRE(centered);
	if (outlined) UI::SET_TEXT_OUTLINE();
	UI::SET_TEXT_RIGHT_JUSTIFY(right_justified);
	UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
	UI::END_TEXT_COMMAND_DISPLAY_TEXT(x, y);
}
void draw_rect(std::float_t x, std::float_t y, std::float_t w, std::float_t h, rgba col) {
	GRAPHICS::DRAW_RECT(x, y, w, h, col.r, col.g, col.b, col.a);
}
bool is_mouse_in_box(std::float_t x, std::float_t y, std::float_t w, std::float_t h) {
	std::float_t mouse_x = CONTROLS::GET_DISABLED_CONTROL_NORMAL(2, INPUT_CURSOR_X);
	std::float_t mouse_y = CONTROLS::GET_DISABLED_CONTROL_NORMAL(2, INPUT_CURSOR_Y);
	return (mouse_x >= x - w / 2.0f && mouse_x <= x + w / 2.0f) && (mouse_y > y - h / 2.0f && mouse_y < y + h / 2.0f);
}
bool add_text_option(std::string text) {
	bool return_value = false;
	if (CONTEXT_STACK_VALID) {
		OPTION_COUNT++;
		if (CURRENT_OPTION <= MAX_OPTIONS && OPTION_COUNT <= MAX_OPTIONS) {
			draw_text(text, g_menu_banner_pos_x - (g_menu_banner_size_x / 2.0f) + g_menu_text_padding, g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, FALSE, FALSE);
		}
		else if ((OPTION_COUNT > (CURRENT_OPTION - MAX_OPTIONS)) && OPTION_COUNT <= CURRENT_OPTION) {
			draw_text(text, g_menu_banner_pos_x - (g_menu_banner_size_x / 2.0f) + g_menu_text_padding, g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, FALSE, FALSE);
		}
		if (CURRENT_OPTION == OPTION_COUNT) {

			if (return_value = g_option_select_pressed) {
				// do stuff
			}
		}
	}
	return return_value;
}
bool add_submenu_option(menu_cxt_fn menu_function, std::string text) {
	bool return_value = false;
	if (CONTEXT_STACK_VALID) {
		OPTION_COUNT++;
		if (CURRENT_OPTION <= MAX_OPTIONS && OPTION_COUNT <= MAX_OPTIONS) {
			draw_text(text, g_menu_banner_pos_x - (g_menu_banner_size_x / 2.0f) + g_menu_text_padding, g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, FALSE, FALSE);
			draw_rect(g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - (g_menu_text_padding / 2.0f), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)), g_menu_text_padding, (g_menu_banner_size_y / 3.0f), g_menu_submenu_accent_colour);
		}
		else if ((OPTION_COUNT > (CURRENT_OPTION - MAX_OPTIONS)) && OPTION_COUNT <= CURRENT_OPTION) {
			draw_text(text, g_menu_banner_pos_x - (g_menu_banner_size_x / 2.0f) + g_menu_text_padding, g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, FALSE, FALSE);
			draw_rect(g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - (g_menu_text_padding / 2.0f), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)), g_menu_text_padding, (g_menu_banner_size_y / 3.0f), g_menu_submenu_accent_colour);
		}
		if (CURRENT_OPTION == OPTION_COUNT) {

			if (return_value = g_option_select_pressed) {
				push_menu(menu_function, text);
			}
		}
	}
	return return_value;
}
void add_break_option(std::string text) {
	if (CONTEXT_STACK_VALID) {
		OPTION_COUNT++;
		if (CURRENT_OPTION <= MAX_OPTIONS && OPTION_COUNT <= MAX_OPTIONS) {
			draw_text(text, g_menu_banner_pos_x, g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 1, 0.35f, g_menu_break_option_colour, TRUE, FALSE, FALSE);
		}
		else if ((OPTION_COUNT > (CURRENT_OPTION - MAX_OPTIONS)) && OPTION_COUNT <= CURRENT_OPTION) {
			draw_text(text, g_menu_banner_pos_x, g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, g_menu_break_option_colour, TRUE, FALSE, FALSE);
		}
		if (CURRENT_OPTION == OPTION_COUNT) {
			if (g_option_up_pressed)
				CURRENT_OPTION--;
			if (g_option_down_pressed)
				CURRENT_OPTION++;
		}
	}
}
bool add_toggle_option(bool* control, std::string text) {
	bool return_value = false;
	if (CONTEXT_STACK_VALID) {
		OPTION_COUNT++;
		auto sizee = GetSpriteScale(0.025f);
		if (CURRENT_OPTION <= MAX_OPTIONS && OPTION_COUNT <= MAX_OPTIONS) {
			draw_text(text, g_menu_banner_pos_x - (g_menu_banner_size_x / 2.0f) + g_menu_text_padding, g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, FALSE, FALSE);
			draw_sprite("timerbars", "circle_checkpoints", g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - (g_menu_text_padding * 2.0f), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)), sizee.x, sizee.y, 0.0f, *control ? g_menu_toggle_on_colour : g_menu_toggle_off_colour, 1.4f, 1.4f);
		}
		else if ((OPTION_COUNT > (CURRENT_OPTION - MAX_OPTIONS)) && OPTION_COUNT <= CURRENT_OPTION) {
			draw_text(text, g_menu_banner_pos_x - (g_menu_banner_size_x / 2.0f) + g_menu_text_padding, g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, FALSE, FALSE);
			draw_sprite("timerbars", "circle_checkpoints", g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - (g_menu_text_padding * 2.0f), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)), sizee.x, sizee.y, 0.0f, *control ? g_menu_toggle_on_colour : g_menu_toggle_off_colour, 1.4f, 1.4f);
		}
		if (CURRENT_OPTION == OPTION_COUNT) {
			if (return_value = g_option_select_pressed) {
				print_notification(7000, text + ":~s~ " + ((*control = !*control) ? "~g~On~s~." : "~r~Off~s~."));
			}
		}
	}
	return return_value;
}
template<typename A, typename B>
bool add_editor_option(bool exec_on_arrow_press, A to_display, B* value_ref, B min, B max, B accuracy, std::string text) {
	bool return_value = false;
	if (CONTEXT_STACK_VALID) {
		std::stringstream ss;
		ss << to_display;
		OPTION_COUNT++;
		auto sizee = GetSpriteScale(0.025f);
		if (CURRENT_OPTION <= MAX_OPTIONS && OPTION_COUNT <= MAX_OPTIONS) {
			draw_text(text, g_menu_banner_pos_x - (g_menu_banner_size_x / 2.0f) + g_menu_text_padding, g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, FALSE, FALSE);
			draw_text(ss.str(), g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - ((CURRENT_OPTION == OPTION_COUNT) ? (g_menu_text_padding * 4.5f) : g_menu_text_padding), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, TRUE, FALSE);
			if (CURRENT_OPTION == OPTION_COUNT) {
				draw_sprite("commonmenu", "arrowright", g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - (g_menu_text_padding * 2.0f), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)), sizee.x, sizee.y, 0.0f, g_menu_variable_arrows_colour);
				draw_sprite("commonmenu", "arrowleft", g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - (g_menu_text_padding * 3.5f), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)), sizee.x, sizee.y, 0.0f, g_menu_variable_arrows_colour);
			}
		}
		else if ((OPTION_COUNT > (CURRENT_OPTION - MAX_OPTIONS)) && OPTION_COUNT <= CURRENT_OPTION) {
			draw_text(text, g_menu_banner_pos_x - (g_menu_banner_size_x / 2.0f) + g_menu_text_padding, g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, FALSE, FALSE);
			draw_text(ss.str(), g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - ((CURRENT_OPTION == OPTION_COUNT) ? (g_menu_text_padding * 4.5f) : g_menu_text_padding), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, TRUE, FALSE);
			if (CURRENT_OPTION == OPTION_COUNT) {
				draw_sprite("commonmenu", "arrowright", g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - (g_menu_text_padding * 2.0f), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)), sizee.x, sizee.y, 0.0f, g_menu_variable_arrows_colour);
				draw_sprite("commonmenu", "arrowleft", g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - (g_menu_text_padding * 3.5f), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)), sizee.x, sizee.y, 0.0f, g_menu_variable_arrows_colour);
			}
		}
		if (CURRENT_OPTION == OPTION_COUNT) {
			if (g_option_left_pressed) {
				*value_ref -= accuracy;
				if (*value_ref < min)
					*value_ref = max;
				exec_on_arrow_press ? return_value = true : return_value = false;
			}
			if (g_option_right_pressed) {
				*value_ref += accuracy;
				if (*value_ref > max)
					*value_ref = min;
				exec_on_arrow_press ? return_value = true : return_value = false;
			}
			if (g_option_select_pressed) {
				exec_on_arrow_press ? return_value = false : return_value = true;
			}
		}
	}
	return return_value;
}
template<typename A, typename B>
bool add_editor_toggle_option(bool* control, A to_display, B* value_ref, B min, B max, B accuracy, std::string text) {
	bool return_value = false; 
	if (CONTEXT_STACK_VALID) {
		std::stringstream ss;
		ss << to_display;
		OPTION_COUNT++;
		auto sizee = GetSpriteScale(0.025f);
		if (CURRENT_OPTION <= MAX_OPTIONS && OPTION_COUNT <= MAX_OPTIONS) {
			draw_text(text, g_menu_banner_pos_x - (g_menu_banner_size_x / 2.0f) + g_menu_text_padding, g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, FALSE, FALSE);
			draw_text(ss.str(), g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - ((CURRENT_OPTION == OPTION_COUNT) ? (g_menu_text_padding * 6.5f) : (g_menu_text_padding * 3.5f)), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, TRUE, FALSE);
			draw_sprite("timerbars", "circle_checkpoints", g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - (g_menu_text_padding * 2.0f), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)), sizee.x, sizee.y, 0.0f, *control ? g_menu_toggle_on_colour : g_menu_toggle_off_colour, 1.4f, 1.4f);
			if (CURRENT_OPTION == OPTION_COUNT) {
				draw_sprite("commonmenu", "arrowright", g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - (g_menu_text_padding * 4.0f), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)), sizee.x, sizee.y, 0.0f, g_menu_variable_arrows_colour);
				draw_sprite("commonmenu", "arrowleft", g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - (g_menu_text_padding * 5.5f), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)), sizee.x, sizee.y, 0.0f, g_menu_variable_arrows_colour);
			}
		}
		else if ((OPTION_COUNT > (CURRENT_OPTION - MAX_OPTIONS)) && OPTION_COUNT <= CURRENT_OPTION) {
			draw_text(text, g_menu_banner_pos_x - (g_menu_banner_size_x / 2.0f) + g_menu_text_padding, g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, FALSE, FALSE);
			draw_text(ss.str(), g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - ((CURRENT_OPTION == OPTION_COUNT) ? (g_menu_text_padding * 6.5f) : (g_menu_text_padding * 3.5f)), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, TRUE, FALSE);
			draw_sprite("timerbars", "circle_checkpoints", g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - (g_menu_text_padding * 2.0f), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)), sizee.x, sizee.y, 0.0f, *control ? g_menu_toggle_on_colour : g_menu_toggle_off_colour, 1.4f, 1.4f);
			if (CURRENT_OPTION == OPTION_COUNT) {
				draw_sprite("commonmenu", "arrowright", g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - (g_menu_text_padding * 4.0f), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)), sizee.x, sizee.y, 0.0f, g_menu_variable_arrows_colour);
				draw_sprite("commonmenu", "arrowleft", g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - (g_menu_text_padding * 5.5f), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)), sizee.x, sizee.y, 0.0f, g_menu_variable_arrows_colour);
			}
		}
		if (CURRENT_OPTION == OPTION_COUNT) {
			if (g_option_left_pressed) {
				*value_ref -= accuracy;
				if (*value_ref < min)
					*value_ref = max;
			}
			if (g_option_right_pressed) {
				*value_ref += accuracy;
				if (*value_ref > max)
					*value_ref = min;
			}
			if (return_value = g_option_select_pressed) {
				print_notification(7000, text + ":~s~ " + ((*control = !*control) ? "~g~On~s~." : "~r~Off~s~."));
			}
		}
	}
	return return_value;
}
bool add_string_array_option(bool exec_on_arrow_press, std::string* array, std::int32_t array_size, std::int32_t* value_ref, std::string text) {
	bool return_value = false;
	if (CONTEXT_STACK_VALID) {
		std::stringstream ss;
		ss << array[*value_ref] << " ~c~[" << *value_ref + 1 << "/" << array_size << "]";
		OPTION_COUNT++;
		auto sizee = GetSpriteScale(0.025f);
		if (CURRENT_OPTION <= MAX_OPTIONS && OPTION_COUNT <= MAX_OPTIONS) {
			draw_text(text, g_menu_banner_pos_x - (g_menu_banner_size_x / 2.0f) + g_menu_text_padding, g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, FALSE, FALSE);
			draw_text(ss.str(), g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - ((CURRENT_OPTION == OPTION_COUNT) ? (g_menu_text_padding * 4.5f) : g_menu_text_padding), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, TRUE, FALSE);
			if (CURRENT_OPTION == OPTION_COUNT) {
				draw_sprite("commonmenu", "arrowright", g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - (g_menu_text_padding * 2.0f), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)), sizee.x, sizee.y, 0.0f, g_menu_variable_arrows_colour);
				draw_sprite("commonmenu", "arrowleft", g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - (g_menu_text_padding * 3.5f), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)), sizee.x, sizee.y, 0.0f, g_menu_variable_arrows_colour);
			}
		}
		else if ((OPTION_COUNT > (CURRENT_OPTION - MAX_OPTIONS)) && OPTION_COUNT <= CURRENT_OPTION) {
			draw_text(text, g_menu_banner_pos_x - (g_menu_banner_size_x / 2.0f) + g_menu_text_padding, g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, FALSE, FALSE);
			draw_text(ss.str(), g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - ((CURRENT_OPTION == OPTION_COUNT) ? (g_menu_text_padding * 4.5f) : g_menu_text_padding), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, TRUE, FALSE);
			if (CURRENT_OPTION == OPTION_COUNT) {
				draw_sprite("commonmenu", "arrowright", g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - (g_menu_text_padding * 2.0f), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)), sizee.x, sizee.y, 0.0f, g_menu_variable_arrows_colour);
				draw_sprite("commonmenu", "arrowleft", g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - (g_menu_text_padding * 3.5f), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)), sizee.x, sizee.y, 0.0f, g_menu_variable_arrows_colour);
			}
		}
		if (CURRENT_OPTION == OPTION_COUNT) {
			if (g_option_left_pressed) {
				if (-- * value_ref < 0) *value_ref = (array_size - 1);
				exec_on_arrow_press ? return_value = true : return_value = false;
			}
			if (g_option_right_pressed) {
				if (++ * value_ref > (array_size - 1)) *value_ref = 0;
				exec_on_arrow_press ? return_value = true : return_value = false;
			}
			if (g_option_select_pressed) {
				exec_on_arrow_press ? return_value = false : return_value = true;
			}
		}
	}
	return return_value;
}
bool add_string_array_toggle_option(bool* control, std::string* array, std::int32_t array_size, std::int32_t* value_ref, std::string text) {
	bool return_value = false;
	if (CONTEXT_STACK_VALID) {
		std::stringstream ss;
		ss << array[*value_ref] << " ~c~[" << *value_ref + 1 << "/" << array_size << "]";
		OPTION_COUNT++;
		auto sizee = GetSpriteScale(0.025f);
		if (CURRENT_OPTION <= MAX_OPTIONS && OPTION_COUNT <= MAX_OPTIONS) {
			draw_text(text, g_menu_banner_pos_x - (g_menu_banner_size_x / 2.0f) + g_menu_text_padding, g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, FALSE, FALSE);
			draw_text(ss.str(), g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - ((CURRENT_OPTION == OPTION_COUNT) ? (g_menu_text_padding * 6.5f) : (g_menu_text_padding * 3.5f)), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, TRUE, FALSE);
			draw_sprite("timerbars", "circle_checkpoints", g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - (g_menu_text_padding * 2.0f), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)), sizee.x, sizee.y, 0.0f, *control ? g_menu_toggle_on_colour : g_menu_toggle_off_colour, 1.4f, 1.4f);
			if (CURRENT_OPTION == OPTION_COUNT) {
				draw_sprite("commonmenu", "arrowright", g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - (g_menu_text_padding * 4.0f) - 0.001f, g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)), sizee.x, sizee.y, 0.0f, g_menu_variable_arrows_colour);
				draw_sprite("commonmenu", "arrowleft", g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - (g_menu_text_padding * 5.5f) - 0.001f, g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)), sizee.x, sizee.y, 0.0f, g_menu_variable_arrows_colour);
			}
		}
		else if ((OPTION_COUNT > (CURRENT_OPTION - MAX_OPTIONS)) && OPTION_COUNT <= CURRENT_OPTION) {
			draw_text(text, g_menu_banner_pos_x - (g_menu_banner_size_x / 2.0f) + g_menu_text_padding, g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, FALSE, FALSE);
			draw_text(ss.str(), g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - ((CURRENT_OPTION == OPTION_COUNT) ? (g_menu_text_padding * 6.5f) : (g_menu_text_padding * 3.5f)), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, TRUE, FALSE);
			draw_sprite("timerbars", "circle_checkpoints", g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - (g_menu_text_padding * 2.0f), g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)), sizee.x, sizee.y, 0.0f, *control ? g_menu_toggle_on_colour : g_menu_toggle_off_colour, 1.4f, 1.4f);
			if (CURRENT_OPTION == OPTION_COUNT) {
				draw_sprite("commonmenu", "arrowright", g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - (g_menu_text_padding * 4.0f) - 0.001f, g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)), sizee.x, sizee.y, 0.0f, g_menu_variable_arrows_colour);
				draw_sprite("commonmenu", "arrowleft", g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - (g_menu_text_padding * 5.5f) - 0.001f, g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)), sizee.x, sizee.y, 0.0f, g_menu_variable_arrows_colour);
			}
		}
		if (CURRENT_OPTION == OPTION_COUNT) {
			if (g_option_left_pressed) {
				if (-- * value_ref < 0) *value_ref = (array_size - 1);
			}
			if (g_option_right_pressed) {
				if (++ * value_ref > (array_size - 1)) *value_ref = 0;
			}
			if (return_value = g_option_select_pressed) {
				print_notification(7000, text + " (" + array[*value_ref] + "):~s~ " + ((*control = !*control) ? "~g~On~s~." : "~r~Off~s~."));
			}
		}
	}
	return return_value;
}
bool add_keyboard_option(bool display_output, std::string* output, std::string::size_type length, std::string text) {
	bool return_value = false; 
	if (CONTEXT_STACK_VALID) {
		OPTION_COUNT++;
		if (CURRENT_OPTION <= MAX_OPTIONS && OPTION_COUNT <= MAX_OPTIONS) {
			draw_text(text, g_menu_banner_pos_x - (g_menu_banner_size_x / 2.0f) + g_menu_text_padding, g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, FALSE, FALSE);
			if (display_output)
				draw_text(*output, g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - g_menu_text_padding, g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + (OPTION_COUNT * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, TRUE, FALSE);
		}
		else if ((OPTION_COUNT > (CURRENT_OPTION - MAX_OPTIONS)) && OPTION_COUNT <= CURRENT_OPTION) {
			draw_text(text, g_menu_banner_pos_x - (g_menu_banner_size_x / 2.0f) + g_menu_text_padding, g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, FALSE, FALSE);
			if (display_output)
				draw_text(*output, g_menu_banner_pos_x + (g_menu_banner_size_x / 2.0f) - g_menu_text_padding, g_menu_banner_pos_y + (g_menu_banner_size_y / 3.0f) + ((OPTION_COUNT - (CURRENT_OPTION - MAX_OPTIONS)) * (g_menu_banner_size_y / 3.0f)) - g_menu_text_offset, 4, 0.4f, (CURRENT_OPTION == OPTION_COUNT) ? g_menu_selected_option_text_colour : g_menu_option_text_colour, FALSE, TRUE, FALSE);
		}
		if (CURRENT_OPTION == OPTION_COUNT) {
			if (g_option_select_pressed) {
				GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(TRUE, "FMMC_MPM_NA", "", "", "", "", "", length);

				while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == NULL)
					Script::GetCurrent()->ScriptYield();

				if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT())
					return return_value;

				*output = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();

				return_value = true;
			}
		}
	}
	return return_value;
}

bool load_list_file(std::string name, std::vector<std::string>* out) {
	char appdata_path[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, NULL, appdata_path))) {
		std::ifstream ifs(std::string(appdata_path) + "\\" + "quantumgta" + "\\" + name + ".txt");
		if (ifs.is_open()) {
			std::string s;
			out->clear();
			while (getline(ifs, s))
				out->push_back(s);
			ifs.close();
			return true;
		}
	}
	return false;
}
Vector3 get_gameplay_camera_direction() {
	Vector3 l_cam_rot = CAM::GET_GAMEPLAY_CAM_ROT(NULL);
	FLOAT l_tz = l_cam_rot.z * 0.0174532924f;
	FLOAT l_tx = l_cam_rot.x * 0.0174532924f;
	FLOAT l_num = abs(cos(l_tx));
	l_cam_rot.x = (-sin(l_tz)) * l_num;
	l_cam_rot.y = (cos(l_tz)) * l_num;
	l_cam_rot.z = sin(l_tx);
	return l_cam_rot;
}
Vector3 multiply_vector(Vector3* vec, std::float_t factor) {
	Vector3 result;
	result.x = vec->x * factor;
	result.y = vec->y * factor;
	result.z = vec->z * factor;
	return result;
}
Vector3 add_vectors(Vector3* first, Vector3* second) {
	Vector3 result;
	result.x = first->x + second->x;
	result.y = first->y + second->y;
	result.z = first->z + second->z;
	return result;
}
Vector3 rotation_to_direction(Vector3* a_fRot) {
	Vector3 result;
	std::float_t rad_z = a_fRot->z * 0.0174532924f;
	std::float_t rad_x = a_fRot->x * 0.0174532924f;
	std::float_t factor = std::abs(std::cos(rad_x));
	result.x = -std::sin(rad_z) * factor;
	result.y = std::cos(rad_z) * factor;
	result.z = std::sin(rad_x);
	return result;
}
void draw_box_esp(std::int32_t entity, rgba colour) {
	Vector3 min;
	Vector3 max;
	if (ENTITY::DOES_ENTITY_EXIST(entity)) {
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(entity), &min, &max);
		std::float_t width = max.x * 2.0f;
		std::float_t length = max.y * 2.0f;
		std::float_t depth = max.z * 2.0f;
		Vector3 offset_1 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(entity, (width / 2) * -1, (length / 2), depth / 2);
		Vector3 offset_4 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(entity, width / 2, (length / 2), depth / 2);
		Vector3 offset_5 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(entity, (width / 2) * -1, (length / 2), (depth / 2) * -1);
		Vector3 offset_7 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(entity, width / 2, (length / 2), (depth / 2) * -1);
		Vector3 offset_2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(entity, (width / 2) * -1, (length / 2) * -1, depth / 2);
		Vector3 offset_3 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(entity, width / 2, (length / 2) * -1, depth / 2);
		Vector3 offset_6 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(entity, (width / 2) * -1, (length / 2) * -1, (depth / 2) * -1);
		Vector3 offset_8 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(entity, width / 2, (length / 2) * -1, (depth / 2) * -1);
		GRAPHICS::DRAW_LINE(offset_1.x, offset_1.y, offset_1.z, offset_4.x, offset_4.y, offset_4.z, colour.r, colour.g, colour.b, colour.a);
		GRAPHICS::DRAW_LINE(offset_1.x, offset_1.y, offset_1.z, offset_2.x, offset_2.y, offset_2.z, colour.r, colour.g, colour.b, colour.a);
		GRAPHICS::DRAW_LINE(offset_1.x, offset_1.y, offset_1.z, offset_5.x, offset_5.y, offset_5.z, colour.r, colour.g, colour.b, colour.a);
		GRAPHICS::DRAW_LINE(offset_2.x, offset_2.y, offset_2.z, offset_3.x, offset_3.y, offset_3.z, colour.r, colour.g, colour.b, colour.a);
		GRAPHICS::DRAW_LINE(offset_3.x, offset_3.y, offset_3.z, offset_8.x, offset_8.y, offset_8.z, colour.r, colour.g, colour.b, colour.a);
		GRAPHICS::DRAW_LINE(offset_4.x, offset_4.y, offset_4.z, offset_7.x, offset_7.y, offset_7.z, colour.r, colour.g, colour.b, colour.a);
		GRAPHICS::DRAW_LINE(offset_4.x, offset_4.y, offset_4.z, offset_3.x, offset_3.y, offset_3.z, colour.r, colour.g, colour.b, colour.a);
		GRAPHICS::DRAW_LINE(offset_5.x, offset_5.y, offset_5.z, offset_7.x, offset_7.y, offset_7.z, colour.r, colour.g, colour.b, colour.a);
		GRAPHICS::DRAW_LINE(offset_6.x, offset_6.y, offset_6.z, offset_2.x, offset_2.y, offset_2.z, colour.r, colour.g, colour.b, colour.a);
		GRAPHICS::DRAW_LINE(offset_6.x, offset_6.y, offset_6.z, offset_8.x, offset_8.y, offset_8.z, colour.r, colour.g, colour.b, colour.a);
		GRAPHICS::DRAW_LINE(offset_5.x, offset_5.y, offset_5.z, offset_6.x, offset_6.y, offset_6.z, colour.r, colour.g, colour.b, colour.a);
		GRAPHICS::DRAW_LINE(offset_7.x, offset_7.y, offset_7.z, offset_8.x, offset_8.y, offset_8.z, colour.r, colour.g, colour.b, colour.a);
	}
}
Vector3 get_coords_in_front_of_cam(std::float_t distance) {
	Vector3 pos = CAM::GET_GAMEPLAY_CAM_COORD();
	Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(NULL);
	Vector3 dir = rotation_to_direction(&rot);
	Vector3 dist = multiply_vector(&dir, distance);
	return add_vectors(&pos, &dist);
}
Vector3 get_coords_in_front_of_cam(std::int32_t cam, std::float_t distance) {
	Vector3 pos = CAM::GET_CAM_COORD(cam);
	Vector3 rot = CAM::GET_CAM_ROT(cam, 2);
	Vector3 dir = rotation_to_direction(&rot);
	Vector3 dist = multiply_vector(&dir, distance);
	return add_vectors(&pos, &dist);
}
Vector3 get_offset_from_camera(std::int32_t cam, Vector3 offset) {
	Vector3 pos = CAM::GET_CAM_COORD(cam);
	Vector3 rot = CAM::GET_CAM_ROT(cam, 2);
	Vector3 dir = rotation_to_direction(&rot);

	const double D2R = 0.01745329251994329576923690768489;
	double num1 = cos(rot.y * D2R);

	Vector3 right;
	right.x = (std::float_t)num1 * cosf(-rot.z * (std::float_t)D2R);
	right.y = (std::float_t)num1 * sinf(rot.z * (std::float_t)D2R);
	right.z = sinf(-rot.y * (std::float_t)D2R);

	Vector3 cross;
	cross.x = right.y * dir.z - right.z * dir.y;
	cross.y = right.z * dir.x - right.x * dir.z;
	cross.z = right.x * dir.y - right.y * dir.x;

	Vector3 cam_coord = CAM::GET_CAM_COORD(cam);

	Vector3 new_right = multiply_vector(&right, offset.x);
	cam_coord = add_vectors(&cam_coord, &new_right);

	Vector3 new_dir = multiply_vector(&dir, offset.y);
	cam_coord = add_vectors(&cam_coord, &new_dir);

	Vector3 new_cross = multiply_vector(&cross, offset.z);
	cam_coord = add_vectors(&cam_coord, &new_cross);

	return cam_coord;
}
bool change_net_obj_owner(std::int32_t script_index, std::int32_t player) {
	if (NETWORK::NETWORK_IS_IN_SESSION()) {
		std::uint64_t network_object_mgr = *(std::uint64_t*)(GTA_NETWORK_OBJECT_MGR_INTERFACE);
		if (network_object_mgr == NULL)
			return false;

		if (!ENTITY::DOES_ENTITY_EXIST(script_index))
			return false;

		std::uint64_t entity = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::int32_t))GTA_GET_ENTITY_FROM_SCRIPT_GUID), script_index);
		if (entity == NULL)
			return false;

		std::uint64_t net_obj = *(std::uint64_t*)(entity + 0xD0);
		if (net_obj == NULL)
			return false;

		if (*(std::uint16_t*)(net_obj + 0x8) == 11)
			return false;

		std::uint64_t net_game_player = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint8_t))GTA_GET_NET_GAME_PLAYER_FROM_PHYSICAL_INDEX), (std::uint8_t)(player));
		if (net_game_player == NULL)
			return false;

		SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint64_t, std::uint64_t, std::uint64_t, std::uint64_t))GTA_CHANGE_NET_OBJ_OWNER), network_object_mgr, net_obj, net_game_player, 0ui64);
	}
	else {
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(script_index);
	}
	return true;
}
std::int32_t spawn_ped(std::uint32_t hash, Vector3 coords, std::float_t heading) {
	if (STREAMING::IS_MODEL_VALID(hash)) {
		STREAMING::REQUEST_MODEL(hash);
		while (!STREAMING::HAS_MODEL_LOADED(hash))
			Script::GetCurrent()->ScriptYield();
		INT l_nNetworkId = NETWORK::PED_TO_NET(PED::CREATE_PED(4, hash, coords.x, coords.y, coords.z, heading, TRUE, FALSE));
		NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(l_nNetworkId, TRUE);
		if (ENTITY::IS_ENTITY_VISIBLE_TO_SCRIPT(NETWORK::NET_TO_PED(l_nNetworkId)))
			return NETWORK::NET_TO_PED(l_nNetworkId);
	}
	return NULL;
}
char* get_vehicle_class_name(std::int32_t vehicle_class) {
	std::stringstream ss; ss << "VEH_CLASS_" << vehicle_class;
	return UI::_GET_LABEL_TEXT(ss.str().c_str()) == "NULL" ? "~c~Unknown Class" : UI::_GET_LABEL_TEXT(ss.str().c_str());
}
std::int32_t spawn_vehicle(std::uint32_t hash, std::int32_t on_entity) {
	if (STREAMING::IS_MODEL_VALID(hash)) {
		std::float_t speed = 0.0f;

		STREAMING::REQUEST_MODEL(hash);
		while (!STREAMING::HAS_MODEL_LOADED(hash))
			Script::GetCurrent()->ScriptYield();

		if (on_entity == PLAYER::PLAYER_PED_ID() && g_vehicle_spawn_options_spawn_inside) {
			if (PED::IS_PED_IN_ANY_VEHICLE(on_entity, FALSE)) {
				std::int32_t current_vehicle = PED::GET_VEHICLE_PED_IS_IN(on_entity, FALSE);
				speed = ENTITY::GET_ENTITY_SPEED(current_vehicle);
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(current_vehicle, TRUE, TRUE);
				VEHICLE::DELETE_VEHICLE(&current_vehicle);
			}
		}

		Vector3 l_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(on_entity, 0.0f, 0.0f, 0.0f);
		std::int32_t net_id = NETWORK::VEH_TO_NET(VEHICLE::CREATE_VEHICLE(hash, l_coords.x, l_coords.y, l_coords.z, ENTITY::GET_ENTITY_HEADING(on_entity), TRUE, FALSE));
		NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(net_id, TRUE);
		if (ENTITY::IS_ENTITY_VISIBLE_TO_SCRIPT(NETWORK::NET_TO_VEH(net_id))) {
			if (g_vehicle_spawn_options_spawn_inside)
				PED::SET_PED_INTO_VEHICLE(on_entity, NETWORK::NET_TO_VEH(net_id), -1);
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(NETWORK::NET_TO_VEH(net_id), speed);
			VEHICLE::SET_VEHICLE_ENGINE_ON(NETWORK::NET_TO_VEH(net_id), TRUE, TRUE, TRUE);
			DECORATOR::DECOR_SET_INT(NETWORK::NET_TO_VEH(net_id), "MPBitset", (1 << 10));
			return NETWORK::NET_TO_VEH(net_id);
		}
	}
	return NULL;
}
std::int32_t spawn_funny_vehicle(std::uint32_t hash) {
	if (STREAMING::IS_MODEL_VALID(hash)) {

		STREAMING::REQUEST_MODEL(hash);
		while (!STREAMING::HAS_MODEL_LOADED(hash))
			Script::GetCurrent()->ScriptYield();

		Vector3 l_object_dim_min, g_object_dim_max;
		GAMEPLAY::GET_MODEL_DIMENSIONS(hash, &l_object_dim_min, &g_object_dim_max);

		Vector3 l_coords;
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			l_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0.0f, ((g_object_dim_max.y * 2) + 3.0f), 0.0f);
		else
			l_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, ((g_object_dim_max.y * 2) + 3.0f), 0.0f);

		std::int32_t net_id = NETWORK::VEH_TO_NET(VEHICLE::CREATE_VEHICLE(hash, l_coords.x, l_coords.y, l_coords.z, ENTITY::GET_ENTITY_HEADING(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())), TRUE, FALSE));
		NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(net_id, TRUE);
		if (ENTITY::IS_ENTITY_VISIBLE_TO_SCRIPT(NETWORK::NET_TO_VEH(net_id))) {
			DECORATOR::DECOR_SET_INT(NETWORK::NET_TO_VEH(net_id), "MPBitset", (1 << 10));
			return NETWORK::NET_TO_VEH(net_id);
		}
	}
	return NULL;
}
std::int32_t spawn_object(std::string name, Vector3 coords, BOOL dynamic) {
	if (STREAMING::IS_MODEL_VALID(GAMEPLAY::GET_HASH_KEY((PCHAR)name.c_str()))) {
		STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY((PCHAR)name.c_str()));
		while (!STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY((PCHAR)name.c_str())))
			Script::GetCurrent()->ScriptYield();
		std::int32_t l_network_id = NETWORK::OBJ_TO_NET(OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY((PCHAR)name.c_str()), coords.x, coords.y, coords.z, TRUE, FALSE, dynamic));
		NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(l_network_id, TRUE);
		if (ENTITY::IS_ENTITY_VISIBLE_TO_SCRIPT(NETWORK::NET_TO_OBJ(l_network_id))) {
			ENTITY::SET_ENTITY_ROTATION(NETWORK::NET_TO_OBJ(l_network_id), 0.0f, 0.0f, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 2, 1);
			ENTITY::FREEZE_ENTITY_POSITION(NETWORK::NET_TO_OBJ(l_network_id), true);
			DECORATOR::DECOR_SET_INT(NETWORK::NET_TO_OBJ(l_network_id), "bombdec", GAMEPLAY::GET_HASH_KEY(PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())));
			return NETWORK::NET_TO_OBJ(l_network_id);
		}
	}
	return NULL;
}
std::int32_t spawn_snapped_object(std::uint32_t hash, Vector3 coords, BOOL dynamic) {
	if (STREAMING::IS_MODEL_VALID(hash)) {
		STREAMING::REQUEST_MODEL(hash);
		if (!STREAMING::HAS_MODEL_LOADED(hash)) Script::GetCurrent()->ScriptYield();
		std::int32_t l_network_id = NETWORK::OBJ_TO_NET(OBJECT::CREATE_OBJECT(hash, coords.x, coords.y, coords.z, TRUE, FALSE, dynamic));
		NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(l_network_id, TRUE);
		if (ENTITY::IS_ENTITY_VISIBLE_TO_SCRIPT(NETWORK::NET_TO_OBJ(l_network_id))) {
			ENTITY::SET_ENTITY_ROTATION(NETWORK::NET_TO_OBJ(l_network_id), 0.0f, 0.0f, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 2, 1);
			ENTITY::FREEZE_ENTITY_POSITION(NETWORK::NET_TO_OBJ(l_network_id), true);
			DECORATOR::DECOR_SET_INT(NETWORK::NET_TO_OBJ(l_network_id), "bombdec", GAMEPLAY::GET_HASH_KEY(PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())));
			return NETWORK::NET_TO_OBJ(l_network_id);
		}
	}
	return NULL;
}
std::uint64_t __fastcall get_element_from_pool(std::uint64_t pool, std::int32_t index) {
	std::uint64_t data = (std::uint64_t)(~((std::int64_t)(*(std::uint8_t*)(*(std::uint64_t*)(pool + 8) + index) & 0x80
		| (std::uint64_t) - (std::int64_t)(*(std::uint8_t*)(*(std::uint64_t*)(pool + 8) + index) & 0x80)) >> 63)
		& (*(std::uint64_t*)(pool) + (std::uint64_t)((*(std::uint32_t*)(pool + 20) * index))));
	return data == NULL ? NULL : data;
}
bool request_network_control(std::int32_t entity) {
	return true;
}
std::uint64_t get_model_info_ptr(std::uint32_t hash) {
	std::int32_t index = 0xFFFF;
	return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint32_t, std::int32_t*))GTA_GET_MODEL_INFO), hash, &index);
}

void add_info_box_title(std::string title) {
	draw_rect((g_menu_banner_pos_x >= 0.5f) ? (g_menu_banner_pos_x - (g_menu_banner_size_x / 2) - (g_info_box_title_width / 2)) : (g_menu_banner_pos_x + (g_menu_banner_size_x / 2) + (g_info_box_title_width / 2)), (g_menu_banner_pos_y - ((g_menu_banner_size_y / 2)) + (g_info_box_title_length / 2)), g_info_box_title_width, g_info_box_title_length, g_menu_background_colour);
	draw_text(title, (g_menu_banner_pos_x >= 0.5f) ? ((g_menu_banner_pos_x - (g_menu_banner_size_x / 2)) - (g_info_box_title_width / 2)) : ((g_menu_banner_pos_x + (g_menu_banner_size_x / 2)) + (g_info_box_title_width / 2)), (g_menu_banner_pos_y - ((g_menu_banner_size_y / 2)) + (g_info_box_title_length / 2)) - 0.016f, 0, 0.44f, g_menu_option_text_colour, TRUE, FALSE, FALSE);
}
template<typename t>
void add_data_to_info_box(std::string desc, t data) {
	std::stringstream ss;
	ss << data;
	draw_text(desc, (g_menu_banner_pos_x >= 0.5f) ? (((g_menu_banner_pos_x - (g_menu_banner_size_x / 2) - (g_info_box_title_width / 2)) - (g_info_box_title_width / 2)) + g_menu_text_padding) : (((g_menu_banner_pos_x + (g_menu_banner_size_x / 2) + (g_info_box_title_width / 2)) - (g_info_box_title_width / 2)) + g_menu_text_padding), (g_menu_banner_pos_y - ((g_menu_banner_size_y / 2)) + (g_info_box_title_length / 2)) + ((g_info_box_count + 1) * (g_info_box_title_length / 2)), 0, 0.35f, g_menu_option_text_colour, FALSE, FALSE, FALSE);
	draw_text(ss.str(), (g_menu_banner_pos_x >= 0.5f) ? (((g_menu_banner_pos_x - (g_menu_banner_size_x / 2) - (g_info_box_title_width / 2)) + (g_info_box_title_width / 2)) - g_menu_text_padding) : (((g_menu_banner_pos_x + (g_menu_banner_size_x / 2) + (g_info_box_title_width / 2)) + (g_info_box_title_width / 2)) - g_menu_text_padding), (g_menu_banner_pos_y - ((g_menu_banner_size_y / 2)) + (g_info_box_title_length / 2)) + ((g_info_box_count + 1) * (g_info_box_title_length / 2)), 0, 0.35f, g_menu_option_text_colour, FALSE, TRUE, FALSE);
	g_info_box_count++;
}
char* get_player_crew_tag(std::int32_t player) {
	std::uint64_t net_game_player = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint8_t))GTA_GET_NET_GAME_PLAYER_FROM_PHYSICAL_INDEX), (std::uint8_t)(player));
	if (net_game_player == NULL) {
		char* tag = (char*)(net_game_player + 0x107);
		if (tag[0] != NULL)
			return tag;
	}
	return "~c~None";
}
char* get_player_crew_name(std::int32_t player) {
	std::uint64_t net_game_player = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint8_t))GTA_GET_NET_GAME_PLAYER_FROM_PHYSICAL_INDEX), (std::uint8_t)(player));
	if (net_game_player == NULL) {
		char* name = (char*)(net_game_player + 0xEE);
		if (name[0] != NULL)
			return name;
	}
	return "~c~None";
}
char* get_player_crew_desc(std::int32_t player) {
	std::uint64_t net_game_player = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint8_t))GTA_GET_NET_GAME_PLAYER_FROM_PHYSICAL_INDEX), (std::uint8_t)(player)); 
	if (net_game_player == NULL) {
		char* desc = (char*)(net_game_player + 0x10C);
		if (desc[0] != NULL)
			return desc;
	}
	return "~c~None";
}
char* get_player_port(std::int32_t player) {
	return "6672";
}
in_addr get_player_public_addr(std::int32_t player) {
	in_addr addr = in_addr();
	const char* name_ptr = PLAYER::GET_PLAYER_NAME(player);
	if (name_ptr == nullptr) return addr;
	addr.S_un.S_addr = *(ULONG*)(name_ptr - 0x38);
	return addr;
}
in_addr get_player_local_addr(std::int32_t player) {
	in_addr addr = in_addr();
	const char* name_ptr = PLAYER::GET_PLAYER_NAME(player);
	if (name_ptr == nullptr) return addr;
	addr.S_un.S_addr = *(ULONG*)(name_ptr - 0x48);
	return addr;
}
char* get_player_street(std::uint32_t player, bool crossing) {
	Hash ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
	Hash street_hash = NULL;
	Hash crossing_hash = NULL;
	if (ENTITY::DOES_ENTITY_EXIST(ped)) {
		Vector3 l_vCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, 0.0f, 0.0f, 0.0f);
		PATHFIND::GET_STREET_NAME_AT_COORD(l_vCoords.x, l_vCoords.y, l_vCoords.z, &street_hash, &crossing_hash);
		if (crossing)
			return crossing_hash == NULL ? "~c~None" : UI::GET_STREET_NAME_FROM_HASH_KEY(crossing_hash);
		else
			return street_hash == NULL ? "~c~None" : UI::GET_STREET_NAME_FROM_HASH_KEY(street_hash);
	}
	return "~c~None";
}
char* get_vehicle_class(std::uint32_t hash) {
	std::string s = "VEH_CLASS_";
	s += VEHICLE::GET_VEHICLE_CLASS_FROM_NAME(hash);
	s = UI::_GET_LABEL_TEXT(s.c_str());
	return !strcmp(s.c_str(), "NULL") ? "~c~None" : s.c_str();
}
std::int32_t get_player_health(std::int32_t player) {
	std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
	if (ENTITY::DOES_ENTITY_EXIST(ped))
		return ENTITY::GET_ENTITY_HEALTH(ped);
	return NULL;
}
std::float_t get_player_speed(std::int32_t player) {
	std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
	if (ENTITY::DOES_ENTITY_EXIST(ped))
		return (ENTITY::GET_ENTITY_SPEED(ped) * 2.23694f);
	return 0.0f;
}
Vector3 get_player_coords(std::int32_t player) {
	std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
	if (ENTITY::DOES_ENTITY_EXIST(ped))
		return ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, 0.0f, 0.0f, 0.0f);
	return Vector3();
}
void draw_player_info_box(std::int32_t player) {
	add_info_box_title(PLAYER::GET_PLAYER_NAME(player));
	Vector3 coords = get_player_coords(player);
	add_data_to_info_box("Axis ~c~(X)", coords.x);
	add_data_to_info_box("Axis ~c~(Y)", coords.y);
	add_data_to_info_box("Axis ~c~(Z)", coords.z);
	add_data_to_info_box("Health", get_player_health(player));
	add_data_to_info_box("Armour", PLAYER::GET_PLAYER_MAX_ARMOUR(player));
	//add_data_to_info_box("Street", get_player_street(player, false));
	//add_data_to_info_box("Crossing", get_player_street(player, true));
	//std::stringstream ss;
	//in_addr public_addr = get_player_public_addr(player);
	//ss << +public_addr.S_un.S_un_b.s_b4 << "." << +public_addr.S_un.S_un_b.s_b3 << "." << +public_addr.S_un.S_un_b.s_b2 << "." << +public_addr.S_un.S_un_b.s_b1;
	add_data_to_info_box("IP Address", "0.0.0.0");
	//ss.str("");
	//ss.clear();
	//in_addr local_addr = get_player_local_addr(player);
	//ss << +local_addr.S_un.S_un_b.s_b4 << "." << +local_addr.S_un.S_un_b.s_b3 << "." << +local_addr.S_un.S_un_b.s_b2 << "." << +local_addr.S_un.S_un_b.s_b1;
	add_data_to_info_box("Internal IP", "10.0.0.173");
	add_data_to_info_box("Port", "6672");
	draw_rect((g_menu_banner_pos_x >= 0.5f) ? (g_menu_banner_pos_x - (g_menu_banner_size_x / 2) - (g_info_box_title_width / 2)) : (g_menu_banner_pos_x + (g_menu_banner_size_x / 2) + (g_info_box_title_width / 2)), ((g_menu_banner_pos_y - ((g_menu_banner_size_y / 2)) + (g_info_box_title_length / 2)) + (g_info_box_title_length / 2)) + ((g_info_box_count * (g_info_box_title_length / 2)) / 2) + 0.0035f, g_info_box_title_width, (g_info_box_count * (g_info_box_title_length / 2)) + 0.007f, g_menu_background_colour);
	g_info_box_count = NULL;
}

//protection
void network_object_attachment_protection() {
	if (GTA_ATTACHMENT_EXTENSION_INST_POOL) {
		std::uint64_t pool = *(uint64_t*)(GTA_ATTACHMENT_EXTENSION_INST_POOL);
		if (pool) {
			std::uint32_t pool_size = *(uint32_t*)(pool + 0x10);
			for (std::uint32_t i = 0; i < pool_size; i++) {
				std::uint64_t extension = get_element_from_pool(pool, i);
				if (extension) {
					std::uint64_t parent_entity = *(std::uint64_t*)(extension);
					if (parent_entity == NULL)
						continue;

					std::int32_t parent = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::int32_t(*)(std::uint64_t))GTA_GET_SCRIPT_INDEX_FROM_ENTITY), parent_entity);
					if (!ENTITY::DOES_ENTITY_EXIST(parent))
						continue;

					if (parent != PLAYER::PLAYER_PED_ID())
						continue;

					std::uint64_t child_entity = *(std::uint64_t*)(extension + 0x18);
					if (child_entity == NULL)
						continue;

					std::uint64_t net_obj = *(std::uint64_t*)(child_entity + 0xD0);
					if (net_obj == NULL)
						continue;

					std::uint16_t net_id = *(SHORT*)(net_obj + 0xA);
					for (std::uint32_t j = 0; j < 100; j++) {
						if (g_received_net_obj[j].m_net_id != net_id)
							continue;

						std::int32_t child = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::int32_t(*)(std::uint64_t))GTA_GET_SCRIPT_INDEX_FROM_ENTITY), child_entity);
						if (!ENTITY::DOES_ENTITY_EXIST(child))
							continue;

						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(child);
						if (!ENTITY::IS_ENTITY_VISIBLE(child))
							ENTITY::SET_ENTITY_VISIBLE(child, TRUE, 0);

						ENTITY::DETACH_ENTITY(child, TRUE, TRUE);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(child, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX((std::int32_t)(g_received_net_obj[j].m_owner_physical_index)), PED::GET_PED_BONE_INDEX(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX((std::int32_t)(g_received_net_obj[j].m_owner_physical_index)), -1), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 1);

						if (g_notify_attacks) {
							std::stringstream ss;
							ss << "From: " << PLAYER::GET_PLAYER_NAME((std::int32_t)(g_received_net_obj[j].m_owner_physical_index));
							map_notification("CHAR_BLOCKED", "<C>Protection</C>", "Attachment redirected", ss.str());
						}
					}
				}
			}
		}
	}
}

//self
void change_self_model(std::uint32_t hash) {
	std::int32_t player_ped = PLAYER::PLAYER_PED_ID();
	if (ENTITY::DOES_ENTITY_EXIST(player_ped)) {

		std::int32_t ped = spawn_ped(hash, ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player_ped, 0.0f, 0.0f, 0.0f), ENTITY::GET_ENTITY_HEADING(player_ped));
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {
			PLAYER::CHANGE_PLAYER_PED(PLAYER::PLAYER_ID(), ped, FALSE, FALSE);
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(player_ped, FALSE, FALSE);
			ENTITY::DELETE_ENTITY(&player_ped);
			PED::DELETE_PED(&player_ped);
		}
	}
}

//weapon
void give_all_weapons(std::int32_t ped) {
	if (ENTITY::DOES_ENTITY_EXIST(ped))
		for (std::uint32_t i = 0; i < std::size(weapon_hashs); i++)
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped, weapon_hashs[i].hash, 1337, TRUE);
}
void vortex_gun() {
	if (PLAYER::IS_PLAYER_FREE_AIMING(PLAYER::PLAYER_ID()) || PLAYER::IS_PLAYER_TARGETTING_ANYTHING(PLAYER::PLAYER_ID())) {
		if (!g_vortex_cooldown) {
			Vector3 vortex_dir = get_gameplay_camera_direction();
			Vector3 vortex_pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.4f, 0.0f, 0.6f);

			if (g_vortex_gun_grab_peds) {
				std::uint64_t ped_pool = *(uint64_t*)(GTA_PED_INST_POOL);
				if (ped_pool == NULL)
					return;

				std::uint32_t found_peds = NULL;
				std::uint32_t ped_pool_size = *(uint32_t*)(ped_pool + 0x10);
				for (std::uint32_t i = 0; i < ped_pool_size; i++) {

					std::uint64_t element = get_element_from_pool(ped_pool, i);
					if (element == NULL)
						continue;

					std::int32_t ped = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::int32_t(*)(std::uint64_t))GTA_GET_SCRIPT_INDEX_FROM_ENTITY), element);
					if (!ENTITY::DOES_ENTITY_EXIST(ped))
						continue;

					if (ped == PLAYER::PLAYER_PED_ID())
						continue;

					if (!ENTITY::IS_ENTITY_ON_SCREEN(ped))
						continue;

					if (found_peds++ == g_vortex_gun_ped_capacity)
						break;

					NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(ped);
					change_net_obj_owner(ped, PLAYER::PLAYER_ID());

					if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ped)) {
						Vector3 l_vHndCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, 0.0f, 0.0f, 0.0f);
						ENTITY::SET_ENTITY_VELOCITY(ped,
							((vortex_pos.x + (vortex_dir.x * g_vortex_gun_distance)) - l_vHndCoords.x) * 4.0f,
							((vortex_pos.y + (vortex_dir.y * g_vortex_gun_distance)) - l_vHndCoords.y) * 4.0f,
							((vortex_pos.z + (vortex_dir.z * g_vortex_gun_distance)) - l_vHndCoords.z) * 4.0f);

						if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID())) {
							Vector3 l_vOffset = ENTITY::GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(ped,
								(vortex_pos.x + (vortex_dir.x * g_vortex_gun_force)),
								(vortex_pos.y + (vortex_dir.y * g_vortex_gun_force)),
								(vortex_pos.z + (vortex_dir.z * g_vortex_gun_force)));

							ENTITY::APPLY_FORCE_TO_ENTITY(ped, 1, l_vOffset.x, l_vOffset.y, l_vOffset.z, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, FALSE, TRUE);
							g_vortex_cooldown = true;
						}
					}
				}
			}

			if (g_vortex_gun_grab_vehicles) {
				ListPool* vehicle_pool = *(ListPool**)(GTA_VEH_LIST_POOL);
				if (vehicle_pool != nullptr) {

					std::uint32_t found_vehicles = NULL;
					for (std::int32_t i = 0; i < vehicle_pool->capacity; i++) {

						std::uint64_t vehicle_entity = vehicle_pool->get(i);
						if (vehicle_entity == NULL)
							continue;

						std::int32_t vehicle = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::int32_t(*)(std::uint64_t))GTA_GET_SCRIPT_INDEX_FROM_ENTITY), vehicle_entity);
						if (!ENTITY::DOES_ENTITY_EXIST(vehicle))
							continue;

						if (!ENTITY::IS_ENTITY_ON_SCREEN(vehicle))
							continue;

						if (found_vehicles++ == g_vortex_gun_vehicle_capacity)
							break;

						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehicle);
						change_net_obj_owner(vehicle, PLAYER::PLAYER_ID());

						if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(vehicle)) {
							Vector3 l_vHndCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(vehicle, 0.0f, 0.0f, 0.0f);
							ENTITY::SET_ENTITY_VELOCITY(vehicle,
								((vortex_pos.x + (vortex_dir.x * g_vortex_gun_distance)) - l_vHndCoords.x) * 4.0f,
								((vortex_pos.y + (vortex_dir.y * g_vortex_gun_distance)) - l_vHndCoords.y) * 4.0f,
								((vortex_pos.z + (vortex_dir.z * g_vortex_gun_distance)) - l_vHndCoords.z) * 4.0f);

							if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID())) {
								Vector3 l_vOffset = ENTITY::GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(vehicle,
									(vortex_pos.x + (vortex_dir.x * g_vortex_gun_force)),
									(vortex_pos.y + (vortex_dir.y * g_vortex_gun_force)),
									(vortex_pos.z + (vortex_dir.z * g_vortex_gun_force)));

								ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 1, l_vOffset.x, l_vOffset.y, l_vOffset.z, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, FALSE, TRUE);
								g_vortex_cooldown = true;
							}
						}
					}
				}
			}

			if (g_vortex_gun_grab_objects) {
				std::uint64_t obj_pool = *(uint64_t*)(GTA_OBJ_INST_POOL);
				if (obj_pool == NULL)
					return;

				std::uint32_t found_objects = NULL;
				std::uint32_t object_pool_size = *(uint32_t*)(obj_pool + 0x10);
				for (std::uint32_t i = 0; i < object_pool_size; i++) {

					std::uint64_t element = get_element_from_pool(obj_pool, i);
					if (element == NULL)
						continue;

					std::int32_t object = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::int32_t(*)(std::uint64_t))GTA_GET_SCRIPT_INDEX_FROM_ENTITY), element);
					if (!ENTITY::DOES_ENTITY_EXIST(object))
						continue;

					if (object == PLAYER::PLAYER_PED_ID())
						continue;

					if (!ENTITY::IS_ENTITY_ON_SCREEN(object))
						continue;

					if (found_objects++ == g_vortex_gun_object_capacity)
						break;

					NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(object);
					change_net_obj_owner(object, PLAYER::PLAYER_ID());

					if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(object)) {
						Vector3 l_vHndCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(object, 0.0f, 0.0f, 0.0f);
						ENTITY::SET_ENTITY_VELOCITY(object,
							((vortex_pos.x + (vortex_dir.x * g_vortex_gun_distance)) - l_vHndCoords.x) * 4.0f,
							((vortex_pos.y + (vortex_dir.y * g_vortex_gun_distance)) - l_vHndCoords.y) * 4.0f,
							((vortex_pos.z + (vortex_dir.z * g_vortex_gun_distance)) - l_vHndCoords.z) * 4.0f);

						if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID())) {
							Vector3 l_vOffset = ENTITY::GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(object,
								(vortex_pos.x + (vortex_dir.x * g_vortex_gun_force)),
								(vortex_pos.y + (vortex_dir.y * g_vortex_gun_force)),
								(vortex_pos.z + (vortex_dir.z * g_vortex_gun_force)));

							ENTITY::APPLY_FORCE_TO_ENTITY(object, 1, l_vOffset.x, l_vOffset.y, l_vOffset.z, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, FALSE, TRUE);
							g_vortex_cooldown = true;
						}
					}
				}
			}
		}
	}
	else {
		g_vortex_cooldown = false;
	}
}

//network
bool is_player_quantum_user(std::int32_t player) {
	const char* name = PLAYER::GET_PLAYER_NAME(player);
	if (name != nullptr)
		if (((*(std::uint64_t*)(name - 0x24) >> 32) & 0xFFFFFFFF) == NULL)
			return true;
	return false;
}
bool is_player_using_tank(std::int32_t player) {
	std::int32_t player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
	if (!ENTITY::DOES_ENTITY_EXIST(player_ped))
		return false;

	std::int32_t blip_handle = UI::GET_BLIP_FROM_ENTITY(player_ped);
	if (UI::DOES_BLIP_EXIST(blip_handle))
		return UI::GET_BLIP_SPRITE(blip_handle) == 421;
	return false;
}
bool is_player_using_oppressor(std::int32_t player) {
	std::int32_t player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
	if (!ENTITY::DOES_ENTITY_EXIST(player_ped))
		return false;

	std::int32_t blip_handle = UI::GET_BLIP_FROM_ENTITY(player_ped);
	if (UI::DOES_BLIP_EXIST(blip_handle))
		return UI::GET_BLIP_SPRITE(blip_handle) == 639;
	return false;
}
bool is_player_in_passive_mode(std::int32_t player) {
	std::int32_t player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
	if (!ENTITY::DOES_ENTITY_EXIST(player_ped))
		return false;

	std::int32_t blip_handle = UI::GET_BLIP_FROM_ENTITY(player_ped);
	if (UI::DOES_BLIP_EXIST(blip_handle))
		return UI::GET_BLIP_SPRITE(blip_handle) == 163;
	return false;
}
bool is_player_freemode_host(std::int32_t player) {
	return (NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0) == player);
}
bool is_player_session_host(std::int32_t player) {
	std::uint8_t* net_game_player = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint8_t * (*)())GTA_GET_SESSION_HOST_NET_GAME_PLAYER));
	if (net_game_player == nullptr)
		return false;
	return (std::int32_t)(net_game_player[0x2D]) == player;
}
bool is_player_next_session_host(std::int32_t player) {

	if (NETWORK::NETWORK_IS_IN_SESSION()) {

		std::int32_t next_host = -1;
		std::uint64_t lowest_key = NULL;

		for (std::int32_t i = 0; i < 32; i++) {

			if (!NETWORK::NETWORK_IS_PLAYER_ACTIVE(i))
				continue;

			if (is_player_session_host(i))
				continue;

			const char* name_ptr = PLAYER::GET_PLAYER_NAME(i);
			if (name_ptr == nullptr)
				continue;

			std::uint64_t player_key = *(std::uint64_t*)(name_ptr - 0x24);
			if (player_key == NULL)
				continue;

			if (lowest_key == NULL) {
				lowest_key = player_key;
				next_host = i;
				continue;
			}

			if (player_key < lowest_key) {
				lowest_key = player_key;
				next_host = i;
			}
		}
		return (player == next_host);
	}
	return false;
}
bool is_player_friend(std::int32_t player) {
	std::int32_t player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
	if (!ENTITY::DOES_ENTITY_EXIST(player_ped))
		return false;

	std::int32_t handle[26];
	NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, &handle[0], 13);
	if (NETWORK::NETWORK_IS_FRIEND(&handle[0]))
		return true;
	return false;
}
void kick_player_disconnect(std::int32_t player) {
	if (player != PLAYER::PLAYER_ID()) {

		std::uint64_t network_player_mgr = *(std::uint64_t*)GTA_NETWORK_PLAYER_MGR_INTERFACE;
		if (network_player_mgr != NULL) {

			std::int32_t player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
			if (ENTITY::DOES_ENTITY_EXIST(player_ped)) {

				std::uint64_t net_game_player = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint8_t))GTA_GET_NET_GAME_PLAYER_FROM_PHYSICAL_INDEX), (std::uint8_t)(player));
				if (net_game_player != NULL) {

					SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint64_t, std::uint64_t))GTA_REMOVE_PLAYER_FROM_PLAYER_MGR), network_player_mgr, net_game_player);
					WEAPON::REMOVE_ALL_PED_WEAPONS(player_ped, TRUE);
				}
			}
		}
	}
}
bool crash_online_player_helper(std::uint64_t net_game_event, std::uint8_t* net_game_player) {
	return (std::int32_t)(net_game_player[0x2D]) == g_selected_online_player_crash_victim;
}
int remove_weapon_event_pack_sync_data_shim(std::uint64_t net_game_event, std::uint64_t sync_data) {
	*reinterpret_cast<std::add_pointer_t<std::int16_t>> (net_game_event + 0x30) = INT16_MAX;
	*reinterpret_cast<std::add_pointer_t<std::int32_t>> (net_game_event + 0x34) = INT32_MAX;
	return SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX),
		((int(*)(std::uint64_t, std::uint64_t))g_remove_weapon_event_pack_sync_data_cache),
		net_game_event, sync_data);
}
void crash_online_player_rwea(std::int32_t player) {

	g_selected_online_player_crash_victim = player;

	if (((std::uint64_t*)(GTA_REMOVE_WEAPON_EVENT_TABLE))[2] != (std::uint64_t)crash_online_player_helper)
		if ((g_remove_weapon_event_check_sender_cache = hook_virtual((std::uint64_t*)(GTA_REMOVE_WEAPON_EVENT_TABLE), crash_online_player_helper, 2)) == NULL)
			return;

	if (((std::uint64_t*)(GTA_REMOVE_WEAPON_EVENT_TABLE))[5] != (std::uint64_t)remove_weapon_event_pack_sync_data_shim)
		if ((g_remove_weapon_event_pack_sync_data_cache = hook_virtual((std::uint64_t*)(GTA_REMOVE_WEAPON_EVENT_TABLE), remove_weapon_event_pack_sync_data_shim, 5)) == NULL)
			return;

	std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

	if (ENTITY::DOES_ENTITY_EXIST(ped))
		WEAPON::REMOVE_WEAPON_FROM_PED(ped, INT32_MAX);

	if (g_remove_weapon_event_check_sender_cache != NULL)
		hook_virtual((std::uint64_t*)(GTA_REMOVE_WEAPON_EVENT_TABLE), (void*)(g_remove_weapon_event_check_sender_cache), 2);

	if (g_remove_weapon_event_pack_sync_data_cache != NULL)
		hook_virtual((std::uint64_t*)(GTA_REMOVE_WEAPON_EVENT_TABLE), (void*)(g_remove_weapon_event_pack_sync_data_cache), 5);
}
void crash_online_player_crem(std::int32_t player) {

	std::int32_t player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
	if (ENTITY::DOES_ENTITY_EXIST(player_ped)) {

		std::int32_t decoy_ped = spawn_ped(GAMEPLAY::GET_HASH_KEY("s_m_m_movalien_01"), ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player_ped, 0.0f, 0.0f, 0.0f), ENTITY::GET_ENTITY_HEADING(player_ped));

		std::uint64_t player_entity = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::int32_t))GTA_GET_ENTITY_FROM_SCRIPT_GUID), player_ped);
		if (player_entity) {

			std::uint64_t player_net_obj = *(std::uint64_t*)(player_entity + 0xD0);
			if (player_net_obj) {

				std::uint64_t net_game_player = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint8_t))GTA_GET_NET_GAME_PLAYER_FROM_PHYSICAL_INDEX), (std::uint8_t)(player));
				if (net_game_player) {

					std::uint64_t decoy_entity = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::int32_t))GTA_GET_ENTITY_FROM_SCRIPT_GUID), decoy_ped);
					if (decoy_entity) {

						std::uint64_t decoy_net_obj = *(std::uint64_t*)(decoy_entity + 0xD0);
						if (decoy_net_obj) {

							// get ptr to net id
							std::uint16_t* decoy_net_id = (std::uint16_t*)(decoy_net_obj + 0xA);

							// cache
							std::uint16_t cached_decoy_net_id = *decoy_net_id;

							// spoof to player's net id
							*decoy_net_id = *(std::uint16_t*)(player_net_obj + 0xA);

							// pack remove
							SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((void(*)(std::uint64_t, std::uint64_t, std::uint64_t, bool))GTA_PACK_CLONE_REMOVE), GTA_NETWORK_OBJECT_MGR_INTERFACE, player_net_obj, net_game_player, true);

							// restore
							*decoy_net_id = cached_decoy_net_id;
						}
					}
				}
			}
		}
	}
}
void crash_online_player_csyn(std::int32_t player) {

	std::int32_t player_ped = PLAYER::PLAYER_PED_ID();
	if (ENTITY::DOES_ENTITY_EXIST(player_ped)) {

		std::int32_t decoy_ped = spawn_ped(GAMEPLAY::GET_HASH_KEY("s_m_m_movalien_01"), ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player_ped, 0.0f, 0.0f, 0.0f), ENTITY::GET_ENTITY_HEADING(player_ped));
		if (ENTITY::DOES_ENTITY_EXIST(decoy_ped)) {

			std::uint64_t player_entity = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::int32_t))GTA_GET_ENTITY_FROM_SCRIPT_GUID), player_ped);
			if (player_entity) {

				std::uint64_t player_net_obj = *(std::uint64_t*)(player_entity + 0xD0);
				if (player_net_obj) {

					std::uint64_t net_game_player = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint8_t))GTA_GET_NET_GAME_PLAYER_FROM_PHYSICAL_INDEX), (std::uint8_t)(player));
					if (net_game_player) {

						std::uint64_t decoy_entity = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::int32_t))GTA_GET_ENTITY_FROM_SCRIPT_GUID), decoy_ped);
						if (decoy_entity) {

							std::uint64_t decoy_net_obj = *(std::uint64_t*)(decoy_entity + 0xD0);
							if (decoy_net_obj) {

								// get ptr to net id
								std::uint16_t* decoy_net_obj_type = (std::uint16_t*)(decoy_net_obj + 0x8);

								// cache
								std::uint16_t cached_decoy_net_obj_type = *decoy_net_obj_type;

								// spoof to heli
								*decoy_net_obj_type = 4;

								// pack sync
								SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((void(*)(std::uint64_t, std::uint64_t, std::uint64_t))GTA_PACK_CLONE_SYNC), GTA_NETWORK_OBJECT_MGR_INTERFACE, player_net_obj, net_game_player);

								// restore
								*decoy_net_obj_type = cached_decoy_net_obj_type;
							}
						}
					}
				}
			}
		}
	}
}

//pedestrian
void draw_pedestrian_info_box(managed_ped ped) {
	add_info_box_title(ped.name);
	add_data_to_info_box("Hash", ENTITY::GET_ENTITY_MODEL(ped.handle));
	Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped.handle, 0.0f, 0.0f, 0.0f);
	add_data_to_info_box("Axis ~c~(X)", coords.x);
	add_data_to_info_box("Axis ~c~(Y)", coords.y);
	add_data_to_info_box("Axis ~c~(Z)", coords.z);
	add_data_to_info_box("Health", ENTITY::GET_ENTITY_HEALTH(ped.handle));
	add_data_to_info_box("Armour", PLAYER::GET_PLAYER_MAX_ARMOUR(ped.handle));
	add_data_to_info_box("Bodyguard", ped.is_bodyguard ? "Yes" : "No");

	std::int32_t last_sequence_event = NULL;
	for (std::int32_t i = 0; i < sizeof(ped.task_sequence) / sizeof(ped.task_sequence[0]); i++) { //type, args
		if (ped.task_sequence[i][0] != NULL)
			if (ped.task_sequence[i][0] > last_sequence_event)
				last_sequence_event = ped.task_sequence[i][0];
	}

	if (last_sequence_event != NULL) {
		std::stringstream ss;
		switch (last_sequence_event) {
		case 1: ss << "Give Weapon"; break;
		case 2: ss << "Fight Hated Targets"; break;
		case 3: ss << "Fight"; break;
		case 4: ss << "Teleport To"; break;
		case 5: ss << "Follow"; break;
		case 6: ss << "Enter"; break;
		case 7: ss << "Exit Vehicle"; break; 
		case 8: ss << "Vehicle Chase"; break;
		case 9: ss << "Heli Chase"; break;
		case 10: ss << "Plane Chase"; break;
		case 11: ss << "Shoot At"; break;
		case 12: ss << "Aim At"; break;
		}
		add_data_to_info_box("Sequence Event", ss.str());
	}

	if (PED::IS_PED_IN_ANY_VEHICLE(ped.handle, FALSE))
		add_data_to_info_box("Vehicle", UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(ped.handle, 0)))));

	std::int32_t street_hash = NULL;
	std::int32_t crossing_hash = NULL;
	//PATHFIND::GET_STREET_NAME_AT_COORD(coords.x, coords.y, coords.z, &street_hash, &crossing_hash);
	add_data_to_info_box("Street", street_hash == NULL ? "~c~None" : UI::GET_STREET_NAME_FROM_HASH_KEY(street_hash));
	add_data_to_info_box("Crossing", crossing_hash == NULL ? "~c~None" : UI::GET_STREET_NAME_FROM_HASH_KEY(crossing_hash));

	draw_rect((g_menu_banner_pos_x >= 0.5f) ? (g_menu_banner_pos_x - (g_menu_banner_size_x / 2) - (g_info_box_title_width / 2)) : (g_menu_banner_pos_x + (g_menu_banner_size_x / 2) + (g_info_box_title_width / 2)), ((g_menu_banner_pos_y - ((g_menu_banner_size_y / 2)) + (g_info_box_title_length / 2)) + (g_info_box_title_length / 2)) + ((g_info_box_count * (g_info_box_title_length / 2)) / 2) + 0.0035f, g_info_box_title_width, (g_info_box_count * (g_info_box_title_length / 2)) + 0.007f, g_menu_background_colour);
	g_info_box_count = NULL;
}
void suicide_ped(std::int32_t ped) {
	if (!ENTITY::DOES_ENTITY_EXIST(ped) || ENTITY::IS_ENTITY_DEAD(ped))
		return;

	Hash weapon = NULL;
	do {
		WEAPON::GIVE_WEAPON_TO_PED(ped, 0x99AEEB3B, 9999, 1, 1);
		WEAPON::SET_CURRENT_PED_WEAPON(ped, 0x99AEEB3B, true);
		WEAPON::GET_CURRENT_PED_WEAPON(ped, &weapon, FALSE);
	} while (weapon != 0x99AEEB3B);

	STREAMING::REQUEST_ANIM_DICT("MP_SUICIDE");
	while (!STREAMING::HAS_ANIM_DICT_LOADED("MP_SUICIDE"))
		Script::GetCurrent()->ScriptYield();

	//STREAMING::REQUEST_ANIM_SET("pistol");

	AI::CLEAR_PED_TASKS_IMMEDIATELY(ped);
	AI::TASK_PLAY_ANIM(ped, "MP_SUICIDE", "pistol", 8, -8, -1, 2105344, 0, false, 0, false);
	if (ENTITY::HAS_ANIM_EVENT_FIRED(ped, GAMEPLAY::GET_HASH_KEY("Fire"))) {
		PED::SET_PED_SHOOTS_AT_COORD(ped, 0, 0, 0, TRUE);
		PED::SET_PED_TO_RAGDOLL(ped, 0, 250, 0, 0, 0, 0);
		ENTITY::SET_ENTITY_HEALTH(ped, 0);
	}
}


//teleport
void teleport_to_position(std::float_t x, std::float_t y, std::float_t z) {
	if (!g_misc_global_teleport_animation) {
		PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE) ? PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), x, y, z + 1.0f) : ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), x, y, z + 1.0f, FALSE, FALSE, FALSE, TRUE);
		return;
	}

	Vector3 gameplay_cam_coord = CAM::GET_GAMEPLAY_CAM_COORD();
	Vector3 gameplay_cam_rot = CAM::GET_GAMEPLAY_CAM_ROT(2);

	if (!CAM::DOES_CAM_EXIST(g_teleport_to_position_cam))
		g_teleport_to_position_cam = CAM::CREATE_CAM("DEFAULT_SPLINE_CAMERA", TRUE);

	if (CAM::DOES_CAM_EXIST(g_teleport_to_position_cam)) {

		CAM::ADD_CAM_SPLINE_NODE(g_teleport_to_position_cam, gameplay_cam_coord.x, gameplay_cam_coord.y, gameplay_cam_coord.z, gameplay_cam_rot.x, gameplay_cam_rot.y, gameplay_cam_rot.z, 5000, 0, 2);

		std::float_t yaw = GAMEPLAY::GET_HEADING_FROM_VECTOR_2D(x, y);

		CAM::ADD_CAM_SPLINE_NODE(g_teleport_to_position_cam, gameplay_cam_coord.x, gameplay_cam_coord.y, gameplay_cam_coord.z + 50.0f, gameplay_cam_rot.x, gameplay_cam_rot.y, yaw, 5000, 0, 2);

		CAM::SET_CAM_ACTIVE(g_teleport_to_position_cam, true);
		CAM::RENDER_SCRIPT_CAMS(1, 1, 5000, 1, 0);

		while (CAM::IS_CAM_INTERPOLATING(g_teleport_to_position_cam))
			Script::GetCurrent()->ScriptYield();

		PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE) ? PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), x, y, z + 1.0f) : ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), x, y, z + 1.0f, FALSE, FALSE, FALSE, TRUE);
		STREAMING::LOAD_SCENE(x, y, z);

		CAM::SET_CAM_ACTIVE(g_teleport_to_position_cam, false);
		CAM::RENDER_SCRIPT_CAMS(0, 1, 10000, 1, 0);

		CAM::DESTROY_CAM(g_teleport_to_position_cam, true);
	}
}

//recovery
void recovery_clear_reports() {
	STATS::STAT_SET_FLOAT(GAMEPLAY::GET_HASH_KEY("MPPLY_OVERALL_BADSPORT"), 0, TRUE);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MPPLY_CHAR_IS_BADSPORT"), 0, TRUE);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BECAME_BADSPORT_NUM"), 0, TRUE);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_REPORT_STRENGTH"), 0, TRUE);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_COMMEND_STRENGTH"), 100, TRUE);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_FRIENDLY"), 100, TRUE);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_HELPFUL"), 100, TRUE);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_GRIEFING"), 0, TRUE);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_VC_ANNOYINGME"), 0, TRUE);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_VC_HATE"), 0, TRUE);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_OFFENSIVE_LANGUAGE"), 0, TRUE);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_OFFENSIVE_TAGPLATE"), 0, TRUE);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_OFFENSIVE_UGC"), 0, TRUE);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_NAME"), 0, TRUE);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_MOTTO"), 0, TRUE);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_STATUS"), 0, TRUE);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_EMBLEM"), 0, TRUE);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_GAME_EXPLOITS"), 0, TRUE);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_EXPLOITS"), 0, TRUE);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_BAD_SPORT_BITSET"), 0, TRUE);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_BAD_SPORT_BITSET"), 0, TRUE);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_BAD_SPORT_BITSET"), 0, TRUE);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHEAT_BITSET"), 0, TRUE);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHEAT_BITSET"), 0, TRUE);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHEAT_BITSET"), 0, TRUE);
	print_notification(7000, "~g~Success:~s~ Reports cleared.");
}
std::int32_t get_rp_from_rank(std::int32_t rank) {
	std::int32_t num1 = 0;
	if (rank > 120) {
		num1 = 0x210C5A;
		std::int32_t num2 = 0;
		for (num2 = 0; num2 < (rank - 120); num2++) {
			num1 += 0x73A0 + (num2 * 50);
		}
		return num1;
	}
	switch (rank) {
	case 1:
		return 0;
	case 2:
		return 800;
	case 3:
		return 0x834;
	case 4:
		return 0xed8;
	case 5:
		return 0x17d4;
	case 6:
		return 0x251c;
	case 7:
		return 0x30d4;
	case 8:
		return 0x3e80;
	case 9:
		return 0x4d58;
	case 10:
		return 0x5dc0;
	case 11:
		return 0x6f54;
	case 12:
		return 0x8278;
	case 13:
		return 0x972c;
	case 14:
		return 0xaca8;
	case 15:
		return 0xc418;
	case 0x10:
		return 0xdc50;
	case 0x11:
		return 0xf618;
	case 0x12:
		return 0x1110c;
	case 0x13:
		return 0x12d2c;
	case 20:
		return 0x14adc;
	case 0x15:
		return 0x16954;
	case 0x16:
		return 0x1895c;
	case 0x17:
		return 0x1aa90;
	case 0x18:
		return 0x1ccf0;
	case 0x19:
		return 0x1f07c;
	case 0x1a:
		return 0x21534;
	case 0x1b:
		return 0x23b18;
	case 0x1c:
		return 0x26228;
	case 0x1d:
		return 0x28a64;
	case 30:
		return 0x2b3cc;
	case 0x1f:
		return 0x2de60;
	case 0x20:
		return 0x30a20;
	case 0x21:
		return 0x3370c;
	case 0x22:
		return 0x364c0;
	case 0x23:
		return 0x39404;
	case 0x24:
		return 0x3c410;
	case 0x25:
		return 0x3f548;
	case 0x26:
		return 0x427ac;
	case 0x27:
		return 0x45b3c;
	case 40:
		return 0x48ff8;
	case 0x29:
		return 0x4c57c;
	case 0x2a:
		return 0x4fc90;
	case 0x2b:
		return 0x53408;
	case 0x2c:
		return 0x56d10;
	case 0x2d:
		return 0x5a744;
	case 0x2e:
		return 0x5e240;
	case 0x2f:
		return 0x61e68;
	case 0x30:
		return 0x65b58;
	case 0x31:
		return 0x699d8;
	case 50:
		return 0x6d920;
	case 0x33:
		return 0x71930;
	case 0x34:
		return 0x75ad0;
	case 0x35:
		return 0x79d38;
	case 0x36:
		return 0x7e0cc;
	case 0x37:
		return 0x82528;
	case 0x38:
		return 0x86ab0;
	case 0x39:
		return 0x8b100;
	case 0x3a:
		return 0x8f8e0;
	case 0x3b:
		return 0x94124;
	case 60:
		return 0x98af8;
	case 0x3d:
		return 0x9d594;
	case 0x3e:
		return 0xa20f8;
	case 0x3f:
		return 0xa6d88;
	case 0x40:
		return 0xabb44;
	case 0x41:
		return 0xb09c8;
	case 0x42:
		return 0xb5978;
	case 0x43:
		return 0xbaa54;
	case 0x44:
		return 0xbfbf8;
	case 0x45:
		return 0xc4e64;
	case 70:
		return 0xca1fc;
	case 0x47:
		return 0xcf6c0;
	case 0x48:
		return 0xd4c4c;
	case 0x49:
		return 0xda2a0;
	case 0x4a:
		return 0xdfa20;
	case 0x4b:
		return 0xe52cc;
	case 0x4c:
		return 0xeac40;
	case 0x4d:
		return 0xf067c;
	case 0x4e:
		return 0xf61e4;
	case 0x4f:
		return 0xfbe78;
	case 80:
		return 0x101bd4;
	case 0x51:
		return 0x1079f8;
	case 0x52:
		return 0x10d948;
	case 0x53:
		return 0x113960;
	case 0x54:
		return 0x119aa4;
	case 0x55:
		return 0x11fcb0;
	case 0x56:
		return 0x125fe8;
	case 0x57:
		return 0x12c3e8;
	case 0x58:
		return 0x1328b0;
	case 0x59:
		return 0x138ea4;
	case 90:
		return 0x13f5c4;
	case 0x5b:
		return 0x145d48;
	case 0x5c:
		return 0x14c5f8;
	case 0x5d:
		return 0x152fd4;
	case 0x5e:
		return 0x159a78;
	case 0x5f:
		return 0x1605e4;
	case 0x60:
		return 0x16727c;
	case 0x61:
		return 0x16dfdc;
	case 0x62:
		return 0x174e04;
	case 0x63:
		return 0x17bd58;
	case 100:
		return 0x182cde;
	case 0x65:
		return 0x189c96;
	case 0x66:
		return 0x190c80;
	case 0x67:
		return 0x197c9c;
	case 0x68:
		return 0x19ecea;
	case 0x69:
		return 0x1a5d6a;
	case 0x6a:
		return 0x1ace1c;
	case 0x6b:
		return 0x1b3f00;
	case 0x6c:
		return 0x1bb016;
	case 0x6d:
		return 0x1bfa4e;
	case 110:
		return 0x1c92d8;
	case 0x6f:
		return 0x1d0484;
	case 0x70:
		return 0x1d7662;
	case 0x71:
		return 0x1de872;
	case 0x72:
		return 0x1e5ab4;
	case 0x73:
		return 0x1ecd28;
	case 0x74:
		return 0x1f3fce;
	case 0x75:
		return 0x1fb2a6;
	case 0x76:
		return 0x2025b0;
	case 0x77:
		return 0x2098ec;
	case 120:
		return 0x210c5a;
	}
	return num1;
}
void recovery_enable_character_redesign() {
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_FM_CHANGECHAR_ASKED"), 0, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP1_FM_CHANGECHAR_ASKED"), 0, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP2_FM_CHANGECHAR_ASKED"), 0, 1);
}
void recovery_max_snacks() {
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_YUM_SNACKS"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_HEALTH_SNACKS"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_EPIC_SNACKS"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_NUMBER_OF_ORANGE_BOUGHT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CIGARETTES_BOUGHT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_NO_BOUGHT_YUM_SNACKS"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_NO_BOUGHT_HEALTH_SNACKS"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_NO_BOUGHT_EPIC_SNACKS"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_NUMBER_OF_ORANGE_BOUGHT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CIGARETTES_BOUGHT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_NO_BOUGHT_YUM_SNACKS"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_NO_BOUGHT_HEALTH_SNACKS"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_NO_BOUGHT_EPIC_SNACKS"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_NUMBER_OF_ORANGE_BOUGHT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CIGARETTES_BOUGHT"), 2000000000, 1);
}
void recovery_max_armour() {
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_1_COUNT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_2_COUNT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_3_COUNT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_4_COUNT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_5_COUNT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MP_CHAR_ARMOUR_1_COUNT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MP_CHAR_ARMOUR_2_COUNT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MP_CHAR_ARMOUR_3_COUNT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MP_CHAR_ARMOUR_4_COUNT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MP_CHAR_ARMOUR_5_COUNT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_MP_CHAR_ARMOUR_1_COUNT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_MP_CHAR_ARMOUR_2_COUNT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_MP_CHAR_ARMOUR_3_COUNT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_MP_CHAR_ARMOUR_4_COUNT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_MP_CHAR_ARMOUR_5_COUNT"), 2000000000, 1);
}
void recovery_max_fireworks() {
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_1_WHITE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_1_RED"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_1_BLUE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_2_WHITE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_2_RED"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_2_BLUE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_3_WHITE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_3_RED"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_3_BLUE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_4_WHITE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_4_RED"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_4_BLUE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_1_WHITE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_1_RED"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_1_BLUE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_2_WHITE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_2_RED"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_2_BLUE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_3_WHITE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_3_RED"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_3_BLUE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_4_WHITE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_4_RED"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_4_BLUE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_1_WHITE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_1_RED"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_1_BLUE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_2_WHITE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_2_RED"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_2_BLUE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_3_WHITE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_3_RED"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_3_BLUE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_4_WHITE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_4_RED"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_4_BLUE"), 2000000000, 1);
}
void recovery_unlock_chrome_rims() {
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_WIN_CAPTURES"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_DROPOFF_CAP_PACKAGES"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_KILL_CARRIER_CAPTURE"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FINISH_HEISTS"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FINISH_HEIST_SETUP_JOB"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_NIGHTVISION_KILLS, 100"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_WIN_LAST_TEAM_STANDINGS"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_ONLY_PLAYER_ALIVE_LTS"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_WIN_CAPTURES"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_DROPOFF_CAP_PACKAGES"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_KILL_CARRIER_CAPTURE"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FINISH_HEISTS"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FINISH_HEIST_SETUP_JOB"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_NIGHTVISION_KILLS, 100"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_WIN_LAST_TEAM_STANDINGS"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_ONLY_PLAYER_ALIVE_LTS"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_WIN_CAPTURES"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_DROPOFF_CAP_PACKAGES"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_KILL_CARRIER_CAPTURE"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_FINISH_HEISTS"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_FINISH_HEIST_SETUP_JOB"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_NIGHTVISION_KILLS, 100"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_WIN_LAST_TEAM_STANDINGS"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_ONLY_PLAYER_ALIVE_LTS"), 50, 1);
}
void recovery_infinite_ammo() {
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("FLAREGUN_FM_AMMO_CURRENT"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("GRNLAUNCH_FM_AMMO_CURRENT"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("RPG_FM_AMMO_CURRENT"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MINIGUNS_FM_AMMO_CURRENT"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("GRENADE_FM_AMMO_CURRENT"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("SMKGRENADE_FM_AMMO_CURRENT"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("STKYBMB_FM_AMMO_CURRENT"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MOLOTOV_FM_AMMO_CURRENT"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("PETROLCAN_FM_AMMO_CURRENT"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("PRXMINE_FM_AMMO_CURRENT"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("HOMLNCH_FM_AMMO_CURRENT"), -1, 1);
}
void recovery_max_skills() {
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STAM"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STRN"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_LUNG"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_DRIV"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_FLY"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_SHO"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STL"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_STAM"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_STRN"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_LUNG"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_DRIV"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_FLY"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_SHO"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_STL"), 100, 1);
}
void recovery_remove_badsport() {
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_BAD_SPORT_BITSET"), 0, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_WAS_I_BAD_SPORT"), 0, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_OVERALL_BADSPORT"), 0, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_CHAR_IS_BADSPORT"), 0, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_BECAME_BADSPORT_NUM"), 0, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_DESTROYED_PVEHICLES"), 0, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_BAD_SPORT_BITSET"), 0, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_WAS_I_BAD_SPORT"), 0, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_OVERALL_BADSPORT"), 0, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_CHAR_IS_BADSPORT"), 0, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_BECAME_BADSPORT_NUM"), 0, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_DESTROYED_PVEHICLES"), 0, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_BAD_SPORT_BITSET"), 0, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_WAS_I_BAD_SPORT"), 0, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_OVERALL_BADSPORT"), 0, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_CHAR_IS_BADSPORT"), 0, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_BECAME_BADSPORT_NUM"), 0, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_DESTROYED_PVEHICLES"), 0, 0);
}
void recovery_unlock_all() {
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_VEHICLE_1_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_VEHICLE_2_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_FM_VEHICLE_1_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_FM_VEHICLE_2_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_FM_VEHICLE_1_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_FM_VEHICLE_2_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_TDM_MVP"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_DM_TOTALKILLS"), 500, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMATTGANGHQ"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMBBETWIN"), 50000, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMWINEVERYGAMEMODE"), 1, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMRACEWORLDRECHOLDER"), 1, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMFULLYMODDEDCAR"), 1, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMMOSTKILLSSURVIVE"), 1, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMKILL3ANDWINGTARACE"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMKILLBOUNTY"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMREVENGEKILLSDM"), 50, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMKILLSTREAKSDM"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_HOLD_UP_SHOPS"), 20, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_LAPDANCES"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_SECURITY_CARS_ROBBED"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_RACES_WON"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_PLAYER_HEADSHOTS"), 500, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DB_PLAYER_KILLS"), 1000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_DM_WINS"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_TDM_MVP"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_DM_TOTALKILLS"), 500, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMATTGANGHQ"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMBBETWIN"), 50000, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMWINEVERYGAMEMODE"), 1, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMRACEWORLDRECHOLDER"), 1, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMFULLYMODDEDCAR"), 1, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMMOSTKILLSSURVIVE"), 1, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMKILL3ANDWINGTARACE"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMKILLBOUNTY"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMREVENGEKILLSDM"), 50, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMKILLSTREAKSDM"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_HOLD_UP_SHOPS"), 20, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_LAPDANCES"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_SECURITY_CARS_ROBBED"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_RACES_WON"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_PLAYER_HEADSHOTS"), 500, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_DB_PLAYER_KILLS"), 1000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_FM_DM_WINS"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_FM_TDM_MVP"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_FM_DM_TOTALKILLS"), 500, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP2_AWD_FMATTGANGHQ"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_FMBBETWIN"), 50000, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP2_AWD_FMWINEVERYGAMEMODE"), 1, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP2_AWD_FMRACEWORLDRECHOLDER"), 1, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP2_AWD_FMFULLYMODDEDCAR"), 1, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP2_AWD_FMMOSTKILLSSURVIVE"), 1, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP2_AWD_FMKILL3ANDWINGTARACE"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_FMKILLBOUNTY"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_FMREVENGEKILLSDM"), 50, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP2_AWD_FMKILLSTREAKSDM"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_HOLD_UP_SHOPS"), 20, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_LAPDANCES"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_SECURITY_CARS_ROBBED"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_RACES_WON"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_PLAYER_HEADSHOTS"), 500, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_DB_PLAYER_KILLS"), 1000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_1_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_2_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_3_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_4_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_5_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_6_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_7_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_8_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_9_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_10_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_11_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_12_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE8"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE9"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE10"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE11"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE12"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_KIT_1_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_KIT_2_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_KIT_3_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_KIT_4_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_KIT_5_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_KIT_6_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_KIT_7_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_KIT_8_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_KIT_9_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_KIT_10_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_KIT_11_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_KIT_12_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_KIT_FM_PURCHASE"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_KIT_FM_PURCHASE2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_KIT_FM_PURCHASE3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_KIT_FM_PURCHASE4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_KIT_FM_PURCHASE5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_KIT_FM_PURCHASE6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_KIT_FM_PURCHASE7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_KIT_FM_PURCHASE8"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_KIT_FM_PURCHASE9"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_KIT_FM_PURCHASE10"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_KIT_FM_PURCHASE11"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_KIT_FM_PURCHASE12"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_KIT_1_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_KIT_2_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_KIT_3_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_KIT_4_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_KIT_5_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_KIT_6_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_KIT_7_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_KIT_8_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_KIT_9_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_KIT_10_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_KIT_11_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_KIT_12_FM_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_KIT_FM_PURCHASE"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_KIT_FM_PURCHASE2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_KIT_FM_PURCHASE3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_KIT_FM_PURCHASE4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_KIT_FM_PURCHASE5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_KIT_FM_PURCHASE6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_KIT_FM_PURCHASE7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_KIT_FM_PURCHASE8"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_KIT_FM_PURCHASE9"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_KIT_FM_PURCHASE10"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_KIT_FM_PURCHASE11"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_KIT_FM_PURCHASE12"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMHORDWAVESSURVIVE"), 10, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMPICKUPDLCCRATE1ST"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_WIN_CAPTURE_DONT_DYING"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_DO_HEIST_AS_MEMBER"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_PICKUP_CAP_PACKAGES"), 100, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FINISH_HEIST_NO_DAMAGE"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_WIN_GOLD_MEDAL_HEISTS"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_KILL_TEAM_YOURSELF_LTS"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_KILL_PSYCHOPATHS"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_DO_HEIST_AS_THE_LEADER"), 25, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_STORE_20_CAR_IN_GARAGES"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMHORDWAVESSURVIVE"), 10, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMPICKUPDLCCRATE1ST"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_WIN_CAPTURE_DONT_DYING"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_DO_HEIST_AS_MEMBER"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_PICKUP_CAP_PACKAGES"), 100, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FINISH_HEIST_NO_DAMAGE"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_WIN_GOLD_MEDAL_HEISTS"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_KILL_TEAM_YOURSELF_LTS"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_KILL_PSYCHOPATHS"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_DO_HEIST_AS_THE_LEADER"), 25, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP1_AWD_STORE_20_CAR_IN_GARAGES"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_FMHORDWAVESSURVIVE"), 10, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_FMPICKUPDLCCRATE1ST"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_WIN_CAPTURE_DONT_DYING"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_DO_HEIST_AS_MEMBER"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_PICKUP_CAP_PACKAGES"), 100, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP2_AWD_FINISH_HEIST_NO_DAMAGE"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_WIN_GOLD_MEDAL_HEISTS"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_KILL_TEAM_YOURSELF_LTS"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_KILL_PSYCHOPATHS"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_DO_HEIST_AS_THE_LEADER"), 25, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP2_AWD_STORE_20_CAR_IN_GARAGES"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("DLC_MP_IND_M_PHEAD_6_0"), 1, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("DLC_MP_IND_M_PHEAD_6_0"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("DLC_MP_IND_M_PHEAD_6_1"), 1, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("DLC_MP_IND_M_PHEAD_6_1"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("DLC_MP_IND_M_PHEAD_6_2"), 1, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("DLC_MP_IND_M_PHEAD_6_2"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("DLC_MP_IND_M_PHEAD_6_3"), 1, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("DLC_MP_IND_M_PHEAD_6_3"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("DLC_MP_IND_M_PHEAD_6_4"), 1, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("DLC_MP_IND_M_PHEAD_6_4"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("DLC_MP_IND_M_PHEAD_6_5"), 1, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("DLC_MP_IND_M_PHEAD_6_5"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_RACES_WON"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_1_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_2_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_3_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_4_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_5_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_6_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_7_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMRALLYWONDRIVE"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMRALLYWONNAV"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMWINSEARACE"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMWINAIRRACE"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_NUMBER_TURBO_STARTS_IN_RACE"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_USJS_COMPLETED"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_RACES_FASTEST_LAP"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_NUMBER_SLIPSTREAMS_IN_RACE"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_RACES_WON"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_FM_CARMOD_1_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_FM_CARMOD_2_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_FM_CARMOD_3_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_FM_CARMOD_4_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_FM_CARMOD_5_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_FM_CARMOD_6_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_FM_CARMOD_7_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMRALLYWONDRIVE"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMRALLYWONNAV"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMWINSEARACE"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMWINAIRRACE"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_NUMBER_TURBO_STARTS_IN_RACE"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_USJS_COMPLETED"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_RACES_FASTEST_LAP"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_NUMBER_SLIPSTREAMS_IN_RACE"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_RACES_WON"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_FM_CARMOD_1_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_FM_CARMOD_2_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_FM_CARMOD_3_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_FM_CARMOD_4_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_FM_CARMOD_5_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_FM_CARMOD_6_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_FM_CARMOD_7_UNLCK"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_FMRALLYWONDRIVE"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_FMRALLYWONNAV"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_FMWINSEARACE"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_FMWINAIRRACE"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_NUMBER_TURBO_STARTS_IN_RACE"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_USJS_COMPLETED"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_AWD_FM_RACES_FASTEST_LAP"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_NUMBER_SLIPSTREAMS_IN_RACE"), 100, 1);
}

//world
Vector2 get_quantum_radar_pos(Vector3 world_pos) {
	Vector3 cam_coord = CAM::GET_GAMEPLAY_CAM_COORD();
	std::float_t cam_yaw = CAM::GET_GAMEPLAY_CAM_ROT(2).z + 90.0f;
	std::float_t cos_yaw = cosf(cam_yaw * (3.14159265358979323846f / 180.0f));
	std::float_t sin_yaw = sinf(cam_yaw * (3.14159265358979323846f / 180.0f));
	std::float_t delta_x = world_pos.x - cam_coord.x;
	std::float_t delta_y = world_pos.y - cam_coord.y;
	std::float_t screen_x = (delta_y * cos_yaw - delta_x * sin_yaw) / g_quantum_radar_fov;
	std::float_t screen_y = (delta_x * cos_yaw + delta_y * sin_yaw) / g_quantum_radar_fov;
	if (screen_x < -(g_quantum_radar_scale / 2.0f)) screen_x = -(g_quantum_radar_scale / 2.0f);
	else if (screen_x > (g_quantum_radar_scale / 2.0f)) screen_x = (g_quantum_radar_scale / 2.0f);
	if (screen_y < -(g_quantum_radar_scale / 2.0f)) screen_y = -(g_quantum_radar_scale / 2.0f);
	else if (screen_y > (g_quantum_radar_scale / 2.0f)) screen_y = (g_quantum_radar_scale / 2.0f);
	Vector2 out{ -screen_x + g_quantum_radar_pos_x, -screen_y + g_quantum_radar_pos_y };
	return out;
}
void update_closest_drawable_handle(std::float_t radius) {
	std::float_t current_closest_drawable_distance = 0.0f;
	std::float_t previous_closest_drawable_distance = radius;
	std::uint64_t pool = *(std::uint64_t*)(GTA_BUILDING_INST_POOL);
	if (pool) {
		std::uint32_t pool_size = *(std::uint32_t*)(pool + 0x10);
		for (std::uint32_t i = 0; i < pool_size; i++) {
			CBuilding* drawable = (CBuilding*)(get_element_from_pool(pool, i));
			if (drawable) {
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, 0.0f, 0.0f);
				current_closest_drawable_distance = abs(coords.x - drawable->x) + abs(coords.y - drawable->y) + abs(coords.z - drawable->z);
				if (current_closest_drawable_distance < previous_closest_drawable_distance) {
					previous_closest_drawable_distance = current_closest_drawable_distance;
					g_menu_drawable_manager_current_closest_drawable = drawable;
				}
			}
		}
	}
}

//misc
void set_session_time(std::int32_t h, std::int32_t m, std::int32_t s) {
	NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(h, m, s);
}
void force_host_of_script(std::string script_name) {
	std::uint64_t pool = *(std::uint64_t*)(GTA_NETWORKED_SCRIPT_HANDLERS);
	if (pool) {

		std::uint32_t pool_size = *(std::uint32_t*)(pool + 0x10);
		for (std::uint32_t i = 0; i < pool_size; i++) {

			CGameScriptHandlerNetwork* handler = (CGameScriptHandlerNetwork*)(get_element_from_pool(pool, i));
			if (handler) {

				if (!GAMEPLAY::ARE_STRINGS_EQUAL(handler->GameScriptId.ScriptName, script_name.c_str()))
					continue;

				CGameScriptHandlerNetComponent* component = handler->GameScriptHandlerNetComponent;
				if (component) {

					std::uint64_t net_game_player = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::uint64_t(*)(std::uint8_t))GTA_GET_NET_GAME_PLAYER_FROM_PHYSICAL_INDEX), (std::uint8_t)(PLAYER::PLAYER_ID()));
					if (net_game_player != NULL) {
						SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((void(*)(CGameScriptHandlerNetComponent*, std::uint64_t))GTA_FORCE_SCRIPT_HOST), component, net_game_player);
					}
				}
			}
		}
	}
}

void menu_loops_handler() {
	
	// self
	if (g_self_god_mode) {
		ENTITY::SET_ENTITY_PROOFS(PLAYER::PLAYER_PED_ID(), TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE);
		PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 32, TRUE);
		PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 33, TRUE);
		PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 281, TRUE);
	}

	if (g_self_invisibility)
		ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), FALSE, 0);

	if (g_self_no_ragdoll)
		PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), FALSE);

	if (g_self_no_cops)
		PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());

	if (g_self_forcefield) {
		Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, 0.0f, 0.0f);
		FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, 7, FLT_MAX, FALSE, TRUE, 0.0f);
	}

	if (g_self_super_run) {
		if (CONTROLS::IS_CONTROL_PRESSED(0, INPUT_SPRINT))
			ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::PLAYER_PED_ID(), TRUE, 0.0f, g_self_super_run_modifier, 0.0f, 0.0f, 0.0f, 0.0f, TRUE, TRUE, TRUE, TRUE, FALSE, TRUE);\
	}

	// ped factory required
	//std::uint64_t ped_factory = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(GTA_PED_FACTORY);
	//if (ped_factory != NULL) {

	//	// local ped addr required
	//	std::uint64_t entity = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(ped_factory + 0x8);
	//	if (entity != NULL) {

	//		// ped weapon manager required
	//		std::add_pointer_t<CPedWeaponManager> ped_weapon_mgr = *reinterpret_cast<std::add_pointer_t<std::add_pointer_t<CPedWeaponManager>>>(entity + 0x10C8);
	//		if (ped_weapon_mgr != nullptr) {

	//			// weapon info required
	//			if (ped_weapon_mgr->WeaponInfo != nullptr) {

	//				if (g_weapon_quick_reload) {
	//					ped_weapon_mgr->WeaponInfo->AnimReloadRate = 5.0f;
	//				}
	//				else {
	//					ped_weapon_mgr->WeaponInfo->AnimReloadRate = 1.0f;
	//				}

	//				if (g_weapon_special_shotgun) {
	//					ped_weapon_mgr->WeaponInfo->BatchSpread = 0.5f;
	//					ped_weapon_mgr->WeaponInfo->BulletsInBatch = 30;
	//					ped_weapon_mgr->WeaponInfo->Force = 200.0f;
	//					ped_weapon_mgr->WeaponInfo->Speed = 5000.0f;
	//				}
	//				else {
	//					ped_weapon_mgr->WeaponInfo->BatchSpread = 0.1f;
	//					ped_weapon_mgr->WeaponInfo->BulletsInBatch = 1;
	//					ped_weapon_mgr->WeaponInfo->Force = 200.0f;
	//					ped_weapon_mgr->WeaponInfo->Speed = 5000.0f;
	//				}

	//				if (g_weapon_special_rubber_bullets) {
	//					ped_weapon_mgr->WeaponInfo->Damage = -1000.0f;
	//				}
	//				else {
	//					ped_weapon_mgr->WeaponInfo->Damage = 100.0f;
	//				}

	//				if (g_weapon_no_recoil) {
	//					ped_weapon_mgr->WeaponInfo->RecoilShakeAmplitude = 0.0f;
	//				}
	//				else {
	//					ped_weapon_mgr->WeaponInfo->RecoilShakeAmplitude = 0.2f;
	//				}

	//				if (g_weapon_no_stun_gun_cooldown) {
	//					ped_weapon_mgr->WeaponInfo->TimeBetweenShots = 0.0f;
	//				}
	//			}
	//		}

	//		if (g_self_menu_ped_lean_active) {
	//			*reinterpret_cast<std::add_pointer_t<std::float_t>>(entity + 0x80) = g_self_menu_ped_lean;
	//		}
	//		if (g_self_menu_ped_width_active) {
	//			*reinterpret_cast<std::add_pointer_t<std::float_t>>(entity + 0x60) = g_self_menu_ped_width;
	//		}
	//		if (g_self_menu_ped_height_active) {
	//			*reinterpret_cast<std::add_pointer_t<std::float_t>>(entity + 0x88) = g_self_menu_ped_height;
	//		}
	//	}
	//}

	if (g_self_super_jump) {
		if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, INPUT_JUMP)) {
			if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(PLAYER::PLAYER_PED_ID()) < 2.0f)
				ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::PLAYER_PED_ID(), TRUE, 0.0f, 0.0f, 15.0f, 0.0f, 0.0f, 0.0f, TRUE, TRUE, TRUE, TRUE, FALSE, TRUE);
		}
	}

	if (g_self_super_swim)
		PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), 10.0f);

	if (g_self_night_vision)
		GRAPHICS::SET_NIGHTVISION(TRUE);

	if (g_self_heat_vision)
		GRAPHICS::SET_SEETHROUGH(TRUE);

	if (g_self_shrink)
		PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 223, TRUE);

	if (g_self_slow_motion)
		GAMEPLAY::SET_TIME_SCALE(0.4f);

	if (g_self_superman) {

		if (!PED::IS_PED_IN_PARACHUTE_FREE_FALL(PLAYER::PLAYER_PED_ID())) {
			if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, INPUT_JUMP))
				ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::PLAYER_PED_ID(), TRUE, 0.0f, 0.0f, 15.0f, 0.0f, 0.0f, 0.0f, TRUE, TRUE, TRUE, TRUE, FALSE, TRUE);
			if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(PLAYER::PLAYER_PED_ID()) > 4.0f)
				AI::TASK_SKY_DIVE(PLAYER::PLAYER_PED_ID());
		}
		else ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::PLAYER_PED_ID(), TRUE, 0.0f, 100.0f, 100.0f, 0.0f, 0.0f, 0.0f, FALSE, TRUE, FALSE, FALSE, FALSE, TRUE);
	}

	if (g_self_mobile_radio)
		AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(TRUE);

	//if (g_self_cops_turn_blind_eye) {
	//	*scr_global(2531497).at(4558).as<std::int32_t*>() = NETWORK::GET_NETWORK_TIME() + 60;
	//	*scr_global(2531497).at(4555).as<std::int32_t*>() = 5;
	//	*scr_global(1590446).at(70).at(PLAYER::PLAYER_ID(), 871).at(746).as<std::int32_t*>() = 1;
	//}

	//if (g_self_off_the_radar) {
	//	*scr_global(2424073).at(PLAYER::PLAYER_ID(), 421).at(200).as<std::int32_t*>() = 1;
	//	*scr_global(2437549).at(70).as<std::int32_t*>() = NETWORK::GET_NETWORK_TIME() + 60;
	//}

	//if (g_self_reveal_players) {
	//	*scr_global(2424073).at(PLAYER::PLAYER_ID(), 421).at(203).as<std::int32_t*>() = 1;
	//	*scr_global(2437549).at(71).as<std::int32_t*>() = NETWORK::GET_NETWORK_TIME() + 60;
	//}

	// weapon
	if (g_vortex_gun_active)
		vortex_gun();

	if (g_weapon_unlimited_ammo)
		WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), TRUE);

	if (g_weapon_no_reload)
		WEAPON::_PED_SKIP_NEXT_RELOADING(PLAYER::PLAYER_PED_ID());

	if (g_weapon_dead_eye) {
		if (PED::IS_PED_ON_FOOT(PLAYER::PLAYER_PED_ID())) {
			if (CONTROLS::IS_CONTROL_PRESSED(0, INPUT_AIM)) {
				GAMEPLAY::SET_TIME_SCALE(0.20f);
				GRAPHICS::ANIMPOSTFX_PLAY("HeistLocate", 0, FALSE);
			}
			else if (CONTROLS::IS_CONTROL_RELEASED(0, INPUT_AIM)) {
				GAMEPLAY::SET_TIME_SCALE(1.00f);
				GRAPHICS::ANIMPOSTFX_STOP("HeistLocate");
			}
		}
	}

	if (PLAYER::IS_PLAYER_FREE_AIMING(PLAYER::PLAYER_ID()) || PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID())) {
		if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
			std::int32_t weapon = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID());
			if (ENTITY::DOES_ENTITY_EXIST(weapon)) {
				//g_weapon_aiming_coords = get_coords_in_front_of_cam(500.0f);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(weapon, 1.5f, 0.0f, 0.0f);

				if (g_weapon_laser_sight) {
					GRAPHICS::DRAW_LINE(coords.x, coords.y, coords.z, g_weapon_aiming_coords.x, g_weapon_aiming_coords.y, g_weapon_aiming_coords.z, g_menu_header_colour.r, g_menu_header_colour.g, g_menu_header_colour.b, g_menu_header_colour.a);
				}

				if (g_weapon_special_gravity) {
					if (!g_gravity_cooldown) {
						if (!ENTITY::DOES_ENTITY_EXIST(g_gravity_entity)) {
							g_shape_test_did_hit = FALSE;
							g_shape_test_entity = NULL;
							g_shape_test_destination.x = 0.0f;
							g_shape_test_destination.y = 0.0f;
							g_shape_test_destination.z = 0.0f;
							g_shape_test_surface.x = 0.0f;
							g_shape_test_surface.y = 0.0f;
							g_shape_test_surface.z = 0.0f;
							g_shape_test_ray = NULL;
							g_shape_test_ray = WORLDPROBE::_START_SHAPE_TEST_RAY(coords.x, coords.y, coords.z, g_weapon_aiming_coords.x, g_weapon_aiming_coords.y, g_weapon_aiming_coords.z, -1, PLAYER::PLAYER_PED_ID(), 7);
							//WORLDPROBE::GET_SHAPE_TEST_RESULT(g_shape_test_ray, &g_shape_test_did_hit, g_shape_test_destination, &g_shape_test_surface, &g_shape_test_entity);

							if (ENTITY::DOES_ENTITY_EXIST(g_shape_test_entity))
								if (ENTITY::IS_ENTITY_AN_OBJECT(g_shape_test_entity) || ENTITY::IS_ENTITY_A_VEHICLE(g_shape_test_entity) || ENTITY::IS_ENTITY_A_PED(g_shape_test_entity))
									g_gravity_entity = g_shape_test_entity;
						}
						else {
							//g_gravity_pos = get_coords_in_front_of_cam(g_weapon_gravity_distance);
							if (change_net_obj_owner(g_gravity_entity, PLAYER::PLAYER_ID())) {
								switch (ENTITY::GET_ENTITY_TYPE(g_gravity_entity)) {
								case 1: {
										if (g_weapon_gravity_entity == 0) {
											if (ENTITY::IS_ENTITY_A_PED(g_shape_test_entity) && !PED::IS_PED_ON_FOOT(g_gravity_entity))
												g_gravity_entity = PED::GET_VEHICLE_PED_IS_IN(g_gravity_entity, 0);
										}
										else if (g_weapon_gravity_entity == 1) {
											ENTITY::FREEZE_ENTITY_POSITION(g_gravity_entity, false);
											PED::SET_PED_TO_RAGDOLL(g_gravity_entity, 1, 1, 1, 1, 1, 1);
											Vector3 l_gravity_entity_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_gravity_entity, 0.0f, 0.0f, 0.0f);
											std::float_t L_force[3];
											L_force[0] = (g_gravity_pos.x - l_gravity_entity_coords.x) * 4;
											L_force[1] = (g_gravity_pos.y - l_gravity_entity_coords.y) * 4;
											L_force[2] = (g_gravity_pos.z - l_gravity_entity_coords.z) * 4;
											ENTITY::SET_ENTITY_VELOCITY(g_gravity_entity, L_force[0], L_force[1], L_force[2]);
										}
									} break;
								case 2: {
										if (g_weapon_gravity_entity == 0) {
											if (!g_check_gravity_veh_dim) {
												/*Grab Dimensions HERE...*/
												g_check_gravity_veh_dim = true;
											}
											else {
												ENTITY::FREEZE_ENTITY_POSITION(g_gravity_entity, false);
												Vector3 l_gravity_entity_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_gravity_entity, 0.0f, 0.0f, 0.0f);
												std::float_t L_force[3];
												L_force[0] = (g_gravity_pos.x - l_gravity_entity_coords.x) * 4;
												L_force[1] = (g_gravity_pos.y - l_gravity_entity_coords.y) * 4;
												L_force[2] = (g_gravity_pos.z - l_gravity_entity_coords.z) * 4;
												ENTITY::SET_ENTITY_VELOCITY(g_gravity_entity, L_force[0], L_force[1], L_force[2]);
											}
										}
									} break;
								case 3: {
										if (g_weapon_gravity_entity == 2) {
											ENTITY::FREEZE_ENTITY_POSITION(g_gravity_entity, false);
											Vector3 l_gravity_entity_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_gravity_entity, 0.0f, 0.0f, 0.0f);
											std::float_t L_force[3];
											L_force[0] = (g_gravity_pos.x - l_gravity_entity_coords.x) * 4;
											L_force[1] = (g_gravity_pos.y - l_gravity_entity_coords.y) * 4;
											L_force[2] = (g_gravity_pos.z - l_gravity_entity_coords.z) * 4;
											ENTITY::SET_ENTITY_VELOCITY(g_gravity_entity, L_force[0], L_force[1], L_force[2]);
										}
									} break;
								default: g_gravity_entity = 0; break;
								}
							}
						}
					}
				}

				if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID())) {
					g_shape_test_did_hit = FALSE;
					g_shape_test_entity = NULL;
					g_shape_test_destination.x = 0.0f;
					g_shape_test_destination.y = 0.0f;
					g_shape_test_destination.z = 0.0f;
					g_shape_test_surface.x = 0.0f;
					g_shape_test_surface.y = 0.0f;
					g_shape_test_surface.z = 0.0f;
					g_shape_test_ray = NULL;
					g_shape_test_ray = WORLDPROBE::_START_SHAPE_TEST_RAY(coords.x, coords.y, coords.z, g_weapon_aiming_coords.x, g_weapon_aiming_coords.y, g_weapon_aiming_coords.z, -1, PLAYER::PLAYER_PED_ID(), 7);
					//WORLDPROBE::GET_SHAPE_TEST_RESULT(g_shape_test_ray, &g_shape_test_did_hit, &g_shape_test_destination, &g_shape_test_surface, &g_shape_test_entity);

					if (ENTITY::DOES_ENTITY_EXIST(g_gravity_entity)) {
						Vector3 l_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, 0.0f, 0.0f);
						Vector3 l_offset = ENTITY::GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(g_gravity_entity, l_coords.x, l_coords.y, l_coords.z);
						std::float_t l_factor = fabs(g_weapon_gravity_sling_force / l_offset.y);
						ENTITY::FREEZE_ENTITY_POSITION(g_gravity_entity, false);
						ENTITY::APPLY_FORCE_TO_ENTITY(g_gravity_entity, 1, -l_offset.x * l_factor, -l_offset.y * l_factor, -l_offset.z * l_factor, 0, 0, 0, 0, 1, 1, 1, 0, 1);
						g_check_gravity_veh_dim = false;
						g_gravity_cooldown = true;
						g_gravity_entity = 0;
					}

					if (g_weapon_special_grapple) {
						if (g_shape_test_destination.x != 0.0f && g_shape_test_destination.y != 0.0f && g_shape_test_destination.z != 0.0f) {
							Vector3 weapon_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID()), 0.0f, 0.0f, 0.0f);
							std::float_t distance = SYSTEM::VDIST(g_shape_test_destination.x, g_shape_test_destination.y, g_shape_test_destination.z, weapon_coords.x, weapon_coords.y, weapon_coords.z);

							g_weapon_special_pos.x = g_shape_test_destination.x;
							g_weapon_special_pos.y = g_shape_test_destination.y;
							g_weapon_special_pos.z = g_shape_test_destination.z;
							g_weapon_special_grapple_enabled = true;
						}
					}

					if (g_weapon_explosive_impact)
						FIRE::ADD_EXPLOSION(g_shape_test_destination.x, g_shape_test_destination.y, g_shape_test_destination.z, g_weapon_explosive_impact_type, FLT_MAX, TRUE, FALSE, 0.2f);

					if (g_weapon_special_teleport)
						ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PLAYER::PLAYER_PED_ID(), g_shape_test_destination.x, g_shape_test_destination.y, g_shape_test_destination.z, 0, 0, 1);
					
					if (g_weapon_special_delete) {
						if (g_shape_test_did_hit) {
							if (ENTITY::DOES_ENTITY_EXIST(g_shape_test_entity)) {
								ENTITY::SET_ENTITY_AS_MISSION_ENTITY(g_shape_test_entity, 0, 1);
								switch (ENTITY::GET_ENTITY_TYPE(g_shape_test_entity)) {
								case 0: g_shape_test_entity = NULL; break;
								case 1: { //PED
										if (change_net_obj_owner(g_shape_test_entity, PLAYER::PLAYER_ID())) {
											if (PED::IS_PED_IN_ANY_VEHICLE(g_shape_test_entity, false)) {
												g_shape_test_entity = PED::GET_VEHICLE_PED_IS_IN(g_shape_test_entity, false);
												INT l_seats = VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(ENTITY::GET_ENTITY_MODEL(g_shape_test_entity));
												for (INT i = -1; i < l_seats - 1; i++) {
													if (!VEHICLE::IS_VEHICLE_SEAT_FREE(g_shape_test_entity, i)) {
														INT l_ped = VEHICLE::GET_PED_IN_VEHICLE_SEAT(g_shape_test_entity, i);
														if (NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(l_ped))
															PED::DELETE_PED(&l_ped);
													}
												}
												VEHICLE::DELETE_VEHICLE(&g_shape_test_entity);
												ENTITY::SET_ENTITY_COORDS(g_shape_test_entity, 6000.0, 6000.0, 6000.0, true, false, false, true);
											}
											else {
												PED::DELETE_PED(&g_shape_test_entity);
												ENTITY::SET_ENTITY_COORDS(g_shape_test_entity, 6000.0, 6000.0, 6000.0, true, false, false, true);
											}
										}
									} break;
								case 2: { //VEHICLE
									if (change_net_obj_owner(g_shape_test_entity, PLAYER::PLAYER_ID())) {
											VEHICLE::DELETE_VEHICLE(&g_shape_test_entity);
											ENTITY::SET_ENTITY_COORDS(g_shape_test_entity, 6000.0, 6000.0, 6000.0, true, false, false, true);
										}
									} break;
								case 3: { //OBJECT
									if (change_net_obj_owner(g_shape_test_entity, PLAYER::PLAYER_ID())) {
											ENTITY::DETACH_ENTITY(g_shape_test_entity, 1, 1);
											ENTITY::SET_ENTITY_COORDS(g_shape_test_entity, 6000.0, 6000.0, 6000.0, true, false, false, true);
											ENTITY::DELETE_ENTITY(&g_shape_test_entity);
										}
									} break;
								}
							}
						}
					}

					if (g_weapon_bullet_changer) {
						std::int32_t hash = GAMEPLAY::GET_HASH_KEY(g_weapon_bullet_types[g_weapon_bullet_changer_selected_arr_index].c_str());
						WEAPON::REQUEST_WEAPON_ASSET(hash, 31, 0);
						while (!WEAPON::HAS_WEAPON_ASSET_LOADED(hash))
							Script::GetCurrent()->ScriptYield();
						GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords.x, coords.y, coords.z, g_weapon_aiming_coords.x, g_weapon_aiming_coords.y, g_weapon_aiming_coords.z, 250, FALSE, hash, PLAYER::PLAYER_PED_ID(), g_weapon_bullet_changer_audible, g_weapon_bullet_changer_invisible, g_weapon_bullet_changer_speed);
					}
				}
			}
		}
	}
	else {
		g_gravity_cooldown = false;
	}

	if (g_weapon_totem_gun) {
		if (PED::IS_PED_ON_FOOT(PLAYER::PLAYER_PED_ID()) && PLAYER::IS_PLAYER_FREE_AIMING(PLAYER::PLAYER_ID())) {
			Vector3 vehicle_dir = get_gameplay_camera_direction();
			Vector3 vehicle_pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID()), 5.0f, 0.0f, 0.0f);

			ListPool* vehicle_pool = *(ListPool**)(GTA_VEH_LIST_POOL);
			if (vehicle_pool != nullptr) {
				for (std::int32_t i = 0; i < vehicle_pool->capacity; i++) {

					std::uint64_t vehicle_entity = vehicle_pool->get(i);
					if (vehicle_entity == NULL)
						continue;

					std::int32_t vehicle = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::int32_t(*)(std::uint64_t))GTA_GET_SCRIPT_INDEX_FROM_ENTITY), vehicle_entity);
					if (!ENTITY::DOES_ENTITY_EXIST(vehicle))
						continue;

					NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehicle);
					change_net_obj_owner(vehicle, PLAYER::PLAYER_ID());

					if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(vehicle))
						ENTITY::SET_ENTITY_COORDS(vehicle, vehicle_pos.x + (vehicle_dir.x * g_weapon_totem_gun_distance), vehicle_pos.y + (vehicle_dir.y * g_weapon_totem_gun_distance), vehicle_pos.z + (vehicle_dir.z * g_weapon_totem_gun_distance) + ((i - 1) * g_weapon_totem_gun_spacing), 1, 1, 1, 1);
				}
			}
		}
	}

	if (g_weapon_special_grapple_enabled) {
		Vector3 player_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, 0.0f, 0.0f);
		std::float_t distance = SYSTEM::VDIST(g_weapon_special_pos.x, g_weapon_special_pos.y, g_weapon_special_pos.z, player_coords.x, player_coords.y, player_coords.z);
		if (distance < 3.0f) {
			AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
			AI::CLEAR_PED_SECONDARY_TASK(PLAYER::PLAYER_PED_ID());
			g_weapon_special_grapple_enabled = false;
		}
		else {
			Vector3 entity_velocity;
			entity_velocity.x = (g_weapon_special_pos.x - player_coords.x) * 3.0f;
			entity_velocity.y = (g_weapon_special_pos.y - player_coords.y) * 3.0f;
			entity_velocity.z = (g_weapon_special_pos.z - player_coords.z) * 3.0f;
			AI::TASK_SKY_DIVE(PLAYER::PLAYER_PED_ID());
			ENTITY::SET_ENTITY_VELOCITY(PLAYER::PLAYER_PED_ID(), entity_velocity.x, entity_velocity.y, entity_velocity.z);
		}
	}

	if (g_weapon_special_vehicle) {
		if (PED::IS_PED_ON_FOOT(PLAYER::PLAYER_PED_ID()) && PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID())) {
			Vector3 vehicle_dir = get_gameplay_camera_direction();
			Vector3 vehicle_pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID()), 5.0f, 0.0f, 0.0f);

			ListPool* vehicle_pool = *(ListPool**)(GTA_VEH_LIST_POOL);
			if (vehicle_pool != nullptr) {

				std::uint32_t found_vehicles = NULL;
				for (std::int32_t i = 0; i < vehicle_pool->capacity; i++) {

					std::uint64_t vehicle_entity = vehicle_pool->get(i);
					if (vehicle_entity == NULL)
						continue;

					std::int32_t vehicle = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::int32_t(*)(std::uint64_t))GTA_GET_SCRIPT_INDEX_FROM_ENTITY), vehicle_entity);
					if (!ENTITY::DOES_ENTITY_EXIST(vehicle))
						continue;

					if (found_vehicles++ == g_vortex_gun_vehicle_capacity)
						break;

					NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehicle);
					change_net_obj_owner(vehicle, PLAYER::PLAYER_ID());

					if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(vehicle)) {

						ENTITY::SET_ENTITY_COORDS(vehicle, vehicle_pos.x, vehicle_pos.y, vehicle_pos.z, 1, 0, 0, 1);

						Vector3 l_vOffset = ENTITY::GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(vehicle,
							(vehicle_pos.x + (vehicle_dir.x * 500.0f)),
							(vehicle_pos.y + (vehicle_dir.y * 500.0f)),
							(vehicle_pos.z + (vehicle_dir.z * 500.0f)));

						ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 1, l_vOffset.x, l_vOffset.y, l_vOffset.z, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, FALSE, TRUE);
					}
				}
			}
		}
	}

	// network
	if (g_menu_network_spoofing_name_active) {
		const char* name = PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID());
		if (name != nullptr) {
			strcpy_s((char*)(name), 16, g_menu_network_spoofing_name.c_str());
		}
	}

	// player required
	for (std::int32_t i = 0; i < 32; i++) {

		if (g_network_streamer_mode_active) {
			if (i != PLAYER::PLAYER_ID() || g_network_streamer_mode_self_included) {

				std::stringstream ss;
				if (g_network_streamer_mode_display_as_hex)
					ss << g_network_streamer_mode_prefix << "_" << std::hex << i;
				else ss << g_network_streamer_mode_prefix << "_" << i;

				if (strcmp(PLAYER::GET_PLAYER_NAME(i), ss.str().c_str()))
					strcpy_s((char*)(PLAYER::GET_PLAYER_NAME(i)), 16, ss.str().c_str());
			}
		}

		// player ped required
		std::int32_t ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {

			// player coords required
			Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, 0.0f, 0.0f, 0.0f);

			if (g_protection_redirect_bullets) {
				if (PED::IS_PED_SHOOTING(ped)) {
					if (PLAYER::IS_PLAYER_FREE_AIMING_AT_ENTITY(i, PLAYER::PLAYER_PED_ID())) {
						Hash weapon = NULL;
						if (WEAPON::GET_CURRENT_PED_WEAPON(ped, &weapon, FALSE)) {
							WEAPON::REQUEST_WEAPON_ASSET(weapon, 31, 0);
							GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords.x, coords.y, coords.z + 10.0f, coords.x, coords.y, coords.z, 100, 0, weapon, PLAYER::PLAYER_PED_ID(), 1, 0, 1000.0f);
						}
					}
				}
			}

			if (g_network_player_vars[i].m_looped_explosion_active) {
				FIRE::ADD_EXPLOSION(coords.x + g_network_player_vars[i].m_looped_explosion_offset.x, coords.y + g_network_player_vars[i].m_looped_explosion_offset.y, coords.z + g_network_player_vars[i].m_looped_explosion_offset.z, g_network_player_vars[i].m_looped_explosion_selected_arr_index, FLT_MAX, g_network_player_vars[i].m_looped_explosion_audible, g_network_player_vars[i].m_looped_explosion_invisible, 0.2f);
			}

			if (g_network_player_vars[i].m_take_weapons) {
				WEAPON::REMOVE_ALL_PED_WEAPONS(ped, TRUE);
			}

			if (g_network_player_vars[i].m_freeze_loop) {
				AI::CLEAR_PED_TASKS_IMMEDIATELY(ped);
			}

			if (PED::IS_PED_IN_ANY_VEHICLE(ped, TRUE)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);

				// vehicle required
				if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {

					// horn required
					if (PLAYER::IS_PLAYER_PRESSING_HORN(PLAYER::PLAYER_ID())) {
						if (g_network_player_vars[i].m_horn_boost_active) {
							ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, TRUE, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, TRUE, TRUE, TRUE, TRUE, FALSE, TRUE);
						}
					}
				}
			}

			std::int32_t our_ped = PLAYER::PLAYER_PED_ID();

			// our ped required
			if (ENTITY::DOES_ENTITY_EXIST(our_ped)) {
				Vector3 our_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(our_ped, 0.0f, 0.0f, 0.0f);
				if (g_network_player_vars[i].m_esp_line) {
					GRAPHICS::DRAW_LINE(our_coords.x, our_coords.y, our_coords.z, coords.x, coords.y, coords.z, g_menu_header_text_colour.r, g_menu_header_text_colour.g, g_menu_header_text_colour.b, g_menu_header_text_colour.a);
				}
			}

			if (g_network_player_vars[i].m_esp_name) {
				GRAPHICS::SET_DRAW_ORIGIN(coords.x, coords.y, coords.z, NULL);
				draw_text(PLAYER::GET_PLAYER_NAME(i), 0.0f, 0.0f, 4, 0.43f, g_menu_header_text_colour, true, false, true);
				GRAPHICS::CLEAR_DRAW_ORIGIN();
			}

			if (g_network_player_vars[i].m_esp_box) {
				draw_box_esp(ped, g_menu_header_text_colour);
			}

		}

		//==== Chat Commands ====

		// help
		if (g_chat_command_clients[i].m_mod_active[0]) {

			std::stringstream ss;
			ss << "~b~Commands~s~" << std::endl;
			for (INT j = 0; j < ARRAYSIZE(g_chat_commands); j++)
				ss << g_chat_commands[j] << std::endl;
			g_chat_command_clients[i].m_mod_active[0] = false;
		}
	}

	// pedestrian required
	for (auto i = 0; i < std::size(g_pedestrian_peds); i++) {
		if (ENTITY::DOES_ENTITY_EXIST(g_pedestrian_peds[i].handle)) {
			if (!PED::IS_PED_DEAD_OR_DYING(g_pedestrian_peds[i].handle, 1)) {
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_pedestrian_peds[i].handle, 0.0f, 0.0f, 0.0f);

				if (g_all_pedestrian_draw_esp) {
					Vector3 my_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, 0.0f, 0.0f);
					GRAPHICS::DRAW_LINE(my_coords.x, my_coords.y, my_coords.z, coords.x, coords.y, coords.z, g_menu_header_text_colour.r, g_menu_header_text_colour.g, g_menu_header_text_colour.b, 255);
				}

				if (g_pedestrian_peds[i].is_invincible)
					ENTITY::SET_ENTITY_PROOFS(g_pedestrian_peds[i].handle, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE);

				if (g_pedestrian_peds[i].is_invisible)
					ENTITY::SET_ENTITY_VISIBLE(g_pedestrian_peds[i].handle, FALSE, 0);

				if (g_pedestrian_peds[i].draw_esp) {
					Vector3 my_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, 0.0f, 0.0f);
					GRAPHICS::DRAW_LINE(my_coords.x, my_coords.y, my_coords.z, coords.x, coords.y, coords.z, g_menu_header_text_colour.r, g_menu_header_text_colour.g, g_menu_header_text_colour.b, 255);
				}

			}
		}
	}

	// vehicle required
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
		std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), TRUE);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {

			// los santos customs
			if (g_vehicle_rainbow_paint_fade) {
				if (g_vehicle_rainbow_paint_fade_colour.r > 0 && g_vehicle_rainbow_paint_fade_colour.b == 0) {
					g_vehicle_rainbow_paint_fade_colour.r--;
					g_vehicle_rainbow_paint_fade_colour.g++;
				}
				if (g_vehicle_rainbow_paint_fade_colour.g > 0 && g_vehicle_rainbow_paint_fade_colour.r == 0) {
					g_vehicle_rainbow_paint_fade_colour.g--;
					g_vehicle_rainbow_paint_fade_colour.b++;
				}
				if (g_vehicle_rainbow_paint_fade_colour.b > 0 && g_vehicle_rainbow_paint_fade_colour.g == 0) {
					g_vehicle_rainbow_paint_fade_colour.r++;
					g_vehicle_rainbow_paint_fade_colour.b--;
				}
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, g_vehicle_rainbow_paint_fade_colour.r, g_vehicle_rainbow_paint_fade_colour.g, g_vehicle_rainbow_paint_fade_colour.b);
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, g_vehicle_rainbow_paint_fade_colour.r, g_vehicle_rainbow_paint_fade_colour.g, g_vehicle_rainbow_paint_fade_colour.b);
			}

			// vehicle handling
			if (g_vehicle_fly_vehicle) {
				if (KEYBOARD::IS_KEYBOARD_INPUT_PRESSED((int)('W')) || CONTROLS::IS_CONTROL_PRESSED(2, INPUT_FRONTEND_RT)) //Forward
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, (ENTITY::GET_ENTITY_SPEED(vehicle) + 0.5f));
				if (KEYBOARD::IS_KEYBOARD_INPUT_PRESSED((int)('S')) || CONTROLS::IS_CONTROL_PRESSED(2, INPUT_FRONTEND_LT)) //Stop
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, 0.0f);
				if (KEYBOARD::IS_KEYBOARD_INPUT_JUST_PRESSED(KeyboardMenuNavLeft) || CONTROLS::IS_CONTROL_PRESSED(2, INPUT_FRONTEND_LEFT)) { //Left
					if (!VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(vehicle)) {
						Vector3 l_rot = ENTITY::GET_ENTITY_ROTATION(vehicle, 2);
						std::float_t l_new_rot = l_rot.z;
						l_new_rot += 1.0f;
						ENTITY::SET_ENTITY_ROTATION(vehicle, l_rot.x, l_rot.y, l_new_rot, 2, 1);
					}
				}
				if (KEYBOARD::IS_KEYBOARD_INPUT_JUST_PRESSED(KeyboardMenuNavRight) || CONTROLS::IS_CONTROL_PRESSED(2, INPUT_FRONTEND_RIGHT)) { //Right
					if (!VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(vehicle)) {
						Vector3 l_rot = ENTITY::GET_ENTITY_ROTATION(vehicle, 2);
						std::float_t l_new_rot = l_rot.z;
						l_new_rot -= 1.0f;
						ENTITY::SET_ENTITY_ROTATION(vehicle, l_rot.x, l_rot.y, l_new_rot, 2, 1);
					}
				}
				if (ENTITY::GET_ENTITY_SPEED(vehicle) >= 40.0f && VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(vehicle))
					ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 1, 0.0f, 0.0f, 0.28f, 0.0f, 2.50f, 0.0f, TRUE, TRUE, TRUE, TRUE, FALSE, TRUE);
			}

			if (g_vehicle_drive_in_air) {
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
					Vector3 l_position = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, 0.0f, 0.0f);
					if (!g_vehicle_drive_in_air) {
						std::float_t l_water_height;
						WATER::GET_WATER_HEIGHT(l_position.x, l_position.y, l_position.z, &l_water_height);
						ENTITY::SET_ENTITY_COORDS(g_drive_wheel_object, l_position.x, l_position.y, l_water_height - 2.0f, 1, 0, 0, 1);
					}
					else
						ENTITY::SET_ENTITY_COORDS(g_drive_wheel_object, l_position.x, l_position.y, 360, 1, 0, 0, 1);
					ENTITY::SET_ENTITY_ROTATION(g_drive_wheel_object, 180, 90, 180, 2, 1);
					ENTITY::SET_ENTITY_VISIBLE(g_drive_wheel_object, false, 0);
					ENTITY::FREEZE_ENTITY_POSITION(g_drive_wheel_object, true);
				}
			}

			if (g_vehicle_drive_on_water) {
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
					Vector3 l_position = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, 0.0f, 0.0f);
					if (!g_vehicle_drive_in_air) {
						std::float_t l_water_height;
						WATER::GET_WATER_HEIGHT(l_position.x, l_position.y, l_position.z, &l_water_height);
						ENTITY::SET_ENTITY_COORDS(g_drive_wheel_object, l_position.x, l_position.y, l_water_height - 2.0f, 1, 0, 0, 1);
					}
					else
						ENTITY::SET_ENTITY_COORDS(g_drive_wheel_object, l_position.x, l_position.y, 360, 1, 0, 0, 1);
					ENTITY::SET_ENTITY_ROTATION(g_drive_wheel_object, 180, 90, 180, 2, 1);
					ENTITY::SET_ENTITY_VISIBLE(g_drive_wheel_object, false, 0);
					ENTITY::FREEZE_ENTITY_POSITION(g_drive_wheel_object, true);
				}
			}

			if (g_vehicle_drive_through_walls) {
				ENTITY::SET_ENTITY_COLLISION(vehicle, FALSE, FALSE);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(vehicle);
			}

			if (g_vehicle_nitrous_active) {
				if (PLAYER::IS_PLAYER_PRESSING_HORN(PLAYER::PLAYER_ID())) {
					if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(vehicle)) {
						std::float_t speed = ENTITY::GET_ENTITY_SPEED(vehicle) + 1.0f;
						VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, speed > 80.0f ? speed : speed * g_vehicle_nitrous_exponent);
						if (g_vehicle_nitrous_play_sound)
							AUDIO::SET_VEHICLE_BOOST_ACTIVE(vehicle, TRUE);
						if (g_vehicle_nitrous_screen_effect)
							GRAPHICS::ANIMPOSTFX_PLAY("RaceTurbo", 0, FALSE);
					}
				}
				else {
					if (g_vehicle_nitrous_play_sound)
						AUDIO::SET_VEHICLE_BOOST_ACTIVE(vehicle, FALSE);
					if (g_vehicle_nitrous_screen_effect)
						GRAPHICS::ANIMPOSTFX_STOP("HeistLocate");
				}
			}

			if (g_vehicle_drift_mode) {
				if (KEYBOARD::IS_KEYBOARD_INPUT_PRESSED((int)('W')) || CONTROLS::IS_CONTROL_PRESSED(2, INPUT_FRONTEND_RT)) {
					ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, true, 0, 0.5f, 0, 0, 0, 0, true, true, true, true, false, true);
					VEHICLE::SET_VEHICLE_REDUCE_GRIP(vehicle, true);
				}
				else
					VEHICLE::SET_VEHICLE_REDUCE_GRIP(vehicle, false);
			}

			if (g_vehicle_gravity) {
				VEHICLE::SET_VEHICLE_GRAVITY(vehicle, FALSE);
			}

			if (g_vehicle_sticky_tires) {
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(vehicle);
			}

			if (g_vehicle_tumble_dryer) {
				if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(vehicle)) {
					Vector3 speed_vector = ENTITY::GET_ENTITY_SPEED_VECTOR(vehicle, TRUE);
					ENTITY::SET_ENTITY_VELOCITY(vehicle, speed_vector.x * 1.01f, speed_vector.y * 1.01f, speed_vector.z * 1.01f);
				}
			}

			// vehicle weapon
			if (g_vehicle_weapon_active) {
				if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, INPUT_FRONTEND_X) || KEYBOARD::IS_KEYBOARD_INPUT_JUST_PRESSED((int)('G'))) {
					Vector3 l_vehicle_dim_min, l_vehicle_dim_max;
					GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(vehicle), &l_vehicle_dim_min, &l_vehicle_dim_max);

					Vector3 l_launch_position, l_launch_position_2, l_target_position, l_target_position_2;
					if (ENTITY::GET_ENTITY_SPEED_VECTOR(vehicle, true).y < 0.0f) {
						l_launch_position = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(vehicle, l_vehicle_dim_min.x - 0.2f, l_vehicle_dim_min.y - 0.5f, 0.0f);
						l_launch_position_2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(vehicle, l_vehicle_dim_max.x + 0.2f, l_vehicle_dim_min.y - 0.5f, 0.0f);
						l_target_position = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(vehicle, l_vehicle_dim_min.x - 0.2f, l_vehicle_dim_min.y - 300.5f, 0.5f);
						l_target_position_2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(vehicle, l_vehicle_dim_max.x + 0.2f, l_vehicle_dim_min.y - 300.5f, 0.5f);
					}
					else {
						l_launch_position = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(vehicle, l_vehicle_dim_min.x - 0.2f, l_vehicle_dim_min.y + 0.5f, 0.0f);
						l_launch_position_2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(vehicle, l_vehicle_dim_max.x + 0.2f, l_vehicle_dim_min.y + 0.5f, 0.0f);
						l_target_position = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(vehicle, l_vehicle_dim_min.x - 0.2f, l_vehicle_dim_min.y + 300.5f, 0.5f);
						l_target_position_2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(vehicle, l_vehicle_dim_max.x + 0.2f, l_vehicle_dim_min.y + 300.5f, 0.5f);

						if (ENTITY::GET_ENTITY_MODEL(vehicle) == GAMEPLAY::GET_HASH_KEY("surfer") || ENTITY::GET_ENTITY_MODEL(vehicle) == GAMEPLAY::GET_HASH_KEY("blazer")) {
							l_target_position.z += 3.5f;
							l_target_position_2.z += 3.5f;
						}
						else {
							l_target_position.z--;
							l_target_position_2.z--;
						}
					}

					std::float_t l_projectile_speed;
					std::float_t l_speed = ENTITY::GET_ENTITY_SPEED(vehicle);
					if ((l_speed * l_speed) > 1500.0f)
						l_projectile_speed = (l_speed * l_speed) + 100.0f;
					else
						l_projectile_speed = 1500.0f;

					WEAPON::REQUEST_WEAPON_ASSET(GAMEPLAY::GET_HASH_KEY(g_vehicle_weapon_hash[g_vehicle_weapon].c_str()), 31, 0);
					GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(l_launch_position.x, l_launch_position.y, l_launch_position.z, l_target_position.x, l_target_position.y, l_target_position.z, 250, 0, GAMEPLAY::GET_HASH_KEY(g_vehicle_weapon_hash[g_vehicle_weapon].c_str()), PLAYER::PLAYER_PED_ID(), 1, 0, l_projectile_speed);
					GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(l_launch_position_2.x, l_launch_position_2.y, l_launch_position_2.z, l_target_position_2.x, l_target_position_2.y, l_target_position_2.z, 250, 0, GAMEPLAY::GET_HASH_KEY(g_vehicle_weapon_hash[g_vehicle_weapon].c_str()), PLAYER::PLAYER_PED_ID(), 1, 0, l_projectile_speed);
				}
			}

			// funny car creator

			// vehicle particle fx
			if (g_vehicle_particle_trails_active) {
				if (g_vehicle_particle_trails_play_when_stationary || (!g_vehicle_particle_trails_play_when_stationary && ENTITY::GET_ENTITY_SPEED(vehicle) > 1.0f)) {
					for (auto i = 0; i < std::size(g_vehicle_particle_trails_bone_active); i++) {
						if (g_vehicle_particle_trails_bone_active[i]) {
							const char* bone_name = g_vehicle_bone_list[i].c_str();
							std::int32_t bone_index = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, bone_name);
							if (bone_index != -1) {
								Vector3 bone_coords = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, bone_index);
								const char* asset = g_particle_effect_list[g_vehicle_particle_trails_selected_particle_arr_index].asset.c_str();
								const char* name = g_particle_effect_list[g_vehicle_particle_trails_selected_particle_arr_index].name.c_str();
								STREAMING::REQUEST_NAMED_PTFX_ASSET(asset);
								GRAPHICS::USE_PARTICLE_FX_ASSET(asset);
								if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(asset)) {
									GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(name, bone_coords.x, bone_coords.y, bone_coords.z, 0.0f, 0.0f, 0.0f, g_vehicle_particle_trails_scale, FALSE, FALSE, FALSE);
								}
							}
						}
					}
				}
			}

			if (g_vehicle_plate_speedo) {
				std::stringstream ss; ss.precision(0);
				ss << std::fixed << ENTITY::GET_ENTITY_SPEED(vehicle) * 2.23694f << " MPH";
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(vehicle, ss.str().c_str());
			}

			if (g_vehicle_seatbelt) {
				PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), FALSE);
				PED::_SET_PED_RAGDOLL_BLOCKING_FLAGS(PLAYER::PLAYER_PED_ID(), 2);
				PED::SET_PED_RAGDOLL_ON_COLLISION(PLAYER::PLAYER_PED_ID(), FALSE);
				PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE);
				if (PED::IS_PED_RAGDOLL(PLAYER::PLAYER_PED_ID()))
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, -1);
			}

			if (g_vehicle_invincible) {
				VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(vehicle, false);
				ENTITY::SET_ENTITY_INVINCIBLE(vehicle, true);
				ENTITY::SET_ENTITY_CAN_BE_DAMAGED(vehicle, false);
				ENTITY::SET_ENTITY_PROOFS(vehicle, true, true, true, true, true, false, false, true);
				VEHICLE::SET_VEHICLE_STRONG(vehicle, true);
				VEHICLE::SET_VEHICLE_BODY_HEALTH(vehicle, 1000);
			}

			if (g_vehicle_invisible) {
				ENTITY::SET_ENTITY_VISIBLE(vehicle, false, 0);
			}

			if (g_vehicle_auto_flip) {
				if (ENTITY::IS_ENTITY_UPSIDEDOWN(vehicle) && !ENTITY::IS_ENTITY_IN_AIR(vehicle) && !PED::IS_PED_IN_ANY_HELI(PLAYER::PLAYER_PED_ID()) && !ENTITY::IS_ENTITY_IN_WATER(vehicle)) {
					Vector3 l_position = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(vehicle, 0.0f, 0.0f, 0.0f);
					std::float_t l_heading = ENTITY::GET_ENTITY_HEADING(vehicle);
					if (l_heading > 180.0)
						l_heading -= 180.0;
					else
						l_heading += 180.0;
					ENTITY::SET_ENTITY_QUATERNION(vehicle, 0, 0, 0, 0);
					ENTITY::SET_ENTITY_COORDS(vehicle, l_position.x, l_position.y, l_position.z, 0, 0, 0, 1);
					ENTITY::SET_ENTITY_HEADING(vehicle, l_heading);
				}
			}
		}
	}

	// object required
	if (g_object_creator_mode) {
		if (PLAYER::IS_PLAYER_FREE_AIMING(PLAYER::PLAYER_ID())) {
			//g_object_handle_position = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.4f, 0.0f, 0.6f);
			//g_object_handle_cam_direction = get_gameplay_camera_direction();
			if (!ENTITY::DOES_ENTITY_EXIST(g_raycast_hit_entity)) {
				std::int32_t l_raycast = WORLDPROBE::_START_SHAPE_TEST_RAY(g_object_handle_position.x, g_object_handle_position.y, g_object_handle_position.z, g_object_handle_position.x + (g_object_handle_cam_direction.x * 1500.0f), g_object_handle_position.y + (g_object_handle_cam_direction.y * 1500.0f), g_object_handle_position.z + (g_object_handle_cam_direction.z * 1500.0f), -1, PLAYER::PLAYER_PED_ID(), 7);
				//WORLDPROBE::GET_SHAPE_TEST_RESULT(l_raycast, &g_did_raycast_hit_entity, &g_raycast_hit_entity_end, &g_raycast_hit_entity_surface_normal, &g_raycast_hit_entity);
			}
			else {
				GRAPHICS::DRAW_LINE(g_object_handle_position.x, g_object_handle_position.y, g_object_handle_position.z, g_object_handle_position.x + (g_object_handle_cam_direction.x * 1500.0f), g_object_handle_position.y + (g_object_handle_cam_direction.y * 1500.0f), g_object_handle_position.z + (g_object_handle_cam_direction.z * 1500.0f), 255, 0, 0, 255);
				if (ENTITY::DOES_ENTITY_EXIST(g_raycast_hit_entity)) {
					switch (ENTITY::GET_ENTITY_TYPE(g_raycast_hit_entity)) {
					case 0: {
							g_raycast_hit_entity = 0;
						} break;
					case 1: { /*PED*/
						g_object_handle = g_raycast_hit_entity;
						print_notification(7000, "Entity handle: ~g~ped.");
						g_raycast_hit_entity = 0;
					} break;
					case 2: { /*VEHICLE*/
						g_object_handle = g_raycast_hit_entity;
						print_notification(7000, "Entity handle: ~g~vehicle.");
						g_raycast_hit_entity = 0;
					} break;
					case 3: { /*OBJECT*/
						g_object_handle = g_raycast_hit_entity;
						print_notification(7000, "Entity handle: ~g~object.");
						g_raycast_hit_entity = 0;
					} break;
					}
				}
			}
		}
	}

	if (g_object_handle_invisibility) {
		if (ENTITY::DOES_ENTITY_EXIST(g_object_handle))
			ENTITY::SET_ENTITY_VISIBLE(g_object_handle, false, 0);
	}

	if (g_object_handle_forcefield) {
		if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
			Vector3 l_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_object_handle, 0.0f, 0.0f, 0.0f);
			FIRE::ADD_EXPLOSION(l_coords.x, l_coords.y, l_coords.z, 29, FLT_MAX, false, true, 0.0f);
		}
	}

	if (g_object_handle_movement_x) {
		if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(g_object_handle);
			Vector3 l_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_object_handle, g_object_handle_movement_value_x, 0, 0);
			ENTITY::SET_ENTITY_COORDS(g_object_handle, l_coords.x, l_coords.y, l_coords.z, 1, 0, 0, 1);
			ENTITY::FREEZE_ENTITY_POSITION(g_object_handle, true);
			ENTITY::SET_ENTITY_COLLISION(g_object_handle, true, 0);
		}
	}

	if (g_object_handle_movement_y) {
		if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(g_object_handle);
			Vector3 l_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_object_handle, 0, g_object_handle_movement_value_y, 0);
			ENTITY::SET_ENTITY_COORDS(g_object_handle, l_coords.x, l_coords.y, l_coords.z, 1, 0, 0, 1);
			ENTITY::FREEZE_ENTITY_POSITION(g_object_handle, true);
			ENTITY::SET_ENTITY_COLLISION(g_object_handle, true, 0);
		}
	}

	if (g_object_handle_movement_z) {
		if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(g_object_handle);
			Vector3 l_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_object_handle, 0, 0, g_object_handle_movement_value_z);
			ENTITY::SET_ENTITY_COORDS(g_object_handle, l_coords.x, l_coords.y, l_coords.z, 1, 0, 0, 1);
			ENTITY::FREEZE_ENTITY_POSITION(g_object_handle, true);
			ENTITY::SET_ENTITY_COLLISION(g_object_handle, true, 0);
		}
	}

	if (g_object_handle_movement_p) {
		if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(g_object_handle);
			Vector3 l_rot = ENTITY::GET_ENTITY_ROTATION(g_object_handle, 2);
			std::float_t l_p = l_rot.x;
			l_p += g_object_handle_movement_value_p;
			ENTITY::SET_ENTITY_ROTATION(g_object_handle, l_p, l_rot.y, l_rot.z, 2, 1);
		}
	}

	if (g_object_handle_movement_ya) {
		if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(g_object_handle);
			Vector3 l_rot = ENTITY::GET_ENTITY_ROTATION(g_object_handle, 2);
			std::float_t l_y = l_rot.z;
			l_y += g_object_handle_movement_value_ya;
			ENTITY::SET_ENTITY_ROTATION(g_object_handle, l_rot.x, l_rot.y, l_y, 2, 1);
		}
	}

	if (g_object_handle_movement_r) {
		if (ENTITY::DOES_ENTITY_EXIST(g_object_handle)) {
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(g_object_handle);
			Vector3 l_rot = ENTITY::GET_ENTITY_ROTATION(g_object_handle, 2);
			std::float_t l_r = l_rot.y;
			l_r += g_object_handle_movement_value_r;
			ENTITY::SET_ENTITY_ROTATION(g_object_handle, l_rot.x, l_r, l_rot.z, 2, 1);
		}
	}

	//world
	if (g_world_time_freeze)
		TIME::PAUSE_CLOCK(TRUE);

	if (g_world_time_sync) {
		TIME::PAUSE_CLOCK(TRUE);
		std::int32_t time[6];
		TIME::GET_LOCAL_TIME(&time[0], &time[1], &time[2], &time[3], &time[4], &time[5]);
		NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(time[3], time[4], time[5]);
	}

	if (g_quantum_radar_active) {
		draw_rect(g_quantum_radar_pos_x, g_quantum_radar_pos_y, g_quantum_radar_scale, g_quantum_radar_scale, rgba(0, 0, 0, 100));
		draw_rect(g_quantum_radar_pos_x, g_quantum_radar_pos_y, g_quantum_radar_center_rect_scale, g_quantum_radar_center_rect_scale, rgba(255, 255, 255, 255));
		draw_rect(g_quantum_radar_pos_x, g_quantum_radar_pos_y, g_quantum_radar_scale, g_quantum_radar_inner_line_width, rgba(255, 255, 255, 100));
		draw_rect(g_quantum_radar_pos_x, g_quantum_radar_pos_y, g_quantum_radar_inner_line_width, g_quantum_radar_scale, rgba(255, 255, 255, 100));
		draw_rect(g_quantum_radar_pos_x, g_quantum_radar_pos_y - (g_quantum_radar_scale / 2.0f) - (g_quantum_radar_outer_line_width / 2.0f), g_quantum_radar_scale + (g_quantum_radar_outer_line_width * 2.0f), g_quantum_radar_outer_line_width, rgba(255, 255, 255, 255));
		draw_rect(g_quantum_radar_pos_x, g_quantum_radar_pos_y + (g_quantum_radar_scale / 2.0f) + (g_quantum_radar_outer_line_width / 2.0f), g_quantum_radar_scale + (g_quantum_radar_outer_line_width * 2.0f), g_quantum_radar_outer_line_width, rgba(255, 255, 255, 255));
		draw_rect(g_quantum_radar_pos_x - (g_quantum_radar_scale / 2.0f) - (g_quantum_radar_outer_line_width / 2.0f), g_quantum_radar_pos_y, g_quantum_radar_outer_line_width, g_quantum_radar_scale, rgba(255, 255, 255, 255));
		draw_rect(g_quantum_radar_pos_x + (g_quantum_radar_scale / 2.0f) + (g_quantum_radar_outer_line_width / 2.0f), g_quantum_radar_pos_y, g_quantum_radar_outer_line_width, g_quantum_radar_scale, rgba(255, 255, 255, 255));

		// radar test
		ListPool* vehicle_pool = *(ListPool**)(GTA_VEH_LIST_POOL);
		if (vehicle_pool != nullptr) {

			std::uint32_t found_vehicles = NULL;
			for (std::int32_t i = 0; i < vehicle_pool->capacity; i++) {

				std::uint64_t vehicle_entity = vehicle_pool->get(i);
				if (vehicle_entity == NULL)
					continue;

				std::int32_t vehicle = SpoofCalls(reinterpret_cast<std::add_pointer_t<void>>(GTA_JMP_RBX), ((std::int32_t(*)(std::uint64_t))GTA_GET_SCRIPT_INDEX_FROM_ENTITY), vehicle_entity);
				if (!ENTITY::DOES_ENTITY_EXIST(vehicle))
					continue;

				Vector2 radar_coord = get_quantum_radar_pos(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(vehicle, 0.0f, 0.0f, 0.0f));
				auto sizee = GetSpriteScale(0.035f);
				draw_sprite("mpcarhud", "transport_car_icon", radar_coord.x, radar_coord.y, sizee.x, sizee.y, 0.0f, rgba(255, 255, 255, 255));
			}
		}
	}

	if (g_world_bypass_restricted_zones) {
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("am_armybase");
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("restrictedareas");
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_armybase");
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_lossantosintl");
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_prison");
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_prisonvanbreak");
	}

	//misc
	if (g_misc_disable_minimap) {
		UI::DISPLAY_HUD(false);
		UI::DISPLAY_RADAR(false);
	}

	if (g_misc_virtual_tv_active) {
		GRAPHICS::SET_TV_AUDIO_FRONTEND(TRUE);
		GRAPHICS::DRAW_TV_CHANNEL(g_misc_virtual_tv_x, g_misc_virtual_tv_y, g_misc_virtual_tv_width, g_misc_virtual_tv_height, g_misc_virtual_tv_rotation, 255, 255, 255, 255);
	}

	// recovery
	//if (g_recovery_rp_increaser_active) {
	//	g_recovery_rp_increaser_timer.start(g_recovery_rp_increaser_delay);
	//	if (g_recovery_rp_increaser_timer.is_ready()) {
	//		PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
	//		*scr_global(2531497).at(3964).as<std::int32_t*>() = g_recovery_rp_increaser_wanted_level;
	//		*scr_global(2531497).at(4548).as<std::int32_t*>() = 0;
	//		*scr_global(2531497).at(3963).as<std::int32_t*>() = 4;
	//		g_recovery_rp_increaser_timer.reset();
	//	}
	//}
}