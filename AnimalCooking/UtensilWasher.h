#pragma once
#include "Component.h"
#include <vector>
#include "GPadController.h"
#include "Utensil.h"
using namespace std;

class UtensilWasher :public Component
{
public:
	UtensilWasher(SDL_Keycode button1, SDL_Keycode button2, SDL_Keycode button3, SDL_Keycode button4);
	void update()override;
	void setToBeWashedUtensil(Utensil* value) {
		toBeWashedUtensil = value;
	}
	virtual ~UtensilWasher() {}
private:
	int lastClean;
	int rateOfFire;
	vector<SDL_Keycode>keys;
	Utensil* toBeWashedUtensil;

};

