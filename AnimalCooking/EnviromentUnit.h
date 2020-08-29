#pragma once
#include "Texture.h"
#include "SDLGame.h"
#include "Transform.h"
#include "PlayerController.h"

class EnviromentUnit
{
public:
	EnviromentUnit(Vector2D pos, double width, double height,Transform* tP1, Transform* tP2,PlayerController* pC1, PlayerController* pC2);
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
	
};

class Snow : public EnviromentUnit {
public:
	Snow(Vector2D pos, double width, double height, Transform* tP1, Transform* tP2, PlayerController* pC1, PlayerController* pC2);
private:
	virtual void act();
	virtual void update();


};

