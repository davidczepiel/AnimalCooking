#pragma once
#include <vector>
#include <SDL_joystick.h>
#include "Vector2D.h"
#include "Timer.h"
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
	void sleepController(int player, int time);
	const bool& isAnyButtonJustPressed() { return lastButtonPressed_.first; }
	const SDL_GameControllerButton& buttonJustPressed() { return lastButtonPressed_.second; }
	void sleep(double time);

	void setIsAnyButtonJustPressed() { lastButtonPressed_.first = false; }

	void update(SDL_Event& event);

	SDL_GameController* player1_;
	SDL_GameController* player2_;
private:
	GPadController();

	//--------------Variables-------------------------
	//Jostick
	static unique_ptr<GPadController> instance_;
	std::pair<bool, SDL_GameControllerButton> lastButtonPressed_;
	bool lastButtonIsBeingPressed = false;
	static const int m_joystickDeadZone = 10000;
	Timer* sleepTimerP1;
	Timer* sleepTimerP2;
};

