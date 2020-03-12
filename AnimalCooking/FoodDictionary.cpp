#include "FoodDictionary.h"

unique_ptr<FoodDictionary> FoodDictionary::instance_;

const std::string jsonFileName = "../AnimalCooking/resources/cfg/food.cfg";

FoodDictionary::FoodDictionary() {
	jSon_ = jute::parser::parse_file(jsonFileName);

	fill(0, "horno");
	fill(1, "sarten");
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

FoodDictionary::~FoodDictionary() {
}