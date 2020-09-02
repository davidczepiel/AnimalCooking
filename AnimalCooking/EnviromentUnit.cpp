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




SlowUnit::SlowUnit(Vector2D pos, double width, double height, Transform* tP1, Transform* tP2, PlayerController* pC1, PlayerController* pC2, EnviromentControl* envC) :
	EnviromentUnit(pos, width, height, tP1, tP2, pC1, pC2, envC)
{
	texture = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Fregadero);
}


void SlowUnit::update()
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

void SlowUnit::act()
{
	PlayerController* pC = nullptr;
	if (playerAffectedNow == 0)pC = pC1;
	else pC = pC2;
	pC->setSpeed(0.3);

}



SlipperyUnit::SlipperyUnit(Vector2D pos, double width, double height, Transform* tP1, Transform* tP2, PlayerController* pC1, PlayerController* pC2, EnviromentControl* envC) :
	EnviromentUnit(pos, width, height, tP1, tP2, pC1, pC2, envC)
{
	texture = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Dish);
}

void SlipperyUnit::act()
{
	Transform* p = nullptr;
	if (playerAffectedNow == 0) {
		p = tP1;
		p1Vel.setX(envC->getPlayerForceX(0) /2.75 );
		p1Vel.setY(envC->getPlayerForceY(0) /2.75);
	}
	else {
		p = tP2;
		p2Vel.setX(envC->getPlayerForceX(1) / 2.75);
		p2Vel.setY(envC->getPlayerForceY(1) / 2.75);
	}
}

void SlipperyUnit::update()
{

	//PARA EL PLAYER 1
	if (!affectingP1 && Collisions::collides(pos, width, height, tP1->getPos(), tP1->getW(), tP1->getH())) {
		envC->enterIceZone(0,tP1->getVel());
		affectingP1 = true;
		playerAffectedNow = 0;
	}
	else if (affectingP1 && Collisions::collides(pos, width, height, tP1->getPos(), tP1->getW(), tP1->getH())) {
		playerAffectedNow = 0;
		envC->playerIsMoving(0,pC1->getinput());
		act();
		tP1->setVel(p1Vel);
	}
	else if (affectingP1 && !Collisions::collides(pos, width, height, tP1->getPos(), tP1->getW(), tP1->getH())) {
		playerAffectedNow = -1;
		affectingP1 = false;
		envC->exitedIceZone(0);
	}


	//PARA EL PLAYER 2
	if (!affectingP2 && Collisions::collides(pos, width, height, tP2->getPos(), tP2->getW(), tP2->getH())) {
		envC->enterIceZone(1, tP2->getVel());
		affectingP2 = true;
		playerAffectedNow = 1;
	}
	else if (affectingP2 && Collisions::collides(pos, width, height, tP2->getPos(), tP2->getW(), tP2->getH())) {
		playerAffectedNow = 1;
		envC->playerIsMoving(1, pC2->getinput());
		act();
		tP2->setVel(p2Vel);
	}
	else if (affectingP2 && !Collisions::collides(pos, width, height, tP2->getPos(), tP2->getW(), tP2->getH())) {
		playerAffectedNow = -1;
		affectingP2 = false;
		envC->exitedIceZone(1);
	}
}
