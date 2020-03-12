#pragma once
#include <map>
#include <set>
#include <iostream>
#include "FoodEnum.h"
#include "jute.h"

using namespace std;

using par = pair<int, set<int>>;
using Par = pair<par, int>;


struct CompareMap {
	bool operator()(const par& par1, const par& par2) const {
		return par1.first < par2.first || par1.second < par2.second;
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
	
private:
	FoodDictionary();
	void fill(int c, std::string cadena);
	static unique_ptr<FoodDictionary> instance_;
	map<par, int, CompareMap> dictionary_;

	jute::jValue jSon_;
};





//int main() {
//	/*set<int> set1, set2;
//
//	set1.insert(B().n);
//	set1.insert(C().n);
//
//	set2.insert(C().n);
//	set2.insert(D().n);
//
//	map<par, A*, CompareMap> m;
//
//	m.insert(Par(par(0, set1), new B()));
//	m.insert(Par(par(0, set2), new C()));
//
//	cout << m.find(par(0, set2))->second << endl;*/
//
//	return 0;
//}