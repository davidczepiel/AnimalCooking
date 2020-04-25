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

    void init() override {}
    virtual void update() override { levelTimer_->update(); }
    virtual void draw() override { levelTimer_->draw(); }
    void setIngredientPool(IngredientsPool* p) {ingPool = p;}
    void setUtensilsPool(UtensilsPool* u) { utensilPool = u; utensilPool->SetGameLogic(this); }
    void hitIngredient(SDL_Rect rect, Resources::UtensilType type);
    void setLevelTimer(Uint32 time, Vector2D pos, Vector2D size);

private:
    CollisionsSystem* colSys_;
    IngredientsPool* ingPool;
    FoodPool* foodPool;
    UtensilsPool* utensilPool;
    LevelTimer* levelTimer_;
};
