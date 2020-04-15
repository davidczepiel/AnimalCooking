#include "SelectorPopUp.h"
using namespace std;

SelectorPopUp::~SelectorPopUp()
{
}
//Checkea para la pool correspondiente si ha colisionado con el jugador
//en la direcci�n indicada. En caso positivo, le pasa al Selector del
//jugador el objeto que puede ser utilizado.
void SelectorPopUp::update()
{

	for (auto& it : *pool_) {
		if (it->isInteractive()) {
			//Si colisiona el rect del player1 con el interactuable
			if (Collisions::collidesWithRotation(it1_->getPos(), it1_->getW(), it1_->getH(), 0, it->getPos(), it->getSize().getX(), it->getSize().getY(), it->getRot())
				&& tP1->getObjectInHands() != it) {
				sl1_->setSelect(it);
			}
			//Si colisiona el rect del player2 con el interactuable
			if (Collisions::collidesWithRotation(it2_->getPos(), it2_->getW(), it2_->getH(), 0, it->getPos(), it->getSize().getX(), it->getSize().getY(), it->getRot())
				&& tP2->getObjectInHands() != it) {
				sl2_->setSelect(it);
			}
		}
	}
}
