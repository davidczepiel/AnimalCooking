#pragma once
#include "State.h"
#include <vector>

struct levelInfo {
	string name = "";
	unsigned int stars = 0;
	string lore = "";
	SDL_Rect house;
	Vector2D housePosition = Vector2D();
	Vector2D buttonPosition = Vector2D();
};

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
};
