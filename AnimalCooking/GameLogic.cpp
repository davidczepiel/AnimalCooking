#include "GameLogic.h"
#include "Ingredient.h"
#include "FoodDictionary.h"

GameLogic::GameLogic(TimerViewer* tv) : Component(ecs::GameLogic), ingPool(nullptr), utensilPool(nullptr),
foodPool(nullptr), levelTimer_(new LevelTimer())
{
    tv->addTimer(levelTimer_);
}

void GameLogic::init()
{
    colSys_ = GETCMP1_(CollisionsSystem);
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

        if (Collisions::collides(Vector2D(rect.x, rect.y), rect.w, rect.h, ing->getPos(), ing->getWidth(), ing->getHeight())) {

            Vector2D ingPos = ing->getPos();
            Resources::IngredientType ingType = ing->getType();
            colSys_->removeCollider(ing);
            ing->destroy(type);  
            Food* f = FoodDictionary::instance()->getResult(type, { (int)ingType }, false);
            GETCMP1_(GameControl)->newFood(f, ingPos);

            //GETCMP1_(GameControl)->newIngredient();

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

void GameLogic::setLevelTimer(Uint32 time, Vector2D pos, Vector2D size)
{
    levelTimer_->setTime(time); 
    levelTimer_->setPos(pos);
    levelTimer_->setSize(size);
}
