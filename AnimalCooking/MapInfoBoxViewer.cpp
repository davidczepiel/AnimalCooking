#include "MapInfoBoxViewer.h"

MapInfoBoxViewer::MapInfoBoxViewer() : Component(ecs::MapInfoBoxViewer),
	info_(),
	boxText_(nullptr),
	gotStar_(nullptr),
	notGotStar_(nullptr),
	active(true),
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
		double heightCasillas = 3;
		//height casillas/6 porque es heightcasillas/2 (para que todo ocupe la mitad) /3(para que sean 3 líneas)
		double lineaHeight = heightCasillas / 6;
		boxText_->render(RECT(40, 40, casillaX_ * 7.5, heightCasillas * casillaY_));
		for (int i = 0; i < 3; i++)
		{
			Texture loreLineai = Texture(game_->getRenderer(), info_->lore[i], game_->getFontMngr()->getFont(Resources::QuarkCheese70), hex2sdlcolor("#FFFFFFFF"));
			loreLineai.render(RECT(60, 60 + i*casillaY_ * lineaHeight, casillaX_ * 7.5 - 60, lineaHeight * casillaY_));
		}
		switch (info_->stars)
		{
		case 0:
			notGotStar_->render(RECT(60, 2 * casillaY_ + 20, casillaX_, casillaY_));
			notGotStar_->render(RECT(60 + 1.1 * casillaX_, 2 * casillaY_ + 20, casillaX_, casillaY_));
			notGotStar_->render(RECT(60 + 2.2 * casillaX_, 2 * casillaY_ + 20, casillaX_, casillaY_));
			break;
		case 1:
			gotStar_->render(RECT(60, 2 * casillaY_ + 20, casillaX_, casillaY_));
			notGotStar_->render(RECT(60 + 1.1* casillaX_, 2 * casillaY_ + 20, casillaX_, casillaY_));
			notGotStar_->render(RECT(60 + 2.2 * casillaX_, 2 * casillaY_ + 20, casillaX_, casillaY_));
			break;
		case 2:
			gotStar_->render(RECT(60, 2 * casillaY_ + 20, casillaX_, casillaY_));
			gotStar_->render(RECT(60 + 1.1 * casillaX_, 2 * casillaY_ + 20, casillaX_, casillaY_));
			notGotStar_->render(RECT(60 + 2.2 * casillaX_, 2 * casillaY_ + 20, casillaX_, casillaY_));
			break;
		case 3:
			gotStar_->render(RECT(60, 2 * casillaY_ + 20, casillaX_, casillaY_));
			gotStar_->render(RECT(60 + 1.1 * casillaX_, 2 * casillaY_ + 20, casillaX_, casillaY_));
			gotStar_->render(RECT(60 + 2.2 * casillaX_, 2 * casillaY_ + 20, casillaX_, casillaY_));

			break;
		default:
			break;
		}
	}
}
