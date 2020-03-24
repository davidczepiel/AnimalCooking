#include "FoodPool.h"
#include "FoodMotion.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Food.h"

FoodMotion::FoodMotion() : Component(ecs::FoodMotion)
{
	foodPool_ = nullptr;
}

void FoodMotion::update()
{
	std::vector<Food*> fp = foodPool_->getPool();

	for (auto f: fp) {
		f->update();
	}
}

void FoodMotion::init()
{
	foodPool_ = GETCMP1_(FoodPool);
}
