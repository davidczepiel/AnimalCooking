#include "SwitcherGPad.h"
#include "SDL_macros.h"
#include "SDLGame.h"

void SwitcherGPad::update()
{
}

void SwitcherGPad::draw()
{
	backGround_->render(RECT(pos_.getX(), pos_.getY(), size_.getX(), size_.getY()));
	Texture c = Texture(SDLGame::instance()->getRenderer(), string(SDL_GameControllerGetStringForButton(gPad_keyToChange)),
		SDLGame::instance()->getFontMngr()->getFont(Resources::FontId::ARIAL12), { COLOR(0x000000ff) });
	c.render(RECT(pos_.getX() + size_.getX() / 2, pos_.getY(), c.getWidth() * size_.getY() / c.getHeight(), size_.getY()));
}
