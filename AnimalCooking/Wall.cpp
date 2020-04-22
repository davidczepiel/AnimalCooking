#include "Wall.h"
#include "Transform.h"
#include "SDLRenderer.h"

Wall::Wall(Vector2D pos, Vector2D size, double rot, Texture* texture, double casilla, EntityManager* mn) : Entity(SDLGame::instance(), mn)
{
	addComponent<Transform>(pos, Vector2D(), size.getX(), size.getY(), rot);
	addComponent<SDLRenderer>(texture, casilla);
}
