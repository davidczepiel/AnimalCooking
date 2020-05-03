#pragma once
#include "Component.h"
class LevelViewer :
	public Component
{
public:
	LevelViewer(int levelTime,int ScoreTime,int barTime,int oneStarPerc, int twoStarPerc, int threeStarPerc):
		Component(ecs::levelViewer),startedTick(SDLGame::instance()->getTime()),
	levelTime(levelTime),scoreTime(ScoreTime),barTime(barTime), oneStarPerc(oneStarPerc),
		twoStarPerc(twoStarPerc), threeStarPerc(threeStarPerc){}
	void draw() override;
	void init() override;
private:
	int startedTick;
	int levelTime;
	int scoreTime;
	int barTime;
	double oneStarPerc;
	double twoStarPerc;
	double threeStarPerc;
	Texture* bar;
	Texture* limitSign;
	Texture* star;
	double casilla;
};

