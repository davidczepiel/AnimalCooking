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
	std::stack<int> digitsStack;

	while (auxPoints / 10 != 0) {
		digitsStack.push(auxPoints % 10);
		auxPoints = auxPoints / 10;
	}
	digitsStack.push(auxPoints);

	SDL_Rect destRect = RECT(50, 50, 100, 50);
	Texture score;
	for (int i = 0; i < digitsStack.size(); i++) {
		score = Texture(game_->getRenderer(), to_string(digitsStack.top()), (game_->getFontMngr()->getFont(Resources::ARIAL24)),
			{ COLOR(0x1111aaff) });
		
		destRect.x += 50;
		score.render(destRect);

		digitsStack.pop();
	}
}
