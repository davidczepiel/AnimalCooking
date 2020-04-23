#pragma once
#include "State.h"
#include "FSM.h"
#include "PlayState.h"

class ScreenLoader : public State
{
public:
	ScreenLoader(Resources::Level nivel, AnimalCooking* ac);
	virtual ~ScreenLoader() { timers_.clear(); }
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
	//lista estática con los timers que se crean en el initializar para poder pasársela por copia a playstate
	static std::list<Timer*>timers_;
	Resources::Level level;
	Entity* barraCarga_;
	Entity* buttonGo_;
	static void goToPlayState(AnimalCooking* ac);
};
