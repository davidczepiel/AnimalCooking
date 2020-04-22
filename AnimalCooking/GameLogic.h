#pragma once

#include "Component.h"
#include "Utensil.h"
#include "UtensilsPool.h"
#include "IngredientsPool.h"
#include "GameControl.h"
#include "CollisionsSystem.h"

class GameLogic : public Component
{
public:
    GameLogic();
    ~GameLogic() {}

    void init() override;
    void update() override {}
    void draw() override {}
    void setIngredientPool(IngredientsPool* p) {ingPool = p;}
    void setUtensilsPool(UtensilsPool* u) { utensilPool = u; utensilPool->SetGameLogic(this); }
    void hitIngredient(SDL_Rect rect, Resources::UtensilType type);

private:
    CollisionsSystem* colSys_;
    IngredientsPool* ingPool;
    FoodPool* foodPool;
    UtensilsPool* utensilPool;
};
