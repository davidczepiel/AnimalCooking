#pragma once
#include "SDL.h"
#include "Component.h"
#include "Transform.h"
#include "Attack.h"
#include "Entity.h"
#include "GPadController.h"
#include "KeyBoardController.h"
#include "InteractionRect.h"
#include "Selector.h"


class PlayerController : public Component {
public:
	PlayerController(int id = 0) :Component(ecs::PlayerController), id_(id) {} 
	void init() override;
	void update() override;
private:
	struct Keys{
		SDL_Keycode up;
		SDL_Keycode down;
		SDL_Keycode left;
		SDL_Keycode right;

		/*SDL_Keycode button1;
		SDL_Keycode button2;
		SDL_Keycode button3;*/
	};
	Keys keys;
	int id_;		//ID del mando {0,1,....n} siendo n=numero de mandos, a -1 si no hay mandos y se quiere con teclado

	Transform* tr_ = nullptr;
	Selector* selector_ = nullptr;
	InteractionRect* ir_ = nullptr;
	Attack* attack_ = nullptr; 

	void joystickUpdate();
	void keyUpdate();
	
};
