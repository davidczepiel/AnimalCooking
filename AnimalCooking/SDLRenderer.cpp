#include "SDLRenderer.h"
#include "Entity.h"
#include "SDL_macros.h"

SDLRenderer::SDLRenderer(Texture* t, size_t size) : Component(ecs::SDLRenderer), t(t), size(size)
{
}

void SDLRenderer::init()
{
	tr = GETCMP1_(Transform);
}

void SDLRenderer::draw()
{
	if (tr->getH() < tr->getW()) { //Horizontal
		double currPos = tr->getPos().getX();

		while (currPos <= tr->getPos().getX() + tr->getW() - size) { //Se dibuja tantas veces se pueda la textura completa
			t->render(RECT(currPos, tr->getPos().getY(), size, tr->getH()));
			currPos += size;
		}
		if (currPos < tr->getPos().getX() + tr->getW()) { //Se dibuja el resto (si queda) haciendo crop
			double rest = tr->getPos().getX() + tr->getW() - currPos;
			SDL_Rect srcRect = RECT(0, 0, rest * t->getWidth() / size, t->getHeight());
			t->render(RECT(currPos, tr->getPos().getY(), rest, tr->getH()), srcRect);
		}
	}
	else { //Vertical
		double currPos = tr->getPos().getY();

		while (currPos <= tr->getPos().getY() + tr->getH() - size) { //Se dibuja tantas veces se pueda la textura completa
			t->render(RECT(tr->getPos().getX(), currPos, tr->getW(), size));
			currPos += size;
		}
		if (currPos < tr->getPos().getY() + tr->getH()) { //Se dibuja el resto (si queda) haciendo crop
			double rest = tr->getPos().getY() + tr->getH() - currPos;
			SDL_Rect srcRect = RECT(0, 0, rest * t->getWidth() / size, t->getHeight());
			t->render(RECT(tr->getPos().getX(), currPos, tr->getW(), rest), srcRect);
		}
	}
}
