#include "GpadKeySwitcherViewer.h"
#include "Entity.h"

void GpadKeySwitcherViewer::init()
{
	t = GETCMP1_(Transform);
	logic_ = GETCMP1_(GpadKeySwitcher);
}
