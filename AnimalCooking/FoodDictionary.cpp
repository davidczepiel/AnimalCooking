#include "FoodDictionary.h"

unique_ptr<FoodDictionary> FoodDictionary::instance_;

const std::string jsonFileName = "../AnimalCooking/resources/cfg/food.cfg";

FoodDictionary::FoodDictionary() {
	jSon_ = jute::parser::parse_file(jsonFileName);

	fill();
}

FoodDictionary::~FoodDictionary() {
}

void FoodDictionary::fill()
{
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
	case -1:
		//return new Poop();
		break;
	case Resources::FoodType::MashedTomato:
		//return new Carrot();
		break;
	case Resources::FoodType::SlicedLettuce:
		//return new SlicedLettuce();
		break;
	case Resources::FoodType::SlicedOnion:
		//return new SlicedOnion();
		break;
	case Resources::FoodType::SlicedMeat:
		//return new SlicedMeat();
		break;
	case Resources::FoodType::MashedMeat:
		//return new MashedMeat();
		break;
	case Resources::FoodType::SlicedCheese:
		//return new SlicedCheese();
		break;
	case Resources::FoodType::GratedCheese:
		//return new GratedCheese();
		break;
	case Resources::FoodType::SlicedPotato:
		//return new SlicedPotato();
		break;
	case Resources::FoodType::SlicedSausage:
		//return new SlicedSausage();
		break;
	case Resources::FoodType::SlicedCarrot:
		//return new SlicedCarrot();
		break;
	case Resources::FoodType::CaughtSausage:
		//return new CaughtSausage();
		break;
	case Resources::FoodType::SlicedMushroom:
		//return new SlicedMushroom();
		break;
	case Resources::FoodType::MashedMushroom:
		//return new MashedMushroom();
		break;
	case Resources::FoodType::CaughtFish:
		//return new CaughtFish();
		break;
	case Resources::FoodType::SlicedChicken:
		//return new SlicedChicken();
		break;
	case Resources::FoodType::CaughtClam:
		//return new CaughtClam();
		break;	
	default:
		//return new Poop();
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