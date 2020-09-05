#include "SDLRendererFrame.h"
#include "Entity.h"

SDLRendererFrame::SDLRendererFrame(Texture* t, Uint8 alpha): Component(ecs::SDLRendererFrame), tr(nullptr), t_(t)
{
	t_->setAlpha(alpha);
}

void SDLRendererFrame::init()
{
	tr = GETCMP1_(Transform);
}

void SDLRendererFrame::draw()
{
	SDL_Rect rect = { tr->getPos().getX(), tr->getPos().getY(), tr->getW(), tr->getH() };
	t_->renderFrame(rect, 0, int(((SDLGame::instance()->getTime() / config::ANIM_SPEED) % t_->getNumCols())), 0);
}
