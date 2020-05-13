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
	PlayerController(int id = 0) :Component(ecs::PlayerController),id_(id), 
		keys(SDLGame::instance()->getOptions().players_keyboardKeys[id_]),
		buttons(SDLGame::instance()->getOptions().players_gPadButtons[id_]) {}
	void init() override;
	void update() override;
private:
	struct MovementKeys {
		bool up;
		bool down;
		bool left;
		bool right;
	};
	MovementKeys movKeys;
	int id_;		//ID del mando {0,1,....n} siendo n=numero de mandos, a -1 si no hay mandos y se quiere con teclado

	config::Options::KeyboardKeys& keys;
	config::Options::GPadButtons& buttons;

	Transform* tr_ = nullptr;
	Selector* selector_ = nullptr;
	InteractionRect* ir_ = nullptr;
	Attack* attack_ = nullptr; 
	Animator* animator = nullptr;
	Transport* transport = nullptr;
	void joystickUpdate();
	bool padNotTouched();
	bool dpadArrosNotUsed();
	void keyUpdate();
	bool idle=true;
	bool ableToPress = true;
	bool dpadArrowsUsed = true;

	void setUtensilState(Animator::States u1, Animator::States u2, Animator::States u3, Animator::States u4);
	void setAnimState(Animator::States d, Animator::States u1, Animator::States u2, Animator::States u3, Animator::States u4, Animator::States s);
};
