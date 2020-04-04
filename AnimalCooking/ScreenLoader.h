#pragma once
#include "State.h"
#include "FSM.h"
#include "PlayState.h"

class ScreenLoader : public State
{
public:	
	ScreenLoader(Resources::Level nivel);
	void resetResources(); // Resources::Nivel nivel: es un enum que indica que recursos cargar en memoria

private:
	void loadTextures(SDL_Renderer* renderer_);
	void loadFonts();
	void loadMessagges(SDL_Renderer* renderer_);
	void loadSounds();
	void loadMusics();
	void updateLength(double extra);

	void initialize();	

	EntityManager* emPlaystate;

	Resources::Level level;
	Entity* barraCarga_;
	Entity* buttonGo_;
	static void goToPlayState();
};
