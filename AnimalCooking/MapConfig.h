#pragma once
#include "Vector2D.h"
#include "SDL_rect.h"
#include <vector>

struct levelInfo {
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
	MapConfig();
	~MapConfig() {};

	void save(string filename);
	void load(string filename);

	const vector <levelInfo>& getLevelInfoRecipes() { return levelsRecipes; }

private:
	void fill();
	vector <levelInfo> levelsRecipes;

};