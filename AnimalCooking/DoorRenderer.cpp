#include "DoorRenderer.h"
#include "SDL_macros.h"
#include "Collisions.h"
#include "GameConfig.h"

DoorRenderer::DoorRenderer(Transform* tr, Transform* p1, Transform* p2, Texture* texture): Component(ecs::DoorRenderer),
	state(State::Closed), tr(tr), t(texture), animState()
{
	players[0] = p1;
	players[1] = p2;
}

void DoorRenderer::update()
{
	state = checkCollision();
}

void DoorRenderer::draw()
{
	SDL_Rect dest = RECT(tr->getPos().getX(), tr->getPos().getY(), tr->getW(), tr->getH());

	if (state == State::Closed) {
		t->renderFrame(dest, 0, 0, 0);
	}
	else {
		t->renderFrame(dest, 0, int(((SDLGame::instance()->getTime() / config::ANIM_SPEED) % t->getNumCols())), 0);
	}
}

State DoorRenderer::checkCollision(){
	if (Collisions::collides(tr->getPos(), tr->getW(), tr->getH(), players[0]->getPos(), players[0]->getW(), players[0]->getH()) ||
		Collisions::collides(tr->getPos(), tr->getW(), tr->getH(), players[1]->getPos(), players[1]->getW(), players[1]->getH())) {
		return State::Open;
	}
	else return State::Closed;
}
