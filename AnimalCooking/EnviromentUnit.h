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

class SlowUnit : public EnviromentUnit {
public:
	SlowUnit(Vector2D pos, double width, double height, Transform* tP1, Transform* tP2, PlayerController* pC1, PlayerController* pC2, EnviromentControl* envC);
private:
	virtual void act();
	virtual void update();


};

class SlipperyUnit: public EnviromentUnit {
public:
	SlipperyUnit(Vector2D pos, double width, double height, Transform* tP1, Transform* tP2, PlayerController* pC1, PlayerController* pC2, EnviromentControl* envC);
private:
	virtual void act();
	virtual void update();

	Vector2D p1Vel;
	Vector2D p2Vel;
};



class TextureUnit : public EnviromentUnit {
public:
	TextureUnit(Vector2D pos, double width, double height, EnviromentControl* envC, Texture* texture);
		
private:
	virtual void act() {};
	virtual void update () {};

};

