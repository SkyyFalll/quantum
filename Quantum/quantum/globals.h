#pragma once
#include "classes.h"

std::int32_t KeyboardMenuOpen = VK_INSERT;
std::int32_t KeyboardMenuSelect = VK_RETURN;
std::int32_t KeyboardMenuBack = VK_BACK;
std::int32_t KeyboardMenuNavUp = VK_UP;
std::int32_t KeyboardMenuNavDown = VK_DOWN;
std::int32_t KeyboardMenuNavLeft = VK_LEFT;
std::int32_t KeyboardMenuNavRight = VK_RIGHT;


struct rgba {
	std::int32_t r;
	std::int32_t g;
	std::int32_t b;
	std::int32_t a;
	rgba(std::int32_t r, std::int32_t g, std::int32_t b, std::int32_t a)
		: r(r), g(g), b(b), a(a) {}
};

std::string g_hud_colours[] = {
	"HUD_COLOUR_PURE_WHITE",
	"HUD_COLOUR_WHITE",
	"HUD_COLOUR_BLACK",
	"HUD_COLOUR_GREY",
	"HUD_COLOUR_GREYLIGHT",
	"HUD_COLOUR_GREYDARK",
	"HUD_COLOUR_RED",
	"HUD_COLOUR_REDLIGHT",
	"HUD_COLOUR_REDDARK",
	"HUD_COLOUR_BLUE",
	"HUD_COLOUR_BLUELIGHT",
	"HUD_COLOUR_BLUEDARK",
	"HUD_COLOUR_YELLOW",
	"HUD_COLOUR_YELLOWLIGHT",
	"HUD_COLOUR_YELLOWDARK",
	"HUD_COLOUR_ORANGE",
	"HUD_COLOUR_ORANGELIGHT",
	"HUD_COLOUR_ORANGEDARK",
	"HUD_COLOUR_GREEN",
	"HUD_COLOUR_GREENLIGHT",
	"HUD_COLOUR_GREENDARK",
	"HUD_COLOUR_PURPLE",
	"HUD_COLOUR_PURPLELIGHT",
	"HUD_COLOUR_PURPLEDARK",
	"HUD_COLOUR_PINK",
	"HUD_COLOUR_RADAR_HEALTH",
	"HUD_COLOUR_RADAR_ARMOUR",
	"HUD_COLOUR_RADAR_DAMAGE",

	"HUD_COLOUR_NET_PLAYER1",
	"HUD_COLOUR_NET_PLAYER2",
	"HUD_COLOUR_NET_PLAYER3",
	"HUD_COLOUR_NET_PLAYER4",
	"HUD_COLOUR_NET_PLAYER5",
	"HUD_COLOUR_NET_PLAYER6",
	"HUD_COLOUR_NET_PLAYER7",
	"HUD_COLOUR_NET_PLAYER8",
	"HUD_COLOUR_NET_PLAYER9",
	"HUD_COLOUR_NET_PLAYER10",
	"HUD_COLOUR_NET_PLAYER11",
	"HUD_COLOUR_NET_PLAYER12",
	"HUD_COLOUR_NET_PLAYER13",
	"HUD_COLOUR_NET_PLAYER14",
	"HUD_COLOUR_NET_PLAYER15",
	"HUD_COLOUR_NET_PLAYER16",
	"HUD_COLOUR_NET_PLAYER17",
	"HUD_COLOUR_NET_PLAYER18",
	"HUD_COLOUR_NET_PLAYER19",
	"HUD_COLOUR_NET_PLAYER20",
	"HUD_COLOUR_NET_PLAYER21",
	"HUD_COLOUR_NET_PLAYER22",
	"HUD_COLOUR_NET_PLAYER23",
	"HUD_COLOUR_NET_PLAYER24",
	"HUD_COLOUR_NET_PLAYER25",
	"HUD_COLOUR_NET_PLAYER26",
	"HUD_COLOUR_NET_PLAYER27",
	"HUD_COLOUR_NET_PLAYER28",
	"HUD_COLOUR_NET_PLAYER29",
	"HUD_COLOUR_NET_PLAYER30",
	"HUD_COLOUR_NET_PLAYER31",
	"HUD_COLOUR_NET_PLAYER32",

	"HUD_COLOUR_SIMPLEBLIP_DEFAULT",
	"HUD_COLOUR_MENU_BLUE",
	"HUD_COLOUR_MENU_GREY_LIGHT",
	"HUD_COLOUR_MENU_BLUE_EXTRA_DARK",
	"HUD_COLOUR_MENU_YELLOW",
	"HUD_COLOUR_MENU_YELLOW_DARK",
	"HUD_COLOUR_MENU_GREEN",
	"HUD_COLOUR_MENU_GREY",
	"HUD_COLOUR_MENU_GREY_DARK",
	"HUD_COLOUR_MENU_HIGHLIGHT",
	"HUD_COLOUR_MENU_STANDARD",
	"HUD_COLOUR_MENU_DIMMED",
	"HUD_COLOUR_MENU_EXTRA_DIMMED",
	"HUD_COLOUR_BRIEF_TITLE",
	"HUD_COLOUR_MID_GREY_MP",

	"HUD_COLOUR_NET_PLAYER1_DARK",
	"HUD_COLOUR_NET_PLAYER2_DARK",
	"HUD_COLOUR_NET_PLAYER3_DARK",
	"HUD_COLOUR_NET_PLAYER4_DARK",
	"HUD_COLOUR_NET_PLAYER5_DARK",
	"HUD_COLOUR_NET_PLAYER6_DARK",
	"HUD_COLOUR_NET_PLAYER7_DARK",
	"HUD_COLOUR_NET_PLAYER8_DARK",
	"HUD_COLOUR_NET_PLAYER9_DARK",
	"HUD_COLOUR_NET_PLAYER10_DARK",
	"HUD_COLOUR_NET_PLAYER11_DARK",
	"HUD_COLOUR_NET_PLAYER12_DARK",
	"HUD_COLOUR_NET_PLAYER13_DARK",
	"HUD_COLOUR_NET_PLAYER14_DARK",
	"HUD_COLOUR_NET_PLAYER15_DARK",
	"HUD_COLOUR_NET_PLAYER16_DARK",
	"HUD_COLOUR_NET_PLAYER17_DARK",
	"HUD_COLOUR_NET_PLAYER18_DARK",
	"HUD_COLOUR_NET_PLAYER19_DARK",
	"HUD_COLOUR_NET_PLAYER20_DARK",
	"HUD_COLOUR_NET_PLAYER21_DARK",
	"HUD_COLOUR_NET_PLAYER22_DARK",
	"HUD_COLOUR_NET_PLAYER23_DARK",
	"HUD_COLOUR_NET_PLAYER24_DARK",
	"HUD_COLOUR_NET_PLAYER25_DARK",
	"HUD_COLOUR_NET_PLAYER26_DARK",
	"HUD_COLOUR_NET_PLAYER27_DARK",
	"HUD_COLOUR_NET_PLAYER28_DARK",
	"HUD_COLOUR_NET_PLAYER29_DARK",
	"HUD_COLOUR_NET_PLAYER30_DARK",
	"HUD_COLOUR_NET_PLAYER31_DARK",
	"HUD_COLOUR_NET_PLAYER32_DARK",

	"HUD_COLOUR_BRONZE",
	"HUD_COLOUR_SILVER",
	"HUD_COLOUR_GOLD",
	"HUD_COLOUR_PLATINUM",
	"HUD_COLOUR_GANG1",
	"HUD_COLOUR_GANG2",
	"HUD_COLOUR_GANG3",
	"HUD_COLOUR_GANG4",
	"HUD_COLOUR_SAME_CREW",
	"HUD_COLOUR_FREEMODE",
	"HUD_COLOUR_PAUSE_BG",
	"HUD_COLOUR_FRIENDLY",
	"HUD_COLOUR_ENEMY",
	"HUD_COLOUR_LOCATION",
	"HUD_COLOUR_PICKUP",
	"HUD_COLOUR_PAUSE_SINGLEPLAYER",
	"HUD_COLOUR_FREEMODE_DARK",
	"HUD_COLOUR_INACTIVE_MISSION",
	"HUD_COLOUR_DAMAGE",
	"HUD_COLOUR_PINKLIGHT",
	"HUD_COLOUR_PM_MITEM_HIGHLIGHT",
	"HUD_COLOUR_SCRIPT_VARIABLE",
	"HUD_COLOUR_YOGA",
	"HUD_COLOUR_TENNIS",
	"HUD_COLOUR_GOLF",

	"HUD_COLOUR_SHOOTING_RANGE",
	"HUD_COLOUR_FLIGHT_SCHOOL",
	"HUD_COLOUR_NORTH_BLUE",
	"HUD_COLOUR_SOCIAL_CLUB",
	"HUD_COLOUR_PLATFORM_BLUE",
	"HUD_COLOUR_PLATFORM_GREEN",
	"HUD_COLOUR_PLATFORM_GREY",
	"HUD_COLOUR_FACEBOOK_BLUE",
	"HUD_COLOUR_INGAME_BG",
	"HUD_COLOUR_DARTS",
	"HUD_COLOUR_WAYPOINT",
	"HUD_COLOUR_MICHAEL",
	"HUD_COLOUR_FRANKLIN",
	"HUD_COLOUR_TREVOR",
	"HUD_COLOUR_GOLF_P1",
	"HUD_COLOUR_GOLF_P2",
	"HUD_COLOUR_GOLF_P3",
	"HUD_COLOUR_GOLF_P4",
	"HUD_COLOUR_WAYPOINTLIGHT",
	"HUD_COLOUR_WAYPOINTDARK",
	"HUD_COLOUR_PANEL_LIGHT",
	"HUD_COLOUR_MICHAEL_DARK",
	"HUD_COLOUR_FRANKLIN_DARK",
	"HUD_COLOUR_TREVOR_DARK",
	"HUD_COLOUR_OBJECTIVE_ROUTE",
	"HUD_COLOUR_PAUSEMAP_TINT",
	"HUD_COLOUR_PAUSE_DESELECT",
	"HUD_COLOUR_PM_WEAPONS_PURCHASABLE",
	"HUD_COLOUR_PM_WEAPONS_LOCKED",
	"HUD_COLOUR_END_SCREEN_BG",
	"HUD_COLOUR_CHOP",
	"HUD_COLOUR_PAUSEMAP_TINT_HALF",
	"HUD_COLOUR_NORTH_BLUE_OFFICIAL",
	"HUD_COLOUR_SCRIPT_VARIABLE_2",

	"HUD_COLOUR_H",
	"HUD_COLOUR_HDARK",
	"HUD_COLOUR_T",
	"HUD_COLOUR_TDARK",
	"HUD_COLOUR_HSHARD",

	"HUD_COLOUR_CONTROLLER_MICHAEL",
	"HUD_COLOUR_CONTROLLER_FRANKLIN",
	"HUD_COLOUR_CONTROLLER_TREVOR",
	"HUD_COLOUR_CONTROLLER_CHOP",

	"HUD_COLOUR_VIDEO_EDITOR_VIDEO",
	"HUD_COLOUR_VIDEO_EDITOR_AUDIO",
	"HUD_COLOUR_VIDEO_EDITOR_TEXT",
	
	"HUD_COLOUR_HB_BLUE",
	"HUD_COLOUR_HB_YELLOW",

	"HUD_COLOUR_VIDEO_EDITOR_SCORE",
	"HUD_COLOUR_VIDEO_EDITOR_AUDIO_FADEOUT",
	"HUD_COLOUR_VIDEO_EDITOR_TEXT_FADEOUT",
	"HUD_COLOUR_VIDEO_EDITOR_SCORE_FADEOUT",
	"HUD_COLOUR_HEIST_BACKGROUND",
	"HUD_COLOUR_VIDEO_EDITOR_AMBIENT",
	"HUD_COLOUR_VIDEO_EDITOR_AMBIENT_FADEOUT",
	"HUD_COLOUR_VIDEO_EDITOR_AMBIENT_DARK",
	"HUD_COLOUR_VIDEO_EDITOR_AMBIENT_LIGHT",
	"HUD_COLOUR_VIDEO_EDITOR_AMBIENT_MID",
	"HUD_COLOUR_LOW_FLOW",
	"HUD_COLOUR_LOW_FLOW_DARK",
	"HUD_COLOUR_G1",
	"HUD_COLOUR_G2",
	"HUD_COLOUR_G3",
	"HUD_COLOUR_G4",
	"HUD_COLOUR_G5",
	"HUD_COLOUR_G6",
	"HUD_COLOUR_G7",
	"HUD_COLOUR_G8",
	"HUD_COLOUR_G9",
	"HUD_COLOUR_G10",
	"HUD_COLOUR_G11",
	"HUD_COLOUR_G12",
	"HUD_COLOUR_G13",
	"HUD_COLOUR_G14",
	"HUD_COLOUR_G15",
	"HUD_COLOUR_ADVERSARY",
	"HUD_COLOUR_DEGEN_RED",
	"HUD_COLOUR_DEGEN_YELLOW",
	"HUD_COLOUR_DEGEN_GREEN",
	"HUD_COLOUR_DEGEN_CYAN",
	"HUD_COLOUR_DEGEN_BLUE",
	"HUD_COLOUR_DEGEN_MAGENTA",
	"HUD_COLOUR_STUNT_1",
	"HUD_COLOUR_STUNT_2",
	"HUD_COLOUR_SPECIAL_RACE_SERIES",
	"HUD_COLOUR_SPECIAL_RACE_SERIES_DARK",
	"HUD_COLOUR_CS",
	"HUD_COLOUR_CS_DARK",
	"HUD_COLOUR_TECH_GREEN",
	"HUD_COLOUR_TECH_GREEN_DARK",
	"HUD_COLOUR_TECH_RED",
	"HUD_COLOUR_TECH_GREEN_VERY_DARK",
};

