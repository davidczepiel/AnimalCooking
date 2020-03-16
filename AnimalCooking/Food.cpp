#include "Food.h"
#include "SDL_macros.h"

Food::Food(Vector2D position, Resources::FoodType type, Transport* p1, Transport* p2) : Pickable(p1, p2)
{
	position_ = position;
	size_ = Vector2D(50, 50);
	type_ = type;
	foodPool_ = nullptr;
	speed_ = Vector2D();
}

Food::Food(Resources::FoodType type): Pickable(nullptr, nullptr) {
	position_ = Vector2D();
	size_ = Vector2D(50, 50);
	type_ = type;
	foodPool_ = nullptr;
	speed_ = Vector2D();
}

void Food::setFoodPool(FoodPool* foodPool, std::vector<Food*>::iterator it)
{
	foodPool_ = foodPool;
	iterator_ = it;
}

void Food::Destroy()
{
	foodPool_->RemoveFood(iterator_);
}

void Food::update()
{
	Pickable::update();
}
