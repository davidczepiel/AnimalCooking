#pragma once
#include "Texture.h"
#include "SDLGame.h"
#include "Transform.h"
#include "PlayerController.h"
#include "EnviromentControl.h"

class EnviromentUnit
{
public:
	EnviromentUnit(Vector2D pos, double width, double height,Transform* tP1, Transform* tP2,PlayerController* pC1, PlayerController* pC2,EnviromentControl* envC);
	virtual void render() const;
	virtual void update()=0;
	virtual void act() = 0;

protected:
	Vector2D pos;
	double width;
	double height;
	Texture* texture;
	Transform* tP1;
	Transform* tP2;
	PlayerController* pC1;
	PlayerController* pC2;
	bool affectingP1;
	bool affectingP2;
	int playerAffectedNow;
	EnviromentControl* envC;
	
};

class Snow : public EnviromentUnit {
public:
	Snow(Vector2D pos, double width, double height, Transform* tP1, Transform* tP2, PlayerController* pC1, PlayerController* pC2, EnviromentControl* envC);
private:
	virtual void act();
	virtual void update();


};

class Ice : public EnviromentUnit {
public:
	Ice(Vector2D pos, double width, double height, Transform* tP1, Transform* tP2, PlayerController* pC1, PlayerController* pC2, EnviromentControl* envC);
private:
	virtual void act();
	virtual void update();
	bool alreadyEntered(Vector2D p, Vector2D v);
	Vector2D p1Pos;
	Vector2D p2Pos;
	Vector2D p1Vel;
	Vector2D p2Vel;

};

