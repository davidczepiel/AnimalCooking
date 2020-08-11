#pragma once
#include "Texture.h"
#include "Entity.h"
#include "Collisions.h"
#include "Transform.h"
#include "Transport.h"
#include "Pickable.h"
#include "GameConfig.h"
#include "Timer.h"
#include "Tool.h"

class GameLogic;
class Utensil : public Tool{

public:
	Utensil( Transport* p1, Transport* p2);
	virtual ~Utensil();

	void action1(int player) override;
	void feedback(int player) override;
	virtual void render() const;
	virtual void update();
	virtual void onDrop(bool onFloor) override;
	virtual void onPick() override;
	void cleanUp();
	void resetDirtTimer();

	int getTimeOnTheFloor() { return dirtTimer_->getTime(); }
	Timer* getTimer() { return dirtTimer_; }
	void changeDirtySpeed(int speedModifier);
	Resources::UtensilType getUtensilType() { return myType; }
	bool isDirty() { return dirty_; }

protected:
	
	void onHit(Vector2D dir);

	Resources::UtensilType myType;
	Timer* dirtTimer_;
	//Mis 2 texturas
	Texture* cleantexture_;
	Texture* dirtyTexture_;
	Texture* attackTexture_;

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
	virtual void attack(Vector2D dir) override {
		onHit(dir);	
	}

};

class Mace : public Utensil
{
public:
	Mace( Transport* p1, Transport* p2);
	~Mace() {}

	virtual void attack(Vector2D dir) override{
		onHit(dir);	
	}
};


class Grater : public Utensil
{
public:
	Grater( Transport* p1, Transport* p2);
	~Grater() {}
	virtual void attack(Vector2D dir) override { 
		onHit(dir); 
	}
};

class Net : public Utensil
{
public:
	Net( Transport* p1, Transport* p2);
	~Net() {}
	virtual void attack(Vector2D dir) override { 
		onHit(dir); 
	}
};