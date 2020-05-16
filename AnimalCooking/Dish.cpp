#include "Dish.h"
#include "DishStack.h"


Dish::Dish(Vector2D pos_, Transport* transPlayer1, Transport* transPlayer2, int maxFood, FoodPool* fp) : Pickable(transPlayer1, transPlayer2, nullptr),
	foods_(vector<Food*>()),isViewingContent(false), inHands(true), foodPool(fp)
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
		//Se vuelve a establecer el size tras salir del plato
		jute::jValue& jsonGeneral = SDLGame::instance()->getJsonGeneral();
		aux->setSize(Vector2D(jsonGeneral["Foods"]["size"]["width"].as_double() * SDLGame::instance()->getCasillaX(), jsonGeneral["Foods"]["size"]["height"].as_double() * SDLGame::instance()->getCasillaY()));
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
	//Elimino de la foodPool las food que tiene el plato
	for (auto& f : foods_)
	{
		foodPool->RemoveFood(std::find(foodPool->getPool().begin(), foodPool->getPool().end(),f));
	}

	auto it = foods_.begin();
	//Elimino las food del plato
	while (it != foods_.end()) {
		delete* it;		
		++it;
	}
	foods_.clear();
}


void Dish::onPick()
{
	inHands = true; 
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::PickUp, 0);
}

void Dish::feedback(int player)

{
	if (isViewingContent)
	{
		vector<Food*> foods = this->getFoodVector();

		int ofset = 40;
		int offsetInside = 15;
		int rows = ceil(foods.size() / 2.0);
		if (rows == 0) rows = 1;

		int w = 140 / 2 - offsetInside * 2;
		SDL_Rect rect = RECT(position_.getX() + ofset, position_.getY() + ofset, 120, rows * w + offsetInside * 2);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Panel);
		feedbackVisual_->render(rect);
		rect.x += offsetInside;
		rect.y += offsetInside;

		for (int i = 0; i < foods.size(); ++i) {
			SDL_Rect r = { rect.x + w * (i % 2), rect.y + w * (i / 2), w, w };
			//Cojo la comida seleccionada y muestro su feedback
			Food* currentFood = *(--this->getCurrentFood());
			if (foods[i] == currentFood)currentFood->getTexture()->render(r);
			//Se dibuja la comida seleccionada
			foods[i]->draw(r);
		}
	}
	else {
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::VerContenidoPlato);
		SDL_Rect r = RECT(position_.getX() + 50, position_.getY() + 50, 200, 32);
		feedbackVisual_->render(r);
	}
}