std::string explosion_types[] = {
	"EXP_TAG_GRENADE",
	"EXP_TAG_GRENADELAUNCHER",
	"EXP_TAG_STICKYBOMB",
	"EXP_TAG_MOLOTOV",
	"EXP_TAG_ROCKET",
	"EXP_TAG_TANKSHELL",
	"EXP_TAG_HI_OCTANE",
	"EXP_TAG_CAR",
	"EXP_TAG_PLANE",
	"EXP_TAG_PETROL_PUMP",
	"EXP_TAG_BIKE",
	"EXP_TAG_DIR_STEAM",
	"EXP_TAG_DIR_FLAME",
	"EXP_TAG_DIR_WATER_HYDRANT",
	"EXP_TAG_DIR_GAS_CANISTER",
	"EXP_TAG_BOAT",
	"EXP_TAG_SHIP_DESTROY",
	"EXP_TAG_TRUCK",
	"EXP_TAG_BULLET",
	"EXP_TAG_SMOKEGRENADELAUNCHER",
	"EXP_TAG_SMOKEGRENADE",
	"EXP_TAG_BZGAS",
	"EXP_TAG_FLARE",
	"EXP_TAG_GAS_CANISTER",
	"EXP_TAG_EXTINGUISHER",
	"EXP_TAG_PROGRAMMABLEAR",
	"EXP_TAG_TRAIN",
	"EXP_TAG_BARREL",
	"EXP_TAG_PROPANE",
	"EXP_TAG_BLIMP",
	"EXP_TAG_DIR_FLAME_EXPLODE",
	"EXP_TAG_TANKER",
	"EXP_TAG_PLANE_ROCKET",
	"EXP_TAG_VEHICLE_BULLET",
	"EXP_TAG_GAS_TANK",
	"EXP_TAG_BIRD_CRAP",
	"EXP_TAG_RAILGUN",
	"EXP_TAG_BLIMP2",
	"EXP_TAG_FIREWORK",
	"EXP_TAG_SNOWBALL",
	"EXP_TAG_PROXMINE",
	"EXP_TAG_VALKYRIE_CANNON",
	"EXP_TAG_AIR_DEFENCE",
	"EXP_TAG_PIPEBOMB",
	"EXP_TAG_VEHICLEMINE",
	"EXP_TAG_EXPLOSIVEAMMO",
	"EXP_TAG_APCSHELL",
	"EXP_TAG_BOMB_CLUSTER",
	"EXP_TAG_BOMB_GAS",
	"EXP_TAG_BOMB_INCENDIARY",
	"EXP_TAG_BOMB_STANDARD",
	"EXP_TAG_TORPEDO",
	"EXP_TAG_TORPEDO_UNDERWATER",
	"EXP_TAG_BOMBUSHKA_CANNON",
	"EXP_TAG_BOMB_CLUSTER_SECONDARY",
	"EXP_TAG_HUNTER_BARRAGE",
	"EXP_TAG_HUNTER_CANNON",
	"EXP_TAG_ROGUE_CANNON",
	"EXP_TAG_MINE_UNDERWATER",
	"EXP_TAG_ORBITAL_CANNON",
	"EXP_TAG_BOMB_STANDARD_WIDE",
	"EXP_TAG_EXPLOSIVEAMMO_SHOTGUN",
	"EXP_TAG_OPPRESSOR2_CANNON",
};

enum vehicle_mods {
	MOD_SPOILER,
	MOD_FRONTBUMPER,
	MOD_REARBUMPER,
	MOD_SIDESKIRT,
	MOD_EXHAUST,
	MOD_CHASSIS,
	MOD_GRILLE,
	MOD_HOOD,
	MOD_FENDER,
	MOD_RIGHTFENDER,
	MOD_ROOF,
	MOD_ENGINE,
	MOD_BRAKES,
	MOD_TRANSMISSION,
	MOD_HORN,
	MOD_SUSPENSION,
	MOD_ARMOR,
	MOD_UNK17 = 17,
	MOD_TURBO = 18,
	MOD_UNK19 = 19,
	MOD_TIRESMOKE = 20,
	MOD_UNK21 = 21,
	MOD_XENONLIGHTS = 22,
	MOD_FRONTWHEELS = 23,
	MOD_BACKWHEELS = 24, //Bikes only

	// Benny's
	MOD_PLATEHOLDER = 25,
	MOD_VANITY_PLATES = 26,
	MOD_TRIM = 27,
	MOD_ORNAMENTS = 28,
	MOD_DASHBOARD = 29,
	MOD_DIAL = 30,
	MOD_DOOR_SPEAKER = 31,
	MOD_SEATS = 32,
	MOD_STEERINGWHEEL = 33,
	MOD_SHIFTER_LEAVERS = 34,
	MOD_PLAQUES = 35,
	MOD_SPEAKERS = 36,
	MOD_TRUNK = 37,
	MOD_HYDRULICS = 38,
	MOD_ENGINE_BLOCK = 39,
	MOD_AIR_FILTER = 40,
	MOD_STRUTS = 41,
	MOD_ARCH_COVER = 42,
	MOD_AERIALS = 43,
	MOD_TRIM2 = 44,
	MOD_TANK = 45,
	MOD_WINDOWS = 46,
	MOD_UNK47 = 47,
	MOD_LIVERY = 48,
};

enum vehicle_horns {
	CMOD_HRN_0 = -1,
	CMOD_HRN_TRK,
	CMOD_HRN_COP,
	CMOD_HRN_CLO,
	CMOD_HRN_MUS1,
	CMOD_HRN_MUS2,
	CMOD_HRN_MUS3,
	CMOD_HRN_MUS4,
	CMOD_HRN_MUS5,
	CMOD_HRN_SAD,
	HORN_CLAS1,
	HORN_CLAS2,
	HORN_CLAS3,
	HORN_CLAS4,
	HORN_CLAS5,
	HORN_CLAS6,
	HORN_CLAS7,
	HORN_CNOTE_C0,
	HORN_CNOTE_D0,
	HORN_CNOTE_E0,
	HORN_CNOTE_F0,
	HORN_CNOTE_G0,
	HORN_CNOTE_A0,
	HORN_CNOTE_B0,
	HORN_CNOTE_C1,
	HORN_HIPS1,
	HORN_HIPS2,
	HORN_HIPS3,
	HORN_HIPS4,
	HORN_INDI_1,
	HORN_INDI_2,
	HORN_INDI_3,
	HORN_INDI_4,
	HORN_LUXE1,
	HORN_LUXE2,
	HORN_LUXE3,
	HORN_HWEEN1 = 38,
	HORN_HWEEN2 = 40,
	HORN_LOWRDER1 = 42,
	HORN_LOWRDER2 = 44,
	HORN_XM15_1 = 46,
	HORN_XM15_2 = 48,
	HORN_XM15_3 = 50,
	CMOD_AIRHORN_01 = 52,
	CMOD_AIRHORN_02 = 54,
	CMOD_AIRHORN_03 = 56,
};

