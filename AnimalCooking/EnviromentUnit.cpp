#include "EnviromentUnit.h"
#include "SDL_macros.h"
#include"Collisions.h"

EnviromentUnit::EnviromentUnit(Vector2D pos, double w, double h, Transform* tP1, Transform* tP2, PlayerController* pC1, PlayerController* pC2, EnviromentControl* envC) : pos(pos), width(w), height(h), tP1(tP1), tP2(tP2),
pC1(pC1), pC2(pC2), affectingP1(false), affectingP2(false), playerAffectedNow(-1), envC(envC)
{
}

void EnviromentUnit::render() const
{
	SDL_Rect rect = RECT(pos.getX(), pos.getY(), width, height);
	texture->render(rect);
}




Snow::Snow(Vector2D pos, double width, double height, Transform* tP1, Transform* tP2, PlayerController* pC1, PlayerController* pC2, EnviromentControl* envC) :
	EnviromentUnit(pos, width, height, tP1, tP2, pC1, pC2, envC)
{
	texture = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Fregadero);
}


void Snow::update()
{
	if (!affectingP1 && Collisions::collides(pos, width, height, tP1->getPos(), tP1->getW(), tP1->getH())) {
		playerAffectedNow = 0;
		act();
		affectingP1 = true;
	}
	else if (affectingP1 && !Collisions::collides(pos, width, height, tP1->getPos(), tP1->getW(), tP1->getH())) {
		playerAffectedNow = -1;
		pC1->resetSpeed();
		affectingP1 = false;
	}
	if (!affectingP2 && Collisions::collides(pos, width, height, tP2->getPos(), tP2->getW(), tP2->getH())) {
		playerAffectedNow = 1;
		act();
		affectingP2 = true;
	}
	else if (affectingP2 && !Collisions::collides(pos, width, height, tP2->getPos(), tP2->getW(), tP2->getH())) {
		playerAffectedNow = -1;
		pC2->resetSpeed();
		affectingP2 = false;
	}
}

void Snow::act()
{
	PlayerController* pC = nullptr;
	if (playerAffectedNow == 0)pC = pC1;
	else pC = pC2;
	pC->setSpeed(0.3);

}



Ice::Ice(Vector2D pos, double width, double height, Transform* tP1, Transform* tP2, PlayerController* pC1, PlayerController* pC2, EnviromentControl* envC) :
	EnviromentUnit(pos, width, height, tP1, tP2, pC1, pC2, envC)
{
	texture = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Dish);
}

void Ice::act()
{
	Transform* p = nullptr;
	if (playerAffectedNow == 0) {
		p = tP1;
		Vector2D vel;
		vel.setX(envC->getPlayerForceX(0) * (config::PLAYER_SPEED * SDLGame::instance()->getCasillaX() / 60)/2);
		vel.setY(envC->getPlayerForceY(0) * (config::PLAYER_SPEED * SDLGame::instance()->getCasillaY() / 60)/2);
		p1Pos = p->getPos();
		p1Pos = p1Pos + vel;
	}
	else {

	}


}

void Ice::update()
{
	if (!affectingP1 && Collisions::collides(pos, width, height, tP1->getPos(), tP1->getW(), tP1->getH())) {
		envC->enterIceZone(0,tP1->getVel());
		affectingP1 = true;
		playerAffectedNow = 0;
		p1Pos = tP1->getPos();
	}
	else if (affectingP1 && Collisions::collides(pos, width, height, tP1->getPos(), tP1->getW(), tP1->getH())) {
		tP1->setPos(p1Pos);// envC->getPlayerForceX()
		playerAffectedNow = 0;
		envC->playerIsMoving(0,tP1->getVel());
		act();
		tP1->setPos(p1Pos);// envC->getPlayerForceX()
	}
	else if (affectingP1 && !Collisions::collides(pos, width, height, tP1->getPos(), tP1->getW(), tP1->getH())) {

		playerAffectedNow = -1;
		affectingP1 = false;
	}

	//if (!affectingP2 && Collisions::collides(pos, width, height, tP2->getPos(), tP2->getW(), tP2->getH())) {
	//	playerAffectedNow = 1;
	//	if (!affectingP2) {
	//		affectingP2 = true;
	//		p2Pos = tP2->getPos();
	//		p2Vel = tP2->getVel();
	//		p2Vel.setX(p2Vel.getX() * (config::PLAYER_SPEED * SDLGame::instance()->getCasillaX() / 60));
	//		p2Vel.setY(p2Vel.getY() * (config::PLAYER_SPEED * SDLGame::instance()->getCasillaY() / 60));
	//	}
	//	act();
	//}
	//else if (affectingP2 && Collisions::collides(pos, width, height, tP2->getPos(), tP2->getW(), tP2->getH())) {
	//	playerAffectedNow=1;
	//	act();
	//}
	//else  {
	//	playerAffectedNow = -1;
	//	//pC2->resetSpeed();
	//	affectingP2 = false;
	
}
