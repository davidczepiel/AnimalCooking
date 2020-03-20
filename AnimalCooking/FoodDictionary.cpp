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
	jute::jValue jSon_ = jute::parser::parse_file(jsonFileName);
	jute::jValue cookers = jSon_["cookers"];

	for (int c = 0; c < cookers.size(); ++c) {
		jute::jValue ar = cookers[c][1];
		for (int i = 0; i < ar.size(); ++i) {
			set<int> set;
			for (int j = 0; j < ar[i]["set"].size(); ++j) {
				set.insert(ar[i]["set"][j].as_int());
			}
			dictionary_.insert(Par(par(c, set), ar[i]["result"].as_int()));
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