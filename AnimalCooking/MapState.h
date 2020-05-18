#pragma once
#include "State.h"
#include "MapConfig.h"
#include <vector>


class MapState :public State{
public:
	MapState(AnimalCooking* ac);
	~MapState() {}
	static void screenLoaderCallback(AnimalCooking* ac);
	static void backButtonCallback(AnimalCooking* ac);	
	void draw() override;
	void update() override;
	void askName();
	void loadGame();
private:
	SDLGame* game_;

	vector<levelInfo> levelsInfo;

	Texture* backgroundTexture;
	Texture* housesBackgroundTexture; 
	Texture* houseButtonTexture;
	Texture* houseButtonOverTexture;
	Texture* playButtonTexture;
	Texture* returnButtonTexture;	
	Texture* infoBoxTexture;

	string playerName;
	int unlockedLevels;
	int maxLevels;		
};
