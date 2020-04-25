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
	MainMenuPadNavigation();
	void update() override;
	void changeFocus(float xValue);
	void setSelectButton(Entity* e);
	void setRightArrow(Entity* e) { rightArrow = e;}
	void setLeftArrow(Entity* e) { leftArrow = e;}
private:
	void arrowFocused(double xValue);
	void noArrowsFocused();
	Entity* leftArrow;
	Entity* rightArrow;
	Entity* selectButton;
	bool xAxisMoved;
	bool aButtonPressed;

};

