#include "KeyboardKeySwitcherViewer.h"
#include "Entity.h"
#include "SDL_macros.h"

void KeyboardKeySwitcherViewer::init()
{
	t = GETCMP1_(Transform);
	logic_ = GETCMP1_(KeyboardKeySwitcher);

	for (auto& s : logic_->getSwitchers()) {
		s->setBackGroundTexture(game_->getTextureMngr()->getTexture(Resources::TextureId::ButtonConfig));
	}
		
}

void KeyboardKeySwitcherViewer::draw()
{
	string s = (logic_->getPlayer() == 0) ? "Player 1 : keyboard" : "Player 2 : keyboard";
	Texture c = Texture(SDLGame::instance()->getRenderer(), s,
		SDLGame::instance()->getFontMngr()->getFont(Resources::FontId::QuarkCheese100), { COLOR(0xffffffff) });

	Vector2D size = Vector2D(c.getWidth() * ((t->getH() / 7 ) - 20) / c.getHeight(), t->getH() / 7);
	c.render(RECT(t->getPos().getX() + t->getW() / 3 - size.getX() / 2, t->getPos().getY() + 10, size.getX(), size.getY()));

	for (auto& s : logic_->getSwitchers())
		s->draw();
}
