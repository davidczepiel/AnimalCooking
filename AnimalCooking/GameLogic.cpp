#include "GameLogic.h"
#include "Ingredient.h"
#include "FoodDictionary.h"

GameLogic::GameLogic(TimerViewer* tv) : 
	Component(ecs::GameLogic), 
	ingPool(nullptr), 
	utensilPool(nullptr),
	foodPool(nullptr), 
	colSys_(nullptr),
	firePool_(nullptr),
	levelTimer_(new LevelTimer()), 
	tv(tv)
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
			colSys_->removeCollider(ing);
			ing->destroy();
			Food* f = FoodDictionary::instance()->getResult(type, { (int)ingType }, false);
			GETCMP1_(GameControl)->newFood(f, ingPos);
			playHit(type);
			break;
		}
	}
	//Si no he dado a nada le doy al sonido por defecto
	if (!hit)
		SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::AttackMiss, 0);
}

void GameLogic::burnIngredients(SDL_Rect rect)
{
	for (Ingredient* ing : ingPool->getPool()) {
		//Si le doy a algo genero su resultado y reproduzco el sonido adecuado 
		if (Collisions::collides(Vector2D(rect.x, rect.y), rect.w, rect.h, ing->getPos(), ing->getWidth(), ing->getHeight())) {
			Resources::IngredientType ingType = ing->getType();
			colSys_->removeCollider(ing);
			ing->destroy();
			GETCMP1_(GameControl)->newIngredient(ingType);
		}
	}
}

void GameLogic::hitFire(SDL_Rect rect)
{
	for (Fire* fire : firePool_->getPool()) {
		if (fire->active && Collisions::collides(Vector2D(rect.x, rect.y), rect.w, rect.h, Vector2D(fire->rect.x, fire->rect.y), fire->rect.w, fire->rect.h)) {
			firePool_->desactivateFire(fire->id);
			//playHit(type);    <--SONIDO CUBO AGUA
			break;
		}
	}
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

void GameLogic::setLevelTimer(Uint32 time, Vector2D pos, Vector2D size)
{
	levelTimer_->setTime(time);
	levelTimer_->setPos(pos);
	levelTimer_->setSize(size);
}