enum controller_inputs {
	INPUT_NEXT_CAMERA = 0,
	INPUT_LOOK_LR = 1,
	INPUT_LOOK_UD = 2,
	INPUT_LOOK_UP_ONLY = 3,
	INPUT_LOOK_DOWN_ONLY = 4,
	INPUT_LOOK_LEFT_ONLY = 5,
	INPUT_LOOK_RIGHT_ONLY = 6,
	INPUT_CINEMATIC_SLOWMO = 7,
	INPUT_SCRIPTED_FLY_UD = 8,
	INPUT_SCRIPTED_FLY_LR = 9,
	INPUT_SCRIPTED_FLY_ZUP = 10,
	INPUT_SCRIPTED_FLY_ZDOWN = 11,
	INPUT_WEAPON_WHEEL_UD = 12,
	INPUT_WEAPON_WHEEL_LR = 13,
	INPUT_WEAPON_WHEEL_NEXT = 14,
	INPUT_WEAPON_WHEEL_PREV = 15,
	INPUT_SELECT_NEXT_WEAPON = 16,
	INPUT_SELECT_PREV_WEAPON = 17,
	INPUT_SKIP_CUTSCENE = 18,
	INPUT_CHARACTER_WHEEL = 19,
	INPUT_MULTIPLAYER_INFO = 20,
	INPUT_SPRINT = 21,
	INPUT_JUMP = 22,
	INPUT_ENTER = 23,
	INPUT_ATTACK = 24,
	INPUT_AIM = 25,
	INPUT_LOOK_BEHIND = 26,
	INPUT_PHONE = 27,
	INPUT_SPECIAL_ABILITY = 28,
	INPUT_SPECIAL_ABILITY_SECONDARY = 29,
	INPUT_MOVE_LR = 30,
	INPUT_MOVE_UD = 31,
	INPUT_MOVE_UP_ONLY = 32,
	INPUT_MOVE_DOWN_ONLY = 33,
	INPUT_MOVE_LEFT_ONLY = 34,
	INPUT_MOVE_RIGHT_ONLY = 35,
	INPUT_DUCK = 36,
	INPUT_SELECT_WEAPON = 37,
	INPUT_PICKUP = 38,
	INPUT_SNIPER_ZOOM = 39,
	INPUT_SNIPER_ZOOM_IN_ONLY = 40,
	INPUT_SNIPER_ZOOM_OUT_ONLY = 41,
	INPUT_SNIPER_ZOOM_IN_SECONDARY = 42,
	INPUT_SNIPER_ZOOM_OUT_SECONDARY = 43,
	INPUT_COVER = 44,
	INPUT_RELOAD = 45,
	INPUT_TALK = 46,
	INPUT_DETONATE = 47,
	INPUT_HUD_SPECIAL = 48,
	INPUT_ARREST = 49,
	INPUT_ACCURATE_AIM = 50,
	INPUT_CONTEXT = 51,
	INPUT_CONTEXT_SECONDARY = 52,
	INPUT_WEAPON_SPECIAL = 53,
	INPUT_WEAPON_SPECIAL_TWO = 54,
	INPUT_DIVE = 55,
	INPUT_DROP_WEAPON = 56,
	INPUT_DROP_AMMO = 57,
	INPUT_THROW_GRENADE = 58,
	INPUT_VEH_MOVE_LR = 59,
	INPUT_VEH_MOVE_UD = 60,
	INPUT_VEH_MOVE_UP_ONLY = 61,
	INPUT_VEH_MOVE_DOWN_ONLY = 62,
	INPUT_VEH_MOVE_LEFT_ONLY = 63,
	INPUT_VEH_MOVE_RIGHT_ONLY = 64,
	INPUT_VEH_SPECIAL = 65,
	INPUT_VEH_GUN_LR = 66,
	INPUT_VEH_GUN_UD = 67,
	INPUT_VEH_AIM = 68,
	INPUT_VEH_ATTACK = 69,
	INPUT_VEH_ATTACK2 = 70,
	INPUT_VEH_ACCELERATE = 71,
	INPUT_VEH_BRAKE = 72,
	INPUT_VEH_DUCK = 73,
	INPUT_VEH_HEADLIGHT = 74,
	INPUT_VEH_EXIT = 75,
	INPUT_VEH_HANDBRAKE = 76,
	INPUT_VEH_HOTWIRE_LEFT = 77,
	INPUT_VEH_HOTWIRE_RIGHT = 78,
	INPUT_VEH_LOOK_BEHIND = 79,
	INPUT_VEH_CIN_CAM = 80,
	INPUT_VEH_NEXT_RADIO = 81,
	INPUT_VEH_PREV_RADIO = 82,
	INPUT_VEH_NEXT_RADIO_TRACK = 83,
	INPUT_VEH_PREV_RADIO_TRACK = 84,
	INPUT_VEH_RADIO_WHEEL = 85,
	INPUT_VEH_HORN = 86,
	INPUT_VEH_FLY_THROTTLE_UP = 87,
	INPUT_VEH_FLY_THROTTLE_DOWN = 88,
	INPUT_VEH_FLY_YAW_LEFT = 89,
	INPUT_VEH_FLY_YAW_RIGHT = 90,
	INPUT_VEH_PASSENGER_AIM = 91,
	INPUT_VEH_PASSENGER_ATTACK = 92,
	INPUT_VEH_SPECIAL_ABILITY_FRANKLIN = 93,
	INPUT_VEH_STUNT_UD = 94,
	INPUT_VEH_CINEMATIC_UD = 95,
	INPUT_VEH_CINEMATIC_UP_ONLY = 96,
	INPUT_VEH_CINEMATIC_DOWN_ONLY = 97,
	INPUT_VEH_CINEMATIC_LR = 98,
	INPUT_VEH_SELECT_NEXT_WEAPON = 99,
	INPUT_VEH_SELECT_PREV_WEAPON = 100,
	INPUT_VEH_ROOF = 101,
	INPUT_VEH_JUMP = 102,
	INPUT_VEH_GRAPPLING_HOOK = 103,
	INPUT_VEH_SHUFFLE = 104,
	INPUT_VEH_DROP_PROJECTILE = 105,
	INPUT_VEH_MOUSE_CONTROL_OVERRIDE = 106,
	INPUT_VEH_FLY_ROLL_LR = 107,
	INPUT_VEH_FLY_ROLL_LEFT_ONLY = 108,
	INPUT_VEH_FLY_ROLL_RIGHT_ONLY = 109,
	INPUT_VEH_FLY_PITCH_UD = 110,
	INPUT_VEH_FLY_PITCH_UP_ONLY = 111,
	INPUT_VEH_FLY_PITCH_DOWN_ONLY = 112,
	INPUT_VEH_FLY_UNDERCARRIAGE = 113,
	INPUT_VEH_FLY_ATTACK = 114,
	INPUT_VEH_FLY_SELECT_NEXT_WEAPON = 115,
	INPUT_VEH_FLY_SELECT_PREV_WEAPON = 116,
	INPUT_VEH_FLY_SELECT_TARGET_LEFT = 117,
	INPUT_VEH_FLY_SELECT_TARGET_RIGHT = 118,
	INPUT_VEH_FLY_VERTICAL_FLIGHT_MODE = 119,
	INPUT_VEH_FLY_DUCK = 120,
	INPUT_VEH_FLY_ATTACK_CAMERA = 121,
	INPUT_VEH_FLY_MOUSE_CONTROL_OVERRIDE = 122,
	INPUT_VEH_SUB_TURN_LR = 123,
	INPUT_VEH_SUB_TURN_LEFT_ONLY = 124,
	INPUT_VEH_SUB_TURN_RIGHT_ONLY = 125,
	INPUT_VEH_SUB_PITCH_UD = 126,
	INPUT_VEH_SUB_PITCH_UP_ONLY = 127,
	INPUT_VEH_SUB_PITCH_DOWN_ONLY = 128,
	INPUT_VEH_SUB_THROTTLE_UP = 129,
	INPUT_VEH_SUB_THROTTLE_DOWN = 130,
	INPUT_VEH_SUB_ASCEND = 131,
	INPUT_VEH_SUB_DESCEND = 132,
	INPUT_VEH_SUB_TURN_HARD_LEFT = 133,
	INPUT_VEH_SUB_TURN_HARD_RIGHT = 134,
	INPUT_VEH_SUB_MOUSE_CONTROL_OVERRIDE = 135,
	INPUT_VEH_PUSHBIKE_PEDAL = 136,
	INPUT_VEH_PUSHBIKE_SPRINT = 137,
	INPUT_VEH_PUSHBIKE_FRONT_BRAKE = 138,
	INPUT_VEH_PUSHBIKE_REAR_BRAKE = 139,
	INPUT_MELEE_ATTACK_LIGHT = 140,
	INPUT_MELEE_ATTACK_HEAVY = 141,
	INPUT_MELEE_ATTACK_ALTERNATE = 142,
	INPUT_MELEE_BLOCK = 143,
	INPUT_PARACHUTE_DEPLOY = 144,
	INPUT_PARACHUTE_DETACH = 145,
	INPUT_PARACHUTE_TURN_LR = 146,
	INPUT_PARACHUTE_TURN_LEFT_ONLY = 147,
	INPUT_PARACHUTE_TURN_RIGHT_ONLY = 148,
	INPUT_PARACHUTE_PITCH_UD = 149,
	INPUT_PARACHUTE_PITCH_UP_ONLY = 150,
	INPUT_PARACHUTE_PITCH_DOWN_ONLY = 151,
	INPUT_PARACHUTE_BRAKE_LEFT = 152,
	INPUT_PARACHUTE_BRAKE_RIGHT = 153,
	INPUT_PARACHUTE_SMOKE = 154,
	INPUT_PARACHUTE_PRECISION_LANDING = 155,
	INPUT_MAP = 156,
	INPUT_SELECT_WEAPON_UNARMED = 157,
	INPUT_SELECT_WEAPON_MELEE = 158,
	INPUT_SELECT_WEAPON_HANDGUN = 159,
	INPUT_SELECT_WEAPON_SHOTGUN = 160,
	INPUT_SELECT_WEAPON_SMG = 161,
	INPUT_SELECT_WEAPON_AUTO_RIFLE = 162,
	INPUT_SELECT_WEAPON_SNIPER = 163,
	INPUT_SELECT_WEAPON_HEAVY = 164,
	INPUT_SELECT_WEAPON_SPECIAL = 165,
	INPUT_SELECT_CHARACTER_MICHAEL = 166,
	INPUT_SELECT_CHARACTER_FRANKLIN = 167,
	INPUT_SELECT_CHARACTER_TREVOR = 168,
	INPUT_SELECT_CHARACTER_MULTIPLAYER = 169,
	INPUT_SAVE_REPLAY_CLIP = 170,
	INPUT_SPECIAL_ABILITY_PC = 171,
	INPUT_CELLPHONE_UP = 172,
	INPUT_CELLPHONE_DOWN = 173,
	INPUT_CELLPHONE_LEFT = 174,
	INPUT_CELLPHONE_RIGHT = 175,
	INPUT_CELLPHONE_SELECT = 176,
	INPUT_CELLPHONE_CANCEL = 177,
	INPUT_CELLPHONE_OPTION = 178,
	INPUT_CELLPHONE_EXTRA_OPTION = 179,
	INPUT_CELLPHONE_SCROLL_FORWARD = 180,
	INPUT_CELLPHONE_SCROLL_BACKWARD = 181,
	INPUT_CELLPHONE_CAMERA_FOCUS_LOCK = 182,
	INPUT_CELLPHONE_CAMERA_GRID = 183,
	INPUT_CELLPHONE_CAMERA_SELFIE = 184,
	INPUT_CELLPHONE_CAMERA_DOF = 185,
	INPUT_CELLPHONE_CAMERA_EXPRESSION = 186,
	INPUT_FRONTEND_DOWN = 187,
	INPUT_FRONTEND_UP = 188,
	INPUT_FRONTEND_LEFT = 189,
	INPUT_FRONTEND_RIGHT = 190,
	INPUT_FRONTEND_RDOWN = 191,
	INPUT_FRONTEND_RUP = 192,
	INPUT_FRONTEND_RLEFT = 193,
	INPUT_FRONTEND_RRIGHT = 194,
	INPUT_FRONTEND_AXIS_X = 195,
	INPUT_FRONTEND_AXIS_Y = 196,
	INPUT_FRONTEND_RIGHT_AXIS_X = 197,
	INPUT_FRONTEND_RIGHT_AXIS_Y = 198,
	INPUT_FRONTEND_PAUSE = 199,
	INPUT_FRONTEND_PAUSE_ALTERNATE = 200,
	INPUT_FRONTEND_ACCEPT = 201,
	INPUT_FRONTEND_CANCEL = 202,
	INPUT_FRONTEND_X = 203,
	INPUT_FRONTEND_Y = 204,
	INPUT_FRONTEND_LB = 205,
	INPUT_FRONTEND_RB = 206,
	INPUT_FRONTEND_LT = 207,
	INPUT_FRONTEND_RT = 208,
	INPUT_FRONTEND_LS = 209,
	INPUT_FRONTEND_RS = 210,
	INPUT_FRONTEND_LEADERBOARD = 211,
	INPUT_FRONTEND_SOCIAL_CLUB = 212,
	INPUT_FRONTEND_SOCIAL_CLUB_SECONDARY = 213,
	INPUT_FRONTEND_DELETE = 214,
	INPUT_FRONTEND_ENDSCREEN_ACCEPT = 215,
	INPUT_FRONTEND_ENDSCREEN_EXPAND = 216,
	INPUT_FRONTEND_SELECT = 217,
	INPUT_SCRIPT_LEFT_AXIS_X = 218,
	INPUT_SCRIPT_LEFT_AXIS_Y = 219,
	INPUT_SCRIPT_RIGHT_AXIS_X = 220,
	INPUT_SCRIPT_RIGHT_AXIS_Y = 221,
	INPUT_SCRIPT_RUP = 222,
	INPUT_SCRIPT_RDOWN = 223,
	INPUT_SCRIPT_RLEFT = 224,
	INPUT_SCRIPT_RRIGHT = 225,
	INPUT_SCRIPT_LB = 226,
	INPUT_SCRIPT_RB = 227,
	INPUT_SCRIPT_LT = 228,
	INPUT_SCRIPT_RT = 229,
	INPUT_SCRIPT_LS = 230,
	INPUT_SCRIPT_RS = 231,
	INPUT_SCRIPT_PAD_UP = 232,
	INPUT_SCRIPT_PAD_DOWN = 233,
	INPUT_SCRIPT_PAD_LEFT = 234,
	INPUT_SCRIPT_PAD_RIGHT = 235,
	INPUT_SCRIPT_SELECT = 236,
	INPUT_CURSOR_ACCEPT = 237,
	INPUT_CURSOR_CANCEL = 238,
	INPUT_CURSOR_X = 239,
	INPUT_CURSOR_Y = 240,
	INPUT_CURSOR_SCROLL_UP = 241,
	INPUT_CURSOR_SCROLL_DOWN = 242,
	INPUT_ENTER_CHEAT_CODE = 243,
	INPUT_INTERACTION_MENU = 244,
	INPUT_MP_TEXT_CHAT_ALL = 245,
	INPUT_MP_TEXT_CHAT_TEAM = 246,
	INPUT_MP_TEXT_CHAT_FRIENDS = 247,
	INPUT_MP_TEXT_CHAT_CREW = 248,
	INPUT_PUSH_TO_TALK = 249,
	INPUT_CREATOR_LS = 250,
	INPUT_CREATOR_RS = 251,
	INPUT_CREATOR_LT = 252,
	INPUT_CREATOR_RT = 253,
	INPUT_CREATOR_MENU_TOGGLE = 254,
	INPUT_CREATOR_ACCEPT = 255,
	INPUT_CREATOR_DELETE = 256,
	INPUT_ATTACK2 = 257,
	INPUT_RAPPEL_JUMP = 258,
	INPUT_RAPPEL_LONG_JUMP = 259,
	INPUT_RAPPEL_SMASH_WINDOW = 260,
	INPUT_PREV_WEAPON = 261,
	INPUT_NEXT_WEAPON = 262,
	INPUT_MELEE_ATTACK1 = 263,
	INPUT_MELEE_ATTACK2 = 264,
	INPUT_WHISTLE = 265,
	INPUT_MOVE_LEFT = 266,
	INPUT_MOVE_RIGHT = 267,
	INPUT_MOVE_UP = 268,
	INPUT_MOVE_DOWN = 269,
	INPUT_LOOK_LEFT = 270,
	INPUT_LOOK_RIGHT = 271,
	INPUT_LOOK_UP = 272,
	INPUT_LOOK_DOWN = 273,
	INPUT_SNIPER_ZOOM_IN = 274,
	INPUT_SNIPER_ZOOM_OUT = 275,
	INPUT_SNIPER_ZOOM_IN_ALTERNATE = 276,
	INPUT_SNIPER_ZOOM_OUT_ALTERNATE = 277,
	INPUT_VEH_MOVE_LEFT = 278,
	INPUT_VEH_MOVE_RIGHT = 279,
	INPUT_VEH_MOVE_UP = 280,
	INPUT_VEH_MOVE_DOWN = 281,
	INPUT_VEH_GUN_LEFT = 282,
	INPUT_VEH_GUN_RIGHT = 283,
	INPUT_VEH_GUN_UP = 284,
	INPUT_VEH_GUN_DOWN = 285,
	INPUT_VEH_LOOK_LEFT = 286,
	INPUT_VEH_LOOK_RIGHT = 287,
	INPUT_REPLAY_START_STOP_RECORDING = 288,
	INPUT_REPLAY_START_STOP_RECORDING_SECONDARY = 289,
	INPUT_SCALED_LOOK_LR = 290,
	INPUT_SCALED_LOOK_UD = 291,
	INPUT_SCALED_LOOK_UP_ONLY = 292,
	INPUT_SCALED_LOOK_DOWN_ONLY = 293,
	INPUT_SCALED_LOOK_LEFT_ONLY = 294,
	INPUT_SCALED_LOOK_RIGHT_ONLY = 295,
	INPUT_REPLAY_MARKER_DELETE = 296,
	INPUT_REPLAY_CLIP_DELETE = 297,
	INPUT_REPLAY_PAUSE = 298,
	INPUT_REPLAY_REWIND = 299,
	INPUT_REPLAY_FFWD = 300,
	INPUT_REPLAY_NEWMARKER = 301,
	INPUT_REPLAY_RECORD = 302,
	INPUT_REPLAY_SCREENSHOT = 303,
	INPUT_REPLAY_HIDEHUD = 304,
	INPUT_REPLAY_STARTPOINT = 305,
	INPUT_REPLAY_ENDPOINT = 306,
	INPUT_REPLAY_ADVANCE = 307,
	INPUT_REPLAY_BACK = 308,
	INPUT_REPLAY_TOOLS = 309,
	INPUT_REPLAY_RESTART = 310,
	INPUT_REPLAY_SHOWHOTKEY = 311,
	INPUT_REPLAY_CYCLEMARKERLEFT = 312,
	INPUT_REPLAY_CYCLEMARKERRIGHT = 313,
	INPUT_REPLAY_FOVINCREASE = 314,
	INPUT_REPLAY_FOVDECREASE = 315,
	INPUT_REPLAY_CAMERAUP = 316,
	INPUT_REPLAY_CAMERADOWN = 317,
	INPUT_REPLAY_SAVE = 318,
	INPUT_REPLAY_TOGGLETIME = 319,
	INPUT_REPLAY_TOGGLETIPS = 320,
	INPUT_REPLAY_PREVIEW = 321,
	INPUT_REPLAY_TOGGLE_TIMELINE = 322,
	INPUT_REPLAY_TIMELINE_PICKUP_CLIP = 323,
	INPUT_REPLAY_TIMELINE_DUPLICATE_CLIP = 324,
	INPUT_REPLAY_TIMELINE_PLACE_CLIP = 325,
	INPUT_REPLAY_CTRL = 326,
	INPUT_REPLAY_TIMELINE_SAVE = 327,
	INPUT_REPLAY_PREVIEW_AUDIO = 328,
	INPUT_VEH_DRIVE_LOOK = 329,
	INPUT_VEH_DRIVE_LOOK2 = 330,
	INPUT_VEH_FLY_ATTACK2 = 331,
	INPUT_RADIO_WHEEL_UD = 332,
	INPUT_RADIO_WHEEL_LR = 333,
	INPUT_VEH_SLOWMO_UD = 334,
	INPUT_VEH_SLOWMO_UP_ONLY = 335,
	INPUT_VEH_SLOWMO_DOWN_ONLY = 336,
	INPUT_MAP_POI = 337
};

