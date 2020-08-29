#include "FoodConfig.h"

FoodConfig::FoodConfig()
{
	fill();
}

void FoodConfig::fill()
{
	///////////////////////////////////////////////////////////////////////////////////
	//Fill transformations1:  Ingredient -> Normal food into utensilsRecipes_  //////
	/////////////////////////////////////////////////////////////////////////////////
	vector <utensilsTrans> uTrans;

	///////////////////////
	// KNIFE  RECIPES    // -------> SET <--------------   -----------> RESULT <--------------
	//////////////////////	
	uTrans.push_back({ Resources::IngredientType::carrot,	Resources::FoodType::SlicedCarrot });
	uTrans.push_back({ Resources::IngredientType::cheese,	Resources::FoodType::SlicedCheese });
	uTrans.push_back({ Resources::IngredientType::chicken,  Resources::FoodType::SlicedChicken });
	uTrans.push_back({ Resources::IngredientType::lettuce,  Resources::FoodType::SlicedLettuce });
	uTrans.push_back({ Resources::IngredientType::meat,		Resources::FoodType::SlicedMeat });
	uTrans.push_back({ Resources::IngredientType::mushroom, Resources::FoodType::SlicedMushroom });
	uTrans.push_back({ Resources::IngredientType::onion,	Resources::FoodType::SlicedOnion });
	uTrans.push_back({ Resources::IngredientType::potato,	Resources::FoodType::SlicedPotato });
	uTrans.push_back({ Resources::IngredientType::sausage,	Resources::FoodType::SlicedSausage });
	uTrans.push_back({ Resources::IngredientType::tomato,	Resources::FoodType::SlicedTomato });
	uTrans.push_back({ Resources::IngredientType::snowman,	Resources::FoodType::Ice });


	//Adding Knife recipes
	utensilsRecipes_.push_back({ Resources::UtensilType::Knife, uTrans });
	uTrans.clear();

	///////////////////////
	// MACE  RECIPES    // -------> SET <--------------   -----------> RESULT <--------------
	//////////////////////	

	uTrans.push_back({ Resources::IngredientType::meat,		Resources::FoodType::MashedMeat });  //
	uTrans.push_back({ Resources::IngredientType::tomato,	Resources::FoodType::MashedTomato }); //


	//Adding Mace recipes
	utensilsRecipes_.push_back({ Resources::UtensilType::Mace, uTrans });
	uTrans.clear();

	///////////////////////
	// GRATER  RECIPES   // -------> SET <--------------   -----------> RESULT <--------------
	//////////////////////	

	uTrans.push_back({ Resources::IngredientType::cheese,	Resources::FoodType::GratedCheese }); //


	//Adding Grater recipes
	utensilsRecipes_.push_back({ Resources::UtensilType::Grater, uTrans });
	uTrans.clear();

	///////////////////////
	// NET  RECIPES      // -------> SET <--------------   -----------> RESULT <--------------
	//////////////////////	

	uTrans.push_back({ Resources::IngredientType::clam,		Resources::FoodType::CaughtClam });
	uTrans.push_back({ Resources::IngredientType::fish,		Resources::FoodType::CaughtFish });
	uTrans.push_back({ Resources::IngredientType::sausage,	Resources::FoodType::CaughtSausage });

	//Adding Net recipes
	utensilsRecipes_.push_back({ Resources::UtensilType::Net, uTrans });
	uTrans.clear();



	///////////////////////////////////////////////////////////////////////////////////
	//Fill transformations2:  Normal Food -> Cooked Food into cookersRecipes_    /////
	/////////////////////////////////////////////////////////////////////////////////
	vector <cookersTrans> cTrans;

	///////////////////////
	// OVEN  RECIPES    //  -------------------------------------> SET <------------------------------------------------------      ----------> RESULT <-------------
	//////////////////////
	cTrans.push_back({ { Resources::FoodType::MashedTomato, Resources::FoodType::PizzaMass, Resources::FoodType::GratedCheese, Resources::FoodType::Dress },	Resources::FoodType::Pizza });

	cTrans.push_back({ { Resources::FoodType::SlicedMeat, Resources::FoodType::SlicedPotato, Resources::FoodType::MashedTomato, Resources::FoodType::Dress },	Resources::FoodType::Roast });
	//ROAST---------------------------------
	cTrans.push_back({ { Resources::FoodType::SlicedMeat, Resources::FoodType::MashedTomato, Resources::FoodType::Dress },	Resources::FoodType::Roast1 });
	cTrans.push_back({ { Resources::FoodType::SlicedMeat, Resources::FoodType::SlicedMushroom,  Resources::FoodType::Dress },	Resources::FoodType::Roast2 });
	cTrans.push_back({ { Resources::FoodType::SlicedMeat, Resources::FoodType::SlicedOnion, Resources::FoodType::MashedTomato},	Resources::FoodType::Roast3 });

	cTrans.push_back({ { Resources::FoodType::CaughtFish, Resources::FoodType::SlicedOnion, Resources::FoodType::SlicedPotato, Resources::FoodType::Dress },	Resources::FoodType::CookedFish });
	//CHICKEN-------------------------------
	cTrans.push_back({ { Resources::FoodType::SlicedCarrot, Resources::FoodType::MashedTomato, Resources::FoodType::SlicedChicken},	Resources::FoodType::BakedChicken });
	cTrans.push_back({ { Resources::FoodType::SlicedMushroom, Resources::FoodType::MashedTomato, Resources::FoodType::SlicedChicken},	Resources::FoodType::BakedChicken1 });
	cTrans.push_back({ { Resources::FoodType::SlicedPotato, Resources::FoodType::MashedTomato, Resources::FoodType::SlicedChicken},	Resources::FoodType::BakedChicken2 });

	cTrans.push_back({ { Resources::FoodType::CaughtClam, Resources::FoodType::SlicedOnion, Resources::FoodType::MashedTomato, Resources::FoodType::Dress },	Resources::FoodType::CookedClams });
	//FISH-------------------------------
	cTrans.push_back({ {Resources::FoodType::CaughtFish,Resources::FoodType::Dress},Resources::FoodType::FishOnStick });

	//Adding Oven recipes
	cookersRecipes_.push_back({ Resources::Oven, cTrans });
	cTrans.clear();


	///////////////////////
	// SKILLET RECIPES      //  -------------------------------------> SET <------------------------------------------------------      ----------> RESULT <-------------
	//////////////////////

	cTrans.push_back({ { Resources::FoodType::MashedMeat},		Resources::FoodType::MashedMeatSkillet });
	cTrans.push_back({ { Resources::FoodType::CaughtSausage},	Resources::FoodType::CaughtSausageSkillet });
	cTrans.push_back({ { Resources::FoodType::SlicedPotato},	Resources::FoodType::SlicedPotatoSkillet });
	cTrans.push_back({ { Resources::FoodType::Rice, Resources::FoodType::SlicedMushroom, Resources::FoodType::GratedCheese, Resources::FoodType::SlicedOnion },	Resources::FoodType::Risotto });
	cTrans.push_back({ { Resources::FoodType::Rice, Resources::FoodType::CaughtClam, Resources::FoodType::MashedTomato, Resources::FoodType::SlicedMushroom},	Resources::FoodType::RiceAndClams });

	cTrans.push_back({ { Resources::FoodType::SlicedCarrot, Resources::FoodType::SlicedTomato, Resources::FoodType::SlicedOnion, Resources::FoodType::SlicedMushroom },	Resources::FoodType::FriedVegs });
	cTrans.push_back({ { Resources::FoodType::SlicedCarrot, Resources::FoodType::SlicedMushroom },	Resources::FoodType::FriedVegs1 });
	cTrans.push_back({ { Resources::FoodType::SlicedTomato, Resources::FoodType::SlicedOnion, Resources::FoodType::SlicedMushroom },	Resources::FoodType::FriedVegs2 });

	cTrans.push_back({ { Resources::FoodType::CaughtFish},	Resources::FoodType::FishSkillet });
	cTrans.push_back({ { Resources::FoodType::Rice,Resources::FoodType::MashedTomato},	Resources::FoodType::Rice1 });
	cTrans.push_back({ { Resources::FoodType::Rice,Resources::FoodType::SlicedFish,Resources::FoodType::Dress},	Resources::FoodType::Rice2 });


	//Adding Skillet recipes
	cookersRecipes_.push_back({ Resources::Skillet, cTrans });
	cTrans.clear();


	///////////////////////
	// HANDS RECIPES     //  -------------------------------------> SET <------------------------------------------------------      ----------> RESULT <-------------
	//////////////////////

	cTrans.push_back({ { Resources::FoodType::SlicedTomato, Resources::FoodType::SlicedLettuce, Resources::FoodType::SlicedOnion, Resources::FoodType::Dress },	Resources::FoodType::Salad });
	cTrans.push_back({ { Resources::FoodType::SlicedTomato, Resources::FoodType::SlicedLettuce, Resources::FoodType::Dress }, Resources::FoodType::Salad1 });
	cTrans.push_back({ { Resources::FoodType::SlicedTomato, Resources::FoodType::Dress },	Resources::FoodType::Salad2 });
	cTrans.push_back({ { Resources::FoodType::SlicedLettuce, Resources::FoodType::Dress, Resources::FoodType::SlicedOnion  }, Resources::FoodType::Salad3 });
	cTrans.push_back({ {  Resources::FoodType::SlicedTomato, Resources::FoodType::SlicedLettuce, Resources::FoodType::Dress, Resources::FoodType::SlicedCarrot  },	Resources::FoodType::Salad4 });

	cTrans.push_back({ { Resources::FoodType::SlicedTomato, Resources::FoodType::SlicedLettuce, Resources::FoodType::BreadBurger, Resources::FoodType::MashedMeatSkillet },	Resources::FoodType::Burger });
	/*cTrans.push_back({ { Resources::FoodType::MashedMeatSkillet, Resources::FoodType::BreadBurger, Resources::FoodType::MashedMeatSkillet }, Resources::FoodType::Burger1 });*/
	cTrans.push_back({ { Resources::FoodType::SlicedLettuce, Resources::FoodType::BreadBurger, Resources::FoodType::MashedMeatSkillet }, Resources::FoodType::Burger2 });
	cTrans.push_back({ { Resources::FoodType::BreadBurger, Resources::FoodType::MashedMeatSkillet }, Resources::FoodType::Burger3 });
	cTrans.push_back({ { Resources::FoodType::CaughtSausageSkillet, Resources::FoodType::BreadBurger, Resources::FoodType::MashedTomato, Resources::FoodType::SlicedCheese},	Resources::FoodType::HotDog });
	cTrans.push_back({ { Resources::FoodType::SlicedPotatoSkillet, Resources::FoodType::Dress},	Resources::FoodType::FrenchFries });
	cTrans.push_back({ { Resources::FoodType::Rice, Resources::FoodType::SlicedSausage, Resources::FoodType::SlicedCarrot, Resources::FoodType::MashedTomato },	Resources::FoodType::RiceDish });
	
	cTrans.push_back({ { Resources::FoodType::FrenchFries,Resources::FoodType::FishSkillet },	Resources::FoodType::FishAndChips });
	cTrans.push_back({ { Resources::FoodType::Dress,Resources::FoodType::FishSkillet,Resources::FoodType::SlicedLettuce,Resources::FoodType::BreadBurger },	Resources::FoodType::FishBurger });
	cTrans.push_back({ { Resources::FoodType::CookedFish,Resources::FoodType::Ice},	Resources::FoodType::IcedCookedFish });
	cTrans.push_back({ { Resources::FoodType::FishOnStick,Resources::FoodType::Ice},	Resources::FoodType::IcedFishOnStick });
	cTrans.push_back({ { Resources::FoodType::FishAndChips,Resources::FoodType::Ice},	Resources::FoodType::IcedFishAndChips });
	cTrans.push_back({ { Resources::FoodType::FishBurger,Resources::FoodType::Ice},	Resources::FoodType::IcedFishBurger });
	cTrans.push_back({ { Resources::FoodType::Rice1,Resources::FoodType::Ice},	Resources::FoodType::IcedRice1 });
	cTrans.push_back({ { Resources::FoodType::Rice2,Resources::FoodType::Ice},	Resources::FoodType::IcedRice2 });
	cTrans.push_back({ { Resources::FoodType::RiceAndClams,Resources::FoodType::Ice},	Resources::FoodType::IcedRiceAndClams });
	cTrans.push_back({ { Resources::FoodType::RiceDish,Resources::FoodType::Ice},	Resources::FoodType::IcedRiceDish});


	//Adding Oven recipes
	cookersRecipes_.push_back({ Resources::Hands, cTrans });
	cTrans.clear();
}
