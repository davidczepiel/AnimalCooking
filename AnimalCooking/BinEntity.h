#pragma once
#include "Interactive.h"
#include "Entity.h"
#include "BinViewer.h"
#include "Transform.h"
#include "Transport.h"
#include "Dish.h"

class BinEntity : public Entity, public Interactive
{
public:
	BinEntity(SDLGame* game, EntityManager* mngr, Transport* p1, Transport* p2) : Entity(game, mngr), Interactive(p1, p2) {
		this->addComponent<Transform>();
		this->addComponent<BinViewer>();
	}
	~BinEntity() {}

	void interactive(int player) override;
};

