#include "CollisionsSystem.h"
#include "Ingredient.h"
#include "Transform.h"
#include "Interactive.h"
#include "SDL_macros.h"
#include "Collisions.h"

#define CHECK_DIFF_BODY(body, other) (body.x != other.x || body.y != other.y || body.w != other.w || body.h != other.h)
#define COLLIDES(body, other) (Collisions::collides(Vector2D(body.x, body.y), body.w, body.h, Vector2D(other.x, other.y), other.w, other.h))

//Devuelve el SDL_Rect de un transform
#define GETBODY_TR(e) RECT(e->getPos().getX(), e->getPos().getY(), e->getW(), e->getH())

//Devuelve el SDL_Rect de un interactive
#define GETBODY_INT(e) RECT(e->getPos().getX(), e->getPos().getY(), e->getSize().getX(), e->getSize().getY())

//Devuelve el SDL_Rect de un ingrediente
#define GETBODY_ING(e) RECT(e->getPos().getX(), e->getPos().getY(), e->getWidth(), e->getHeight())

//Calcula el �rea de un SDL_Rect
#define AREA(rect) rect.w * rect.h

#define DIVIDEROUNDUP(x) (collisions.back().x / 2) + (collisions.back().x % 2 != 0)

void CollisionsSystem::update()
{
	//Resolvemos las colisiones si el objeto es movible
	for (auto en : entidadesTr) {
		if(en.second) resolveCollisions(en.first->getPosReference(), Vector2D(en.first->getW(), en.first->getH()), en.first->getVel());
	}

	for (auto en : entidadesIng) {
		if (en.second){
			ColisionType cT = resolveCollisions(en.first->getPosReference(), Vector2D(en.first->getWidth(), en.first->getHeight()), en.first->getVel()); 
			
			//Aviso al ingrediente que ha colisionado
			tellIngredient(en.first, cT);
		}
	}
}

list<SDL_Rect> CollisionsSystem::collisions(SDL_Rect body)
{
	list<SDL_Rect> collisions;
	for (auto en : entidadesTr) {
		//Si choca con algo, y es movible, mueve ese objeto la mitad que le corresponde
		if (checkCollision(body, GETBODY_TR(en.first), collisions) && en.second) {
			SDL_Rect col = RECT(collisions.back().x, collisions.back().y, DIVIDEROUNDUP(w), DIVIDEROUNDUP(h));
			singleCollision(en.first->getPosReference(), Vector2D(en.first->getW(), en.first->getH()), en.first->getVel(), col);
			changeBackCol(collisions, col);
		}
	}

	for (auto en : entidadesInt) {
		checkCollision(body, GETBODY_INT(en.first), collisions);
	}

	for (auto en : entidadesIng) {
		//Si choca con algo, y es movible, mueve ese objeto la mitad que le corresponde
		if (checkCollision(body, GETBODY_ING(en.first), collisions) && en.second) {
			SDL_Rect col = RECT(collisions.back().x, collisions.back().y, DIVIDEROUNDUP(w), DIVIDEROUNDUP(h));
			ColisionType cT = singleCollision(en.first->getPosReference(), Vector2D(en.first->getWidth(), en.first->getHeight()), en.first->getVel(), col);
			changeBackCol(collisions, col);
			
			//Aviso al ingrediente que ha colisionado
			//tellIngredient(en.first, cT);
		}
	}

	return collisions;
}

void CollisionsSystem::changeBackCol(std::list<SDL_Rect>& collisions, const SDL_Rect& col)
{
	collisions.pop_back();
	collisions.push_back(col);
}

