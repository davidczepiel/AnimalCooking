#include "GameLogic.h"
#include "Ingredient.h"

GameLogic::GameLogic() : Component(ecs::GameLogic)
{
}

void GameLogic::hitIngredient(SDL_Rect rect, Resources::UtensilType type)
{
    for (Ingredient* ing : ingPool->getPool()) { //colision temporal

        if (Collisions::collides(Vector2D(rect.x, rect.y), rect.w, rect.h, ing->getPos(), ing->getWidth(), ing->getHeight())) {
            Vector2D ingPos = ing->getPos();
            Resources::FoodType result = ing->destroy(type);
            GETCMP1_(GameControl)->newFood(result, ingPos);
            //GETCMP1_(GameControl)->newIngredient();
        }
    }
}
