#include "SelectorPopUp.h"
#include "SDL_macros.h"
using namespace std;

SelectorPopUp::~SelectorPopUp()
{
}
//Checkea para la pool correspondiente si ha colisionado con el jugador
//en la direcci�n indicada. En caso positivo, le pasa al Selector del
//jugador el objeto que puede ser utilizado.
void SelectorPopUp::update()
{
	SDL_Rect itRect;
	SDL_Rect interactionRect1 = RECT(it1_->getPos().getX(), it1_->getPos().getY(), it1_->getW(), it1_->getH());
	SDL_Rect interactionRect2 = RECT(it2_->getPos().getX(), it2_->getPos().getY(), it2_->getW(), it2_->getH());
	SDL_Rect resultRect;
	SDL_Rect bestRect = RECT(0, 0, 0, 0);

	for (auto& it : *pool_) {
		if (it->isInteractive()) {
			itRect = RECT(it->getPos().getX(), it->getPos().getY(), it->getSize().getX(), it->getSize().getY());

			//Si colisiona el rect del player1 con el interactuable
			if (Collisions::collidesWithRotation(it1_->getPos(), it1_->getW(), it1_->getH(), 0, it->getPos(), it->getSize().getX(), it->getSize().getY(), it->getRot())
				&& tP1->getObjectInHands() != it) {
				SDL_IntersectRect(&interactionRect1, &itRect, &resultRect);
				if(resultRect.w * resultRect.h > bestRect.w * bestRect.h) sl1_->setSelect(it, resultRect.w * resultRect.h);
			}
			//Si colisiona el rect del player2 con el interactuable
			if (Collisions::collidesWithRotation(it2_->getPos(), it2_->getW(), it2_->getH(), 0, it->getPos(), it->getSize().getX(), it->getSize().getY(), it->getRot())
				&& tP2->getObjectInHands() != it) {
				SDL_IntersectRect(&interactionRect2, &itRect, &resultRect);
				if (resultRect.w * resultRect.h > bestRect.w* bestRect.h) sl2_->setSelect(it, resultRect.w * resultRect.h);
			}
		}
	}
}
