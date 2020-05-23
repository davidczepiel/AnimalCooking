#include "MapInfoBoxViewer.h"

MapInfoBoxViewer::MapInfoBoxViewer() : Component(ecs::MapInfoBoxViewer),
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
	if (active) {
		boxText_->render(RECT(40, 40, casillaX_ * 6, 3 * casillaY_));
		info_.lore;
		Texture lore = Texture(game_->getRenderer(), info_.lore, game_->getFontMngr()->getFont(Resources::QuarkCheese50), hex2sdlcolor("#000000FF"));
		//lore.render()
		switch (info_.stars)
		{
		case 0:
			notGotStar_->render(RECT(40, 1.5 * casillaY_, casillaX_, casillaY_));
			notGotStar_->render(RECT(40 + 1.1 * casillaX_, 1.5 * casillaY_, casillaX_, casillaY_));
			notGotStar_->render(RECT(40 + 2.2 * casillaX_, 1.5 * casillaY_, casillaX_, casillaY_));
			break;
		case 1:
			gotStar_->render(RECT(40 , 1.5 * casillaY_, casillaX_, casillaY_));
			notGotStar_->render(RECT(40 + 1.1* casillaX_, 1.5 * casillaY_, casillaX_, casillaY_));
			notGotStar_->render(RECT(40 + 2.2 * casillaX_, 1.5 * casillaY_, casillaX_, casillaY_));
			break;
		case 2:
			gotStar_->render(RECT(40, 1.5 * casillaY_, casillaX_, casillaY_));
			gotStar_->render(RECT(40 + 1.1 * casillaX_, 1.5 * casillaY_, casillaX_, casillaY_));
			notGotStar_->render(RECT(40 + 2.2 * casillaX_, 1.5 * casillaY_, casillaX_, casillaY_));
			break;
		case 3:
			gotStar_->render(RECT(40, 1.5 * casillaY_, casillaX_, casillaY_));
			gotStar_->render(RECT(40 + 1.1 * casillaX_, 1.5 * casillaY_, casillaX_, casillaY_));
			gotStar_->render(RECT(40 + 2.2 * casillaX_, 1.5 * casillaY_, casillaX_, casillaY_));

			break;
		default:
			break;
		}
	}
}
