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

void EnviromentPool::addEnvUnit(Vector2D pos, double width, double height,string type, string texture)
{
	if(envC == nullptr)	envC=entity_->addComponent<EnviromentControl>(pC1,pC2,tF1,tF2);

	if(type=="Slow"){
		pool_.push_back(new SlowUnit(pos, width, height, tF1, tF2, pC1, pC2,envC));
	}
	else if (type == "Resbalar") {
		pool_.push_back(new SlipperyUnit(pos, width, height, tF1, tF2, pC1, pC2,envC));
	}
	else pool_.push_back(new TextureUnit(pos, width, height, envC,selectTexture(texture)));	//Nieve sin colision
	
		
	
}

void EnviromentPool::update()
{
	for (EnviromentUnit* u : pool_) {
		u->update();
	}
}

Texture* EnviromentPool::selectTexture(string file)
{
	if (file == "islaPeq")				return game_->getTextureMngr()->getTexture(Resources::IslaPequenaNieve);
	else if (file == "islaGran")		return game_->getTextureMngr()->getTexture(Resources::IslaGrandeNieve);
	else if (file == "islaMdiana")		return game_->getTextureMngr()->getTexture(Resources::IslaMedianaNieve);
	else if (file == "nieve")			return game_->getTextureMngr()->getTexture(Resources::SoloNieve);
	else if (file == "hielo")			return game_->getTextureMngr()->getTexture(Resources::SoloHielo);
	else								return nullptr;
}

