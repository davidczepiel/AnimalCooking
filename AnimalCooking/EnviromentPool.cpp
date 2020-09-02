#include "EnviromentPool.h"

EnviromentPool::EnviromentPool(Transform* tF1, Transform* tF2, PlayerController* pC1, PlayerController* pC2) :Component(ecs::EnviromentPool), pool_(), tF1(tF1), tF2(tF2), pC1(pC1), pC2(pC2)
{
	//envC=entity_->addComponent<EnviromentControl>();
	//envC = nullptr;
}

EnviromentPool::~EnviromentPool()
{
	for (EnviromentUnit* u : pool_) {
		delete u;
	}
}

void EnviromentPool::addEnvUnit(Vector2D pos, double width, double height,string type)
{
	if(envC == nullptr)	envC=entity_->addComponent<EnviromentControl>(pC1,pC2,tF1,tF2);

	if(type=="Nieve"){
		pool_.push_back(new Snow(pos, width, height, tF1, tF2, pC1, pC2,envC));
	}
	else if (type == "Hielo") {
		pool_.push_back(new Ice(pos, width, height, tF1, tF2, pC1, pC2,envC));
	}
}

void EnviromentPool::update()
{
	for (EnviromentUnit* u : pool_) {
		u->update();
	}
}

