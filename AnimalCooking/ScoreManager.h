#pragma once
#include "Component.h"
class ScoreManager : public Component
{
public:
	ScoreManager() : Component(ecs::ScoreManager),
		score_(0), maxScore(0)
	{}

	inline Uint32 getScore() const { return score_; }
	inline Uint32 getMaxScore() const { return maxScore; }
	void addScore(int points);
	void setScore(Uint32 value);
	void setMaxScore(Uint32 mScore);
	void resetScore() {
		score_ = 0;
		SDLGame::instance()->setScore(0);
	}
private:
	Uint32 score_;
	Uint32 maxScore;
};

