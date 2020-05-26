#pragma once
#include <vector>
#include <SDL_joystick.h>
#include "Vector2D.h"
#include <SDL.h>
using namespace std;

class GPadController {
public:
	GPadController(GPadController&) = delete;
	GPadController& operator=(GPadController&) = delete;

	virtual ~GPadController() {}

	static GPadController* instance() {
		if (instance_.get() == nullptr) {
			instance_.reset(new GPadController());
		}
		return instance_.get();
	}

	void getPlayerGPADS();
	bool playerControllerConnected(int id);
	double getAxis(int player, SDL_GameControllerAxis axis);
	bool playerPressed(int player, SDL_GameControllerButton button);
	SDL_GameController* player1_;
	SDL_GameController* player2_;

	void update(SDL_Event& event);

	void setIsAnyButtonJustPressed() { lastButtonPressed_.first = false; }
	const bool& isAnyButtonJustPressed() { return lastButtonPressed_.first; }
	const SDL_GameControllerButton& buttonJustPressed() { return lastButtonPressed_.second; }

private:
	static unique_ptr<GPadController> instance_;

	GPadController();
	//--------------Variables-------------------------
	//Jostick
	std::pair<bool, SDL_GameControllerButton> lastButtonPressed_;
	bool lastButtonIsBeingPressed = false;
	static const int m_joystickDeadZone = 10000;
};

