#pragma once
#include "Component.h"
#include <vector>
#include "GPadController.h"
#include "Utensil.h"
#include "SDL_macros.h"
using namespace std;

class UtensilWasher :public Component
{
public:
	UtensilWasher(SDL_Keycode button);
	void update()override;
	void draw()override;
	void setToBeWashedUtensil(Utensil* value) {
		toBeWashedUtensil = value;
	}
	virtual ~UtensilWasher() {}
private:
	int lastClean;
	int cadence;
	SDL_Keycode button;
	Utensil* toBeWashedUtensil;

};

