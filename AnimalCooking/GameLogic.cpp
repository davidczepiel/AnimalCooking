#include "GameLogic.h"
#include "Ingredient.h"
#include "FoodDictionary.h"

GameLogic::GameLogic() : Component(ecs::GameLogic)
{
}

void GameLogic::hitIngredient(SDL_Rect rect, Resources::UtensilType type)
{
    bool hit = false;
    for (Ingredient* ing : ingPool->getPool()) { //colision temporal

        if (Collisions::collides(Vector2D(rect.x, rect.y), rect.w, rect.h, ing->getPos(), ing->getWidth(), ing->getHeight())) {
            hit = true;
            Vector2D ingPos = ing->getPos();
            Resources::IngredientType ingType = ing->getType();
            ing->destroy(type);  
            Food* f = FoodDictionary::instance()->getResult(type, { (int)ingType });
            GETCMP1_(GameControl)->newFood(f, ingPos);
            break;
        }
    }
    if (hit) {
        switch (type) {
        case Resources::UtensilType::Knife:
            SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::KnifeAttack, 0);
            break;
        case Resources::UtensilType::Mace:
            SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::MaceAttack, 0);
            break;
        case Resources::UtensilType::Grater:
            SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::KnifeAttack, 0);
            break;
        case Resources::UtensilType::Net:
            SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::KnifeAttack, 0);
            break;
        }
    }
    else
        SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::AttackMiss, 0);

}
