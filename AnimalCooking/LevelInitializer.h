#pragma once
#include "jute.h"
#include "Resources.h"
#include <array>
#include <vector>
#include <list>
#include "Timer.h"
#include "DishPool.h"
class EntityManager;
class Entity;
class Bucket;
class ScreenLoader;
class Interactive;
class TimerViewer;

class LevelInitializer
{
public:
	LevelInitializer(EntityManager* em, int level ,ScreenLoader* sL);

private:

	void initialize_players();
	void initialize_ingredientsPool();
	void initialize_foodPool();
	void initialize_utensilPool();
	void initialize_timerViewer();
	void initialize_cookersPool();
	void initialize_shelfs();
	void initialize_sinks();
	void initialize_bin();
	void initialize_dishes();
	void initialize_gameManager();
	void initialize_foodGivers();
	void initialize_colSystem();
	void initialize_feedback();
	void initialize_levelIngredients();
	void initialize_clients();
	void initialize_walls();
	void initialize_firePool();
	void initialize_adversities();

	Entity* ingPoolEntity_;
	Entity* utensil;
	Entity* foodPool;
	Entity* gameManager;
	Entity* cookerPool;
	Entity* firesPool;
	ScreenLoader* sL;
	TimerViewer* tv_;
	DishPool* dp;
	Bucket* bucket_;
	EntityManager* emPlaystate;
	jute::jValue jsonLevel;
	jute::jValue jsonGeneral;
	std::array<Entity*, 2> players;
	std::vector<Interactive*> interactives_;

	double casillaX;
	double casillaY;
	double offsetX;
	double offsetY;
};

