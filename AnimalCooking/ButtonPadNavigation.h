#pragma once
#include "Component.h"
#include "Entity.h"
#include "GPadController.h"
#include "ButtonBehaviour.h"
#include "ButtonRenderer.h"
#include "SDL_macros.h"
class ButtonPadNavigation :
	public Component
{
public:
	ButtonPadNavigation();
	void AddButton(Entity* e,Entity* up, Entity* down, Entity* left, Entity* right);
	void update() override;
private:
	void changeFocus(Entity* e);
	void action();
	void horizontalMove(double xValue);
	void verticalMove(double yValue);
	struct button {
		Entity* e;
		Entity* up;
		Entity* down;
		Entity* left;
		Entity* right;
	};
	button focus;
	bool xAxisMoved;
	bool aButtonPressed;
	vector<button> buttons;

};

