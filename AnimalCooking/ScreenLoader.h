#pragma once
#include "State.h"
#include "FSM.h"
#include "PlayState.h"
#include "jute.h"
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

	void initialize_players();
	void players_addComponents(Entity* entity);
	void players_initializeTransform(size_t player);
	void players_initializeExtraComponents();

	void initialize_ingredientsPool();

	void initializeComponent(const string& component, Entity* entity);

	EntityManager* emPlaystate;

	jute::jValue jsonLevel; // json con la informacion del nivel (pos, componentes extras particulares, etc...)
	jute::jValue jsonGeneral; // json con las caracteristicas de los actores (size, velocidad, componentes genericos, etc...)

	std::array<Entity*, 2> players {};
	Entity* ingPoolEntity_;

	Resources::Level level;
	Entity* barraCarga_;
	Entity* buttonGo_;
	static void goToPlayState();
};
