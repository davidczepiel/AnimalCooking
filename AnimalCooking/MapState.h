#pragma once
#include "State.h"
#include "Entity.h"
#include <vector>
#include "NameAsker.h"
#include "MapInfoBoxViewer.h"
#include "ButtonPadNavigation.h"

class MapState :public State {
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
	void setState();
	void hideChooseButtons();
	void prepareNavPadFewProfiles(bool many);

	inline void setName(const string& n) { playerName_ = n; game_->setName(n); }
	inline void setCurrentLevel(int nl) { currentLevel_ = nl; }
	inline int getCurrentLevel() { return currentLevel_; }
	inline void isNewGame() { isNewGame_ = true; }
	inline void isNotNewGame() { isNewGame_ = false; }
	inline bool isCurrentLevelUnlocked() { return levelinfos_.at(currentLevel_).unlocked; }

	void askProfile();
	void removeProfile(const string& name);

private:
	void configPadNavigation();

	void placeHousesAndButtons();

	SDLGame* game_;
	Entity* newGameButton_;
	Entity* loadGameButton_;
	Entity* infoBox_;
	Entity* playButton_;
	Entity* returnButton_;
	Entity* chooser;
	Entity* nameAsker;
	Entity* exit;
	vector <Entity*> profileAskers;
	vector <Texture*> profileTextures;
	vector <Entity*> levelButtonsPool_;
	vector<levelInfo> levelinfos_;
	Entity* pad;
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
