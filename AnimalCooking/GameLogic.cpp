#include "GameLogic.h"
#include "Ingredient.h"
#include "FoodDictionary.h"

GameLogic::GameLogic() : Component(ecs::GameLogic)
{
}

void GameLogic::hitIngredient(SDL_Rect rect, Resources::UtensilType type)
{
	bool hit = false;
	for (Ingredient* ing : ingPool->getPool()) { 
		//Si le doy a algo genero su resultado y reproduzco el sonido adecuado 
		if (Collisions::collides(Vector2D(rect.x, rect.y), rect.w, rect.h, ing->getPos(), ing->getWidth(), ing->getHeight())) {
			hit = true;
			Vector2D ingPos = ing->getPos();
			Resources::IngredientType ingType = ing->getType();
			ing->destroy(type);
			Food* f = FoodDictionary::instance()->getResult(type, { (int)ingType });
			GETCMP1_(GameControl)->newFood(f, ingPos);
			playHit(type); 
			break;
		}
	}
	//Si no he dado a nada le doy al sonido por defecto
	if(!hit)
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::AttackMiss, 0);

}

void GameLogic::playHit(Resources::UtensilType type) {
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
