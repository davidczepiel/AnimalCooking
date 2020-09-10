#include "GhostPool.h"
#include "Transform.h"
#include "GhostLife.h"

GhostPool::GhostPool(): Component(ecs::GhostPool)
{
}

void GhostPool::init()
{
	for (size_t i = 0; i < 8; i++) //pool de ocho
	{
		ghosts_.push_back(new Ghost());
	}
}

void GhostPool::update()
{
	for (Ghost* g : ghosts_)
		if (g->getActive()) g->update();
}

void GhostPool::draw()
{
	for (Ghost* g : ghosts_)
		if (g->getActive()) g->draw();
}

void GhostPool::activateGhost(const Vector2D& pos)
{
	for (Ghost* g : ghosts_) {
		if (!g->getActive()) {
			g->activate(pos);
			return;
		}
	}
}