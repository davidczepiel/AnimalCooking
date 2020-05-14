#pragma once
#include "State.h"
#include <vector>

struct levelInfo {
	string name = "";
	unsigned int stars = 0;
	string lore = "";
	Vector2D housePosition = Vector2D();
	Vector2D buttonPosition = Vector2D();
};

class MapState :public State{
public:
	MapState(AnimalCooking* ac);
	~MapState() { delete jugarText; delete volverText; }
	static void screenLoaderCallback(AnimalCooking* ac);
	static void backButtonCallback(AnimalCooking* ac);
	void setLevelInfo(struct levelInfo lvl);
private:
	SDLGame* game_;

	vector<levelInfo>* unlockedLevelsInfo;

	Texture* jugarText;
	Texture* volverText;
	Texture* background;
	Texture* houseButtonTexture;

	int unlockedLevels;
	int maxLevels;	
};