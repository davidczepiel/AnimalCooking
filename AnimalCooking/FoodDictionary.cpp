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
		return new Poop();
		break;
	case foodEnum::Carrot:
		return new Carrot();
		break;
	case foodEnum::Onion:
		return new Onion();
		break;
	case foodEnum::Potatoes:
		return new Potatoes();
		break;
	case foodEnum::Rice:
		return new Rice();
		break;
	case foodEnum::Steak:
		return new Steak();
		break;
	case foodEnum::Tomato:
		return new Tomato();
		break;
	case foodEnum::SteakAsaoYpunto:
		return new SteakAsaoYpunto();
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
		if (!set.insert(elem.getType()).second) return bind(-1); //Devuelvo fallo si hay dos elementos repetidos
	}
	return getResult(c, set);
}


Food* FoodDictionary::getResult(const int& c, const set<int>& set)
{
	auto it = dictionary_.find(par(c, set));
	return it != dictionary_.end() ? bind(it->second) : bind(-1); //Devuelve el result si lo encuentra, y si no devuelve fallo
}