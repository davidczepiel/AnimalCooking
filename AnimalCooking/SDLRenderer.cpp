#include "SDLRenderer.h"
#include "Entity.h"
#include "SDL_macros.h"

SDLRenderer::SDLRenderer(Texture* t, Vector2D size) : Component(ecs::SDLRenderer), t(t), size(size)
{
}

void SDLRenderer::init()
{
	tr = GETCMP1_(Transform);
}

void SDLRenderer::draw()
{
	double currPosX = tr->getPos().getX();
	while (currPosX <= tr->getPos().getX() + tr->getW() - size.getX()) { //Se dibuja tantas veces se puedan una columna
		renderColumn(currPosX, size.getX());
		currPosX += size.getX();
	}
	if (currPosX < tr->getPos().getX() + tr->getW())  //Se dibuja el resto (si queda) haciendo crop
		renderColumn(currPosX, tr->getPos().getX() + tr->getW() - currPosX);
}

void SDLRenderer::renderColumn(size_t x, size_t restX)
{
	double currPosY = tr->getPos().getY();
	while (currPosY <= tr->getPos().getY() + tr->getH() - size.getY()) { //Se dibuja tantas veces se pueda la textura completa
		t->render(RECT(x, currPosY, restX, size.getY()), RECT(0, 0, restX * t->getWidth() / size.getX(), t->getHeight()));
		currPosY += size.getY();
	}
	if (currPosY < tr->getPos().getY() + tr->getH()) { //Se dibuja el resto (si queda) haciendo crop
		double rest = tr->getPos().getY() + tr->getH() - currPosY;
		t->render(RECT(x, currPosY, restX, rest), RECT(0, 0, restX * t->getWidth() / size.getX(), rest * t->getHeight() / size.getY()));
	}
}
