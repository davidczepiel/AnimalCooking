#pragma once

#include "Component.h"
#include "IngredientsPool.h"
#include "Food.h"
#include "FoodPool.h"

class GameControl : public Component
{
public:
    GameControl(Transport* p1, Transport* p2);
    ~GameControl() {}

    void init() override {}
    void update() override {}
    void newIngredient();
    void newFood(Resources::FoodType type, Vector2D pos);
private:
    Ingredient* newIngType();
    IngredientsPool* ingPool_;
    FoodPool* foodPool;
    Transport* tP1;
    Transport* tP2;
};
