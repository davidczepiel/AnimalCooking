#pragma once
#include "ObjectPool.h"
#include "Button.h"
class ButtonPool: public Component
{
private:
	ObjectPool<Button*, 5> pool_;
};

