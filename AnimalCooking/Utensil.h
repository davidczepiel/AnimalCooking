#pragma once
#include "Texture.h"
#include "Entity.h"
#include "Collisions.h"
#include "Transform.h"
#include "Transport.h"
#include "Pickable.h"
#include "GameConfig.h"
#include "Timer.h"

class GameLogic;
class Utensil : public Pickable{

public:
	Utensil( Transport* p1, Transport* p2);
	virtual ~Utensil();

	void action1(int player) override;
	void feedback(int player) override;
	virtual void render() const;
	virtual void update();
	virtual void attack(Vector2D dir) = 0;
	virtual void onDrop(bool onFloor);
	virtual void onPick();
	void cleanUp();
	void resetDirtTimer();

	int getTimeOnTheFloor() { return dirtTimer_->getTime(); }
	Timer* getTimer() { return dirtTimer_; }
	void changeDirtySpeed(int speedModifier);
	void setGameLogic(GameLogic* glc) {	gameLogic = glc;}
	Resources::UtensilType getUtensilType() { return myType; }
	bool isDirty() { return dirty_; }

protected:
	//Estado
	enum  State
	{
		floor, playerHand, shelf
	};
	void onHit(Vector2D dir);

	Resources::UtensilType myType;
	State myState;
	Timer* dirtTimer_;
	//Mis 2 texturas
	Texture* cleantexture_;
	Texture* dirtyTexture_;
	Texture* attackTexture_;
	//Rect que se usa para calcular las colisiones entre la hitbox de un ataque y los ingredientes
	GameLogic* gameLogic;

	//Suciedad
	int myDirt_;
	int maxDirt_;
	int maxTimeOnFloor_;
	//Ataque
	int rangeX_;
	int rangeY_;
	int attackHitBoxWidth_;
	int attackHitBoxHeight_;
	int attackRate_;
	int lastAttack_;
	//Confirmaci�n de que esta  sucio
	bool dirty_;
	//Control animacion ataque
	int frameAttack;
	int lastFrameTick;
	bool attacking_;
};

/////////////////////////////////////////////Utensilios//////////////////////////////

class Knife : public Utensil
{
public:
	Knife( Transport* p1, Transport* p2);
	~Knife() {}
	virtual void attack(Vector2D dir) {
		onHit(dir);	}

};

class Mace : public Utensil
{
public:
	Mace( Transport* p1, Transport* p2);
	~Mace() {}

	virtual void attack(Vector2D dir) {  onHit(dir);	}


};


class Grater : public Utensil
{
public:
	Grater( Transport* p1, Transport* p2);
	~Grater() {}
	virtual void attack(Vector2D dir) {  onHit(dir); }

};

class Net : public Utensil
{
public:
	Net( Transport* p1, Transport* p2);
	~Net() {}
	virtual void attack(Vector2D dir) {  onHit(dir); }

};