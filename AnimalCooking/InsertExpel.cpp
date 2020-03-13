#include "InsertExpel.h"

//InsertExpel::InsertExpel(Transport* tr) :
//	Component(ecs::InsertExpel),
//	pool_(nullptr),
//	transport_ = tr; {
//}

InsertExpel::InsertExpel() :
	Component(ecs::InsertExpel){
}

InsertExpel::~InsertExpel() {	
}

void InsertExpel::init() {
}

void InsertExpel::insertFood(Cooker *c, Food* f) {
	//Terminar de perfilar comportamiento cuando se haya hecho Transport (para saber si tiene plato y quitarlo del vector del plato o quitarlo de la mano del player en caso de que se ponga esa acción)
	//Por ahora solo se programa el comportamiento para sacarlo de un plato (supuesto caso en que un player lleve comida dentro de un plato y quiera meterlo a un cocinador)
	//if (transport_.getEmptyDish()) {
		if (c->getCookerState() == CookerStates::empty ||
			c->getCookerState() == CookerStates::ready) {
				c->getFoods().push_back(f);
				//poner borrado del elemento en el vector del transport
				c->setCookerState(CookerStates::ready);
		}
	//}
}

void InsertExpel::insertFood(Cooker* c) {
	//Terminar de perfilar comportamiento cuando se haya hecho Transport (para saber si tiene plato y quitarlo del vector del plato o quitarlo de la mano del player en caso de que se ponga esa acción)
	//Por ahora solo se programa el comportamiento para sacarlo de un plato (supuesto caso en que un player lleve comida dentro de un plato y quiera meterlo a un cocinador)
	//if (transport_.getEmptyDish()) {
		if (c->getCookerState() == CookerStates::empty ||
			c->getCookerState() == CookerStates::ready) {
				//c->getFoods().insert(c->getFoods().end(), transport_.getItem().getVector().begin(), transport_.getItem().getVector().end());
				//transport_.getItem().getVector().clear()
				c->setCookerState(CookerStates::ready);				
		}
	//}
}

void InsertExpel::extractFood(Cooker *c, int foodSelectorPosition) {
	//Terminar de perfilar comportamiento cuando se haya hecho Transport (para saber si tiene plato y quitarlo del vector del plato o quitarlo de la mano del player en caso de que se ponga esa acción)
	//Por ahora solo se programa el comportamiento para sacarlo de un plato (supuesto caso en que un player lleve comida dentro de un plato y quiera meterlo a un cocinador)
	//if (transport_.getEmptyDish() && c->getCookerState() != CookerStates::cooking) {
		//transport_.getItem().getVector().insert(transport_.getItem().getVector().end(), c->getFoods()[foodSelectorPosition]);
		//poner borrado del elemento en el vector del cooker
		if (c->getFoods().size > 0)
			c->setCookerState(CookerStates::ready);
		else c->setCookerState(CookerStates::empty);
	//}
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