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
	SDL_Rect houseBox = SDL_Rect();
	Vector2D housePosition = Vector2D();
	Vector2D buttonPosition = Vector2D();
	unsigned int stars = 0;
	bool unlocked = false;
};

class MapConfig {
public: 
	MapConfig(string fileN);
	~MapConfig() {};

	void save();
	void load();

	const vector <levelInfo>& getLevelInfoRecipes() { return levelsRecipes_; }

private:
	void fill();
	vector <levelInfo> levelsRecipes_;
	string fileName_ = "";
};