HMODULE g_proc_module;
HANDLE g_thread_handle;
HANDLE g_console_handle;
HANDLE g_main_fiber;
HANDLE g_script_fiber;
std::uint64_t g_fiber_wake;

// native cache
std::uint64_t g_main_persistent_wait_cache;
std::uint64_t g_freemode_wait_cache;

// virtual cache
std::uint64_t g_receive_clone_create_cache;
std::uint64_t g_receive_clone_sync_cache;
std::uint64_t g_receive_clone_remove_cache;
std::uint64_t g_remove_weapon_event_read_sync_data_cache;
std::uint64_t g_remove_weapon_event_check_sender_cache;
std::uint64_t g_remove_weapon_event_pack_sync_data_cache;
std::uint64_t g_remove_all_weapons_event_read_sync_data_cache;
std::uint64_t g_game_weather_event_read_sync_data_cache;
std::uint64_t g_game_clock_event_read_sync_data_cache;
std::uint64_t g_scripted_game_event_callback_cache;
std::uint64_t g_explosion_event_callback_cache;
std::uint64_t g_fire_event_callback_cache;
std::uint64_t g_increment_stat_event_callback_cache;
std::uint64_t g_spawn_net_obj_ped_cache;
std::uint64_t g_spawn_net_obj_object_cache;

bool g_was_texture_file_load_attempted = false;
bool g_was_texture_file_loaded = false;
bool g_misc_weapons_in_apartment = true;
bool g_misc_weapons_in_casino = true;
bool g_misc_player_join_leave_notify = true;

// menu
simple_timer g_menu_scroll_timer[5];
bool g_menu_is_open = false;
bool g_option_select_pressed = false;
bool g_option_up_pressed = false;
bool g_option_down_pressed = false;
bool g_option_left_pressed = false;
bool g_option_right_pressed = false;
bool g_option_alt_pressed = false;

std::string g_menu_banner_texture = "quantum_header_new";

std::float_t g_menu_banner_pos_x = 0.8700f;
std::float_t g_menu_banner_pos_x_cache = 0.8700f;
std::float_t g_menu_banner_pos_y = 0.0650f;
std::float_t g_menu_banner_pos_y_cache = 0.0650f;

std::float_t g_menu_banner_size_x = 0.2000f;
std::float_t g_menu_banner_size_y = 0.0970f;
std::float_t g_menu_text_padding = 0.0035f;
std::float_t g_menu_text_offset = 0.0145f;

std::float_t g_menu_scroll_bar_pos = 0.0000f;
std::float_t g_menu_scroll_bar_dest = 0.0000f;
std::float_t g_menu_scroll_bar_inc = 0.0000f;
std::float_t g_menu_scroll_bar_smoothness = 3.0000f;

rgba* g_selected_menu_colour_to_edit;
rgba g_menu_header_colour(10, 20, 30, 200);
rgba g_menu_header_text_colour(66, 225, 221, 150);
rgba g_menu_background_colour(10, 20, 30, 60);
rgba g_menu_option_text_colour(255, 255, 255, 200);
rgba g_menu_selected_option_text_colour(66, 225, 221, 150);
rgba g_menu_scroll_bar_colour(14, 14, 14, 200);
rgba g_menu_footer_colour(10, 20, 30, 200);
rgba g_menu_footer_arrows_colour(66, 225, 221, 200);
rgba g_menu_footer_text_colour(66, 225, 221, 200);
rgba g_menu_variable_arrows_colour(66, 225, 221, 200);
rgba g_menu_submenu_accent_colour(10, 20, 30, 150);
rgba g_menu_toggle_on_colour(66, 225, 221, 200);
rgba g_menu_toggle_off_colour(210, 50, 90, 200);
rgba g_menu_break_option_colour(140, 140, 140, 200);

