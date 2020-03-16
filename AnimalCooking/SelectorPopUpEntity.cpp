#include "SelectorPopUpEntity.h"

void SelectorPopUpEntity::update()
{
	if (Collisions::collidesWithRotation(it1_->getPos(), it1_->getW(), it1_->getH(), 0, proper->getPos(), proper->getSize().getX(), proper->getSize().getY(), proper->getRot())) {
		sl1_->setSelect(proper);
	}
	if (Collisions::collidesWithRotation(it2_->getPos(), it2_->getW(), it2_->getH(), 0, proper->getPos(), proper->getSize().getX(), proper->getSize().getY(), proper->getRot())) {
		sl2_->setSelect(proper);
	}
}
