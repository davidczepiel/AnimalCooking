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

class GameControl : public Component
{
public:
    GameControl(Transport* p1, Transport* p2,UtensilsPool* u, FoodPool* fp,IngredientsPool* ip, int casilla);
    ~GameControl() {}

    void init() override;
	void update() override;
    void newIngredient();
    Food* newFood(Resources::FoodType type, Vector2D pos);
    void newFood(Food* f, Vector2D pos);
	vector<Resources::IngredientType>& getLevelIngType() { return levelIngType; }

private:
    CollisionsSystem* colSys_;
    Ingredient* newIngType(const Resources::IngredientType& iT);
    Resources::IngredientType chooseIng();
    IngredientsPool* ingPool_;
    FoodPool* foodPool;
    UtensilsPool* utensilsPool;
    Transport* tP1;
    Transport* tP2;
	jute::jValue jsonGeneral;
	Timer timer;
	int casillaLength;
	vector<Resources::IngredientType> levelIngType;
    bool justStarted;
    int maxIngr;
};
