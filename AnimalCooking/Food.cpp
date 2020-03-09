#include "Food.h"
#include "SDL_macros.h"

Food::Food(Vector2D position, Resources::FoodType type)
{
	position_ = position;
	type_ = type;
	foodPool_ = nullptr;
	dir_ = Vector2D();
}

void Food::setFoodPool(FoodPool* foodPool)
{
	foodPool_ = foodPool;
	std::vector<Food*>::iterator it = --foodPool->getPool()->end();
	iterator_ = it;
}

void Food::Destroy()
{
	foodPool_->getPool()->erase(iterator_);
}

void Food::update()
{
	position_ = position_ + dir_;
}
