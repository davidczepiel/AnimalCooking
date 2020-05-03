#include "Shelf.h"


Shelf::Shelf(Vector2D pos, Pickable* c, Transport* p1, Transport* p2, EntityManager* mng, Texture* texture) :Entity(SDLGame::instance(), mng), Interactive(p1, p2,nullptr), content(c) {
	addComponent<ShelfViewer>(this, texture);
	dishFinisher=addComponent<DishFinisher>(p1,p2);
	position_ = pos;
	size_ = Vector2D(128, 128);
	if (content != nullptr) {
		contentType = Resources::PickableType::Utensil;
		setContentPos();
	}
	else
		contentType = Resources::PickableType::none;
}

void Shelf::setContentPos()
{
	content->setPos(Vector2D(position_.getX() + (size_.getX() / 2 - content->getSize().getX() / 2),
		position_.getY() + (size_.getY() / 2 - content->getSize().getY() / 2)));
	content->setCanInteract(false);
}


void Shelf::action1(int id) {
	Transport* player;
	//Dependiendo del numero que me ha llegado trabajare con el player1 o el player2
	if (id == 0)player = player1_;
	else player = player2_;
	Resources::PickableType onPlayerHands;
	//Sabiendo con quien interactuo le pido lo que tiene en las manos
	onPlayerHands = player->getObjectTypeInHands();

	if (contentType == Resources::PickableType::Dish && static_cast<Dish*>(content)->getIsViewingContent()) {
		Dish* d = static_cast<Dish*>(content);

		if (onPlayerHands == Resources::PickableType::Food)
		{
			Food* aux = d->takeFood();
			Food* hands = static_cast<Food*>(player->getObjectInHands());
			static_cast<Dish*>(content)->addFood(hands);
			player->pick(aux, Resources::PickableType::Food, false);
		}
		else if (onPlayerHands == Resources::PickableType::none)
			player->pick(d->takeFood(), Resources::PickableType::Food, false);

	}
	else {
		Swap(player, onPlayerHands);
		if (content != nullptr) {
			setContentPos();
		}
	}

}

//Mueve el selector hacia delante
void Shelf::action2(int id)
{
	if (contentType == Resources::PickableType::Dish)
	{
		static_cast<Dish*>(content)->nextFood();
	}
}
//Mueve el selector hacia atras
void Shelf::action3(int id)
{
	if (contentType == Resources::PickableType::Dish)
	{
		static_cast<Dish*>(content)->previousFood();
	}
}
//Activa el selector
void Shelf::action4(int id)
{
	if (contentType == Resources::PickableType::Dish)
	{
		Dish* d = static_cast<Dish*>(content);
		//Si no esta mostrando el selector y el plato no esta vacio
		if (!d->getIsViewingContent() && !d->isEmpty())
		{
			d->firstFood();
			d->setIsViewingContent(true);
		}
	}
}
//Desactiva el selector si nos movemos
void Shelf::onMoved(int id) {

	if (contentType == Resources::PickableType::Dish)
	{
		Dish* d = static_cast<Dish*>(content);
		if (d->getIsViewingContent())
			d->setIsViewingContent(false);
	}
}

//Finaliza el plato
void Shelf::action5(int id)
{
	if (contentType == Resources::PickableType::Dish)
	{
	  Dish* d = static_cast<Dish*>(content);
      dishFinisher->finish(id,d);
	}
	
}

void Shelf::feedback(int player)
{
	if (contentType == Resources::PickableType::Dish)
	{
		Dish* d = static_cast<Dish*>(content);
		setTexture(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Panel));
		if (d->getIsViewingContent())
		{
			vector<Food*> foods = d->getFoodVector();

			int ofset = 55;
			int offsetInside = 15;
			int rows = ceil(foods.size() / 2.0);
			if (rows == 0) rows = 1;

			int w = 140 / 2 - offsetInside * 2;
			SDL_Rect rect = RECT(position_.getX() + ofset, position_.getY() + ofset, 140, rows * w + offsetInside * 2);
			feedbackVisual_->render(rect);
			rect.x += offsetInside;
			rect.y += offsetInside;

			for (int i = 0; i < foods.size(); ++i) {

				SDL_Rect r = { rect.x + w * (i % 2), rect.y + w * (i / 2), w, w };
				//Cojo la comida seleccionada y muestro su feedback
				Food* currentFood = *(--d->getCurrentFood());
				if(foods[i]==currentFood)currentFood->getTexture()->render(r);		
				//Se dibuja la comida seleccionada
				foods[i]->draw(r);
			}
		}		
	}
}

void Shelf::Swap(Transport* player, Resources::PickableType onPlayerHands) {
	Pickable* c = content;

	//Segun lo que tenga en las manos
	switch (onPlayerHands) {
		//SI no tiene nada, le paso mi contenido, diciendole de que tipo es y me quedo con nada
	case Resources::PickableType::none:
		player->pick(content, contentType);
		content = nullptr;
		contentType = Resources::PickableType::none;
		break;
		//Si tiene comida. SI Y SOLO SI tengo un plato, lo a�ado a este y le digo al player que lo suelte
	case Resources::PickableType::Food:
		if (contentType == Resources::PickableType::Dish) {
			static_cast<Dish*>(content)->addFood(static_cast<Food*>(player->getObjectInHands()));
			player->drop(false);
		}
		break;
		//En caso de que tenga o un plato o un utensilio hago un intercambio
	default:
		content = player->getObjectInHands();
		player->drop(false);
		player->pick(c, contentType);
		contentType = onPlayerHands;
		break;
	}
}