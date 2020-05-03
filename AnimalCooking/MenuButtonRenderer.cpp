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

	InputHandler* ih = InputHandler::instance();
	Vector2D buttonPos = tr_->getPos();
	Vector2D mousePos = ih->getMousePos();

	SDL_Point mousePosition = { mousePos.getX(), mousePos.getY() };
	SDL_Rect buttonRect = RECT(buttonPos.getX(), buttonPos.getY(), tr_->getW(), tr_->getH());

	if (SDL_PointInRect(&mousePosition, &buttonRect) || focused) {
		texture->renderWithTint(dest, 160, 50, 0);
	}
	else texture->render(dest);
}
