#include "CollisionsSystem.h"



bool CollisionsSystem::Collides(SDL_Rect body, Vector2D vel) {
	if (vel.getX() != 0 || vel.getY() != 0) {
		bool hasCollided = false;
		int i = 0;
		SDL_Rect result = body;
		result.x += vel.getX();
		result.y += vel.getY();
		/*auto iter0 = entidades.begin();
		while (!hasCollided && iter0 != entidades.end()) {
			if ((body.x != (int)(*iter0)->getPos().getX() && body.y != (int)(*iter0)->getPos().getY()) &&
				Collisions::collides(Vector2D(result.x,result.y), body.w, body.h,
				(*iter0)->getPos(), (*iter0)->getW(), (*iter0)->getH())) {
				hasCollided = true;
				SDL_Rect obstacle;
				obstacle.x = (*iter0)->getPos().getX();
				obstacle.y = (*iter0)->getPos().getY();
				obstacle.w = (*iter0)->getW();
				obstacle.h = (*iter0)->getH();
				 SDL_IntersectRect(&result,&obstacle,&lastCol);
			}
			++iter0;
		}*/
		auto iter = entidadesInt.begin();
		while (!hasCollided && iter != entidadesInt.end()) {
			if (Collisions::collides(Vector2D(result.x, result.y), body.w, body.h,
				(*iter)->getPos(), (*iter)->getSize().getX(), (*iter)->getSize().getY())) {
				hasCollided = true;
				SDL_Rect obstacle;
				obstacle.x = (*iter)->getPos().getX();
				obstacle.y = (*iter)->getPos().getY();
				obstacle.w = (*iter)->getSize().getX();
				obstacle.h = (*iter)->getSize().getY();
				SDL_IntersectRect(&result, &obstacle, &lastCol);
			}
			++iter;
		}
		auto iter2 = cookersPool.begin();
		while (!hasCollided && iter2 != cookersPool.end()) {
			if (Collisions::collides(Vector2D(result.x, result.y), body.w, body.h,
				(*iter2)->getPos(), (*iter2)->getSize().getX(), (*iter2)->getSize().getY())) {
				hasCollided = true;
				SDL_Rect obstacle;
				obstacle.x = (*iter2)->getPos().getX();
				obstacle.y = (*iter2)->getPos().getY();
				obstacle.w = (*iter2)->getSize().getX();
				obstacle.h = (*iter2)->getSize().getY();
				SDL_IntersectRect(&result, &obstacle, &lastCol);
			}
			i++;
		}
		auto iter3 = ingredientesPools.begin();
		while (!hasCollided && i < ingredientesPools.size()) {
			if ((body.x != (int)(*iter3)->getPos().getX() && body.y != (int)(*iter3)->getPos().getY()) &&
				Collisions::collides(Vector2D(result.x, result.y), body.w, body.h,
				(*iter3)->getPos(), (*iter3)->getSize().getX(), (*iter3)->getSize().getY())) {
				hasCollided = true;
				SDL_Rect obstacle;
				obstacle.x = (*iter3)->getPos().getX();
				obstacle.y = (*iter3)->getPos().getY();
				obstacle.w = (*iter3)->getSize().getX();
				obstacle.h = (*iter3)->getSize().getY();
				SDL_IntersectRect(&result, &obstacle, &lastCol);
			}
			i++;
		}

		return hasCollided;
	}
	else
		return false;
}


SDL_Rect CollisionsSystem::getLastCollision() {
	SDL_Rect aux = lastCol;
	lastCol = SDL_Rect();
	return aux;
}


