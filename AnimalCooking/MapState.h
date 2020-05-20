#pragma once
#include "State.h"
#include "MapConfig.h"
#include <vector>
#include "NameAsker.h"

class MapLevel;

class MapState :public State{
public:
	MapState(AnimalCooking* ac);
	~MapState();
	static void screenLoaderCallback(AnimalCooking* ac);
	static void backButtonCallback(AnimalCooking* ac);	
	void draw() override;
	void update() override;
	inline void setName(string n) { playerName_ = n; }

	void init();
	void askName();
	void loadGame();

private:
	SDLGame* game_;
	vector <Entity*> levelsEntityList_;		//Referencias a todos los niveles incluidos en el mapstate para actualizar infobox y para saber cual hay que lanzar cuando se de a jugar
	Entity* infoBox_;
	Entity* playButton_;
	Entity* returnButton_;
	Entity* padNavigation_;

	vector<levelInfo> levelsInfo_;	//Total de informaci�n de cada nivel incluido en el mapstate
	vector<MapLevel>* mapPool_;

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
};
