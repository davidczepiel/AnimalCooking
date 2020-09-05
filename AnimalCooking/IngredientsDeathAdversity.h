#pragma once
#include "Adversity.h"
#include "Texture.h"
#include "SDLGame.h"
#include "IngredientsPool.h"
#include "SDL_macros.h"
#include "Ingredient.h"
#include "Timer.h"
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
		double timeToStart=0;
		double timeToFinish=0;
	};

	void killIngredients();
	void killIngredient();
	void getPosIngredient(int i);
	int getNumber();
	bool alreadyTaken(int i);
	Texture* mTexture;
	Timer* deathTimer;
	SDL_Rect dest;
	SDL_Rect src;
	double timeToDeath;
	double timePostDeath;
	int numKills;
	//int killsDone;
	//double percentagePerKill;
	vector<Ingredientinfo> ingInfo;
	vector<Ingredient*> ingredients;
	vector<int> indexIngredients;
	
	
};

