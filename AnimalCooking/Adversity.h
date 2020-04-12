#pragma once
#include "AdversityManager.h"

class Adversity
{
	AdversityManager* adversityMngr_;

public:
	Adversity(AdversityManager* am) : adversityMngr_(am) {}

	virtual void update()=0;
	virtual void draw()=0;
	virtual void reset()=0;

};