std::int32_t g_info_box_count = NULL;
std::float_t g_info_box_title_width = 0.16f;
std::float_t g_info_box_title_length = 0.05f;

typedef void(*menu_cxt_fn)();
struct menu_cxt {
	int m_current_option{};
	int m_max_options{};
	int m_option_count{};
	menu_cxt_fn m_cxt_fn{};
	std::string m_title{};
};
bool g_push_menu_cxt = true;
bool g_push_main_menu = true;
menu_cxt g_menu_cxt_to_push;
std::stack<menu_cxt> g_menu_cxt_stack;
#define MENU_TITLE g_menu_cxt_stack.top().m_title
#define MAX_OPTIONS g_menu_cxt_stack.top().m_max_options
#define OPTION_COUNT g_menu_cxt_stack.top().m_option_count
#define CURRENT_OPTION g_menu_cxt_stack.top().m_current_option
#define CONTEXT_STACK_VALID g_menu_cxt_stack.size() > NULL

class scr_global {
private:
	std::uint64_t m_index;
	static void* get_scr_global(std::uint64_t index) { return ((std::uint64_t**)(GTA_GAME_GLOBALS))[index >> 18 & 0x3F] + (index & 0x3FFFF); }
public:
	constexpr explicit scr_global(std::uint64_t index) : m_index(index) {}
	constexpr scr_global at(std::uint64_t index) { return scr_global(m_index + index); }
	constexpr scr_global at(std::uint64_t index, std::uint64_t size) { return at(1 + (index * size)); }
	template <typename T>
	std::enable_if_t<std::is_pointer<T>::value, T> as() const { return (T)(get_scr_global(m_index)); }
};

// Protections
std::int32_t g_received_net_obj_count = NULL;
struct received_net_obj {
	std::uint16_t m_clone_type;
	std::uint16_t m_net_id;
	std::uint64_t m_timestamp;
	std::uint8_t m_owner_physical_index;
} g_received_net_obj[100];
bool g_object_protection = false;
bool g_spam_protection = false;
bool g_notify_attacks = false;
bool g_protection_remove_weapon = false;
bool g_protection_remove_all_weapons = false;
bool g_protection_weather_change = false;
bool g_protection_explosion = false;
bool g_protection_fire = false;
bool g_protection_stat_increment = false;
bool g_protection_redirect_bullets = false;
bool g_fake_position;

//Self
bool g_self_god_mode = false;
bool g_self_invisibility;
bool g_self_no_ragdoll = false;
bool g_self_no_cops = false;
bool g_self_super_run; std::float_t g_self_super_run_modifier = 1.5f;
bool g_self_super_jump;
bool g_self_super_swim;
bool g_self_night_vision;
bool g_self_heat_vision;
bool g_self_shrink;
bool g_self_cops_turn_blind_eye;
bool g_self_reveal_players;
bool g_self_off_the_radar;
bool g_self_forcefield;
bool g_self_slow_motion;
bool g_self_superman;
bool g_self_mobile_radio;
bool g_self_menu_ped_lean_active = false;
std::float_t g_self_menu_ped_lean = 0.0f;
bool g_self_menu_ped_width_active = false;
std::float_t g_self_menu_ped_width = 0.0f;
bool g_self_menu_ped_height_active = false;
std::float_t g_self_menu_ped_height = 0.0f;
std::int32_t g_self_wanted_level = 0;
std::int32_t g_self_outfit_selected_component_id = 0;
std::int32_t g_self_outfit_current_texture_id[12] = { 0 };
std::int32_t g_self_outfit_current_drawable_id[12] = { 0 };
std::int32_t g_self_outfit_current_pallette_id[12] = { 0 };
bool g_loaded_list_file_peds_did_load = false;
std::vector<std::string> g_loaded_list_file_peds;
std::int32_t g_loaded_list_file_peds_filter_count = NULL;
std::string g_loaded_list_file_peds_filter;
std::int32_t g_self_model_cam, g_self_model_temp_cam; bool g_self_outfit_model_cam_active = false;
std::int32_t g_ped_bone_list[] = {
	31086, //head
	31086,
	31086,
	11816, //torso
	11816,
	0, //root
	11816, //foot
	0, //root
	0,
	0,
	0,
	11816 //torso
};
std::float_t g_animation_speed = 1.0f;
struct anim_set {
	std::string local_name;
	std::string anim_dict;
	std::string anim_name;
};
anim_set g_sport_anims[] = { { "Situps", "amb@world_human_sit_ups@male@base", "base" },
{ "Pushups", "amb@world_human_push_ups@male@base", "base" },
{ "Bench Press", "amb@prop_human_seat_muscle_bench_press@idle_a", "idle_a" },
{ "Pullups", "SWITCH@FRANKLIN@GYM", "001942_02_GC_FRAS_IG_5_BASE" },
{ "Chin Ups 1", "amb@prop_human_muscle_chin_ups@male@base", "base" },
{ "Chin Ups 2", "amb@prop_human_muscle_chin_ups@male@enter", "enter" },
{ "Chin Ups 3", "amb@prop_human_muscle_chin_ups@male@exit", "exit_flee" },
{ "Chin Ups 4", "amb@prop_human_muscle_chin_ups@male@idle_a", "idle_a" },
{ "Free Weights 1", "amb@world_human_muscle_free_weights@male@barbell@base", "base" },
{ "Free Weights 2", "amb@world_human_muscle_free_weights@male@barbell@idle_a", "idle_a" },
{ "Flex 1", "amb@world_human_muscle_flex@arms_at_side@base", "base" },
{ "Flex 2", "amb@world_human_muscle_flex@arms_at_side@idle_a", "idle_a" },
{ "Flex 3", "amb@world_human_muscle_flex@arms_in_front@base", "base" },
{ "Flex 4", "amb@world_human_muscle_flex@arms_in_front@idle_a", "idle_b" } };
anim_set g_sex_anims[] = { { "Fuck 1", "rcmpaparazzo_2", "shag_loop_a" },
{ "Fuck 2", "rcmpaparazzo_2", "shag_loop_poppy" },
{ "Prostitue Male Sex", "mini@prostitutes@sexnorm_veh", "sex_loop_male" },
{ "Prostitue Female Sex", "mini@prostitutes@sexnorm_veh", "sex_loop_prostitute" },
{ "Prostitue Male BJ", "mini@prostitutes@sexnorm_veh", "bj_loop_male" },
{ "Prostitue Female BJ", "mini@prostitutes@sexnorm_veh", "bj_loop_prostitute" },
{ "Drunk Sex Male", "random@drunk_driver_2", "cardrunksex_loop_m" },
{ "Drunk Sex Female", "random@drunk_driver_2", "cardrunksex_loop_f" } };
anim_set g_dance_anims[] = { { "Pole Dance 1", "mini@strip_club@pole_dance@pole_dance1", "pd_dance_01" },
{ "Pole Dance 2", "mini@strip_club@pole_dance@pole_dance2", "pd_dance_02" },
{"Pole Dance 3", "mini@strip_club@pole_dance@pole_dance3", "pd_dance_03" },
{ "Private Dance", "mini@strip_club@private_dance@part1", "priv_dance_p1" },
{ "Tap Dance", "special_ped@mountain_dancer@monologue_2@monologue_2a", "mnt_dnc_angel" },
{ "Buttwag Dance", "special_ped@mountain_dancer@monologue_3@monologue_3a", "mnt_dnc_buttwag" },
{"Verse Dance", "special_ped@mountain_dancer@monologue_4@monologue_4a", "mnt_dnc_verse" },
{ "Heaven Dance", "special_ped@mountain_dancer@monologue_1@monologue_1a", "mtn_dnc_if_you_want_to_get_to_heaven" } };
anim_set g_super_hero_anims[] = { { "I'm An Actor", "special_ped@impotent_rage@convo_1@convo_1a", "im_an_actor_0" },
{ "You Can't Stop Me", "special_ped@impotent_rage@monologue_12@monologue_12d", "you_cant_stop_my_3" },
{ "I Wanna Do Hamlet", "special_ped@impotent_rage@convo_2@convo_2a", "i_wanna_do_hamlet_0" },
{ "Having About As Much", "special_ped@impotent_rage@convo_3@convo_3a", "having_about_as_much_0" },
{ "Just Wondering When", "special_ped@impotent_rage@convo_4@convo_4a", "just_woundering_when_0" },
{ "Great I Wanted To", "special_ped@impotent_rage@convo_5@convo_5a", "great_i_wanted_to_0" },
{ "A Tourist Just Asked to", "special_ped@impotent_rage@convo_6@convo_6a", "a_tourist_just_asked_0" },
{ "Idle Intro", "special_ped@impotent_rage@intro", "idle_intro" },
{ "Defeat 1", "special_ped@impotent_rage@monologue_10@monologue_10b", "i_will_defeat_the_1" },
{ "Defeat 2", "special_ped@impotent_rage@monologue_10@monologue_10c", "i_will_defeat_the_2" },
{ "Unhappy 1", "special_ped@impotent_rage@monologue_11@monologue_11a", "really_very_unhappy_0" },
{ "Unhappy 2", "special_ped@impotent_rage@monologue_11@monologue_11b", "really_very_unhappy_1" },
{ "Unhappy 3", "special_ped@impotent_rage@monologue_11@monologue_11c", "really_very_unhappy_2" },
{ "Unhappy 4", "special_ped@impotent_rage@monologue_11@monologue_11d", "really_very_unhappy_3" } };
anim_set g_misc_anims[] = { { "Tazer", "ragdoll@human", "electrocute" },
{ "Stun Fire", "ragdoll@human", "on_fire" },
{ "Electrocute", "stungun@standing", "damage" },
{ "Waving Arms", "random@car_thief@victimpoints_ig_3", "arms_waving" },
{ "Meditating", "rcmcollect_paperleadinout@", "meditiate_idle" },
{ "Rolling Barrel", "misschinese2_barrelroll", "barrel_roll_loop_A" },
{ "Cop Kneeling Arrest", "random@arrests", "kneeling_arrest_idle" },
{ "Jerking Off", "switch@trevor@jerking_off", "trev_jerking_off_loop" },
{ "Drunk Howling", "switch@trevor@drunk_howling", "loop" },
{ "Pee", "misscarsteal2peeing", "peeing_intro" } };
std::string g_scenario_name[] = { "Drill", "Drink Coffee", "Smoke", "Binoculars", "Freeway Bum", "Slumped Bum", "Standing Bum", "Bum Washing", "Park Attendant", "Cheering", "Clipboard", "Idle Cop", "Drinking", "Drug Dealer", "Drug Dealer (Hard)", "Mobile Film", "Leaf Blower", "Gardener", "Gold Player", "Guard Patrol", "Guard Stand", "Guard Stand (Military)", "Hammering", "Hangout Street", "Hiker Standing", "Human Statue", "Janitor", "Jog Standing", "Leaning", "Maid Cleaning", "Muscle Flex", "Free Weights", "Musician", "Paparazzi", "Partying", "Picnic", "Prostitute (High)", "Prostitute (Low)", "Pushups", "Security Shine Torch", "Situps", "Smoking", "Smoking Pot", "Standing By Fire", "Fishing", "Impatient", "Stand Mobile", "Strip Watch", "Stupor", "Sunbathing (Front)", "Sunbathing (Back)", "Superhero", "Swimming", "Tennis", "Tourist 1", "Tourist 2", "Mechanic", "Welding", "Window Shop Browse", "Yoga" };
std::string g_scenario_to_do[] = { "WORLD_HUMAN_CONST_DRILL", "WORLD_HUMAN_AA_COFFEE", "WORLD_HUMAN_AA_SMOKE", "WORLD_HUMAN_BINOCULARS", "WORLD_HUMAN_BUM_FREEWAY", "WORLD_HUMAN_BUM_SLUMPED", "WORLD_HUMAN_BUM_STANDING", "WORLD_HUMAN_BUM_WASH", "WORLD_HUMAN_CAR_PARK_ATTENDANT", "WORLD_HUMAN_CHEERING", "WORLD_HUMAN_CLIPBOARD", "WORLD_HUMAN_COP_IDLES", "WORLD_HUMAN_DRINKING", "WORLD_HUMAN_DRUG_DEALER", "WORLD_HUMAN_DRUG_DEALER_HARD", "WORLD_HUMAN_MOBILE_FILM_SHOCKING", "WORLD_HUMAN_GARDENER_LEAF_BLOWER", "WORLD_HUMAN_GARDENER_PLANT", "WORLD_HUMAN_GOLF_PLAYER", "WORLD_HUMAN_GUARD_PATROL", "WORLD_HUMAN_GUARD_STAND", "WORLD_HUMAN_GUARD_STAND_ARMY", "WORLD_HUMAN_HAMMERING", "WORLD_HUMAN_HANG_OUT_STREET", "WORLD_HUMAN_HIKER_STANDING", "WORLD_HUMAN_HUMAN_STATUE", "WORLD_HUMAN_JANITOR", "WORLD_HUMAN_JOG_STANDING", "WORLD_HUMAN_LEANING", "WORLD_HUMAN_MAID_CLEAN", "WORLD_HUMAN_MUSCLE_FLEX", "WORLD_HUMAN_MUSCLE_FREE_WEIGHTS", "WORLD_HUMAN_MUSICIAN", "WORLD_HUMAN_PAPARAZZI", "WORLD_HUMAN_PARTYING", "WORLD_HUMAN_PICNIC", "WORLD_HUMAN_PROSTITUTE_HIGH_CLASS", "WORLD_HUMAN_PROSTITUTE_LOW_CLASS", "WORLD_HUMAN_PUSH_UPS", "WORLD_HUMAN_SECURITY_SHINE_TORCH", "WORLD_HUMAN_SIT_UPS", "WORLD_HUMAN_SMOKING", "WORLD_HUMAN_SMOKING_POT", "WORLD_HUMAN_STAND_FIRE", "WORLD_HUMAN_STAND_FISHING", "WORLD_HUMAN_STAND_IMPATIENT", "WORLD_HUMAN_STAND_MOBILE", "WORLD_HUMAN_STRIP_WATCH_STAND", "WORLD_HUMAN_STUPOR", "WORLD_HUMAN_SUNBATHE", "WORLD_HUMAN_SUNBATHE_BACK", "WORLD_HUMAN_SUPERHERO", "WORLD_HUMAN_SWIMMING", "WORLD_HUMAN_TENNIS_PLAYER", "WORLD_HUMAN_TOURIST_MAP", "WORLD_HUMAN_TOURIST_MOBILE", "WORLD_HUMAN_VEHICLE_MECHANIC", "WORLD_HUMAN_WELDING", "WORLD_HUMAN_WINDOW_SHOP_BROWSE", "WORLD_HUMAN_YOGA" };

