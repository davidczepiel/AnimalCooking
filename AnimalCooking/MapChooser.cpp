#include "MapChooser.h"

MapChooser::MapChooser() : 
	Component(ecs::nameAsker), 
	active_(true), 
	bgText_(nullptr), 
	casillaX_(0), 
	casillaY_(0){
}

void MapChooser::draw()
{
	if (active_) {
		bgText_->render(RECT(casillaX_, casillaY_, 14 * casillaX_, 7 * casillaY_));		
	}
}

void MapChooser::init()
{
	bgText_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::MapChooserPannel);
	casillaX_ = SDLGame::instance()->getCasillaX();
	casillaY_ = SDLGame::instance()->getCasillaY();
}
