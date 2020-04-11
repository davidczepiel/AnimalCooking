#pragma once
#include "State.h"
#include "FSM.h"
#include "PlayState.h"
class ScreenLoader : public State
{
public:	
	ScreenLoader(Resources::Level nivel);
	void resetResources(Resources::Level nivel); // Resources::Nivel nivel: es un enum que indica que recursos cargar en memoria
private:
	void loadTextures(Resources::Level level, SDL_Renderer* renderer_);
	void loadFonts(Resources::Level level);
	void loadMessagges(Resources::Level level, SDL_Renderer* renderer_);
	void loadSounds(Resources::Level level);
	void loadMusics(Resources::Level level);
	void updateLength(double extra);
	Entity* barraCarga_;
	Entity* buttonGo_;
	static void goToPlayState();
};

