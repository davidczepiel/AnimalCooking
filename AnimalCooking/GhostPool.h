#pragma once
#include "Component.h"
#include "Ghost.h"
#include <list>

class GhostPool : public Component
{
public:
	GhostPool();
	~GhostPool() { 
		for (Ghost* g : ghosts_)
			delete g;
	}
	void init() override;
	void update() override;
	void draw() override;
	void activateGhost(const Vector2D& pos);

private:
	list<Ghost*> ghosts_;
};

