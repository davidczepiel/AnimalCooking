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
	//Confirmaci�n de que se puede limpiar y que est� sucio
	bool dirty_;
	bool ableToClean_;

	bool isInUse;
	//Mis 2 texturas
	Texture* texture_;
	Texture* secondTexture_;
	//Control animacion ataque
	int frameAttack;
	int lastFrameTick;
	bool attacking_;
	//Rect que se usa para calcular las colisiones entre la hitbox de un ataque y los ingredientes
	SDL_Rect interactionTrigger_;

	void onHit(Vector2D dir);
public:
	Utensil(Vector2D pos, Transport* p1, Transport* p2);
	virtual ~Utensil() {}
	void interactive() override { pickMe(); };

	virtual void render() const;
	virtual void update();
	virtual void attack(Vector2D dir) = 0;

	int getDirt() { return myDirt_; }
	void drop(bool suelo);
	void pickMe();
	void cleanUp();
	void changeDirtySpeed(int speedModifier);
	bool inUse() { return isInUse; }
	void setInUse(bool x) { isInUse = x; }

};

/////////////////////////////////////////////Utensilios//////////////////////////////

class Knife : public Utensil
{
public:
	Knife(Vector2D pos, Transport* p1, Transport* p2);
	~Knife() {}
	virtual void attack(Vector2D dir) {  onHit(dir); }

};

class Mace : public Utensil
{
public:
	Mace(Vector2D pos, Transport* p1, Transport* p2);
	~Mace() {}

	virtual void attack(Vector2D dir) {  onHit(dir); }


};


class Grater : public Utensil
{
public:
	Grater(Vector2D pos, Transport* p1, Transport* p2);
	~Grater() {}
	virtual void attack(Vector2D dir) {  onHit(dir); }

};

class Net : public Utensil
{
public:
	Net(Vector2D pos, Transport* p1, Transport* p2);
	~Net() {}
	virtual void attack(Vector2D dir) {  onHit(dir); }

};