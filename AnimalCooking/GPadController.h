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
	void update(SDL_Event& event);

	inline bool joysticksInitialised() const{
		return m_bJoysticksInitialised;
	}
	//-joy = ID del joystick que queremos usar
	// buttonNumber 
	//https://wiki.libsdl.org/SDL_GameControllerButton?highlight=%28%5CbCategoryGameController%5Cb%29%7C%28CategoryEnum%29
	inline bool getButtonState(int joy, int buttonNumber)
	{
		return m_buttonStates[joy][buttonNumber];
	}

	double xvalue(int joy, int stick);
	double yvalue(int joy, int stick);

private:
	static unique_ptr<GPadController> instance_;
	void ControllerButtonDown(SDL_Event& event);
	void ControllerButtonUp(SDL_Event& event);
	GPadController();
	void initialiseJoysticks();
	void clean();

	//--------------Variables-------------------------
	//Jostick
	const int m_joystickDeadZone = 10000;
	vector<SDL_Joystick*> m_joysticks;
	vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;	//contiene los controladores con axis multiples(uno para cada stick)
	bool m_bJoysticksInitialised;

	//Botones
	vector<std::vector<bool>> m_buttonStates;




};

