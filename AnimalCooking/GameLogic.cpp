#include "GameLogic.h"
#include "Ingredient.h"
#include "FoodDictionary.h"

GameLogic::GameLogic() : Component(ecs::GameLogic)
{
}

void GameLogic::hitIngredient(SDL_Rect rect, Resources::UtensilType type)
{
    for (Ingredient* ing : ingPool->getPool()) { //colision temporal

        if (Collisions::collides(Vector2D(rect.x, rect.y), rect.w, rect.h, ing->getPos(), ing->getWidth(), ing->getHeight())) {

            Vector2D ingPos = ing->getPos();
            Resources::IngredientType ingType = ing->getType();
            ing->destroy(type);  
            Food* f = FoodDictionary::instance()->getResult(type, { (int)ingType });
            GETCMP1_(GameControl)->newFood(f, ingPos);

            //GETCMP1_(GameControl)->newIngredient();

            break;
        }
    }
}
