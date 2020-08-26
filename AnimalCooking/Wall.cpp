#include "Wall.h"
#include "Transform.h"
#include "SDLRenderer.h"
#include "WallOpacityManager.h"

Wall::Wall(Vector2D pos, Vector2D size, Texture* texture, double casillaX, const double casillaY, double thickness, EntityManager* mn) : Entity(SDLGame::instance(), mn)
{
	Transform* t = addComponent<Transform>(pos, Vector2D(), size.getX(), size.getY());
	t->setHitboxSize(size.getX(), size.getY());
	Vector2D s;
	if (size.getX() > size.getY())
		s = Vector2D(casillaX, thickness);
	else 
		s = Vector2D(thickness, casillaY);
	addComponent<SDLRenderer>(texture, s);
}
