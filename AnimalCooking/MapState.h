#pragma once
#include "State.h"
#include "Entity.h"
#include <vector>
#include "NameAsker.h"
#include "MapInfoBoxViewer.h"
#include "ButtonPadNavigation.h"
#include "ButtonRendererHouse.h"

class MapState :public State {
public:
	MapState(AnimalCooking* ac);
	~MapState();

	static void screenLoaderCallback(AnimalCooking* ac);
	static void backButtonCallback(AnimalCooking* ac);
	static void newGameCallback(AnimalCooking* ac);
	static void loadGameCallback(AnimalCooking* ac);
	static void nextScreenCallBack(AnimalCooking* ac);
	static void previousScreenCallBack(AnimalCooking* ac);

	void draw() override;
	void update() override;
	void chooseOption();
	void askName();
	void init();
	void setState();
	void hideChooseButtons();
	void prepareNavPadFewProfiles(bool many);
	void askProfile();
	void removeProfile(const string& name);

	inline void setName(const string& n) { playerName_ = n; game_->setName(n); }
	inline void setCurrentLevel(int nl) {
		currentLevel_ = nl;
		GETCMP2(playButton_, ButtonRendererHouse)->setLevel(levelinfos_->at(nl));
	}
	void nextScreen();
	void previousScreen();
	inline int getCurrentLevel() { return currentLevel_; }
	inline void isNewGame() { isNewGame_ = true; }
	inline void isNotNewGame() { isNewGame_ = false; }
	inline bool isCurrentLevelUnlocked() { return levelinfos_->at(currentLevel_)->unlocked; }

private:
	void configPadNavigation();
	void placeHousesAndButtons();
	void refreshHousesAndButtons();

	SDLGame* game_;
	Entity* newGameButton_;	
	Entity* loadGameButton_;
	Entity* infoBox_;
	Entity* playButton_;
	Entity* nextScreenButton_;
	Entity* PreviousScreenButton_;
	Entity* returnButton_;
	Entity* chooser;
	Entity* nameAsker;
	Entity* exit;

	vector <Entity*> profileAskers;
	vector <Texture*> profileTextures;
	vector <Entity*> levelButtonsPool_;
	vector<levelInfo*>* levelinfos_;
	Entity* pad;
	ButtonPadNavigation* padNavigation_;
	vector<Texture*> bgText_;
	Texture* playButtonText_;
	std::string playerName_;
	Texture* starScore_;
	Texture* starScoreBackground_;
	Texture* totalStars_;
	SDL_Rect starScoreRect_;
	SDL_Rect TotalStarsRect_;
	SDL_Rect starScoreBackGroundRect_;

	double casillaX;
	double casillaY;
	int currentLevel_;
	int lastLevel_;
	int maxLevels_;
	int levelPacks_;
	bool hasToBreak = false;
	bool isNewGame_ = true;
	bool gameStarted = false;
	bool inMap = false;

	bool transition_ = false;
	int xTransition_ = 0;
	float transitionVelocity_ = 40;
	int transitionDirection_ = 0;
	int currentMapScene_ = 0;
};
