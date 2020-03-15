#include "InsertExpel.h"
#include <list>
//InsertExpel::InsertExpel(Transport* tr) :
//	Component(ecs::InsertExpel),
//	pool_(nullptr),
//	transport_ = tr; {
//}

InsertExpel::InsertExpel() :
	Component(ecs::InsertExpel),
	foodCooker_(nullptr)
{
}

InsertExpel::~InsertExpel() {	
}

void InsertExpel::init() {
	foodCooker_ = GETCMP1_(FoodCooker);
}

//void InsertExpel::insertFood(Cooker *c, list<Food*>& f) {
//	//Terminar de perfilar comportamiento cuando se haya hecho Transport (para saber si tiene plato y quitarlo del vector del plato o quitarlo de la mano del player en caso de que se ponga esa acción)
//	//Por ahora solo se programa el comportamiento para sacarlo de un plato (supuesto caso en que un player lleve comida dentro de un plato y quiera meterlo a un cocinador)
//	//if (transport_.getEmptyDish()) {
//		if (c->getCookerState() == CookerStates::empty) {
//			c->getFoods().insert(c->getFoods().end(), f.begin(), f.end());
//				//poner borrado del elemento en el vector del transport
//			f.clear();
//			c->setCookerState(CookerStates::cooking);
//			c->getCookerTimer()->setTime(c->getCookingTime());
//			c->getCookerTimer()->timerStart();
//		}
//	//}
//}

void InsertExpel::insertFood(Cooker* c) {
	//Terminar de perfilar comportamiento cuando se haya hecho Transport (para saber si tiene plato y quitarlo del vector del plato o quitarlo de la mano del player en caso de que se ponga esa acción)
	//Por ahora solo se programa el comportamiento para sacarlo de un plato (supuesto caso en que un player lleve comida dentro de un plato y quiera meterlo a un cocinador)
	//if (transport_.getEmptyDish()) {
		if (c->getCookerState() == CookerStates::empty) {
				//c->getFoods().insert(c->getFoods().end(), transport_.getItem().getVector().begin(), transport_.getItem().getVector().end());
				//transport_.getItem().getVector().clear()
			foodCooker_->startCooked(c);
		}
	//}
}

void InsertExpel::extractFood(Cooker *c, int foodSelectorPosition) {
	//Terminar de perfilar comportamiento cuando se haya hecho Transport (para saber si tiene plato y quitarlo del vector del plato o quitarlo de la mano del player en caso de que se ponga esa acción)
	//Por ahora solo se programa el comportamiento para sacarlo de un plato (supuesto caso en que un player lleve comida dentro de un plato y quiera meterlo a un cocinador)
	if (/*transport_.getEmptyDish() &&*/ c->getCookerState() == CookerStates::cooked || c->getCookerState() == CookerStates::burned) {
		//transport_.getItem().getVector().insert(transport_.getItem().getVector().end(), c->getFoods()[foodSelectorPosition]);
		//poner borrado del elemento en el vector del cooker
		c->setCookerState(CookerStates::empty);
	}
}

void InsertExpel::extractAllFood(Cooker *c){
	//Terminar de perfilar comportamiento cuando se haya hecho Transport (para saber si tiene plato y quitarlo del vector del plato o quitarlo de la mano del player en caso de que se ponga esa acción)
	//Por ahora solo se programa el comportamiento para sacarlo de un plato (supuesto caso en que un player lleve comida dentro de un plato y quiera meterlo a un cocinador)
	//if (transport_.getEmptyDish() && c->getCookerState() != CookerStates::cooking) {
		//transport_.getItem().getVector().insert(transport_.getItem().getVector().end(), c->getFoods().begin(), c->getFoods().end())
		c->getFoods().clear();
		c->setCookerState(CookerStates::empty);
	//}
}