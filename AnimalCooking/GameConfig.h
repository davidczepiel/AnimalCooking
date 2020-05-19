#pragma once
#include "SDL.h"
#include <array>

namespace config {
	//AI CLIENT
	//constexpr int AI_CLIENT_DELTA_TIME_PER_ORDER = 25;
	constexpr int AI_CLIENT_SECONDS_PER_ING = 5;

	//AI INGREDIENT
	constexpr int AI_INGREDIENT_RANGE = 3;

	constexpr int AI_INGREDIENT_MIN_TIME_WALKING = 500;
	constexpr int AI_INGREDIENT_MAX_TIME_WALKING = 2000;
	constexpr int AI_INGREDIENT_MIN_TIME_IDLE = 500;
	constexpr int AI_INGREDIENT_MAX_TIME_IDLE = 2000;
	constexpr int AI_INGREDIENT_MAX_VEL = 2;

	//ANIMATOR
	constexpr int ANIM_SPEED = 150;
	constexpr int ANIM_TIME = 20000;

	//COOKERS
	constexpr int SKILLET_SECONDS_TO_COOK = 10;
	constexpr int OVEN_SECONDS_TO_COOK = 15;
	constexpr int COOKER_ANIM_SPEED = 150;
	constexpr int COOKER_ANIM_OVERHEATED = 150;

	//DISHES
	constexpr int DISH_MAX_INGR = 5;

	//INGREDIENTS
	constexpr int ING_STARTING_DELTA_TIME = 500;
	constexpr int ING_MAX_IN_SCENE = 8;

	//PauseState
	constexpr double PAUSESTATE_BUTTON_WIDTH = 1 / 10; //Porcentaje respecto a la pantalla
	constexpr double PAUSESTATE_BUTTON_HEIGHT = 1 / 15; //Porcentaje respecto a la pantalla

	//Player 
	constexpr double PLAYER_SPEED = 5;   //Casillas por segundo
	constexpr double INTERACTION_RECT_OFFSET = 1;
	constexpr double INTERACTION_RECT_SIDELENGTH = 1;

	//Score Manager

	constexpr double SCORE_MANAGER_NOT_SERVED_PENALIZATION = -7.5;
	constexpr double SCORE_MANAGER_SERVED_BONUS = 15.0;
	//Score Viewer
	constexpr double SCOREVIEWER_BUTTON_WIDTH = 1 / 10; //Porcentaje respecto a la pantalla
	constexpr double SCOREVIEWER_BUTTON_HEIGHT = 1 / 15; //Porcentaje respecto a la pantalla

	//Orders
	constexpr double ORDERVIEWER_START_RED_OFFSET = 0.25;
	constexpr double ORDERVIEWER_MAX_RED_OFFSET = 0.75;

	//Interaction Rect
	constexpr double INTERACTION_RECT_RADIUS = 0.6;
	constexpr double INTERACTION_RECT_SIZE_X = 0.6;
	constexpr double INTERACTION_RECT_SIZE_Y = 0.6;

	//UTENSILS
	constexpr double KNIFE_RANGE = 0.8;
	constexpr double KNIFE_HITBOX_WIDTH = 0.8;
	constexpr double KNIFE_HITBOX_HEIGHT = 0.5;
	constexpr int MAX_TIME_ON_FLOOR = 20;

	constexpr double MACE_RANGE = 0.8;
	constexpr double MACE_HITBOX_WIDTH = 0.8;
	constexpr double MACE_HITBOX_HEIGHT = 0.5;

	constexpr double GRATER_RANGE = 0.8;
	constexpr double GRATER_HITBOX_WIDTH = 0.8;
	constexpr double GRATER_HITBOX_HEIGHT = 0.5;

	constexpr double NET_RANGE = 0.8;
	constexpr double NET_HITBOX_WIDTH = 0.8;
	constexpr double NET_HITBOX_HEIGHT = 0.5;

	//SINK
	constexpr int SINK_MIN_TRIES = 3;
	constexpr int SINK_MAX_TRIES = 6;
	constexpr int SINK_CADENCE = 333;

	//CREDITS
	constexpr double PIXELS_TO_MOVE = 1;

	struct Options
	{
		Options() {
			players_keyboardKeys[1].UP = SDLK_UP;
			players_keyboardKeys[1].DOWN = SDLK_DOWN;
			players_keyboardKeys[1].LEFT = SDLK_LEFT;
			players_keyboardKeys[1].RIGHT = SDLK_RIGHT;
			players_keyboardKeys[1].PICKUP = SDLK_b;
			players_keyboardKeys[1].ATTACK = SDLK_n;
			players_keyboardKeys[1].OPEN = SDLK_v;
			players_keyboardKeys[1].PREVIOUS = SDLK_c;
			players_keyboardKeys[1].NEXT = SDLK_g;
			players_keyboardKeys[1].FINISHER = SDLK_j;
		}

		struct KeyboardKeys {
			//PlayerController 1
			SDL_Keycode UP = SDLK_w;
			SDL_Keycode DOWN = SDLK_s;
			SDL_Keycode LEFT = SDLK_a;
			SDL_Keycode RIGHT = SDLK_d;
			SDL_Keycode PICKUP = SDLK_k;
			SDL_Keycode ATTACK = SDLK_p;
			SDL_Keycode OPEN = SDLK_f;
			SDL_Keycode PREVIOUS = SDLK_q;
			SDL_Keycode NEXT = SDLK_e;
			SDL_Keycode FINISHER = SDLK_r;
		};
		struct GPadButtons {
			//PlayerController 1
			SDL_GameControllerButton PICKUP = SDL_CONTROLLER_BUTTON_A;
			SDL_GameControllerButton ATTACK = SDL_CONTROLLER_BUTTON_X;
			SDL_GameControllerButton OPEN = SDL_CONTROLLER_BUTTON_B;
			SDL_GameControllerButton PREVIOUS = SDL_CONTROLLER_BUTTON_DPAD_LEFT;
			SDL_GameControllerButton NEXT = SDL_CONTROLLER_BUTTON_DPAD_RIGHT;
			SDL_GameControllerButton FINISHER = SDL_CONTROLLER_BUTTON_Y;
		};

		struct Volume {
			Uint8 music_ = 64;
			Uint8 sounds_ = 64;
		};

		std::array<KeyboardKeys, 2> players_keyboardKeys;
		std::array<GPadButtons, 2> players_gPadButtons;
		Volume volume;

		bool showKeyToPress = true;
	};
}

