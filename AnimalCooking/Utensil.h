#pragma once
#include "Texture.h"
#include "Entity.h"
#include "Collisions.h"
#include "Transform.h"
#include "Pickable.h"


class Utensil : public Pickable{

protected:
	//Estado
	enum  State
	{
		floor, playerHand, shelf, sink
	};
	Resources::UtensilType myType;
	State myState;
	//Suciedad
	int myDirt_;
	int maxDirt_;
	int getDirtSpeed_;
	//Limpieza
	int cleanUpSpeed_;
	//Ataque
	int range_;
	int attackHitBoxWidth_;
	int attackHitBoxHeight_;
	int attackRate_;
	int lastAttack_;
	//Confirmación de que se puede limpiar y que está sucio
	bool dirty_;
	bool ableToClean_;

	bool isInUse;

	Transform* player_;
	//Mis 2 texturas
	Texture* texture_;
	Texture* secondTexture_;
	//Control animación ataque
	int frameAttack;
	int lastFrameTick;
	bool attacking_;
	//Rect que se usará para calcular las colisiones entre la hitbox de un ataque y los ingredientes
	SDL_Rect interactionTrigger_;

	Entity* onHit(Vector2D dir);
public:
	Utensil(Vector2D pos,Transform* p);
	virtual ~Utensil() {}

	virtual void render() const;
	virtual void update();
	virtual void attack() = 0;

	int getDirt() { return myDirt_; }
	void drop(bool suelo);
	void pickMe();
	void inTheWasher(bool x);
	void cleanUp();
	void changeDirtySpeed(int speedModifier);
	bool inUse() { return isInUse; }
	void setInUse(bool x) { isInUse = x; }

};

/////////////////////////////////////////////Utensilios//////////////////////////////

class Knife : public Utensil
{
public:
	Knife(Vector2D pos, Transform* p);
	~Knife() {}
	virtual void attack() { Entity* e = onHit(Vector2D(1, 1)); }// if (e != nullptr) static_cast<Ingredient>(e)->attacked(myType);
};

class Mace : public Utensil
{
public:
	Mace(Vector2D pos, Transform* p);
	~Mace() {}
	virtual void attack() { Entity* e = onHit(Vector2D(1, 1)); }// if (e != nullptr) static_cast<Ingredient>(e)->attacked(myType);
};


class Grater : public Utensil
{
public:
	Grater(Vector2D pos, Transform* p);
	~Grater() {}
	virtual void attack() { Entity* e = onHit(Vector2D(1, 1)); }// if (e != nullptr) static_cast<Ingredient>(e)->attacked(myType);
};

class Net : public Utensil
{
public:
	Net(Vector2D pos, Transform* p);
	~Net() {}
	virtual void attack() { Entity* e = onHit(Vector2D(1, 1)); }// if (e != nullptr) static_cast<Ingredient>(e)->attacked(myType);
};