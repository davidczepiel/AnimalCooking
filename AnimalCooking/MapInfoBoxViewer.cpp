#include "MapInfoBoxViewer.h"

MapInfoBoxViewer::MapInfoBoxViewer(double cX, double cY): Component(ecs::MapInfoBoxViewer),
	info_(),
	boxText_(nullptr),
	gotStar_(nullptr),
	notGotStar_(nullptr),
	casillaX_(cX),
	casillaY_(cY) {
		init();
}

MapInfoBoxViewer::~MapInfoBoxViewer()
{
}

void MapInfoBoxViewer::init()
{
	boxText_ = game_->getTextureMngr()->getTexture(Resources::MapStateInfoBox);
	gotStar_ = game_->getTextureMngr()->getTexture(Resources::YellowStar);
	notGotStar_ = game_->getTextureMngr()->getTexture(Resources::Star);
}

void MapInfoBoxViewer::draw()
{
}
