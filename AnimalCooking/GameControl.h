#pragma once

#include "Component.h"
#include "IngredientsPool.h"
#include "Food.h"
#include "FoodPool.h"

class GameControl : public Component
{
public:
    GameControl();
    ~GameControl() {}

    void init() override {}
    void update() override {}
    void newIngredient();
    void newFood(Resources::FoodType type, Vector2D pos);
private:
    IngredientsPool* ingPool_;
    FoodPool* foodPool;
};
