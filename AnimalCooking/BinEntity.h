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
	BinEntity(EntityManager* mngr, Transport* p1, Transport* p2) : Entity(SDLGame::instance(), mngr), Interactive(p1, p2,nullptr) {
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PapelertaFeedBack);
	}
	~BinEntity() {}

	void action1(int player) override;
	void feedback() override;
};

