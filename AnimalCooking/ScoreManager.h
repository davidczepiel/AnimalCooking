#pragma once
#include "Component.h"
class ScoreManager : public Component
{
public:
	ScoreManager(Uint32 maxScore): Component(ecs::ScoreManager), 
		score_(0),maxScore(maxScore)
	{}

	inline Uint32 getScore() const { return score_; }
	inline Uint32 getMaxScore() const { return maxScore; }
	void addScore(int points) { 
		score_ += points; if (score_ < 0) score_ = 0; }
	void setScore(Uint32 value) {
		if(value>=0) score_ = value; }
	void resetScore() { score_ = 0; }
private:
	Uint32 score_;
	Uint32 maxScore;
};

