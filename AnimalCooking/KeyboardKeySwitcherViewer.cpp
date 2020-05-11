#include "KeyboardKeySwitcherViewer.h"
#include "Entity.h"

void KeyboardKeySwitcherViewer::init()
{
	t = GETCMP1_(Transform);
	logic_ = GETCMP1_(KeyboardKeySwitcher);
}
