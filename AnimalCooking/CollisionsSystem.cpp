#include "CollisionsSystem.h"
#include "Ingredient.h"

#define CHECK_DIFF_BODY(body, other) body.x != other.x && body.y != other.y && body.w != other.w && body.h != other.h
#define COLLIDES(body, other) Collisions::collides(Vector2D(body.x, body.y), body.w, body.h, Vector2D(other.x, other.y), other.w, other.h)

//Devuelve el SDL_Rect de un transform
#define GETBODY_TR(e) { e->getPos().getX(), e->getPos().getY(), e->getW(), e->getH() }

//Devuelve el SDL_Rect de un interactive
#define GETBODY_INT(e) { e->getPos().getX(), e->getPos().getY(), e->getSize().getX(), e->getSize().getY() }

//Devuelve el SDL_Rect de un ingrediente
#define GETBODY_ING(e) { e->getPos().getX(), e->getPos().getY(), e->getWidth(), e->getHeight() }

void CollisionsSystem::update()
{
	//Resolvemos las colisiones si el objeto es movible
	for (auto en : entidadesTr) {
		if(en.second) resolveCollisions(en.first);
	}

	for (auto en : entidadesInt) {
		if (en.second) resolveCollisions(en.first);
	}

	for (auto en : entidadesIng) {
		if (en.second) resolveCollisions(en.first);
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
}

void CollisionsSystem::checkCollision(SDL_Rect body, SDL_Rect other, list<SDL_Rect>& collisions)
{
	if (CHECK_DIFF_BODY(body, other) && COLLIDES(body, other)) { //Si es otro cuerpo y colisionan
		SDL_Rect colision_;
		SDL_IntersectRect(&body, &other, &colision_);
		collisions.push_back(colision_); //Se mete en la lista de colisiones
	}
}

void CollisionsSystem::resolveCollisions(Transform* tr)
{
	list<SDL_Rect> collisions_ = collisions(GETBODY_TR(tr));

	//Arregla la colision
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



	resolveCollisions(tr);
}

void CollisionsSystem::resolveCollisions(Interactive* in)
{
	list<SDL_Rect> collisions_ = collisions(GETBODY_INT(in));

	//Arregla la colision

	resolveCollisions(in);
}

void CollisionsSystem::resolveCollisions(Ingredient* in)
{
	list<SDL_Rect> collisions_ = collisions(GETBODY_ING(in));

	//Arregla la colision

	resolveCollisions(in);
}
