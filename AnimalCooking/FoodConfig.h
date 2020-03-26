#pragma once
#include "Resources.h"

// Transformations: Ingredient -> Normal food
struct utensilsTrans {
	Resources::IngredientType set;
	Resources::FoodType result;
};

struct utensilsRecipes {
	Resources::UtensilType utensils;
	vector <utensilsTrans> transformations;
};

// Transformations:  Normal Food -> Cooked Food
struct cookersTrans {
	vector <Resources::FoodType> set;
	Resources::FoodType result;
};

struct cookersRecipes {
	Resources::Cookers cookers;
	vector <cookersTrans> transformations;
};


class FoodConfig {
public:
	FoodConfig();
	~FoodConfig();

	const vector <cookersRecipes>& getCookersRecipes()  { return cookersRecipes_; };
	const vector <utensilsRecipes>& getUtensilsRecipes()  { return utensilsRecipes_; };

private:
	void fill();
	vector <cookersRecipes> cookersRecipes_;
	vector <utensilsRecipes> utensilsRecipes_;
};