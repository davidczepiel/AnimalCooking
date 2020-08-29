#pragma once
#include "EnviromentUnit.h"
#include "Component.h"
#include "Transform.h"
#include "PlayerController.h"


class EnviromentPool: public Component
{

public:
	EnviromentPool(Transform* tF1, Transform* tF2, PlayerController* tP1, PlayerController* tP2);
	~EnviromentPool();
	void addEnvUnit(Vector2D pos,double width, double height,string type);
	vector<EnviromentUnit*>& getPool() { return pool_; }private:

private:
	void update() override;
	Transform* tF1;
	Transform* tF2;
	PlayerController* pC1;
	PlayerController* pC2;
	bool player1Affected;
	bool player2Affected;


	vector<EnviromentUnit*> pool_;
};

