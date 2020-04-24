#include "Wall.h"
#include "Transform.h"
#include "SDLRenderer.h"

Wall::Wall(Vector2D pos, Vector2D size, Texture* texture, double casilla, EntityManager* mn) : Entity(SDLGame::instance(), mn)
{
	addComponent<Transform>(pos, Vector2D(), size.getX(), size.getY());
	addComponent<SDLRenderer>(texture, casilla);
}
