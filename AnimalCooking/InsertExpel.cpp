#include "InsertExpel.h"
#include "Dish.h"
#include <list>

InsertExpel::InsertExpel(Transport* tr1, Transport* tr2) :
	Component(ecs::InsertExpel),
	transport1_(tr1), transport2_(tr2),
	foodCooker_(nullptr)
{
}

InsertExpel::~InsertExpel() {	
}

void InsertExpel::init() {
	foodCooker_ = GETCMP1_(FoodCooker);
}

void InsertExpel::insertFood(Cooker* cooker, int player) {

	Transport* t;
	if (player == 0) t = transport1_;
	else t = transport2_;

	if (cooker->getCookerState() == CookerStates::empty )
    {

		if (t->getObjectTypeInHands() == Resources::Dish) 
		{
			Dish* dish_ = static_cast<Dish*>(t->getObjectInHands());
			if (!dish_->getFoodVector().empty()) {
				for (auto& i : dish_->getFoodVector()) {
					i->setCanInteract(false);
					i->setCanDraw(false);
				}
				cooker->getFoods().insert(cooker->getFoods().end(), dish_->getFoodVector().begin(), dish_->getFoodVector().end());
				dish_->getFoodVector().clear();
				foodCooker_->startCooked(cooker);
			}
		}
		else if (t->getObjectTypeInHands() == Resources::Food)
		{
			Food* f = static_cast<Food*>(t->getObjectInHands());
			f->setCanInteract(false);
			f->setCanDraw(false);
			cooker->getFoods().push_back(f);
			t->setObjectInHands(nullptr);
			t->setObjectTypeInHands(Resources::PickableType::none);
			foodCooker_->startCooked(cooker);
		}
	}
}

void InsertExpel::extractFood(Cooker *cooker, Timer* timer, int player){
	Transport* t;
	if (player == 0) t = transport1_;
	else t = transport2_;

	if ((cooker->getCookerState() == CookerStates::cooked ||
		cooker->getCookerState() == CookerStates::burned)) 
	{
		if (t->getObjectTypeInHands() == Resources::Dish) {
			Dish* dish_ = static_cast<Dish*>(t->getObjectInHands());
			dish_->getFoodVector().insert(dish_->getFoodVector().end(), cooker->getFoods().begin(), cooker->getFoods().end());
			for (auto& i : dish_->getFoodVector()) {
				i->setCanInteract(false);
				i->setCanDraw(true);
			}
			cooker->getFoods().clear();
			cooker->setCookerState(CookerStates::empty);
			timer->timerReset();
		}
		else if (t->getObjectTypeInHands() == Resources::PickableType::none)
		{
			Food* f = cooker->getFoods()[0];
			f->setCanInteract(false);
			f->setCanDraw(true);
			t->setObjectInHands(f);
			t->setObjectTypeInHands(Resources::PickableType::Food);
			cooker->getFoods().clear();
			cooker->setCookerState(CookerStates::empty);
			timer->timerReset();
		}
	}

	cooker->getCookerTimer()->setTexture(game_->getTextureMngr()->getTexture(Resources::CircularTimer));
}