#include "GPadController.h"
#include <SDL.h>

unique_ptr<GPadController> GPadController::instance_;
SDL_GameController* GPadController::player1_ = nullptr;
SDL_GameController* GPadController::player2_ = nullptr;

GPadController::GPadController()
{
	initialiseJoysticks();
}

void GPadController::getPlayer(int id) {
	if (id == 0) {
		SDL_GameController* g = SDL_GameControllerOpen(0);
		player1_ = g;
	}
	else {
		SDL_GameController* g = SDL_GameControllerOpen(1);
		player2_ = g;
	}
}

//Inicialilamos el GamePad. Para ello encontramos el numero de 
//joysticks al que SDL tiene acceso y los inicializamos.
void GPadController::initialiseJoysticks()
{
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)    //Inicialimamos con un subsistema
	{
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);   //Si no se inicializa usamos esta llamada para inicializarlo
	}
	if (SDL_NumJoysticks() > 0)
	{
		//Para casa joystick usable, lo abrimos y metemos en el vector
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_Joystick* joy = SDL_JoystickOpen(i);

			if (SDL_JoystickOpen(i))
			{
				m_joysticks.push_back(joy);
				m_joystickValues.push_back(std::make_pair(new Vector2D(0, 0), new Vector2D(0, 0))); //Añadimos un nuevo par de stick
				vector<bool> tempButtons;
				for (int j = 0; j < SDL_JoystickNumButtons(joy); j++)
				{
					tempButtons.push_back(false);
				}
				m_buttonStates.push_back(tempButtons);
			}
		}
		//Le decimos a SDL que empiece a "escuchar" a los eventos de tipo joystick
		SDL_JoystickEventState(SDL_ENABLE);
		m_bJoysticksInitialised = true;
	}
	else
	{
		m_bJoysticksInitialised = false;
	}
}

//Desinicializamos los joysticks
void GPadController::clean()
{
	if (m_bJoysticksInitialised)
	{
		for (unsigned int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_JoystickClose(m_joysticks[i]);
		}
	}
}
//-joy = ID del joystick que queremos usar
//-stick = 1(para stick izquierdo) 2(para stick dcho)
double GPadController::xvalue(int joy, int stick)
{
	if (m_joystickValues.size() > 0)
	{
		if (stick == 1)
		{
			return m_joystickValues[joy].first->getX();
		}
		else if (stick == 2)
		{
			return m_joystickValues[joy].second->getX();
		}
	}
	return 0;
}

//-joy = ID del joystick que queremos usar
//-stick = 1(para stick izquierdo) 2(para stick dcho)
double GPadController::yvalue(int joy, int stick)
{
	if (m_joystickValues.size() > 0)
	{
		if (stick == 1)
		{
			return m_joystickValues[joy].first->getY();
		}
		else if (stick == 2)
		{
			return m_joystickValues[joy].second->getY();
		}
	}
	return 0;
}
void GPadController::update(SDL_Event& event)
{
	if (event.type == SDL_JOYAXISMOTION)
	{
		int whichOne = event.jaxis.which;
		// left stick move left or right
		if (event.jaxis.axis == 0)
		{
			if (event.jaxis.value > m_joystickDeadZone || event.jaxis.value < -m_joystickDeadZone)
			{
				m_joystickValues[whichOne].first->setX(event.jaxis.value / 32678.0);
							}
			else
			{
				m_joystickValues[whichOne].first->setX(0);
			}

		}
		// left stick move up or down
		if (event.jaxis.axis == 1)
		{
			if (event.jaxis.value > m_joystickDeadZone || event.jaxis.value < -m_joystickDeadZone)
			{
				m_joystickValues[whichOne].first->setY(event.jaxis.value / 32678.0);
				SDL_GameController* g = SDL_GameControllerOpen(1);
				cout << SDL_GameControllerGetAxis(g, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) << endl;
				g = SDL_GameControllerOpen(0);
				cout << SDL_GameControllerGetAxis(g, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) << endl;

			}
			else
			{
				m_joystickValues[whichOne].first->setY(0);
			}
		}
	}

	else if (event.type == SDL_JOYBUTTONDOWN)
		ControllerButtonDown(event);
	else if (event.type == SDL_JOYBUTTONUP)
		ControllerButtonUp(event);
}

double ::GPadController::getAxisX(int player, int axis) {
	SDL_GameController* p;
	if (player == 0)
		p = player1_;
	else
		p = player2_;
	double value = SDL_GameControllerGetAxis(p, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX);

	if (abs(value) < m_joystickDeadZone) return (0);
	else return (value/32678);
}

double ::GPadController::getAxisY(int player, int axis) {
	SDL_GameController* p;
	if (player == 0)
		p = player1_;
	else
		p = player2_;
	double value = SDL_GameControllerGetAxis(p, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY);
	if (abs(value) < m_joystickDeadZone) return (0);
	else 
		return (value / 32678);
}

bool GPadController::playerPressed(int id, SDL_GameControllerButton button) {
	SDL_GameController* c;
	if (id == 0)c = player1_;
	else c = player2_;
	return SDL_GameControllerGetButton(c, button);
}


void GPadController::ControllerButtonDown(SDL_Event& event) {
	int whichOne = event.jaxis.which;
	switch (event.cbutton.button) {
	case SDL_CONTROLLER_BUTTON_A:
		m_buttonStates[whichOne].at(SDL_CONTROLLER_BUTTON_A) = true;
		break;
	case SDL_CONTROLLER_BUTTON_B:
		m_buttonStates[whichOne].at(SDL_CONTROLLER_BUTTON_B) = true;
		break;
	case SDL_CONTROLLER_BUTTON_X:
		m_buttonStates[whichOne].at(SDL_CONTROLLER_BUTTON_X) = true;
		break;
	case SDL_CONTROLLER_BUTTON_Y:
		m_buttonStates[whichOne].at(SDL_CONTROLLER_BUTTON_Y) = true;
		break;

	}

}

void GPadController::ControllerButtonUp(SDL_Event& event) {
	int whichOne = event.jaxis.which;
	switch (event.cbutton.button) {
	case SDL_CONTROLLER_BUTTON_A:
		m_buttonStates[whichOne].at(SDL_CONTROLLER_BUTTON_A) = false;
		break;
	case SDL_CONTROLLER_BUTTON_B:
		m_buttonStates[whichOne].at(SDL_CONTROLLER_BUTTON_B) = false;
		break;
	case SDL_CONTROLLER_BUTTON_X:
		m_buttonStates[whichOne].at(SDL_CONTROLLER_BUTTON_X) = false;
		break;
	case SDL_CONTROLLER_BUTTON_Y:
		m_buttonStates[whichOne].at(SDL_CONTROLLER_BUTTON_Y) = false;
		break;

	}
}