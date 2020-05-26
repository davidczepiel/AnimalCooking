#include "ScoreViewer.h"
#include "Entity.h"
#include "SDL_macros.h"
#include <stack>

void ScoreViewer::init()
{
	scoreManager_ = GETCMP1_(ScoreManager);
}

void ScoreViewer::draw()
{
	int auxPoints = scoreManager_->getScore();
	int digits = 0;

	while (auxPoints / 10 != 0) {
		digits++;
		auxPoints = auxPoints / 10;
	}
	digits++;


	Texture score = Texture(game_->getRenderer(), to_string(scoreManager_->getScore()), (game_->getFontMngr()->getFont(Resources::QuarkCheese100)),
		{ COLOR(0x000000ff) });
	SDL_Rect destRect = RECT(pos_.getX(), pos_.getY(), score.getWidth(), score.getHeight());
	score.render(destRect);
}
