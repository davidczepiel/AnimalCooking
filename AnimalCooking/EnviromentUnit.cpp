#include "EnviromentUnit.h"
#include "SDL_macros.h"
#include"Collisions.h"

EnviromentUnit::EnviromentUnit(Vector2D pos, double w, double h, Transform* tP1, Transform* tP2, PlayerController* pC1, PlayerController* pC2): pos(pos),width(w),height(h),tP1(tP1),tP2(tP2),
pC1(pC1),pC2(pC2),affectingP1(false),affectingP2(false),playerAffectedNow(-1)
{
}

void EnviromentUnit::render() const
{
	SDL_Rect rect = RECT(pos.getX(), pos.getY(), width, height);
	texture->render(rect);
}




Snow::Snow(Vector2D pos, double width, double height, Transform* tP1, Transform* tP2, PlayerController* pC1, PlayerController* pC2):
	EnviromentUnit(pos,width,height,tP1,tP2,pC1,pC2)
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
	else if(affectingP1 && !Collisions::collides(pos, width, height, tP1->getPos(), tP1->getW(), tP1->getH()) ){
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
