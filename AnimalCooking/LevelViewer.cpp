#include "LevelViewer.h"
#include "SDL_macros.h"
#include<string>
LevelViewer::LevelViewer(int levelTime, int ScoreTime, int barTime, int oneStarPerc, int twoStarPerc, int threeStarPerc, double scorePercentage)
	: Component(ecs::levelViewer), bar(nullptr), limitSign(nullptr), star(nullptr), casillaX(0), casillaY(0), scoreProgress_(0)
	, barBackground(nullptr), yellowStar(nullptr), timeSpan_(0),
	startedTick_(SDLGame::instance()->getTime()),
	levelTime_(levelTime), scoreTime_(ScoreTime), barTime_(barTime), oneStarPerc_(oneStarPerc),
	twoStarPerc_(twoStarPerc), threeStarPerc_(threeStarPerc), scorePercentage_(scorePercentage) {
	if (scorePercentage_ > 1.0)
		scorePercentage_ = 1.0;
	int stars = 0;
	if (scorePercentage_ >= threeStarPerc_)
		stars = 3;
	else if (scorePercentage_ >= twoStarPerc_)
		stars = 2;
	else if (scorePercentage_ >= oneStarPerc_)
		stars = 1;
	SDLGame::instance()->addStarsPerLevel(stars, SDLGame::instance()->getCurrentLevel());
}

void LevelViewer::draw()
{
	timeSpan_ = SDLGame::instance()->getTime() - startedTick_;
	int winW = SDLGame::instance()->getWindowWidth();

	if (timeSpan_ >= levelTime_)
	{
		int lv = SDLGame::instance()->getCurrentLevel() + 1;
		string lvs = "level " + std::to_string(lv);
		Texture(SDLGame::instance()->getRenderer(), lvs,
			SDLGame::instance()->getFontMngr()->getFont(Resources::FontId::QuarkCheese100), hex2sdlcolor(
				"#FFFFFFFF")).render(RECT(
					winW - 3 * casillaX,
					casillaY * 3,
					2 * casillaX,
					casillaY), 7);
	}

	if (timeSpan_ >= scoreTime_)
		Texture(SDLGame::instance()->getRenderer(), std::to_string(SDLGame::instance()->getScore()) + " points",
			SDLGame::instance()->getFontMngr()->getFont(Resources::FontId::QuarkCheese100), hex2sdlcolor(
				"#FFFFFFFF")).render(RECT(
					winW - 3.25 * casillaX
					,
					casillaY * 4,
					2 * casillaX,
					casillaY), 7);

	if (timeSpan_ >= barTime_) {
		double w = barBackground->getWidth() * 1.8;
		int h= barBackground->getHeight() * 1.5;

		barBackground->render(RECT(casillaX, casillaY, w, h));
		//bar->render(RECT(casillaX, casillaY, scoreProgress_ * w, h));
		bar->render(RECT(casillaX, casillaY, scoreProgress_ * w, h), 0, RECT(0, 0, scoreProgress_ * w/ 1.8, h/ 1.5));
		double osp = casillaX + (oneStarPerc_ / 100) * w - casillaX / 10;
		double tsp = casillaX + (twoStarPerc_ / 100) * w - casillaX / 10;
		double thsp = casillaX + (threeStarPerc_ / 100) * w - casillaX / 10;

		limitSign->render(RECT(osp, casillaY, casillaX / 10, casillaY / 5));
		limitSign->render(RECT(tsp, casillaY, casillaX / 10, casillaY / 5));
		limitSign->render(RECT(thsp, casillaY, casillaX / 10, casillaY / 5));

		double starSizeX = casillaX / 2.5;
		double starSizeY = casillaY / 2.5;
		//casilla - casilla / 2.5 porque está en la y casilla y casilla/2.5 es la mitad de casilla/5
		if (scoreProgress_ * 100 >= oneStarPerc_)
			yellowStar->render(RECT(osp - starSizeX / 2, casillaY - casillaY / 2.5, starSizeX, starSizeY));
		else
			star->render(RECT(osp - starSizeX / 2, casillaY - casillaY / 2.5, starSizeX, starSizeY));

		//dos estrellas
		if (scoreProgress_ * 100 >= twoStarPerc_) {
			yellowStar->render(RECT(tsp - starSizeX, casillaY - casillaY / 2.5, starSizeX, starSizeY));
			yellowStar->render(RECT(tsp, casillaY - casillaY / 2.5, starSizeX, starSizeY));

		}
		else
		{
			star->render(RECT(tsp - starSizeX, casillaY - casillaY / 2.5, starSizeX, starSizeY));
			star->render(RECT(tsp, casillaY - casillaY / 2.5, starSizeX, starSizeY));
		}

		//tres estrellas
		if (scoreProgress_ * 100 >= threeStarPerc_) {
			yellowStar->render(RECT(thsp - 3 * starSizeX / 2, casillaY - casillaY / 2.5, starSizeX, starSizeY));
			yellowStar->render(RECT(thsp - starSizeX / 2, casillaY - casillaY / 2.5, starSizeX, starSizeY));
			yellowStar->render(RECT(thsp + starSizeX / 2, casillaY - casillaY / 2.5, starSizeX, starSizeY));

		}
		else
		{
			star->render(RECT(thsp - 3 * starSizeX / 2, casillaY - casillaY / 2.5, starSizeX, starSizeY));
			star->render(RECT(thsp - starSizeX / 2, casillaY - casillaY / 2.5, starSizeX, starSizeY));
			star->render(RECT(thsp + starSizeX / 2, casillaY - casillaY / 2.5, starSizeX, starSizeY));
		}

	}

}

void LevelViewer::init()
{
	bar = SDLGame::instance()->getTextureMngr()->getTexture(Resources::BarEndState);
	star = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Star);
	limitSign = SDLGame::instance()->getTextureMngr()->getTexture(Resources::LimitSign);
	barBackground = SDLGame::instance()->getTextureMngr()->getTexture(Resources::BarBackgroundEndState);
	casillaX = SDLGame::instance()->getCasillaX();
	casillaY = SDLGame::instance()->getCasillaY();
	yellowStar = SDLGame::instance()->getTextureMngr()->getTexture(Resources::YellowStar);
}

void LevelViewer::update()
{
	timeSpan_ = SDLGame::instance()->getTime() - startedTick_;
	if (timeSpan_ > barTime_&& scoreProgress_ < scorePercentage_)
		scoreProgress_ += .01;
}
