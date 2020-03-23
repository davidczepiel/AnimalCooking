#pragma once
#include "Resources.h"

// Transform: Ingredient -> Normal food
struct f1 {
	Resources::IngredientType set;
	Resources::FoodType result;
};

struct foodKilled {
	Resources::UtensilType utensils;
	vector <f1> transformations;
};

// Transform:  Normal Food -> Cooked Food
struct f2 {
	vector <Resources::FoodType> set;
	Resources::FoodType result;
};

struct foodCooked {
	Resources::Cookers cookers;
	vector <f2> transformations;
};


class FoodConfig {
public:
	FoodConfig();
	~FoodConfig();
	const vector <foodCooked>& getFoodCooked()  { return foodCooked_; };
	const vector <foodKilled>& getFoodKilled()  { return foodKilled_; };

private:
	void fill();
	vector <foodCooked> foodCooked_;
	vector <foodKilled> foodKilled_;
};