#pragma once
#include "Vector2D.h"
#include "SDL_rect.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

struct levelInfo {
	int level = -1;
	string name = "";
	string lore = "";	
	Vector2D housePosition = Vector2D();
	unsigned int stars = 0;
	bool unlocked = false;
};

class MapConfig {
public: 
	MapConfig(string fileN);
	MapConfig(string fileN, bool isNewGame);
	~MapConfig() {};

	void save();
	void load();

	inline const vector <levelInfo>& getLevelInfoRecipes() { return levelsRecipes_; }
	inline const int getMaxLevels() { return levelsRecipes_.size(); }
	vector<string>& getProfiles();

private:
	void fill();
	vector <levelInfo> levelsRecipes_;
	string fileName_ = "";
	bool newGame_;
};