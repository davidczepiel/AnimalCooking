#include "FoodDictionary.h"

unique_ptr<FoodDictionary> FoodDictionary::instance_;

const std::string jsonFileName = "../AnimalCooking/resources/cfg/food.cfg";

FoodDictionary::FoodDictionary() {

	fill();
}

FoodDictionary::~FoodDictionary() {
}

void FoodDictionary::fill()
{
	FoodConfig foodCfg;

	for (int u = 0; u < foodCfg.getUtensilsRecipes().size(); ++u) {		
		

		for (int i = 0; i < foodCfg.getUtensilsRecipes()[u].transformations.size(); ++i) {
			set<int> set;

			set.insert(foodCfg.getUtensilsRecipes()[u].transformations[i].set);
			dictionary_.insert(Par(par(u, set), foodCfg.getUtensilsRecipes()[u].transformations[i].result));			
		}
	}

	for (int c = 0; c < foodCfg.getCookersRecipes().size(); ++c) {

		for (int i = 0; i < foodCfg.getCookersRecipes()[c].transformations.size(); ++i) {
			set<int> set;

			for (int j = 0; j < foodCfg.getCookersRecipes()[c].transformations[i].set.size(); ++j) {
				set.insert(foodCfg.getCookersRecipes()[c].transformations[i].set[j]);
			}

			dictionary_.insert(Par(par(c, set), foodCfg.getCookersRecipes()[c].transformations[i].result));
			resultToSetDictionary_.insert(std::make_pair(foodCfg.getCookersRecipes()[c].transformations[i].result, set));
		}
	}
}

Food* FoodDictionary::bind(const int& c) const
{
	switch (c)
	{
		// Poop
	case -1:
		return new Poop();
		break;
		// Platos enteros :

	case Resources::FoodType::Pizza:
		return new Pizza();
		break;
	case Resources::FoodType::Roast:
		return new Roast();
		break;
	case Resources::FoodType::RiceDish:
		return new RiceDish();
		break;
	case Resources::FoodType::Risotto:
		return new Risotto();
		break;
	case Resources::FoodType::CookedFish:
		return new CookedFish();
		break;
	case Resources::FoodType::BakedChicken:
		return new BakedChicken();
		break;
	case Resources::FoodType::FriedVegs:
		return new FriedVegs();
		break;
	case Resources::FoodType::CookedClams:
		return new CookedClams();
		break;
	case Resources::FoodType::RiceAndClams:
		return new RiceAndClams();
		break;

		// Alimentos individuales : 

	case Resources::FoodType::MashedMeatSkillet:
		return new MashedMeatSkillet();
		break;
	case Resources::FoodType::CaughtSausageSkillet:
		return new CaughtSausageSkillet();
		break;
	case Resources::FoodType::SlicedPotatoSkillet:
		return new SlicedPotatoSkillet();
		break;
	default:
		return new Poop();
		break;
	}
}

Food* FoodDictionary::getResult(const int& c, vector<int>& vector)
{
	set<int> set;
	for (auto elem : vector) {
		if (!set.insert(elem).second) return bind(-1); //Devuelvo fallo si hay dos elementos repetidos
	}
	return getResult(c, set);
}

Food* FoodDictionary::getResult(const int& c, vector<Food*>& vector)
{
	set<int> set;
	for (auto elem : vector) {
		if (!set.insert(elem->getType()).second) return bind(-1); //Devuelvo fallo si hay dos elementos repetidos
	}
	return getResult(c, set);
}


Food* FoodDictionary::getResult(const int& c, const set<int>& set)
{
	auto it = dictionary_.find(par(c, set));
	return it != dictionary_.end() ? bind(it->second) : bind(-1); //Devuelve el result si lo encuentra, y si no devuelve fallo
}

const set<int>& FoodDictionary::getIngsForFood(const int& result)
{
	auto it = resultToSetDictionary_.find(result);
	if (it != resultToSetDictionary_.end()) return it->second;
	else {
		set<int> vacio;
		return vacio;
	}
}
