#include "GameLogic.h"
#include "Ingredient.h"
#include "FoodDictionary.h"

GameLogic::GameLogic(TimerViewer* tv) : Component(ecs::GameLogic), ingPool(nullptr), utensilPool(nullptr),
foodPool(nullptr), levelTimer_(new LevelTimer()), tv(tv)
{
    tv->addTimer(levelTimer_);
}

void GameLogic::init()
{
    colSys_ = GETCMP1_(CollisionsSystem);

}

void GameLogic::hitIngredient(SDL_Rect rect, Resources::UtensilType type)
{
    for (Ingredient* ing : ingPool->getPool()) { //colision temporal

        if (Collisions::collides(Vector2D(rect.x, rect.y), rect.w, rect.h, ing->getPos(), ing->getWidth(), ing->getHeight())) {

            Vector2D ingPos = ing->getPos();
            Resources::IngredientType ingType = ing->getType();
            colSys_->removeCollider(ing);
            ing->destroy(type);  
            Food* f = FoodDictionary::instance()->getResult(type, { (int)ingType }, false);
            GETCMP1_(GameControl)->newFood(f, ingPos);

            //GETCMP1_(GameControl)->newIngredient();

            break;
        }
    }
}

void GameLogic::setLevelTimer(Uint32 time, Vector2D pos, Vector2D size)
{
    levelTimer_->setTime(time); 
    levelTimer_->setPos(pos);
    levelTimer_->setSize(size);
}
