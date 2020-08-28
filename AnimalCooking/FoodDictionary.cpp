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
			dictionaryIng_.insert(Par(par(u, set), foodCfg.getUtensilsRecipes()[u].transformations[i].result));
		}
	}

	for (int c = 0; c < foodCfg.getCookersRecipes().size(); ++c) {
		for (int i = 0; i < foodCfg.getCookersRecipes()[c].transformations.size(); ++i) {
			set<int> set;
			for (int j = 0; j < foodCfg.getCookersRecipes()[c].transformations[i].set.size(); ++j) {
				set.insert(foodCfg.getCookersRecipes()[c].transformations[i].set[j]);
			}
			dictionaryCookers_.insert(Par(par(c, set), foodCfg.getCookersRecipes()[c].transformations[i].result));
			resultToSetDictionary_.insert(std::make_pair(foodCfg.getCookersRecipes()[c].transformations[i].result, set));
		}
	}
}

Food* FoodDictionary::bind(const int& c) const
{
	switch (c)
	{
		// Poop
	case -1:		return new Poop();		break;

	//Ingredientes
	case Resources::FoodType::SlicedTomato:		return new SlicedTomato;	break;
	case Resources::FoodType::MashedTomato:		return new MashedTomato;	break;
	case Resources::FoodType::SlicedLettuce:	return new SlicedLettuce;	break;
	case Resources::FoodType::SlicedOnion:		return new SlicedOnion;		break;
	case Resources::FoodType::SlicedMeat:		return new SlicedMeat;		break;
	case Resources::FoodType::MashedMeat:		return new MashedMeat;		break;
	case Resources::FoodType::SlicedCheese:		return new SlicedCheese;	break;
	case Resources::FoodType::GratedCheese:		return new GratedCheese;	break;
	case Resources::FoodType::SlicedPotato:		return new SlicedPotato;	break;
	case Resources::FoodType::SlicedSausage:	return new SlicedSausage;	break;
	case Resources::FoodType::SlicedCarrot:		return new SlicedCarrot;	break;
	case Resources::FoodType::CaughtSausage:	return new CaughtSausage;	break;
	case Resources::FoodType::SlicedMushroom:	return new SlicedMushroom;	break;
	case Resources::FoodType::CaughtFish:		return new CaughtFish;		break;
	case Resources::FoodType::SlicedChicken:	return new SlicedChicken;	break;
	case Resources::FoodType::CaughtClam:		return new CaughtClam;		break;

	//Platos enteros :
	case Resources::FoodType::Salad:			return new Salad();			break;
	case Resources::FoodType::Salad1:			return new Salad1();		break;
	case Resources::FoodType::Salad2:			return new Salad2();		break;
	case Resources::FoodType::Salad3:			return new Salad3();		break;
	case Resources::FoodType::Salad4:			return new Salad4();		break;
	//---------------------------------------------------------------------------
	case Resources::FoodType::Burger:			return new Burger();		break;
	case Resources::FoodType::Burger1:			return new Burger1();		break;
	case Resources::FoodType::Burger2:			return new Burger2();		break;
	case Resources::FoodType::Burger3:			return new Burger3();		break;
	//---------------------------------------------------------------------------
	case Resources::FoodType::Pizza:			return new Pizza();			break;
	//---------------------------------------------------------------------------
	case Resources::FoodType::Roast:			return new Roast();			break;
	case Resources::FoodType::Roast1:			return new Roast1();		break;
	case Resources::FoodType::Roast2:			return new Roast2();		break;
	case Resources::FoodType::Roast3:			return new Roast3();		break;
	//---------------------------------------------------------------------------
	case Resources::FoodType::RiceDish:			return new RiceDish();		break;
	//---------------------------------------------------------------------------
	case Resources::FoodType::Risotto:			return new Risotto();		break;
	//---------------------------------------------------------------------------
	case Resources::FoodType::CookedFish:		return new CookedFish();	break;
	//---------------------------------------------------------------------------
	case Resources::FoodType::BakedChicken:		return new BakedChicken();	break;
	case Resources::FoodType::BakedChicken1:	return new BakedChicken1();	break;
	case Resources::FoodType::BakedChicken2:	return new BakedChicken2();	break;
	//---------------------------------------------------------------------------
	case Resources::FoodType::FriedVegs:		return new FriedVegs();		break;
	case Resources::FoodType::FriedVegs1:		return new FriedVegs1();	break;
	case Resources::FoodType::FriedVegs2:		return new FriedVegs2();	break;
	//---------------------------------------------------------------------------
	case Resources::FoodType::FrenchFries:		return new FrenchFries();	break;
		//---------------------------------------------------------------------------
	case Resources::FoodType::CookedClams:		return new CookedClams();	break;
	//---------------------------------------------------------------------------
	case Resources::FoodType::RiceAndClams:		return new RiceAndClams();	break;
	//---------------------------------------------------------------------------
	case Resources::FoodType::FishSkillet:		return new FishSkillet();	break;
	case Resources::FoodType::FishOnStick:		return new FishOnStick();	break;
	case Resources::FoodType::FishAndChips:		return new FishAndChips();	break;
	case Resources::FoodType::FishBurger:		return new FishBurger();	break;
	//---------------------------------------------------------------------------
	case Resources::FoodType::Rice1:		return new Rice1();	break;
	case Resources::FoodType::Rice2:		return new Rice2();	break;
	//---------------------------------------------------------------------------
	case Resources::FoodType::Ice:		return new Ice();	break;
	case Resources::FoodType::IcedCookedFish:		return new IcedCookedFish();	break;
	case Resources::FoodType::IcedFishOnStick:		return new IcedFishOnStick();	break;
	case Resources::FoodType::IcedFishAndChips:		return new IcedFishAndChips();	break;
	case Resources::FoodType::IcedFishBurger:		return new IcedFishBurger();	break;
	case Resources::FoodType::IcedRice1:		return new IcedRice1();	break;
	case Resources::FoodType::IcedRice2:		return new IcedRice2();	break;
	case Resources::FoodType::IcedRiceAndClams:		return new IcedRiceAndClams();	break;
	case Resources::FoodType::IcedRiceDish:		return new IcedRiceDish();	break;

		// Alimentos individuales : 

	case Resources::FoodType::MashedMeatSkillet:	return new MashedMeatSkillet();		break;
	case Resources::FoodType::CaughtSausageSkillet:	return new CaughtSausageSkillet();	break;
	case Resources::FoodType::SlicedPotatoSkillet:	return new SlicedPotatoSkillet();	break;
	default:										return new Poop();					break;
	}
}

Food* FoodDictionary::getResult(const int& c, vector<int>& vector, bool isCooker)
{
	set<int> set;
	for (auto elem : vector) {
		if (!set.insert(elem).second) return bind(-1); //Devuelvo fallo si hay dos elementos repetidos
	}
	return getResult(c, set, isCooker);
}

Food* FoodDictionary::getResult(const int& c, vector<Food*>& vector, bool isCooker)
{
	set<int> set;
	for (auto elem : vector) {
		if (!set.insert(elem->getType()).second) return bind(-1); //Devuelvo fallo si hay dos elementos repetidos
	}
	return getResult(c, set, isCooker);
}

Food* FoodDictionary::getResult(const int& c, const set<int>& set, bool isCooker)
{
	if (isCooker) {
		auto it = dictionaryCookers_.find(par(c, set));
		return it != dictionaryCookers_.end() ? bind(it->second) : bind(-1); //Devuelve el result si lo encuentra, y si no devuelve fallo
	}
	else {
		auto it = dictionaryIng_.find(par(c, set));
		return it != dictionaryIng_.end() ? bind(it->second) : bind(-1); //Devuelve el result si lo encuentra, y si no devuelve fallo
	}
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
