#pragma once
#include "Component.h"
class LevelViewer :
	public Component
{
public:
	LevelViewer(int levelTime, int ScoreTime, int barTime, int oneStarPerc, int twoStarPerc, int threeStarPerc,
		double scorePercentage) :
		Component(ecs::levelViewer), bar(nullptr), limitSign(nullptr), star(nullptr), casillaX(0),casillaY(0), scoreProgress_(0)
		,barBackground(nullptr),yellowStar(nullptr),timeSpan_(0),
		startedTick_(SDLGame::instance()->getTime()),
		levelTime_(levelTime), scoreTime_(ScoreTime), barTime_(barTime), oneStarPerc_(oneStarPerc),
		twoStarPerc_(twoStarPerc), threeStarPerc_(threeStarPerc), scorePercentage_(scorePercentage) {
		if (scorePercentage_ > 1.0)
			scorePercentage_ = 1.0;
	}
	void draw() override;
	void init() override;
	void update() override;
private:
	int startedTick_;
	int levelTime_;
	int scoreTime_;
	int barTime_;
	int timeSpan_;
	double scorePercentage_;
	double scoreProgress_;
	double oneStarPerc_;
	double twoStarPerc_;
	double threeStarPerc_;
	Texture* bar;
	Texture* barBackground;
	Texture* limitSign;
	Texture* star;
	Texture* yellowStar;
	double casillaX;
	double casillaY;

};

