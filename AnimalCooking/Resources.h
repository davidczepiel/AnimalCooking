#pragma once

#include <SDL.h>
#include <string>
#include <vector>

using namespace std;

class Resources {
public:
	//El tipo de cada uno de los utensilios
	enum UtensilType: std::size_t {
		Knife, 
		Mace, 
		Grater, 
		Net
	};

	enum Player: std::size_t {
		Player1, Player2
	};

	enum TextureId : std::size_t {
		// images basic
		Button,
		RectangleOutline,
		
		SliderBackground,
		SliderMovPoint,

		// images all
		Repisa,
		Plato,
		Suelo,
		Hierba,
		Cooker,
		CookerCooking,
		CookerBurned,
		CookerCooked,
		Platera,
		Cuchillo,
		CuchilloSucio,
		Fregadero,
		Ingrediente,
		Panera,
		Pedido,
		Papelera,
		Cerdo,
		Pollo,
		CuadradoAux,
		level0Menu,
		level1Menu,
		level2Menu,
		level3Menu,
		level4Menu,

		//Pedidos------------------------------------------------------
		Bocadillo,
		SaladOrder,
		BurgerOrder,
		PizzaOrder,
		RoastOrder,
		RiceDishOrder,
		HotDogOrder,
		RisottoOrder,
		CookedFishOrder,
		FriedVegsOrder,
		BakedChickenOrder,
		FrenchFriesOrder,
		CookedClamsOrder,
		RiceAndClamsOrder,
		//Food---------------------------------------------------------
		PoopT,
		SlicedTomatoT,
		SlicedLettuceT,
		SlicedOnionT,
		SlicedMeatT,
		MashedMeatT,
		SlicedCheeseT,
		GratedCheeseT,
		SlicedPotatoT,
		SlicedSausageT,
		SlicedCarrotT,
		CaughtSausageT,
		SlicedMushroomT,
		CaughtFishT,
		SlicedChickenT,
		CaughtClamT,
		RiceT,
		BreadBurgerT,
		BreadHotDogT,
		PizzaMassT,
		SaladT,
		BurgerT,
		PizzaT,
		RoastT,
		RiceDishT,
		HotDogT,
		RisottoT,
		CookedFishT,
		FriedVegsT,
		BakedChickenT,
		FrenchFriesT,
		CookedClamsT,
		RiceAndClamsT,
		MashedMeatSkilletT,
		CaughtSausageSkilletT,
		SlicedPotatoSkilletT,
		DressT,
		MashedTomatoT,

		//FeedBackImages---------------------------------------------
			//Food
			PoopFeedBack,
			SlicedTomatoFeedBack,
			SlicedLettuceFeedBack,
			SlicedOnionFeedBack,
			SlicedMeatFeedBack,
			MashedMeatFeedBack,
			SlicedCheeseFeedBack,
			GratedCheeseFeedBack,
			SlicedPotatoFeedBack,
			SlicedSausageFeedBack,
			SlicedCarrotFeedBack,
			CaughtSausageFeedBack,
			SlicedMushroomFeedBack,
			CaughtFishFeedBack,
			SlicedChickenFeedBack,
			CaughtClamFeedBack,
			RiceFeedBack,
			BreadBurgerFeedBack,
			BreadHotDogFeedBack,
			PizzaMassFeedBack,
			SaladFeedBack,
			BurgerFeedBack,
			PizzaFeedBack,
			RoastFeedBack,
			RiceDishFeedBack,
			HotDogFeedBack,
			RisottoFeedBack,
			CookedFishFeedBack,
			FriedVegsFeedBack,
			BakedChickenFeedBack,
			FrenchFriesFeedBack,
			CookedClamsFeedBack,
			RiceAndClamsFeedBack,
			MashedMeatSkilletFeedBack,
			CaughtSausageSkilletFeedBack,
			SlicedPotatoSkilletFeedBack,
			DressFeedBack,
			MashedTomatoFeedBack,

			//Utensils
			CuchilloFeedBack,
			//General
			Panel,
			PlatoFeedBack,
			PapeleraFeedBack,
			Coger,
			Dejar,

		// images level specific
		Arroz,
		Aceite,
		
		//spritesheets
		CircularTimer,
		BurnedTimer

		// text
		
	
	};

	enum Level : std::size_t {
		Basic,
		AllLevels,
		Nivel1,
		Nivel2,
		Nivel3,
		Nivel4,
		Nivel5,
		Nivel6,
		Nivel7,
		Nivel8 
		//etc...
	};

	enum IngredientType: std::size_t {
		tomato,
		carrot,
		lettuce,
		mushroom,
		sausage,
		chicken,
		meat,
		potato,
		onion,
		clam,
		cheese,
		fish
	};

	enum AudioId : std::size_t {
		// music
		Beat,
		Cheer,
		Boooo,

		// sound effects
		Wall_Hit,
		Paddle_Hit
	};

	enum FontId : std::size_t {
		ARIAL12,
	};

	struct FontInfo {
		Level level;
		FontId id;
		string fileName;
		int size;
	};

	struct ImageInfo {
		Level level;
		TextureId id;
		string fileName;
	};

	struct SpritesheetInfo {
		Level level;
		TextureId id;
		string fileName;
		int numRows;
		int numCols;
	};

	struct TextMsgInfo {
		Level level;
		TextureId id;
		string msg;
		SDL_Color color;
		FontId fontId;
	};

	struct MusicInfo {
		Level level;
		AudioId id;
		string fileName;
	};

	struct SoundInfo {
		Level level;
		AudioId id;
		string fileName;
	};

	static vector<FontInfo> fonts_; // initialized in .cpp
	static vector<ImageInfo> images_; // initialized in .cpp
	static vector<SpritesheetInfo> spritesheets_; // initialized in .cpp
	static vector<TextMsgInfo> messages_; // initialized in .cpp
	static vector<MusicInfo> musics_; // initialized in .cpp
	static vector<SoundInfo> sounds_; // initialized in .cpp

	enum FoodType : std::size_t {
		SlicedTomato,
		MashedTomato,
		SlicedLettuce,
		SlicedOnion,
		SlicedMeat,
		MashedMeat,
		SlicedCheese,
		GratedCheese,
		SlicedPotato,
		SlicedSausage,
		SlicedCarrot,
		CaughtSausage,
		SlicedMushroom,
		MashedMushroom,
		CaughtFish,
		SlicedChicken,
		CaughtClam,
		///
		Rice,
		BreadBurger,
		BreadHotDog,
		PizzaMass,
		Dress,
		///
		Empty,
		///
		MashedMeatSkillet,
		CaughtSausageSkillet,
		SlicedPotatoSkillet,
		///
		_FirstOfFoods_, //Debe estar siempre justo debajo de la primera comida finalizada
		///
		Salad,
		Burger,
		Pizza,
		Roast,
		RiceDish,
		HotDog,
		Risotto,
		CookedFish,
		FriedVegs,
		BakedChicken,
		FrenchFries,
		CookedClams,
		RiceAndClams
		///

	};

	enum PickableType : std::size_t {
		Food,
		Dish,
		Utensil,
		none
	};

	enum Cookers : std::size_t {
		Oven,
		Skillet,
		Hands		//Hands represents the action of finishing a recipe from the dish
	};
};
