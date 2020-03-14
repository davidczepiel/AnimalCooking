#pragma once
#include "Component.h"
#include <vector>
#include "GPadController.h"
#include "Utensil.h"
#include "SDL_macros.h"
#include "Entity.h"
#include "Transport.h"
using namespace std;

class UtensilWasher :public Component, public Interactive
{
public:
	UtensilWasher(SDL_Keycode button, Transport* p1, Transport* p2);
	void update() override ;
	void draw() override ;
	void init() override;
	virtual ~UtensilWasher() {}
	virtual void interactive(int player);
private:
	int lastClean;
	int cadence;
	SDL_Keycode button;
	Texture* text;


};

