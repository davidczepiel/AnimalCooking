#pragma once
#include "Component.h"
#include "Entity.h"
#include "GPadController.h"
#include "MenuButtonBehaviour.h"
#include "MenuButtonRenderer.h"
#include "SDL_macros.h"

class MainMenuPadNavigation :
	public Component
{
public:
	void setSelectButton(Entity* e);
	void setRightArrow(Entity* e) { rightArrow = e; }
	void setLeftArrow(Entity* e) { leftArrow = e; }

	MainMenuPadNavigation();
	void update() override;
	void changeFocus(float xValue);

private:

	Entity* leftArrow;
	Entity* rightArrow;
	Entity* selectButton;
	bool xAxisMoved;
	bool xDpadMoved;
	bool aButtonPressed;
	bool someDpadConnected;

	void arrowFocused(double xValue);
	void noArrowsFocused();
	bool dPadUsed(double* dpad);
	bool dPadNotUsed();
};

