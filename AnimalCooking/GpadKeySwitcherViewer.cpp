#include "GpadKeySwitcherViewer.h"
#include "Entity.h"

void GpadKeySwitcherViewer::init()
{
	t = GETCMP1_(Transform);
	logic_ = GETCMP1_(GpadKeySwitcher);

	//for (auto& s : logic_->getSwitchers()) {
	////Give textures and others
	//}

}

void GpadKeySwitcherViewer::draw()
{
	/*for (auto& s : logic_->getSwitchers())
		s->draw();*/
}
