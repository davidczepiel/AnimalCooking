
#include "Selector.h"
#include "Dish.h"

void Selector::update()
{
	//OnCollisionExit
	if (select_ != nullptr) {	//Si tiene algo seleccionado y no sigue colisionando con el lo ponemos a nullptr
		if (!(Collisions::collidesWithRotation(GETCMP1_(InteractionRect)->getPos(), GETCMP1_(InteractionRect)->getW(), GETCMP1_(InteractionRect)->getH(), 0,
		select_->getPos(), select_->getSize().getX(), select_->getSize().getY(), select_->getRot()))) {
			select_->onCollisionExit(id_);
			select_ = nullptr;
		}
	}
	else interationArea = 0;
}
