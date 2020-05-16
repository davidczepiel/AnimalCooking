#include "SelectorPopUpEntity.h"
#include "SDL_macros.h"
using namespace std;

void SelectorPopUpEntity::update()
{
	SDL_Rect interactionRect1 = RECT(it1_->getPos().getX(), it1_->getPos().getY(), it1_->getW(), it1_->getH());
	SDL_Rect interactionRect2 = RECT(it2_->getPos().getX(), it2_->getPos().getY(), it2_->getW(), it2_->getH());
	SDL_Rect properRect = RECT(proper->getPos().getX(), proper->getPos().getY(), proper->getSize().getX(), proper->getSize().getY());
	SDL_Rect result;

	if (proper->isInteractive()) {
		if (Collisions::collidesWithRotation(it1_->getPos(), it1_->getW(), it1_->getH(), 0, proper->getPos(), proper->getSize().getX(), proper->getSize().getY(), proper->getRot())) {
			SDL_IntersectRect(&interactionRect1, &properRect, &result);
			if(result.w * result.h > sl1_->getInteractionArea()) 
				sl1_->setSelect(proper, result.w * result.h);
		}
		if (Collisions::collidesWithRotation(it2_->getPos(), it2_->getW(), it2_->getH(), 0, proper->getPos(), proper->getSize().getX(), proper->getSize().getY(), proper->getRot())) {
			SDL_IntersectRect(&interactionRect2, &properRect, &result);
			if (result.w * result.h > sl2_->getInteractionArea()) 
				sl2_->setSelect(proper, result.w * result.h);
		}
	}
}
