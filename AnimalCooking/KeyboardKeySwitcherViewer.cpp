#include "KeyboardKeySwitcherViewer.h"
#include "Entity.h"
#include "SDL_macros.h"

void KeyboardKeySwitcherViewer::init()
{
	t = GETCMP1_(Transform);
	logic_ = GETCMP1_(KeyboardKeySwitcher);

	for (auto& s : logic_->getSwitchers()) {
		s->setBackGroundTexture(clickTexture_);
	}
}

void KeyboardKeySwitcherViewer::draw()
{
	for (auto& s : logic_->getSwitchers())
		s->draw();
}
