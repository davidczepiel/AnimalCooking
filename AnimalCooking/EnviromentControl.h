#pragma once
#include "Component.h"
#include "Transform.h"
#include "PlayerController.h"

class EnviromentControl :
	public Component
{

public:
	EnviromentControl();
	~EnviromentControl() {}
	virtual void update();
	void enterIceZone(int player, Vector2D vel);
	double getPlayerForceX(int p);
	double getPlayerForceY(int p);
	void isThereForce();
	void playerIsMoving(int p, Vector2D v);
private:
	Vector2D p1Force;
	Vector2D p2Force;
	double lastP1Entered;
	double lastP2Entered;
	double accelerationIce;

};

