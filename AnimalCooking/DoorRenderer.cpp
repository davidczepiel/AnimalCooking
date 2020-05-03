#include "DoorRenderer.h"
#include "SDL_macros.h"
#include "Collisions.h"

DoorRenderer::DoorRenderer(Transform* tr, Transform* p1, Transform* p2, Texture* texture): Component(ecs::DoorRenderer),
	state(State::Closed), tr(tr), t(texture), animState()
{
	players[0] = p1;
	players[1] = p2;
}

void DoorRenderer::update()
{
	if (state == State::Closed) {
		state = checkCollision();
		if (state != State::Closed) {
			animState = 0;
		}
	}
	else if (animState > 10) {
		 animState = 0;
		 state = State::Closed;
	} 
	else if(true /*Check de tempo*/) animState++;
}

void DoorRenderer::draw()
{
	SDL_Rect dest = RECT(tr->getPos().getX(), tr->getPos().getY(), tr->getW(), tr->getH());
	SDL_Rect src = RECT(
		t->getWidth() * animState / 10,
		t->getHeight() * state / 3,
		t->getWidth() / 10,
		t->getHeight() / 3
	);

	t->render(dest, src);
}

State DoorRenderer::checkCollision()
{
	if (Collisions::collides(tr->getPos(), tr->getW(), tr->getH(), players[0]->getPos(), players[0]->getW(), players[0]->getH())) {
		if (players[0]->getPos().getX() < tr->getPos().getX()) return State::OpenedRight;
		else return State::OpenedLeft;
	}
	else if (Collisions::collides(tr->getPos(), tr->getW(), tr->getH(), players[1]->getPos(), players[1]->getW(), players[1]->getH())) {
		if (players[1]->getPos().getX() < tr->getPos().getX()) return State::OpenedRight;
		else return State::OpenedLeft;
	}
	return State::Closed;
}
