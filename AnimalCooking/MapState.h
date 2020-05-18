#pragma once
#include "State.h"
#include "MapConfig.h"
#include <vector>


class MapState :public State{
public:
	MapState(AnimalCooking* ac);
	~MapState() { delete playButtonTexture; delete returnButtonTexture; }
	static void screenLoaderCallback(AnimalCooking* ac);
	static void backButtonCallback(AnimalCooking* ac);	
	void draw() override;
	void update() override;

	void addUnlockedLevelsInfo(struct levelInfo lvl);
	void fillUnlockedLevelsInfo(vector<levelInfo>* totalUnlockedLevelsInfo);
private:
	SDLGame* game_;

	vector<levelInfo>* unlockedLevelsInfo;

	Texture* backgroundTexture;
	Texture* housesBackgroundTexture; 
	Texture* houseButtonTexture;
	Texture* houseButtonOverTexture;
	Texture* playButtonTexture;
	Texture* returnButtonTexture;	
	Texture* infoBoxTexture;

	int unlockedLevels;
	int maxLevels;	
	vector<levelInfo> levels;
};
