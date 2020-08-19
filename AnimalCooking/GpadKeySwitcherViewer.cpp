#include "GpadKeySwitcherViewer.h"
#include "Entity.h"
#include "SDL_macros.h"

void GpadKeySwitcherViewer::init()
{
	t = GETCMP1_(Transform);
	logic_ = GETCMP1_(GpadKeySwitcher);

	for (auto& s : logic_->getSwitchers()) {
		s->setBackGroundTexture(clickTexture_);
	}

}

void GpadKeySwitcherViewer::draw()
{
	for (auto& s : logic_->getSwitchers())
		s->draw();
}
