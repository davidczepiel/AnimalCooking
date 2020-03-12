#include "FoodDictionary.h"

unique_ptr<FoodDictionary> FoodDictionary::instance_;

const std::string jsonFileName = "../AnimalCooking/resources/cfg/food.cfg";

FoodDictionary::FoodDictionary() {
	jSon_ = jute::parser::parse_file(jsonFileName);

	fill(0, "horno");
	fill(1, "sarten");
}

FoodDictionary::~FoodDictionary() {
}

void FoodDictionary::fill(int c, std::string cadena)
{
	jute::jValue ar = jSon_[cadena];

	for (int i = 0; i < ar.size(); ++i) {
		set<int> set;
		for (int j = 0; j < ar[i]["set"].size(); ++j) {
			set.insert(ar[i]["set"][j].as_int());
		}
		dictionary_.insert(Par(par(c, set), ar[i]["result"].as_int()));
	}
}

int FoodDictionary::getResult(const int& c, const list<int>& list)
{
	set<int> set;
	for (auto elem : list) {
		if (!set.insert(elem).second) return -1; //Devuelvo fallo si hay dos elementos repetidos
	}
	return getResult(c, set);
}

int FoodDictionary::getResult(const int& c, const set<int>& set)
{
	auto it = dictionary_.find(par(c, set));
	return it != dictionary_.end() ? it->second : -1; //Devuelve el result si lo encuentra, y si no devuelve fallo
}