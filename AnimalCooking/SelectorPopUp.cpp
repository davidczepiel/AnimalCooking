#include "SelectorPopUp.h"
using namespace std;

SelectorPopUp::~SelectorPopUp()
{
}
//Checkea para la pool correspondiente si ha colisionado con el jugador
//en la dirección indicada. En caso positivo, le pasa al Selector del
//jugador el objeto que puede ser utilizado.
void SelectorPopUp::update()
{
	bool interact1 = false, interact2 = false;
	for (auto it : pool_) {
		//Si colisiona el rect del player1 con el interactuable
		if (Collisions::collidesWithRotation(it1_->getPos(), it1_->getW(), it1_->getH(), 0, it->getPos(), it->getSize().getX(), it->getSize().getY(), it->getRot())) {
			sl1_->setSelect(it);
			cout << "Cogido";
		}
		//Si colisiona el rect del player2 con el interactuable
		if (Collisions::collidesWithRotation(it2_->getPos(), it2_->getW(), it2_->getH(), 0, it->getPos(), it->getSize().getX(), it->getSize().getY(), it->getRot())) {
			sl2_->setSelect(it);
		}
	}
}
