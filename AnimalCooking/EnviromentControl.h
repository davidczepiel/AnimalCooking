#pragma once
#include "Component.h"
#include "Transform.h"
#include "PlayerController.h"
#include "Transform.h"

class EnviromentControl :
	public Component
{

public:
	EnviromentControl(PlayerController* p1, PlayerController* p2, Transform* p1T, Transform* p2T);
	~EnviromentControl() {}
	virtual void update();
	void enterIceZone(int player, Vector2D vel);
	void exitedIceZone(int p);
	double getPlayerForceX(int p);
	double getPlayerForceY(int p);
	void isThereForce();
	void playerIsMoving(int p, Vector2D v);
private:
	Vector2D p1Force;
	Vector2D p2Force;
	int p1NumBlocksStepping;
	int p2NumBlocksStepping;
	double accelerationIce;
	PlayerController* pC1;
	PlayerController* pC2;
	Transform* pT1;
	Transform* pT2;

};

