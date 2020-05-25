#include "ScoreManager.h"

void ScoreManager::addScore(int points)
{
	score_ += points; if (score_ < 0) score_ = 0;
	SDLGame::instance()->setScore(score_);
}

void ScoreManager::setScore(Uint32 value)
{
	if (value >= 0) {
		score_ = value;
		SDLGame::instance()->setScore(score_);
	}
}

void ScoreManager::setMaxScore(Uint32 mScore)
{
	if (mScore >= 0) {
		maxScore = mScore;
		SDLGame::instance()->setMaxScore(mScore);
	}
}
