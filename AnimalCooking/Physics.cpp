#include "Physics.h"

bool Physics::Collided(SDL_Rect pos)
{
	return colSystem->Collides(pos);
}
