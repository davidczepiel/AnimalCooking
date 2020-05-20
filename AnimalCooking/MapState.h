#pragma once
#include "State.h"
#include "Entity.h"
#include <vector>
#include "NameAsker.h"
#include "MapInfoBoxViewer.h"
#include "ButtonPadNavigation.h"

class MapState :public State{
public:
	MapState(AnimalCooking* ac);
	~MapState();
	static void screenLoaderCallback(AnimalCooking* ac);
	static void backButtonCallback(AnimalCooking* ac);	
	void draw() override;
	void update() override;
	inline void setName(string n) { playerName_ = n; }
	inline void setCurrentLevel(int nl) { currentLevel_ = nl; }
	inline int getCurrentLevel() { return currentLevel_; }
	void init();
	void askName();
	void loadGame();
	void saveGame();

private:
	void configPadNavigation();
	SDLGame* game_;	
	Entity* infoBox_;
	Entity* playButton_;
	Entity* returnButton_;
	vector <Entity*> mapButtonsPool_;
	ButtonPadNavigation* padNavigation_;

	Texture* bgText_;
	Texture* housesBackgroundText_; 
	Texture* playButtonText_;
	Texture* returnButtonText_;	

	string playerName_;
	int currentLevel_;
	int lastLevel_;
	int maxLevels_;	
	double casillaX;
	double casillaY;	
	bool hasToBreak = false;
};
