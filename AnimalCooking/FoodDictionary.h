#pragma once
#include <map>
#include <set>
#include <vector>

#include "Food.h"
#include "FoodConfig.h"
#include "jute.h"

using namespace std;

using par = pair<int, set<int>>;
using Par = pair<par, int>;

struct CompareMap {
	bool operator()(const par& par1, const par& par2) const {
		if (par1.first < par2.first) return true;
		else if (par1.first == par2.first) return par1.second < par2.second;
		else return false;
	}
};

class FoodDictionary {
public:

	FoodDictionary(FoodDictionary&) = delete;
	FoodDictionary& operator=(FoodDictionary&) = delete;

	virtual ~FoodDictionary();

	static FoodDictionary* instance() {
		if (instance_.get() == nullptr) {
			instance_.reset(new FoodDictionary());
		}
		return instance_.get();
	}

	//Devuelve un int identificador, o -1 si en la lista hay elementos repetidos o no existe dicha combinacion
	Food* getResult(const int& c, vector<int>& vector, bool isCooker = true);

	//Devuelve un int identificador, o -1 si en la lista hay elementos repetidos o no existe dicha combinacion
	Food* getResult(const int& c, vector<Food*>& vector, bool isCooker = true);

	//Devuelve un int identificador, o -1 si no existe dicha combinacion
	Food* getResult(const int& c, const set<int>& set, bool isCooker = true);

	const set<int>& getIngsForFood(const int& result);

private:
	FoodDictionary();
	void fill();
	Food* bind(const int& c) const;
	static unique_ptr<FoodDictionary> instance_;
	map<par, int, CompareMap> dictionaryCookers_;
	map<par, int, CompareMap> dictionaryIng_;
	map<int, set<int>> resultToSetDictionary_;
};