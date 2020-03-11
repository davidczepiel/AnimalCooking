#pragma once
#include "Texture.h"
#include "Entity.h"
#include "Collisions.h"
#include "Transform.h"



class Utensil{

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

	Vector2D pos_, vel_, size_;
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

	void onHit(Vector2D dir);
public:
	Utensil(Vector2D pos,Transform* p);
	virtual ~Utensil() {}

	virtual void render() const;
	virtual void update();
	virtual void attack(Vector2D dir) = 0;

	Vector2D getPos() { return pos_; }
	Vector2D getVel() { return vel_; }
	Vector2D getSize() { return size_; }

	int getDirt() { return myDirt_; }
	void drop(bool suelo);
	void pickMe();
	void inTheWasher(bool x);
	void cleanUp();
	inline void setSize(double w, double h) { size_.set(w, h); }
	inline void setPos(Vector2D pos) { pos_.set(pos); }
	inline void setVel(Vector2D vel) { vel_.set(vel); }
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
	virtual void attack(Vector2D dir) {  onHit(dir); }
};

class Mace : public Utensil
{
public:
	Mace(Vector2D pos, Transform* p);
	~Mace() {}
	virtual void attack(Vector2D dir) {  onHit(dir); }
};


class Grater : public Utensil
{
public:
	Grater(Vector2D pos, Transform* p);
	~Grater() {}
	virtual void attack(Vector2D dir) {  onHit(dir); }
};

class Net : public Utensil
{
public:
	Net(Vector2D pos, Transform* p);
	~Net() {}
	virtual void attack(Vector2D dir) {  onHit(dir); }
};