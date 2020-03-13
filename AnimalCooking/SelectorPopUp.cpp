#include "SelectorPopUp.h"

SelectorPopUp::~SelectorPopUp()
{
	for (auto it : pool_) {
		delete it;
	}
}
//Checkea para la pool correspondiente si ha colisionado con el jugador
//en la dirección indicada. En caso positivo, le pasa al Selector del
//jugador el objeto que puede ser utilizado.
void SelectorPopUp::update()
{
	for (auto it : pool_) {
		/*if(Collisions::collidesWithRotation(tr1_->getPos(),tr1_->getW(),tr1_->getH(),tr1_->getRot(),it->getPos(),it->getSize().getX(),it->getSize().getY(),it->getRot() && //Si colisiona player1
		  )*/
	}
}
