
#include "Selector.h"

void Selector::update()
{
	//OnCollisionExit
	if (select_ != nullptr) {	//Si tiene algo seleccionado y no sigue colisionando con el lo ponemos a nullptr
		if (!(Collisions::collidesWithRotation(GETCMP1_(Transform)->getPos(), GETCMP1_(Transform)->getW(), GETCMP1_(Transform)->getH(), GETCMP1_(Transform)->getRot(),
			select_->getPos(), select_->getSize().getX(), select_->getSize().getY(), select_->getRot()))) {
			select_ = nullptr;
		}
	}
}
