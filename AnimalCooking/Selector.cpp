
#include "Selector.h"

void Selector::update()
{
	//OnCollisionExit
	if (select_ != nullptr) {	//Si tiene algo seleccionado y no sigue colisionando con el lo ponemos a nullptr
		if (!(Collisions::collidesWithRotation(GETCMP1_(InteractionRect)->getPos(), GETCMP1_(InteractionRect)->getW(), GETCMP1_(InteractionRect)->getH(), 0,
			select_->getPos(), select_->getSize().getX(), select_->getSize().getY(), select_->getRot()))) {
			cout << "NULL" << endl;
			select_ = nullptr;
		}
	}
}
