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
	digits ++;

	SDL_Rect destRect = RECT(50, 50, 50*digits, 100);
	Texture score = Texture(game_->getRenderer(),"Score: " + to_string(scoreManager_->getScore()), (game_->getFontMngr()->getFont(Resources::ARIAL24)),
		{ COLOR(0x1111aaff) });
	score.render(destRect);
}
