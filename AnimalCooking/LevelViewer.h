#pragma once
#include "Component.h"
class LevelViewer :
	public Component
{
public:
	LevelViewer(int levelTime, int ScoreTime, int barTime, int oneStarPerc, int twoStarPerc, int threeStarPerc,
		double scorePercentage);
	void draw() override;
	void init() override;
	void update() override;

private:
	Texture* bar;
	Texture* barBackground;
	Texture* limitSign;
	Texture* star;
	Texture* yellowStar;

	double scorePercentage_;
	double scoreProgress_;
	double oneStarPerc_;
	double twoStarPerc_;
	double threeStarPerc_;
	double casillaX;
	double casillaY;
	int startedTick_;
	int levelTime_;
	int scoreTime_;
	int barTime_;
	int timeSpan_;
};

