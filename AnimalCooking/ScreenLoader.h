#pragma once
#include "State.h"
#include "FSM.h"
#include "PlayState.h"

class ScreenLoader : public State
{
public:
	ScreenLoader(int nivel, AnimalCooking* ac);
	void resetResources(); // Resources::Nivel nivel: es un enum que indica que recursos cargar en memoria
	void updateLength();
	EntityManager* getEntityManager() { return emPlaystate; }
private:

	void loadTextures(SDL_Renderer* renderer_);
	void loadFonts();
	void loadMessagges(SDL_Renderer* renderer_);
	void loadSounds();
	void loadMusics();

	void initialize();

	EntityManager* emPlaystate;

	int level;
	Entity* barraCarga_;
	Entity* buttonGo_;
	Entity* padNavigation_;
	static void goToPlayState(AnimalCooking* ac);
};