bool CollisionsSystem::checkCollision(const SDL_Rect& body, const SDL_Rect& other, list<SDL_Rect>& collisions)
{
	if (CHECK_DIFF_BODY(body, other) && COLLIDES(body, other)) { //Si es otro cuerpo y colisionan
		SDL_Rect colision_;
		SDL_IntersectRect(&body, &other, &colision_);
		collisions.push_back(colision_); //Se mete en la lista de colisiones
		return true;
	}
	else return false;
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

ColisionType CollisionsSystem::resolveCollisions(Vector2D& pos, const Vector2D& size, const Vector2D& vel)
{
	list<SDL_Rect> collisions_ = collisions(RECT(pos.getX(), pos.getY(), size.getX(), size.getY()));
	ColisionType cT = ColisionType::noColision;

	//Check de colisiones con los bordes del mundo
	if (pos.getX() < 0)
		cT = singleCollision(pos, size, vel, RECT(pos.getX(), pos.getY(), ceil(-pos.getX()), size.getY()));
	else if (pos.getX() + size.getX() > game_->getWindowWidth())
		cT = singleCollision(pos, size, vel, RECT(game_->getWindowWidth(), pos.getY(), ceil(pos.getX() + size.getX() - game_->getWindowWidth()), size.getY()));
	if (pos.getY() < 0)
		cT = singleCollision(pos, size, vel, RECT(pos.getX(), pos.getY(), size.getX(), ceil(-pos.getY())));
	else if (pos.getY() + size.getY() > game_->getWindowHeight())
		cT = singleCollision(pos, size, vel, RECT(pos.getX(), game_->getWindowHeight(), size.getX(), ceil(pos.getY() + size.getY() - game_->getWindowHeight())));

	if (!collisions_.empty()) {
		if (collisions_.size() == 1) {
			cT = singleCollision(pos, size, vel, collisions_.front());
		}
		else if (collisions_.size() == 2) {
			SDL_Rect col1 = collisions_.front(), col2 = collisions_.back();
			//se prioriza el de mayor area
			if (AREA(col1) > AREA(col2)) {
				cT = singleCollision(pos, size, vel, col1);
			}
			else if (AREA(col1) < AREA(col2)) {
				cT = singleCollision(pos, size, vel, col2);
			}
			else { //Ambas areas son iguales
				if (col1.x == col2.x) { //Los rectangulos estan alineados en vertical
					col1.h += col2.h;
					cT = singleCollision(pos, size, vel, col1);
				}
				else if (col1.y == col2.y) { //Los rectangulos estan alineados en horizontal
					col1.w += col2.w;
					cT = singleCollision(pos, size, vel, col1);
				}
				else {
					if (vel.getX() < 0) { //Se mueve hacia la izda
						if (vel.getY() < 0) pos = Vector2D(pos.getX() + col1.w, pos.getY() + col1.h); //arriba a la izda
						else pos = Vector2D(pos.getX() + col1.w, pos.getY() - col1.h); //abajo a la izda
						cT = ColisionType::horizontal;
					}
					else { //Se mueve hacia la dcha
						if (vel.getY() < 0) pos = Vector2D(pos.getX() - col1.w, pos.getY() + col1.h); //arriba a la dcha
						else pos = Vector2D(pos.getX() - col1.w, pos.getY() - col1.h); //abajo a la dcha
						cT = ColisionType::vertical;
					}
				}
			}
		}
		else { //Choca con 3 objetos a la vez
			SDL_Rect col1, col2, col3;
			col1 = collisions_.front();
			collisions_.pop_front();
			col2 = collisions_.front();
			col3 = collisions_.back();

			if (col1.x == col2.x) { //Los rectangulos estan alineados en vertical
				col1.h += col2.h;
				cT = singleCollision(pos, size, vel, col1);
			}
			else if (col1.y == col2.y) { //Los rectangulos estan alineados en horizontal
				col1.w += col2.w;
				cT = singleCollision(pos, size, vel, col1);
			}
			else {
				if (col1.x == col3.x) { //Los rectangulos estan alineados en vertical
					col1.h += col3.h;
					cT = singleCollision(pos, size, vel, col1);
				}
				else if (col1.y == col3.y) { //Los rectangulos estan alineados en horizontal
					col1.w += col3.w;
					cT = singleCollision(pos, size, vel, col1);
				}
			}
		}
		//resolveCollisions(pos, size, vel);	
	}
	return cT;
}

ColisionType CollisionsSystem::singleCollision(Vector2D& pos, const Vector2D& size, const Vector2D& vel, const SDL_Rect& col)
{
	if (col.w - col.h > flexibility) { //Colision Vertical
		verticalCollision(pos, size, vel, col);
		return ColisionType::vertical;
	}
	else if (col.w - col.h < -flexibility) { //Colision horizontal
		horizontalCollision(pos, size, vel, col);
		return ColisionType::horizontal;
	}
	else { //Colision en esquina-->Check de la velocidad
		if (abs(vel.getX()) > abs(vel.getY())) { //Movimiento horizontal
			verticalCollision(pos, size, vel, col);
			return ColisionType::vertical;
		}
		else if (abs(vel.getX()) < abs(vel.getY())) { //Movimiento vertical
			horizontalCollision(pos, size, vel, col);
			return ColisionType::horizontal;
		}
		else { // El movimiento es justo hacia la esquina
			verticalCollision(pos, size, vel, col);
			horizontalCollision(pos, size, vel, col);
			return ColisionType::both;
		}
	}
}

void CollisionsSystem::verticalCollision(Vector2D& pos, const Vector2D& size, const Vector2D& vel, const SDL_Rect& col)
{
	if ((int)pos.getY() < col.y) pos.setY(pos.getY() - col.h); //Hay que subirlo
	else pos.setY(pos.getY() + col.h); // Hay que bajarlo
}

void CollisionsSystem::horizontalCollision(Vector2D& pos, const Vector2D& size, const Vector2D& vel, const SDL_Rect& col)
{
	if ((int)pos.getX() < col.x)pos.setX(pos.getX() - col.w); //Hay que moverlo a la izda
	else pos.setX(pos.getX() + col.w); // Hay que moverlo a la dcha
}

void CollisionsSystem::tellIngredient(Ingredient* en, const ColisionType& colType)
{
	if (colType != ColisionType::noColision) {
		if (colType == ColisionType::horizontal) en->onCollisionX();
		else if (colType == ColisionType::vertical) en->onCollisionY();
		else if (colType == ColisionType::both) {
			en->onCollisionX();
			en->onCollisionY();
		}
	}	
}
