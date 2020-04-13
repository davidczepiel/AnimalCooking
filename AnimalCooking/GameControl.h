#pragma once

#include "Component.h"
#include "IngredientsPool.h"
#include "Food.h"
#include "UtensilsPool.h"
#include "GameLogic.h"
#include "FoodPool.h"

class GameControl : public Component
{
public:
    GameControl(Transport* p1, Transport* p2,UtensilsPool* u, FoodPool* fp);
    ~GameControl() {}

    void init() override {}
    void update() override {}
    void newIngredient();
    Food* newFood(Resources::FoodType type, Vector2D pos);
    void newFood(Food* f, Vector2D pos);
private:
    Ingredient* newIngType();
    IngredientsPool* ingPool_;
    FoodPool* foodPool;
    UtensilsPool* utensilsPool;
    Transport* tP1;
    Transport* tP2;
};