//Weapon
struct weapon_set {
	std::string name;
	std::uint32_t hash;
};
weapon_set weapon_hashs[] = { {"Antique Cavalry Dagger", 0x92A27487}, {"Baseball Bat", 0x958A4A8F}, {"Broken Bottle", 0xF9E6AA4B}, {"Crowbar", 0x84BD7BFD}, {"Fist", 0xA2719263}, {"Flashlight", 0x8BB05FD7}, {"Golf Club", 0x440E4788}, {"Hammer", 0x4E875F73}, {"Hatchet", 0xF9DCBF2D}, {"Brass Knuckles", 0xD8DF3C3C },
{"Knife", 0x99B507EA}, {"Machete", 0xDD5DF8D9}, {"Switchblade", 0xDFE37640}, {"Nightstick", 0x678B81B1}, {"Pipe Wrench", 0x19044EE0}, {"Battle Axe", 0xCD274149}, {"Pool Cue", 0x94117305}, {"Stone Hatchet", 0x3813FC08}, {"Pistol", 0x1B06D571}, {"Pistol Mk II", 0xBFE256D4},
{"Combat Pistol", 0x5EF9FEC4}, {"AP Pistol", 0x22D8FE39}, {"Stun Gun", 0x3656C8C1}, {"Pistol .50", 0x99AEEB3B}, {"SNS Pistol", 0xBFD21232}, {"SNS Pistol Mk II", 0x88374054}, {"Heavy Pistol", 0xD205520E}, {"Vintage Pistol", 0x83839C4}, {"Flare Gun", 0x47757124}, {"Marksman Pistol", 0xDC4DB296},
{"Heavy Revolver", 0xC1B3C3D1}, {"Heavy Revolver Mk II", 0xCB96392F}, {"Double Action Revolver", 0x97EA20B8}, {"Up-n-Atomizer", 0xAF3696A1}, {"Ceramic Pistol", 0x2B5EF5EC}, {"Navy Revolver", 0x917F6C8C}, {"Micro SMG", 0x13532244}, {"SMG", 0x2BE6766B}, {"SMG Mk II", 0x78A97CD0}, {"Assault SMG", 0xEFE7E2DF},
{"Combat PDW", 0xA3D4D34}, {"Machine Pistol", 0xDB1AA450}, {"Mini SMG", 0xBD248B55}, {"Unholy Hellbringer", 0x476BF155}, {"Pump Shotgun", 0x1D073A89}, {"Pump Shotgun Mk II", 0x555AF99A}, {"Sawed-Off Shotgun", 0x7846A318}, {"Assault Shotgun", 0xE284C527}, {"Bullpup Shotgun", 0x9D61E50F}, {"Musket", 0xA89CB99E},
{"Heavy Shotgun", 0x3AABBBAA}, {"Double Barrel Shotgun", 0xEF951FBB}, {"Sweeper Shotgun", 0x12E82D3D}, {"Assault Rifle", 0xBFEFFF6D}, {"Assault Rifle Mk II", 0x394F415C}, {"Carbine Rifle", 0x83BF0278}, {"Carbine Rifle Mk II", 0xFAD1F1C9}, {"Advanced Rifle", 0xAF113F99}, {"Special Carbine", 0xC0A3098D}, {"Special Carbine Mk II", 0x969C3D67},
{"Bullpup Rifle", 0x7F229F94}, {"Bullpup Rifle Mk II", 0x84D6FAFD}, {"Compact Rifle", 0x624FE830}, {"MG", 0x9D07F764}, {"Combat MG", 0x7FD62962}, {"Combat MG Mk II", 0xDBBD7280}, {"Gusenberg Sweeper", 0x61012683}, {"Sniper Rifle", 0x5FC3C11}, {"Heavy Sniper", 0xC472FE2}, {"Heavy Sniper Mk II", 0xA914799},
{"Marksman Rifle", 0xC734385A}, {"Marksman Rifle Mk II", 0x6A6C02E0}, {"RPG", 0xB1CA77B1}, {"Grenade Launcher", 0xA284510B}, {"Grenade Launcher Smoke", 0x4DD2DC56}, {"Minigun", 0x42BF8A85}, {"Firework Launcher", 0x7F7497E5}, {"Railgun", 0x6D544C99}, {"Homing Launcher", 0x63AB0442}, {"Compact Grenade", 0x781FE4A},
{"Widowmaker", 0xB62D1F67}, {"Grenade", 0x93E220BD}, {"BZ Gas", 0xA0973D5E}, {"Tear Gas", 0xFDBC8A50}, {"Flare", 0x497FACC3}, {"Molotov Cocktail", 0x24B17070}, {"Sticky Bomb", 0x2C3731D9}, {"Proximity Mines", 0xAB564B93}, {"Snowballs", 0x787F0BB}, {"Pipe Bombs", 0xBA45E8B8},
{"Baseball", 0x23C9F95C}, {"Jerry Can", 0x34A67B97}, {"Fire Extinguisher", 0x60EC506}, {"Parachute", 0xFBAB5776}, {"Hazardous Jerry Can", 0xBA536372 } };
bool g_weapon_unlimited_ammo = true;
bool g_weapon_explosive_impact;
std::int32_t g_weapon_explosive_impact_type = NULL;
bool g_weapon_no_stun_gun_cooldown, g_weapon_no_reload, g_weapon_no_recoil, g_weapon_quick_reload, g_weapon_laser_sight, g_weapon_dead_eye;
std::string g_weapon_bullet_types[] = {
	"WEAPON_FIREWORK",
	"WEAPON_GRENADE",
	"WEAPON_MOLOTOV",
	"WEAPON_VEHICLE_ROCKET",
	"VEHICLE_WEAPON_TANK",
	"VEHICLE_WEAPON_ENEMY_LASER",
};
bool g_weapon_bullet_changer;
bool g_weapon_bullet_changer_audible = true;
bool g_weapon_bullet_changer_invisible;
std::int32_t g_weapon_bullet_changer_selected_arr_index;
std::float_t g_weapon_bullet_changer_speed;
bool g_weapon_special_gravity;
std::int32_t g_weapon_gravity_entity = 0;
std::string g_weapon_gravity_entity_type[] = { "Vehicle", "Ped", "Object" };
std::float_t g_weapon_gravity_distance = 10.0f;
std::float_t g_weapon_gravity_sling_force = 100.0f;
Vector3 g_gravity_cam_dir;
Vector3 g_gravity_pos;
bool g_check_gravity_veh_dim = false;
bool g_gravity_cooldown = false;
std::int32_t g_gravity_entity = NULL;
std::int32_t g_vortex_gun_ped_capacity = 10;
std::int32_t g_vortex_gun_vehicle_capacity = 10;
std::int32_t g_vortex_gun_object_capacity = 10;
std::float_t g_vortex_gun_distance = 10.0f;
std::float_t g_vortex_gun_force = 500.0f;
bool g_vortex_gun_active = false;
bool g_vortex_gun_grab_peds = true;
bool g_vortex_gun_grab_vehicles = true;
bool g_vortex_gun_grab_objects = true;
bool g_vortex_cooldown = false;
bool g_weapon_totem_gun = false;
std::float_t g_weapon_totem_gun_distance = 10.0f;
std::float_t g_weapon_totem_gun_spacing = 5.0f;
bool g_weapon_special_grapple, g_weapon_special_grapple_enabled, g_weapon_special_shotgun, g_weapon_special_rubber_bullets, g_weapon_special_teleport, g_weapon_special_delete, g_weapon_special_vehicle;
Vector3 g_weapon_special_pos;
Vector3 g_weapon_aiming_coords;
BOOL g_shape_test_did_hit = FALSE;
std::int32_t g_shape_test_entity = FALSE;
Vector3 g_shape_test_destination;
Vector3 g_shape_test_surface;
std::int32_t g_shape_test_ray = FALSE;

