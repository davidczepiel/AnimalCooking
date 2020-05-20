#include "MapInfoBoxViewer.h"

MapInfoBoxViewer::MapInfoBoxViewer(): Component(ecs::MapInfoBoxViewer),
	info_(),
	boxText_(nullptr),
	gotStar_(nullptr),
	notGotStar_(nullptr),
	casillaX_(),
	casillaY_() {
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
	casillaX_ = game_->getCasillaX();
	casillaY_ = game_->getCasillaY();
}

void MapInfoBoxViewer::draw()
{
	boxText_->render(RECT(0, 0, casillaX_ * 3, casillaY_));
}
