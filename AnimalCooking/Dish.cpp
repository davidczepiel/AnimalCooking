#include "Dish.h"
#include "DishStack.h"
#include "GPadController.h"


Dish::Dish(Vector2D pos_, Transport* transPlayer1, Transport* transPlayer2, int maxFood, FoodPool* fp) : Pickable(transPlayer1, transPlayer2, nullptr),
currentFood(), foods_(), isViewingContent(false), inHands(true), foodPool(fp), game_(SDLGame::instance())
{	
	feedbackVisual_ = game_->getTextureMngr()->getTexture(Resources::PlatoFeedBack);
}

// si el vector estaba vacío pone el iterador al principio
void Dish::addFood(Food* f)
{
	if (f != nullptr)
	{
		f->setInHands(false);
		foods_.push_back(f);
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
		aux->setInHands(true);
		//Se vuelve a establecer el size tras salir del plato
		jute::jValue& jsonGeneral = game_->getJsonGeneral();
		aux->setSize(Vector2D(jsonGeneral["Foods"]["size"]["width"].as_double() * game_->getCasillaX(), jsonGeneral["Foods"]["size"]["height"].as_double() * game_->getCasillaY()));
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
		foodPool->RemoveFood(std::find(foodPool->getPool().begin(), foodPool->getPool().end(), f));
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
	game_->getAudioMngr()->playChannel(Resources::AudioId::PickUp, 0);
}

void Dish::feedback(int player)
{
	if (isViewingContent)
	{
		vector<Food*> foods = this->getFoodVector();

		int offset = 40;
		int offsetInside = 15;
		int rows = ceil(foods.size() / 2.0);
		if (rows == 0) rows = 1;

		int w = 140 / 2 - offsetInside * 2;
		SDL_Rect rect = RECT(position_.getX() + offset, position_.getY() + offset, 120, rows * w + offsetInside * 2);
		feedbackVisual_ = game_->getTextureMngr()->getTexture(Resources::Panel);
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
	else if (game_->getOptions().showKeyToPress && getFoodVector().size() > 0) {
		if (getFoodVector().size() > 3) {
			if (GPadController::instance()->playerControllerConnected(player))
				game_->renderFeedBack(position_, "Finish Dish", SDL_GameControllerGetStringForButton(game_->getOptions().players_gPadButtons[player].FINISHER));
			else
				game_->renderFeedBack(position_, "Finish Dish", SDL_GetKeyName(game_->getOptions().players_keyboardKeys[player].FINISHER));
		}
		else {
			if (GPadController::instance()->playerControllerConnected(player))
				game_->renderFeedBack(position_, "View Content", SDL_GameControllerGetStringForButton(game_->getOptions().players_gPadButtons[player].OPEN));
			else
				game_->renderFeedBack(position_, "View Content", SDL_GetKeyName(game_->getOptions().players_keyboardKeys[player].OPEN));
		}
	}
}
