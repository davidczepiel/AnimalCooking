#pragma once
#include "Interactive.h"
#include "Entity.h"
#include "BinViewer.h"
#include "Transport.h"

class BinEntity : public Entity, public Interactive
{
public:
	BinEntity(SDLGame* game, EntityManager* mngr, Transport* p1, Transport* p2) : Entity(game, mngr), Interactive(p1, p2) {
		addComponent<BinViewer>(ecs::BinViewer);
	}
	~BinEntity() {}

	void interactive(int player) override;
};