//network
bool g_network_streamer_mode_active;
bool g_network_streamer_mode_self_included;
bool g_network_streamer_mode_display_as_hex;
std::string g_network_streamer_mode_prefix = "Player";
std::string g_menu_network_spoofing_name;
bool g_menu_network_spoofing_name_active;
std::string g_menu_network_spoofing_rid;
bool g_menu_network_spoofing_rid_active;
std::uint32_t g_network_selected_player;
class network_player_vars {
public:

	// mailcious
	Vector3 m_looped_explosion_offset;
	std::int32_t m_looped_explosion_selected_arr_index{ 0 };
	bool m_looped_explosion_invisible{ false };
	bool m_looped_explosion_audible{ true };
	bool m_looped_explosion_active{ false };

	bool m_take_weapons{ false };
	bool m_freeze_loop{ false };

	// vehicle
	bool m_horn_boost_active{ false };

	// spoofing
	std::string m_spoofing_name{ "" };
	bool m_spoofing_name_active{ false };

	// misc
	bool m_spectate_player{ false };

	// esp
	bool m_esp_line{ false };
	bool m_esp_box{ false };
	bool m_esp_name{ false };

	// 

	std::int32_t m_spam_crash_entity{ 0 };
	bool m_do_spam_crash{ false };

	std::uint64_t m_clone_crash_entity_target{ 0 };
	bool m_do_clone_crash{ false };

	void reset_vars() {

		// mailcious
		m_looped_explosion_offset.x = 0.0f;
		m_looped_explosion_offset.y = 0.0f;
		m_looped_explosion_offset.z = 0.0f;
		m_looped_explosion_selected_arr_index = 0;
		m_looped_explosion_invisible = false;
		m_looped_explosion_audible = true;
		m_looped_explosion_active = false;

		m_take_weapons = false;
		m_freeze_loop = false;

		// vehicle
		m_horn_boost_active = false;

		// spoofing
		m_spoofing_name = "";
		m_spoofing_name_active = false;

		// misc
		m_spectate_player = false;

		// esp
		m_esp_line = false;
		m_esp_box = false;
		m_esp_name = false;

		// crash
		m_spam_crash_entity = 0;
		m_do_spam_crash = false;
	}
};
network_player_vars g_network_player_vars[32];
template<int i>
class chat_command_client {
public:
	bool m_has_access;
	bool m_mod_active[i];
	void revoke_access() {
		for (std::int32_t i = 0; i < ARRAYSIZE(m_mod_active); i++)
			m_mod_active[i] = false;
		m_has_access = false;
	}
};
std::string g_chat_commands[] = {
	"/help",
	"/semigod",
};
chat_command_client<ARRAYSIZE(g_chat_commands)> g_chat_command_clients[32];

std::string g_take_money_arr_strings[] = { "1K", "10K", "100K", "1M", "10M", "100M", "1B" };
std::int32_t g_take_money_arr_values[] = { 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };
std::int32_t g_selected_online_player_crash_victim;
std::int32_t g_selected_menu_network_attachment_manager_manage_attached_manage_entity = NULL;
std::vector<std::pair<std::uint64_t, std::int32_t>> g_network_lobby_host_migration_queue;
std::int32_t g_network_attachment_manager_manage_attached_count = NULL;

// pedestrian
std::int32_t g_selected_pedestrian_cam; std::float_t g_pedestrian_right_angle1, g_pedestrian_right_angle2;
bool g_selected_pedestrian_camera = true;
struct managed_ped {
	std::string name;
	std::int32_t handle{ 0 };
	std::int32_t selected_component_id{ 0 };
	std::int32_t current_texture_id[12]{ 0 };
	std::int32_t current_drawable_id[12]{ 0 };
	std::int32_t current_pallette_id[12]{ 0 };
	std::int32_t task_sequence_active{ 0 };
	std::int32_t task_sequence[20][10]{ 0 };
	bool is_bodyguard{ false };
	bool is_invincible{ false };
	bool is_invisible{ false };
	bool draw_esp{ false };
	std::float_t width{ 0.0f };
	std::float_t height{ 0.0f };
	std::float_t lean{ 0.0f };
};
std::int32_t g_selected_pedestrian;
managed_ped g_pedestrian_peds[32];
std::int32_t g_pedestrian_task_pause = 4000;
std::float_t temp_hated_targets_radius = 5.0f;
std::int32_t g_pedestrian_task_sequence_add = NULL;
std::int32_t g_pedestrian_task_weapon = NULL;
std::int32_t g_pedestrian_hated_target = NULL;
std::string g_pedestrian_hated_targets[] = {
	"PLAYER",
	"CIVMALE",
	"CIVFEMALE",
	"COP",
	"SECURITY_GUARD",
	"PRIVATE_SECURITY",
	"FIREMAN",
	"GANG_1",
	"GANG_2",
	"GANG_9",
	"GANG_10",
	"AMBIENT_GANG_LOST",
	"AMBIENT_GANG_MEXICAN",
	"AMBIENT_GANG_FAMILY",
	"AMBIENT_GANG_BALLAS",
	"AMBIENT_GANG_MARABUNTE",
	"AMBIENT_GANG_CULT",
	"AMBIENT_GANG_SALVA",
	"AMBIENT_GANG_WEICHENG",
	"AMBIENT_GANG_HILLBILLY",
	"DEALER",
	"HATES_PLAYER",
	"HEN",
	"WILD_ANIMAL",
	"SHARK",
	"COUGAR",
	"NO_RELATIONSHIP",
	"SPECIAL",
	"MISSION2",
	"MISSION3",
	"MISSION4",
	"MISSION5",
	"MISSION6",
	"MISSION7",
	"MISSION8",
	"ARMY",
	"GUARD_DOG",
	"AGGRESSIVE_INVESTIGATE",
	"MEDIC",
	"CAT"
};
std::float_t g_pedestrian_enter_vehicle_radius = 20.0f;
std::int32_t g_pedestrian_enter_vehicle_seat = NULL;
std::string g_pedestrian_enter_vehicle[] = {
	"Driver",
	"Passenger",
	"Left Backseat",
	"Right Backseat"
};
std::int32_t g_pedestrian_all_group_formation_type = NULL;
std::string g_pedestrian_all_group_formation[] = {
	"Default",
	"Circle Leader",
	"Alternative Circle Leader",
	"Line, with Leader"
};
bool g_all_pedestrian_draw_esp = false;

// vehicle 
bool g_vehicle_spawn_options_spawn_in_a_line = false;
bool g_vehicle_spawn_options_spawn_inside = true;
std::int32_t g_vehicle_spawn_options_spawn_amount = 1;
bool g_vehicle_spawn_options_max_upgrades = true;
std::int32_t g_vehicle_spawner_selected_class;
bool g_vehicle_lsc_cam_active = true; std::int32_t g_vehicle_lsc_cam, g_vehicle_lsc_cam_temp;
std::string g_vehicle_lsc_plate_text;
std::int32_t g_vehicle_lsc_neon_rgb[3];
std::int32_t g_vehicle_lsc_respray_category;
std::int32_t g_vehicle_lsc_respray_type;
std::int32_t g_vehicle_lsc_respray_custom_primary[3];
std::int32_t g_vehicle_lsc_respray_custom_secondary[3];
bool g_vehicle_rainbow_paint_fade;
rgba g_vehicle_rainbow_paint_fade_colour(255, 0, 0, 255);
struct particle_effect_info {
	std::string asset;
	std::string name;
};
particle_effect_info g_particle_effect_list[] = {
	{ "core", "muz_rpg" },
	{ "scr_rcbarry1", "scr_alien_teleport" },
	{ "scr_rcbarry1", "scr_alien_disintegrate" },
	{ "scr_rcbarry2", "scr_clown_death" },
	{ "scr_rcbarry2", "scr_clown_appears" },
	{ "weap_xs_weapons", "exp_xs_ray" },
	{ "weap_xs_weapons", "muz_xs_sr_minigun" },
};
std::string g_particle_effect_names[] = {
	"RPG Muzzle",
	"Alien Teleport",
	"Alien Disintegrate",
	"Clown Death",
	"Clown Appears",
	"XS Raygun",
	"XS Minigun",
};
std::string g_vehicle_bone_list[] = {
	"CHASSIS"
	"WHEEL_LF",
	"WHEEL_RF",
	"WHEEL_LR",
	"WHEEL_RR",
	"HEADLIGHT_L",
	"HEADLIGHT_R",
	"TAILLIGHT_L",
	"TAILLIGHT_R",
};
std::int32_t g_vehicle_particle_trails_selected_bone_arr_index;
std::int32_t g_vehicle_particle_trails_selected_particle_arr_index;
std::float_t g_vehicle_particle_trails_scale;
bool g_vehicle_particle_trails_bone_active[std::size(g_vehicle_bone_list)];
bool g_vehicle_particle_trails_play_when_stationary;
bool g_vehicle_particle_trails_active;
#define PED_DRIVE_FLAG_STOP_BEFORE_VEHICLES			(1 << 0)
#define PED_DRIVE_FLAG_STOP_BEFORE_PEDS				(1 << 1)
#define PED_DRIVE_FLAG_AVOID_VEHICLES				(1 << 2)
#define PED_DRIVE_FLAG_AVOID_EMPTY_VEHICLES			(1 << 3)
#define PED_DRIVE_FLAG_AVOID_PEDS					(1 << 4)
#define PED_DRIVE_FLAG_AVOID_OBJECTS				(1 << 5)
#define PED_DRIVE_FLAG_STOP_AT_TRAFFIC_LIGHTS		(1 << 7)
#define PED_DRIVE_FLAG_USE_BLINKERS					(1 << 8)
#define PED_DRIVE_FLAG_ALLOW_TO_GO_WRONG_WAY		(1 << 9)
#define PED_DRIVE_FLAG_GO_IN_REVERSE_GEAR			(1 << 10)
#define PED_DRIVE_FLAG_TAKE_SHORTEST_PATH			(1 << 18)
#define PED_DRIVE_FLAG_AVOID_OFFROAD				(1 << 19)
#define PED_DRIVE_FLAG_AVOID_HIGHWAYS				(1 << 29)
bool g_vehicle_drive_to_waypoint_stop_before_vehicles = false;
bool g_vehicle_drive_to_waypoint_stop_before_peds = false;
bool g_vehicle_drive_to_waypoint_avoid_vehicles = false;
bool g_vehicle_drive_to_waypoint_avoid_empty_vehicles = false;
bool g_vehicle_drive_to_waypoint_avoid_peds = false;
bool g_vehicle_drive_to_waypoint_avoid_objects = false;
bool g_vehicle_drive_to_waypoint_stop_at_traffic_lights = false;
bool g_vehicle_drive_to_waypoint_use_blinkers = false;
bool g_vehicle_drive_to_waypoint_allow_to_go_wrong_way = false;
bool g_vehicle_drive_to_waypoint_go_in_reverse_gear = false;
bool g_vehicle_drive_to_waypoint_take_shortest_path = false;
bool g_vehicle_drive_to_waypoint_avoid_offroad = false;
bool g_vehicle_drive_to_waypoint_avoid_highways = false;
std::float_t g_vehicle_drive_to_waypoint_speed = 40.0f;
std::float_t g_vehicle_drive_to_waypoint_driver_ability = 1.0f;
struct vehicle_base_model_info {
	std::string name;
	std::int32_t type;
};
std::int32_t g_vehicle_base_model;
vehicle_base_model_info vehicle_base_model[] = { {"Car", 0}, {"Plane", 1}, {"Trailer", 2}, {"Quad", 3}, {"Heli", 8}, {"Blimp", 9}, {"Bike", 11}, {"Bicycle", 12}, {"Boat", 13}, {"Train", 14}, {"Sub", 15} };
bool g_vehicle_fly_vehicle;
std::int32_t g_drive_wheel_object;
bool g_vehicle_drive_in_air = false;
bool g_vehicle_drive_on_water = false;
bool g_vehicle_drive_through_walls = false;
std::float_t g_vehicle_nitrous_exponent = 1.010f;
bool g_vehicle_nitrous_play_sound;
bool g_vehicle_nitrous_screen_effect;
bool g_vehicle_nitrous_active;
bool g_vehicle_drift_mode;
bool g_vehicle_super_grip;
bool g_vehicle_gravity;
bool g_vehicle_tumble_dryer;
bool g_vehicle_sticky_tires;
std::int32_t g_vehicle_weapon; bool g_vehicle_weapon_active;
std::string g_vehicle_weapon_hash[] = { "WEAPON_VEHICLE_ROCKET", "WEAPON_REMOTESNIPER", "VEHICLE_WEAPON_TANK", "WEAPON_COMBATMG", "WEAPON_FLARE", "WEAPON_MOLOTOV" };
std::int32_t g_vehicle_funny_car_temp_object;
std::float_t g_vehicle_funny_car_cam_zoom = 5.0f, g_vehicle_funny_car_x = 0, g_vehicle_funny_car_y = 0, g_vehicle_funny_car_z = 0, g_vehicle_funny_car_p = 0, g_vehicle_funny_car_r = 0, g_vehicle_funny_car_ya = 0;
std::int32_t g_vehicle_funny_car_bone = NULL;
bool g_vehicle_funny_car_invisible = false;
bool g_vehicle_plate_speedo;
bool g_vehicle_seatbelt;
bool g_vehicle_invincible = true;
bool g_vehicle_invisible;
bool g_vehicle_auto_flip;
std::string g_radio_stations[] = {
	"RADIO_01_CLASS_ROCK",
	"RADIO_02_POP",
	"RADIO_03_HIPHOP_NEW",
	"RADIO_04_PUNK",
	"RADIO_05_TALK_01",
	"RADIO_06_COUNTRY",
	"RADIO_07_DANCE_01",
	"RADIO_08_MEXICAN",
	"RADIO_09_HIPHOP_OLD",
	"RADIO_12_REGGAE",
	"RADIO_13_JAZZ",
	"RADIO_14_DANCE_02",
	"RADIO_15_MOTOWN",
	"RADIO_20_THELAB",
	"RADIO_16_SILVERLAKE",
	"RADIO_17_FUNK",
	"RADIO_18_90S_ROCK",
	"RADIO_21_DLC_XM17",
	"RADIO_11_TALK_02",
	"RADIO_22_DLC_BATTLE_MIX1_RADIO",
	"RADIO_19_USER",
	"HIDDEN_RADIO_01_CLASS_ROCK",
	"HIDDEN_RADIO_AMBIENT_TV_BRIGHT",
	"HIDDEN_RADIO_AMBIENT_TV",
	"HIDDEN_RADIO_ADVERTS",
	"HIDDEN_RADIO_02_POP",
	"HIDDEN_RADIO_03_HIPHOP_NEW",
	"HIDDEN_RADIO_04_PUNK",
	"HIDDEN_RADIO_06_COUNTRY",
	"HIDDEN_RADIO_07_DANCE_01",
	"HIDDEN_RADIO_09_HIPHOP_OLD",
	"HIDDEN_RADIO_12_REGGAE",
	"HIDDEN_RADIO_15_MOTOWN",
	"HIDDEN_RADIO_16_SILVERLAKE",
	"HIDDEN_RADIO_STRIP_CLUB",
	"RADIO_22_DLC_BATTLE_MIX1_CLUB",
	"DLC_BATTLE_MIX1_CLUB_PRIV",
	"HIDDEN_RADIO_BIKER_CLASSIC_ROCK",
	"DLC_BATTLE_MIX2_CLUB_PRIV",
	"RADIO_23_DLC_BATTLE_MIX2_CLUB",
	"HIDDEN_RADIO_BIKER_MODERN_ROCK",
	"RADIO_25_DLC_BATTLE_MIX4_CLUB",
	"RADIO_26_DLC_BATTLE_CLUB_WARMUP",
	"DLC_BATTLE_MIX4_CLUB_PRIV",
	"HIDDEN_RADIO_BIKER_PUNK",
	"RADIO_24_DLC_BATTLE_MIX3_CLUB",
	"DLC_BATTLE_MIX3_CLUB_PRIV",
	"HIDDEN_RADIO_BIKER_HIP_HOP",
	"OFF",
};
bool g_vehicle_radio_manager_music_only = false;

