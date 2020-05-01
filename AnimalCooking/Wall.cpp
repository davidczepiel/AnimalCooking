#include "Wall.h"
#include "Transform.h"
#include "SDLRenderer.h"

Wall::Wall(Vector2D pos, Vector2D size, Texture* texture, double casilla, double thickness, EntityManager* mn) : Entity(SDLGame::instance(), mn)
{
	addComponent<Transform>(pos, Vector2D(), size.getX(), size.getY());
	Vector2D s;
	if (size.getX() > size.getY())
		s = Vector2D(casilla, thickness);
	else 
		s = Vector2D(thickness, casilla);
	addComponent<SDLRenderer>(texture, s);
}
