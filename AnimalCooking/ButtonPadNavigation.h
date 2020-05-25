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
	void AddButton(Entity* e, Entity* up, Entity* down, Entity* left, Entity* right, bool posibleFocus = false);
	void update() override;
	void onlyListenTo(int player) { playerToListen = player; }
	void resetNavigation();
private:
	struct button {
		Entity* e;
		Entity* up;
		Entity* down;
		Entity* left;
		Entity* right;
		bool posibleFocus;
	};
	void stopFocusButton(button b);
	void changeFocus(Entity* e);
	void action();
	void horizontalInput();
	void verticalInput();
	void horizontalMove(double xValue);
	void verticalMove(double yValue);
	button focus;
	bool xAxisMoved;
	bool aButtonPressed;
	vector<button> buttons;
	bool focushing;
	int playerToListen;
};

