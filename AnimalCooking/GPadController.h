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

	virtual ~GPadController(){}

	static GPadController* instance() {
		if (instance_.get() == nullptr) {
			instance_.reset(new GPadController());
		}
		return instance_.get();
	}

	static bool playerDPAD(int id);
	static double getAxisX(int player, int axis);
	static double getAxisY(int player, int axis);
	static bool playerPressed(int player, SDL_GameControllerButton button);
	


	//-joy = ID del joystick que queremos usar
	// buttonNumber 
	//https://wiki.libsdl.org/SDL_GameControllerButton?highlight=%28%5CbCategoryGameController%5Cb%29%7C%28CategoryEnum%29
	inline bool getButtonState(int joy, int buttonNumber)
	{
		return m_buttonStates[joy][buttonNumber];
	}

	
	static SDL_GameController* player1_;
	static SDL_GameController* player2_;

private:
	static unique_ptr<GPadController> instance_;

	void ControllerButtonDown(SDL_Event& event);
	void ControllerButtonUp(SDL_Event& event);
	GPadController();
	void clean();

	//--------------Variables-------------------------
	//Jostick
	static const int m_joystickDeadZone = 10000;

	//Botones
	vector<std::vector<bool>> m_buttonStates;




};

