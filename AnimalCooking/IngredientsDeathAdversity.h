#pragma once
#include "Adversity.h"
#include "Texture.h"
#include "SDLGame.h"
#include "IngredientsPool.h"
#include "SDL_macros.h"
#include "Ingredient.h"
#include "Timer.h"
#include "GameLogic.h"
#include "TimerViewer.h"

class MultipleAdversityManager;

class IngredientsDeathAdversity :
	public Adversity
{
public:
	IngredientsDeathAdversity(MultipleAdversityManager* mAdvMng);
	~IngredientsDeathAdversity() {};
	virtual void update() ;
	virtual void draw() ;
	virtual void reset();
	void start();
private:

	struct Ingredientinfo {
		Ingredient* ing=nullptr;
		Timer* animationTimer;
		int row;
		int col;
		bool dead;
		bool end;
		Vector2D pos;
	};

	void killIngredients();
	void killIngredient();
	void inspectIngredients();
	void getPosIngredient(int i);
	int getNumber();
	bool allCompleted();
	void startIngredient(int i);
	bool alreadyTaken(int i);
	Texture* deathTexture;
	Timer* deathTimer;
	SDL_Rect dest;
	SDL_Rect src;
	double timePostDeath;
	double numKills;
	double animationSpeed;
	int killsDone;
	int killsStarted;
	double percentagePerKill;
	vector<Ingredientinfo> ingInfo;
	vector<Ingredient*> ingredients;
	GameLogic* gl;
	
	
};

