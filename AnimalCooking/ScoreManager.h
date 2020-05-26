#pragma once
#include "Component.h"
class ScoreManager : public Component
{
public:
	ScoreManager() : Component(ecs::ScoreManager),
		score_(0), maxScore(0)
	{}
	void resetScore() {
		score_ = 0;
		SDLGame::instance()->setScore(0);
	}
	void addScore(int points);

	inline Uint32 getScore() const { return score_; }
	inline Uint32 getMaxScore() const { return maxScore; }	
	void setScore(Uint32 value);
	void setMaxScore(Uint32 mScore);
	
private:
	Uint32 score_;
	Uint32 maxScore;
};

