#pragma once
#include "State.h"
#include "Entity.h"
#include <vector>
#include "NameAsker.h"

class MapLevel;
class MapPool;

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
	Entity* infoBox_;
	Entity* playButton_;
	Entity* returnButton_;
	Entity* padNavigation_;

	vector<MapLevel>* mapPool_;		//Estructura para representar la información en pantalla

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
