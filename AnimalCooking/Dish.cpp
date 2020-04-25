#include "Dish.h"
#include "DishStack.h"


Dish::Dish(Vector2D pos_, Transport* transPlayer1, Transport* transPlayer2,int maxFood, FoodPool* fp) : Pickable(transPlayer1, transPlayer2,nullptr),foods_(vector<Food*>()),isViewingContent(false),inHands(true),foodPool(fp)
{
	foods_.reserve(maxFood);
	feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PlatoFeedBack);
}

// si el vector estaba vacío pone el iterador al principio
void Dish::addFood(Food* f)
{
	if (f != nullptr) 
	{
		foods_.emplace_back(f);			
		currentFood = ++(foods_.rbegin());		
		f->setCanInteract(false);
	}
}

Food* Dish::takeFood()
{
	//si el vector no se ha vaciado pone el iterador al principio para evitar errores
	if (!foods_.empty()) 
	{
		Food* aux = *currentFood.base();
		foods_.erase(currentFood.base());
		if (!foods_.empty())
			currentFood = ++(foods_.rbegin());
		return aux;
	}
	else return nullptr;
}

//Comprobamos que no está el vector vacío y no se ha llegado al último elemento
void Dish::nextFood() 
{
	if (!foods_.empty() && isViewingContent && currentFood != foods_.rend())
		currentFood++;
}

//Comprobamos que no está el vector vacío y no estamos en el primer elemento
void Dish::previousFood() 
{
	if (!foods_.empty() && isViewingContent && currentFood != ++(foods_.rbegin()))
		currentFood--;
}

void Dish::firstFood()
{
	currentFood = ++(foods_.rbegin());
}

void Dish::clearFoods()
{	
	auto it = foods_.begin();
	while (it != foods_.end()) {
		delete* it;		
		++it;
	}
	foods_.clear();
	foodPool->getPool().clear();
}

void Dish::feedback()
{
	SDL_Rect rect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
	feedbackVisual_->render(rect);
}
