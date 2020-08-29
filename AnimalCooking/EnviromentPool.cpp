#include "EnviromentPool.h"

EnviromentPool::EnviromentPool(Transform* tF1, Transform* tF2, PlayerController* pC1, PlayerController* pC2) :Component(ecs::EnviromentPool), pool_(), tF1(tF1), tF2(tF2), pC1(pC1), pC2(pC2)
, player1Affected(false), player2Affected(false)
{

}

EnviromentPool::~EnviromentPool()
{
	for (EnviromentUnit* u : pool_) {
		delete u;
	}
}

void EnviromentPool::addEnvUnit(Vector2D pos, double width, double height,string type)
{
	if(type=="Nieve"){
		pool_.push_back(new Snow(pos, width, height, tF1, tF2, pC1, pC2));
	}
}

void EnviromentPool::update()
{
	for (EnviromentUnit* u : pool_) {
		u->update();
	}
}

