#include "InteractionRect.h"

void InteractionRect::init()
{
	pos_.set(GETCMP1_(Transform)->getPos().getX() + radius, GETCMP1_(Transform)->getPos().getY() + radius);
	size_.set(10, 10);
}
