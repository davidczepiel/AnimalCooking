#pragma once
#include "Component.h"
#include "IngredientsPool.h"
#include "Food.h"
#include "UtensilsPool.h"
#include "GameLogic.h"
#include "FoodPool.h"
#include "jute.h"
#include "Timer.h"
#include "CollisionsSystem.h"
#define GETTRANSFORM(pl) pl->getPlayerTransform()
class GameControl : public Component
{
public:
	GameControl(Transport* p1, Transport* p2, UtensilsPool* u, FoodPool* fp, IngredientsPool* ip, int levelMaxIngredients);
	~GameControl() {}

	void init() override;
	void update() override;
	void newIngredient();
	//void newIngredient(Resources::IngredientType ing);
	Food* newFood(Resources::FoodType type, Vector2D pos);
	void newFood(Food* f, Vector2D pos);

	vector<Resources::IngredientType>& getLevelIngType() { return levelIngType; }

	inline void setIngs(const vector<Resources::IngredientType>& ings) { levelIngType = ings; }

	inline Timer* getAdversityTime() { return &adversityTimer; }

private:
	void makeIngredient(Ingredient* ing);

	CollisionsSystem* colSys_;
	Ingredient* newIngType(const Resources::IngredientType& iT);
	Resources::IngredientType chooseIng();
	IngredientsPool* ingPool_;
	FoodPool* foodPool;
	UtensilsPool* utensilsPool;
	Transport* tP1;
	Transport* tP2;
	vector<Resources::IngredientType> levelIngType;
	FoodTimer timer;
	Timer adversityTimer;	

	list<Uint32> ingToMake_;

	int maxIngr;
	int casillaLength;
	int indexType;
	bool justStarted;
};
