#include "MapInfoBoxViewer.h"

MapInfoBoxViewer::MapInfoBoxViewer(Transform* buttonT) : Component(ecs::MapInfoBoxViewer),
	info_(),
	boxText_(nullptr),
	gotStar_(nullptr),
	notGotStar_(nullptr),
	buttonT(buttonT),
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

		vector<Texture*> loreLines;
		int size = 0;
		for (int i = 0; i < 3; i++)
		{
			Texture* line = new Texture(game_->getRenderer(), info_->lore[i], game_->getFontMngr()->getFont(Resources::QuarkCheese70), hex2sdlcolor("#FFFFFFFF"));
			loreLines.push_back(line);
			if (loreLines[i]->getWidth() > size) size = loreLines[i]->getWidth();
		}

		boxText_->render(RECT(40, 40, size + 60 , heightCasillas * casillaY_));

		buttonT->setPosX(size - 1.5 * casillaX_);

		for (int i = 0; i < 3; i++)
		{
			loreLines[i]->render(RECT(70 + size / 2 - loreLines[i]->getWidth() / 2, 60 + i * casillaY_ * lineaHeight, loreLines[i]->getWidth(), lineaHeight * casillaY_));
			delete loreLines[i]; loreLines[i] = nullptr;
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