// object
std::int32_t g_object_handle;
bool g_loaded_list_file_objects_did_load = false;
std::vector<std::string> g_loaded_list_file_objects;
std::int32_t g_loaded_list_file_objects_filter_count = NULL;
std::string g_loaded_list_file_objects_filter;
std::string g_object_save_map_creation;
std::int32_t g_object_cam;
bool g_do_object_spawn_preview = false;
bool g_was_object_spawn_preview_exited = false;
bool g_was_object_spawn_preview_finished = false;
bool g_object_creator_mode;
Vector3 g_object_handle_position;
Vector3 g_object_handle_cam_direction;
BOOL g_did_raycast_hit_entity;
Vector3 g_raycast_hit_entity_end;
Vector3 g_raycast_hit_entity_surface_normal;
std::int32_t g_raycast_hit_entity;
bool g_object_snap_mode;
bool g_spawn_object_snap_mode = false; 
std::int32_t g_object_snap = 0;
std::string g_object_smap_mode_text[] = { "Forward", "Backward", "Right", "Left" };
std::float_t g_object_forward_snap_mode = 0.0f, g_object_backward_snap_mode = 0.0f, g_object_right_snap_mode = 0.0f, g_object_left_snap_mode = 0.0f;
std::int32_t g_object_spam_snap_mode;
std::int32_t g_object_incrment_snap_mode = 0;
std::int32_t g_object_snap_mode_cam;
bool g_object_spawn_snap_mode_cam = false;
std::float_t g_object_snap_mode_angle_1 = 0.0f, g_object_snap_mode_angle_2 = 0.6f, g_object_snap_mode_cam_zoom = 20.0f;
bool g_object_handle_invisibility = false;
bool g_object_handle_forcefield = false;
bool g_object_handle_movement_x, g_object_handle_movement_y, g_object_handle_movement_z, g_object_handle_movement_p, g_object_handle_movement_ya, g_object_handle_movement_r;
std::float_t g_object_handle_movement_value_x, g_object_handle_movement_value_y, g_object_handle_movement_value_z, g_object_handle_movement_value_p, g_object_handle_movement_value_ya, g_object_handle_movement_value_r;

//teleport
std::int32_t g_teleport_to_position_cam = NULL;

//recovery 
std::int32_t g_recovery_rank = 0;
std::float_t g_recovery_view_reports_overall_badsport;
BOOL g_recovery_view_reports_is_badsport;
std::int32_t g_recovery_view_reports_became_badsport_num;
std::int32_t g_recovery_view_reports_char_0_badsport_bitset;
std::int32_t g_recovery_view_reports_char_1_badsport_bitset;
std::int32_t g_recovery_view_reports_char_2_badsport_bitset;
std::int32_t g_recovery_view_reports_char_0_cheat_bitset;
std::int32_t g_recovery_view_reports_char_1_cheat_bitset;
std::int32_t g_recovery_view_reports_char_2_cheat_bitset;
std::int32_t g_recovery_view_reports_griefing;
std::int32_t g_recovery_view_reports_vc_annoying_me;
std::int32_t g_recovery_view_reports_tc_annoying_me;
std::int32_t g_recovery_view_reports_offensive_language;
std::int32_t g_recovery_view_reports_offensive_ugc;
std::int32_t g_recovery_view_reports_vc_hate;
std::int32_t g_recovery_view_reports_tc_hate;
std::int32_t g_recovery_view_reports_offensive_tagplate;
std::int32_t g_recovery_view_reports_game_exploits;
std::int32_t g_recovery_view_reports_exploits;
std::int32_t g_recovery_view_reports_report_strength;
std::int32_t g_recovery_view_reports_commend_strength;
std::int32_t g_recovery_view_reports_friendly;
std::int32_t g_recovery_view_reports_helpful;
std::int32_t g_recovery_view_reports_bad_crew_name;
std::int32_t g_recovery_view_reports_bad_crew_motto;
std::int32_t g_recovery_view_reports_bad_crew_status;
std::int32_t g_recovery_view_reports_bad_crew_emblem;
bool g_recovery_rp_increaser_active = false;
std::int32_t g_recovery_rp_increaser_wanted_level = 1;
std::uint64_t g_recovery_rp_increaser_delay = 2500;
simple_timer g_recovery_rp_increaser_timer;
std::int32_t g_recovery_money_deposit = 1000;
std::int32_t g_recovery_money_withdraw = 1000;

//world
bool g_world_time_freeze;
bool g_world_time_sync;
bool g_quantum_radar_active = false;
float g_quantum_radar_fov = 350.0f;
float g_quantum_radar_scale = 0.25f;
float g_quantum_radar_pos_x = 0.15f;
float g_quantum_radar_pos_y = 0.15f;
float g_quantum_radar_inner_line_width = 0.002f;
float g_quantum_radar_outer_line_width = 0.004f;
float g_quantum_radar_center_rect_scale = 0.008f;
bool g_world_blackout;
bool g_world_bypass_restricted_zones;
std::float_t g_menu_drawable_manager_radius = 500.0f;
static CBuilding* g_menu_drawable_manager_current_closest_drawable = nullptr;

//misc
bool g_misc_global_teleport_animation = false;
bool g_misc_disable_minimap;
bool g_misc_disable_gameplay_phone;
CGameScriptHandlerNetwork* g_misc_selected_script_handler;
std::size_t g_menu_misc_hud_colour_selected_index = NULL;
std::string g_tv_playlists[] = {
	"PL_STD_CNT",
	"PL_STD_WZL",
	"PL_LO_CNT",
	"PL_LO_WZL",
	"PL_SP_WORKOUT",
	"PL_SP_INV",
	"PL_SP_INV_EXP",
	"PL_LO_RS",
	"PL_LO_RS_CUTSCENE",
	"PL_SP_PLSH1_INTRO",
	"PL_LES1_FAME_OR_SHAME",
	"PL_STD_WZL_FOS_EP2",
	"PL_MP_WEAZEL",
	"PL_MP_CCTV",
};
float g_misc_virtual_tv_x = 0.5f;
float g_misc_virtual_tv_y = 0.5f;
float g_misc_virtual_tv_width = 0.3f;
float g_misc_virtual_tv_height = 0.3f;
float g_misc_virtual_tv_rotation = 0.0f;
bool g_misc_virtual_tv_subtitles = false;
bool g_misc_virtual_tv_playlists_restart_on_change = false;
bool g_misc_virtual_tv_active = false;