#include "KeyboardKeySwitcherViewer.h"
#include "Entity.h"

void KeyboardKeySwitcherViewer::init()
{
	t = GETCMP1_(Transform);
	logic_ = GETCMP1_(KeyboardKeySwitcher);

	for (auto& s : logic_->getSwitchers()) {
		s->setBackGroundTexture(game_->getTextureMngr()->getTexture(Resources::TextureId::Button));
	}
		
}

void KeyboardKeySwitcherViewer::draw()
{
	for (auto& s : logic_->getSwitchers())
		s->draw();
}
