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
	static void newGameCallback(AnimalCooking* ac);
	static void loadGameCallback(AnimalCooking* ac);

	void draw() override;
	void update() override;

	void chooseOption();
	void askName();
	void init();
	void setState(bool firstTime);
	void saveGame();
	void hideChooseButtons();

	inline void setName(string n) { playerName_ = n; }
	inline void setCurrentLevel(int nl) { currentLevel_ = nl; }
	inline int getCurrentLevel() { return currentLevel_; }
	void activateNameAsker();
	inline void isNewGame() { isNewGame_ = true; }
	inline void isNotNewGame() { isNewGame_ = false; }

private:
	void configPadNavigation();

	SDLGame* game_;	
	Entity* newGameButton_;
	Entity* loadGameButton_;
	Entity* infoBox_;
	Entity* playButton_;
	Entity* returnButton_;
	Entity* chooser;
	Entity* nameAsker;
	vector <Entity*> levelButtonsPool_;
	ButtonPadNavigation* padNavigation_;

	Texture* bgText_;
	Texture* housesBackgroundText_; 
	Texture* playButtonText_;
	Texture* returnButtonText_;	

	std::string playerName_;
	int currentLevel_;
	int lastLevel_;
	int maxLevels_;	
	double casillaX;
	double casillaY;	
	bool hasToBreak = false;
	bool isNewGame_ = true;
	bool gameStarted = false;
};
