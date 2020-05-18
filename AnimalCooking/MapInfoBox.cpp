#include "MapInfoBox.h"

MapInfoBox::MapInfoBox(double cX, double cY) : Component(ecs::MapInfoBox), 
	info_(),
	boxText_(nullptr), 
	gotStar_(nullptr),
	notGotStar_(nullptr),
	casillaX_(cX), 
	casillaY_(cY){
		init();
}

void MapInfoBox::init()
{
	boxText_ = game_->getTextureMngr()->getTexture(Resources::MapStateInfoBox);
	gotStar_ = game_->getTextureMngr()->getTexture(Resources::YellowStar);
	notGotStar_ = game_->getTextureMngr()->getTexture(Resources::Star);
}

void MapInfoBox::draw()
{
}
