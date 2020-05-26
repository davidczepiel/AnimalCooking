#pragma once

class MultipleAdversityManager;
class AdversityManager;
class Adversity
{
protected:
	AdversityManager* adversityMngr_;
	MultipleAdversityManager* multipleAdversityMngr_;

public:
	Adversity(MultipleAdversityManager* mam) : adversityMngr_(nullptr), multipleAdversityMngr_(mam) {}

	virtual void update()=0;
	virtual void draw()=0;
	virtual void reset()=0;

};

