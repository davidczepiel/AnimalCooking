#include "CollisionsSystem.h"
#include "Ingredient.h"
#include "SDL_macros.h"

#define CHECK_DIFF_BODY(body, other) body.x != other.x || body.y != other.y || body.w != other.w || body.h != other.h
#define COLLIDES(body, other) Collisions::collides(Vector2D(body.x, body.y), body.w, body.h, Vector2D(other.x, other.y), other.w, other.h)

//Devuelve el SDL_Rect de un transform
#define GETBODY_TR(e) RECT(e->getPos().getX(), e->getPos().getY(), e->getW(), e->getH())

//Devuelve el SDL_Rect de un interactive
#define GETBODY_INT(e) RECT(e->getPos().getX(), e->getPos().getY(), e->getSize().getX(), e->getSize().getY())

//Devuelve el SDL_Rect de un ingrediente
#define GETBODY_ING(e) RECT(e->getPos().getX(), e->getPos().getY(), e->getWidth(), e->getHeight())

//Calcula el área de un SDL_Rect
#define AREA(rect) rect.w * rect.h

void CollisionsSystem::update()
{
	//Resolvemos las colisiones si el objeto es movible
	for (auto en : entidadesTr) {
		if(en.second) resolveCollisions(en.first->getPosReference(), Vector2D(en.first->getW(), en.first->getH()), en.first->getVel());
	}

	for (auto en : entidadesIng) {
		if (en.second) resolveCollisions(en.first->getPosReference(), Vector2D(en.first->getWidth(), en.first->getHeight()), en.first->getVel());
	}
}

list<SDL_Rect> CollisionsSystem::collisions(SDL_Rect body)
{
	list<SDL_Rect> collisions;
	for (auto en : entidadesTr) {
		checkCollision(body, GETBODY_TR(en.first), collisions);
	}

	for (auto en : entidadesInt) {
		checkCollision(body, GETBODY_INT(en.first), collisions);
	}

	for (auto en : entidadesIng) {
		checkCollision(body, GETBODY_ING(en.first), collisions);
	}
	return collisions;
}

void CollisionsSystem::checkCollision(SDL_Rect body, SDL_Rect other, list<SDL_Rect>& collisions)
{
	if ((CHECK_DIFF_BODY(body, other)) && COLLIDES(body, other)) { //Si es otro cuerpo y colisionan
		SDL_Rect colision_;
		SDL_IntersectRect(&body, &other, &colision_);
		collisions.push_back(colision_); //Se mete en la lista de colisiones
	}
}

/*
	Caso 1 colision
		si no es cuadrado, se elige la orientacion por ancho > alto
			si alto = ancho, se elige por velocidad
				si abs(velovidad.x) = abs(velovidad.y) se resuelve en diagonal
	Caso 2 colisiones
		se resuelve antes la mayor area como un caso de 1 colision, si no es un cuadrado perfecto
			si es cuadrado perfecto, se suman las colisiones y se resuelve como un caso de 1 colision
		si areas son iguales, se suman las colisiones y se resuelve como un caso de 1 colision
	Caso 3 colisiones
		Se elige la de mayor area, se suma su colision vertical u horizontal con su vecino y se resulve como una sola colision
	Se vuelve a arreglar las colisiones que puedan quedar sin resolver recursivamente
*/

void CollisionsSystem::resolveCollisions(Vector2D& pos, const Vector2D& size, const Vector2D& vel)
{
	list<SDL_Rect> collisions_ = collisions(RECT(pos.getX(), pos.getY(), size.getX(), size.getY()));

	if (!collisions_.empty()) {
		if (collisions_.size() == 1) {
			singleCollision(pos, size, vel, collisions_.front());
		}
		else if (collisions_.size() == 2) {
			SDL_Rect col1 = collisions_.front(), col2 = collisions_.back();
			//se prioriza el de mayor area
			if (AREA(col1) > AREA(col2)) {
				singleCollision(pos, size, vel, col1);
			}
			else if (AREA(col1) < AREA(col2)) {
				singleCollision(pos, size, vel, col2);
			}
			else { //Ambas areas son iguales
				if (col1.x == col2.x) { //Los rectangulos estan alineados en vertical
					col1.h += col2.h;
					singleCollision(pos, size, vel, col1);
				}
				else if (col1.y == col2.y) { //Los rectangulos estan alineados en horizontal
					col1.w += col2.w;
					singleCollision(pos, size, vel, col1);
				}
				else {
					if (vel.getX() < 0) { //Se mueve hacia la izda
						if (vel.getY() < 0) pos = Vector2D(pos.getX() + col1.w, pos.getY() + col1.h); //arriba a la izda
						else pos = Vector2D(pos.getX() + col1.w, pos.getY() - col1.h); //abajo a la izda
					}
					else { //Se mueve hacia la dcha
						if (vel.getY() < 0) pos = Vector2D(pos.getX() - col1.w, pos.getY() + col1.h); //arriba a la dcha
						else pos = Vector2D(pos.getX() - col1.w, pos.getY() - col1.h); //abajo a la dcha
					}
				}
			}
		}
		else {
			SDL_Rect col1, col2, col3;
			col1 = collisions_.front();
			collisions_.pop_front();
			col2 = collisions_.front();
			col3 = collisions_.back();

			if (col1.x == col2.x) { //Los rectangulos estan alineados en vertical
				col1.h += col2.h;
				singleCollision(pos, size, vel, col1);
			}
			else if (col1.y == col2.y) { //Los rectangulos estan alineados en horizontal
				col1.w += col2.w;
				singleCollision(pos, size, vel, col1);
			}
			else {
				if (col1.x == col3.x) { //Los rectangulos estan alineados en vertical
					col1.h += col3.h;
					singleCollision(pos, size, vel, col1);
				}
				else if (col1.y == col3.y) { //Los rectangulos estan alineados en horizontal
					col1.w += col3.w;
					singleCollision(pos, size, vel, col1);
				}
			}
		}
		resolveCollisions(pos, size, vel);
	}
}


void CollisionsSystem::singleCollision(Vector2D& pos, const Vector2D& size, const Vector2D& vel, const SDL_Rect& col)
{
	if (col.w - col.h > 5) { //Colision Vertical
		verticalCollision(pos, size, vel, col);
	}
	else if (col.w - col.h < -5) { //Colision horizontal
		horizontalCollision(pos, size, vel, col);
	}
	else { //Colision en esquina-->Check de la velocidad
		if (abs(vel.getX()) > abs(vel.getY())) { //Movimiento horizontal
			verticalCollision(pos, size, vel, col);
		}
		else if (abs(vel.getX()) < abs(vel.getY())) { //Movimiento vertical
			horizontalCollision(pos, size, vel, col);
		}
		else { // El movimiento es justo hacia la esquina
			verticalCollision(pos, size, vel, col);
			horizontalCollision(pos, size, vel, col);
		}
	}
}

void CollisionsSystem::verticalCollision(Vector2D& pos, const Vector2D& size, const Vector2D& vel, const SDL_Rect& col)
{
	if (pos.getY() < col.y) pos.setY(pos.getY() - col.h); //Hay que subirlo
	else pos.setY(pos.getY() + col.h); // Hay que bajarlo
}

void CollisionsSystem::horizontalCollision(Vector2D& pos, const Vector2D& size, const Vector2D& vel, const SDL_Rect& col)
{
	if (pos.getX() < col.x)pos.setX(pos.getX() - col.w); //Hay que moverlo a la izda
	else pos.setX(pos.getX() + col.w); // Hay que moverlo a la dcha
}
