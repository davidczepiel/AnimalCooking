#include "LevelViewer.h"
#include "SDL_macros.h"
#include<string>
void LevelViewer::draw()
{
	timeSpan_ = SDLGame::instance()->getTime() - startedTick_;

	if (timeSpan_ >= levelTime_)
	{
		int lv = SDLGame::instance()->getCurrentLevel() - 1;
		string lvs = "level " + std::to_string(lv);
		Texture(SDLGame::instance()->getRenderer(), lvs,
			SDLGame::instance()->getFontMngr()->getFont(Resources::FontId::ARIAL12), hex2sdlcolor(
				"#FFFFFFFF")).render(RECT(
					SDLGame::instance()->getWindowWidth() - 3 * casilla,
					casilla * 3,
					2 * casilla,
					casilla), 7);
	}
	if (timeSpan_ >= scoreTime_)
		Texture(SDLGame::instance()->getRenderer(), std::to_string(SDLGame::instance()->getScore())+" points",
			SDLGame::instance()->getFontMngr()->getFont(Resources::FontId::ARIAL12), hex2sdlcolor(
				"#FFFFFFFF")).render(RECT(
					SDLGame::instance()->getWindowWidth() - 3.25 * casilla
					,
					casilla * 4,
					2 * casilla,
					casilla), 7);
	if (timeSpan_ >= barTime_) {
		int w = 10 * casilla;
		int h = casilla;
		barBackground->render(RECT(casilla, casilla, w, h));
		bar->render(RECT(casilla, casilla, scoreProgress_ * w, h));
		double osp = casilla + (oneStarPerc_ / 100) * w - casilla / 10;
		double tsp = casilla + (twoStarPerc_ / 100) * w - casilla / 10;
		double thsp = casilla + (threeStarPerc_ / 100) * w - casilla / 10;
		limitSign->render(RECT(osp, casilla, casilla / 10, casilla / 5));
		limitSign->render(RECT(tsp, casilla, casilla / 10, casilla / 5));
		limitSign->render(RECT(thsp, casilla, casilla / 10, casilla / 5));
		double starSize = casilla / 3;
		//casilla - casilla / 2.5 porque está en la y casilla y casilla/2.5 es la mitad de casilla/5
		if (scoreProgress_ * 100 >= oneStarPerc_)
			yellowStar->render(RECT(osp - starSize / 2, casilla - casilla / 2.5, starSize, starSize));
		else
			star->render(RECT(osp - starSize / 2, casilla - casilla / 2.5, starSize, starSize));
		
		//dos estrellas
		if (scoreProgress_ * 100 >= twoStarPerc_){
			yellowStar->render(RECT(tsp - starSize, casilla - casilla / 2.5, starSize, starSize));
			yellowStar->render(RECT(tsp, casilla - casilla / 2.5, starSize, starSize));

		}
		else
		{
			star->render(RECT(tsp - starSize, casilla - casilla / 2.5, starSize, starSize));
			star->render(RECT(tsp, casilla - casilla / 2.5, starSize, starSize));
		}
		
		//tres estrellas
		if (scoreProgress_ * 100 >= threeStarPerc_) {
			yellowStar->render(RECT(thsp - 3 * starSize / 2, casilla - casilla / 2.5, starSize, starSize));
			yellowStar->render(RECT(thsp - starSize / 2, casilla - casilla / 2.5, starSize, starSize));
			yellowStar->render(RECT(thsp + starSize / 2, casilla - casilla / 2.5, starSize, starSize));

		}
		else
		{
			star->render(RECT(thsp - 3 * starSize / 2, casilla - casilla / 2.5, starSize, starSize));
			star->render(RECT(thsp - starSize / 2, casilla - casilla / 2.5, starSize, starSize));
			star->render(RECT(thsp + starSize / 2, casilla - casilla / 2.5, starSize, starSize));
		}

	}

}

void LevelViewer::init()
{
	bar = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CuadradoAux);
	star = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Star);
	limitSign = SDLGame::instance()->getTextureMngr()->getTexture(Resources::LimitSign);
	barBackground = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RectangleOutline);
	casilla = SDLGame::instance()->getCasillaLength();
	yellowStar = SDLGame::instance()->getTextureMngr()->getTexture(Resources::YellowStar);
}

void LevelViewer::update()
{
	timeSpan_ = SDLGame::instance()->getTime() - startedTick_;
	if (timeSpan_ > barTime_&& scoreProgress_ < scorePercentage_)
		scoreProgress_ += .01;
}
