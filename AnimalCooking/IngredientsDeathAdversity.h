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

	void killIngredients();
	void getPosIngredient(int i);
	int getNumber();
	bool alreadyTaken(int i);
	Texture* mTexture;
	Timer* deathTimer;
	SDL_Rect dest;
	SDL_Rect src;
	double timeToDeath;
	double timePostDeath;
	vector<Ingredient*> ingredients;
	vector<int> indexIngredients;
	IngredientsPool* ingPool;
	
};

