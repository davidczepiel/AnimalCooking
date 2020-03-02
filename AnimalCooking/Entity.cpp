#include "Entity.h"

Entity::Entity()
{
	game_ = nullptr;
	mngr_ = nullptr;
}

Entity::Entity(SDLGame *game, EntityManager *mngr) :
		game_(game), //
		mngr_(mngr) //
{
}

Entity::~Entity() {
}

