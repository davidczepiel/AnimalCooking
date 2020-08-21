#include "WallOpacityManager.h"
#include "Entity.h"
#include "Ingredient.h"

void WallOpacityManager::init()
{
	renderer_ = GETCMP1_(SDLRenderer);
	tr_ = GETCMP1_(Transform);
}

void WallOpacityManager::update()
{
	if (ingPool_) {
		for (auto& ing : ingPool_->getPool()) {
			if (ing->getPos().getY() + ing->getHeight() / 1.5 > tr_->getPos().getY()) {
				renderer_->setOpacity(100);
				return; //Parar si 1 cumple la condicion
			}
		}
	}
}
