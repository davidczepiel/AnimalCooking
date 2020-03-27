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
		

	//Adding Knife recipes
	utensilsRecipes_.push_back({ Resources::UtensilType::Knife, uTrans });
	
	utensilsRecipes_.clear();


	///////////////////////
	// MACE  RECIPES    // -------> SET <--------------   -----------> RESULT <--------------
	//////////////////////	

	uTrans.push_back({ Resources::IngredientType::meat,		Resources::FoodType:: MashedMeat });  //
	uTrans.push_back({ Resources::IngredientType::mushroom, Resources::FoodType:: MashedMushroom }); //
	uTrans.push_back({ Resources::IngredientType::tomato,	Resources::FoodType:: MashedTomato }); //


	//Adding Mace recipes
	utensilsRecipes_.push_back({ Resources::UtensilType::Mace, uTrans });
	//AÑADIR AQUI AL DICCIONARIO
	utensilsRecipes_.clear();

	///////////////////////
	// GRATER  RECIPES   // -------> SET <--------------   -----------> RESULT <--------------
	//////////////////////	

	uTrans.push_back({ Resources::IngredientType::cheese,	Resources::FoodType::GratedCheese }); //


	//Adding Grater recipes
	utensilsRecipes_.push_back({ Resources::UtensilType::Grater, uTrans });
	//AÑADIR AQUI AL DICCIONARIO
	utensilsRecipes_.clear();

	///////////////////////
	// NET  RECIPES      // -------> SET <--------------   -----------> RESULT <--------------
	//////////////////////	
	
	uTrans.push_back({ Resources::IngredientType::clam,		Resources::FoodType::CaughtClam }); 
	uTrans.push_back({ Resources::IngredientType::fish,		Resources::FoodType::CaughtFish }); 
	uTrans.push_back({ Resources::IngredientType::sausage,	Resources::FoodType::CaughtSausage }); 

	//Adding Net recipes
	utensilsRecipes_.push_back({ Resources::UtensilType::Net, uTrans });
	//AÑADIR AQUI AL DICCIONARIO
	utensilsRecipes_.clear();

	

	///////////////////////////////////////////////////////////////////////////////////
	//Fill transformations2:  Normal Food -> Cooked Food into cookersRecipes_    /////
	/////////////////////////////////////////////////////////////////////////////////
	vector <cookersTrans> cTrans;

	///////////////////////
	// OVEN  RECIPES    //  -------------------------------------> SET <------------------------------------------------------      ----------> RESULT <-------------
	//////////////////////
	cTrans.push_back({ { Resources::FoodType::MashedTomato, Resources::FoodType::PizzaMass, Resources::FoodType::GratedCheese, Resources::FoodType::Dress },	Resources::FoodType::Pizza });
	cTrans.push_back({ { Resources::FoodType::SlicedMeat, Resources::FoodType::SlicedPotato, Resources::FoodType::MashedTomato, Resources::FoodType::Dress },	Resources::FoodType::Roast });
	cTrans.push_back({ { Resources::FoodType::CaughtFish, Resources::FoodType::SlicedOnion, Resources::FoodType::SlicedPotato, Resources::FoodType::Dress },	Resources::FoodType::CookedFish });
	cTrans.push_back({ { Resources::FoodType::SlicedCarrot, Resources::FoodType::MashedTomato, Resources::FoodType::SlicedChicken},	Resources::FoodType::BakedChicken });
	cTrans.push_back({ { Resources::FoodType::CaughtClam, Resources::FoodType::SlicedOnion, Resources::FoodType::MashedTomato, Resources::FoodType::Dress },	Resources::FoodType::CookedClams });


	//Adding Oven recipes
	cookersRecipes_.push_back({ Resources::Oven, cTrans });	
	//AÑADIR AQUI AL DICCIONARIO
	cookersRecipes_.clear();


	///////////////////////
	// SKILLET RECIPES      //  -------------------------------------> SET <------------------------------------------------------      ----------> RESULT <-------------
	//////////////////////

	cTrans.push_back({ { Resources::FoodType::MashedMeat},		Resources::FoodType::MashedMeatSkillet });
	cTrans.push_back({ { Resources::FoodType::CaughtSausage},	Resources::FoodType::CaughtSausageSkillet });
	cTrans.push_back({ { Resources::FoodType::SlicedPotato},	Resources::FoodType::SlicedPotatoSkillet });
	cTrans.push_back({ { Resources::FoodType::Rice, Resources::FoodType::SlicedSausage, Resources::FoodType::SlicedCarrot, Resources::FoodType::MashedTomato },	Resources::FoodType::RiceDish });
	cTrans.push_back({ { Resources::FoodType::Rice, Resources::FoodType::SlicedMushroom, Resources::FoodType::GratedCheese, Resources::FoodType::SlicedOnion },	Resources::FoodType::Risotto });
	cTrans.push_back({ { Resources::FoodType::Rice, Resources::FoodType::CaughtClam, Resources::FoodType::MashedMushroom, Resources::FoodType::SlicedMushroom},	Resources::FoodType::RiceAndClams });
	cTrans.push_back({ { Resources::FoodType::SlicedCarrot, Resources::FoodType::SlicedTomato, Resources::FoodType::SlicedOnion, Resources::FoodType::MashedMushroom },	Resources::FoodType::FriedVegs });


	//Adding Oven recipes
	cookersRecipes_.push_back({ Resources::Skillet, cTrans });
	//AÑADIR AQUI AL DICCIONARIO
	cookersRecipes_.clear();


	///////////////////////
	// HANDS RECIPES     //  -------------------------------------> SET <------------------------------------------------------      ----------> RESULT <-------------
	//////////////////////

	cTrans.push_back({ { Resources::FoodType::SlicedTomato, Resources::FoodType::SlicedLettuce, Resources::FoodType::SlicedOnion, Resources::FoodType::Dress },	Resources::FoodType::Salad });
	cTrans.push_back({ { Resources::FoodType::SlicedTomato, Resources::FoodType::SlicedLettuce, Resources::FoodType::Bread, Resources::FoodType::MashedMeatSkillet },	Resources::FoodType::Burger });
	cTrans.push_back({ { Resources::FoodType::CaughtSausageSkillet, Resources::FoodType::Bread, Resources::FoodType::MashedTomato, Resources::FoodType::SlicedCheese},	Resources::FoodType::HotDog });
	cTrans.push_back({ { Resources::FoodType::SlicedPotatoSkillet, Resources::FoodType::Dress},	Resources::FoodType::FrenchFries });


	//Adding Oven recipes
	cookersRecipes_.push_back({ Resources::Hands, cTrans });
	//AÑADIR AQUI AL DICCIONARIO
	cookersRecipes_.clear();
}
