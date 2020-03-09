#include "Food.h"
#include "SDL_macros.h"

Food::Food(Vector2D position)
{
	position_ = position;

	foodPool_ = nullptr;
	dir_ = Vector2D();
}

void Food::setFoodPool(FoodPool* foodPool)
{
	foodPool_ = foodPool;
	iterator_ = --foodPool->getPool()->end();
}

void Food::Destroy()
{
	foodPool_->getPool()->erase(iterator_);
}

void Food::update()
{
	position_ = position_ + dir_;
}
