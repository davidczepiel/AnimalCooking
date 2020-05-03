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
#include "Animator.h"
#include "Transport.h"

class PlayerController : public Component {
public:
	PlayerController(int id = 0) :Component(ecs::PlayerController),id_(id) {} 
	void init() override;
	void update() override;
private:
	struct Keys{
		SDL_Keycode up;
		SDL_Keycode down;
		SDL_Keycode left;
		SDL_Keycode right;

		SDL_Keycode pickUp;
		SDL_Keycode attack;
		SDL_Keycode open;
		SDL_Keycode next;
		SDL_Keycode back;
		SDL_Keycode finish;
	};
	Keys keys;
	int id_;		//ID del mando {0,1,....n} siendo n=numero de mandos, a -1 si no hay mandos y se quiere con teclado

	Transform* tr_ = nullptr;
	Selector* selector_ = nullptr;
	InteractionRect* ir_ = nullptr;
	Attack* attack_ = nullptr; 
	Animator* animator = nullptr;
	Transport* transport = nullptr;

	void joystickUpdate();
	void keyUpdate();
	bool idle=true;

	void updateKeys(int id);

	void setUtensilState(Animator::States u1, Animator::States u2, Animator::States u3, Animator::States u4);
	void setAnimState(Animator::States d, Animator::States u1, Animator::States u2, Animator::States u3, Animator::States u4, Animator::States s);
};
