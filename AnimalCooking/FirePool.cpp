#include "FirePool.h"
#include "GameLogic.h"

Fire* FirePool::activateSingleFire(SDL_Rect rect_, int id_, bool hitbox) {
	int i = 0;
	while (i < fires_.size() && fires_[i]->active) i++;

	if (i >= fires_.size()) return nullptr;

	fires_[i]->rect = rect_;
	fires_[i]->tr->setPos(Vector2D(rect_.x, rect_.y));
	fires_[i]->tr->setWH(rect_.w, rect_.h);
	fires_[i]->tr->setHitboxSize(Vector2D(rect_.w - 10, rect_.h - 10));
	fires_[i]->active = true;
	fires_[i]->id = id_;
	fires_[i]->extinguish = false;

	if (activeFires == 0) SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::burningFireSound, -1, 4);

	activeFires++;

	if (hitbox) {
		gl_->burnIngredients(fires_[i]->rect);
		cs_->addCollider(fires_[i]->tr, false);
	}

	return fires_[i];
}
