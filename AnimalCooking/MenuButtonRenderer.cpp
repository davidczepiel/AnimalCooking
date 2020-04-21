#include "MenuButtonRenderer.h"
#include "SDL_macros.h"
#include "Entity.h"

void MenuButtonRenderer::init()
{
	tr_ = GETCMP1_(Transform);
}

void MenuButtonRenderer::draw()
{
	Vector2D pos = tr_->getPos();

	SDL_Rect dest = RECT(pos.getX(), pos.getY(), tr_->getW(), tr_->getH());
}
