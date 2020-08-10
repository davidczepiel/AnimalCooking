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
		////----->Menu<---------
		MainMenuBackground,
		MainMenuRuedecilla,
		MainMenuRuedecillaShadow,
		MainMenuArrow,
		MainMenuArrowR,
		MainMenuPlayButton,
		MainMenuConfigButton,
		MainMenuExitButton,
		MainMenuCreditsButton,
		//----->InGame<--------------
		LevelTimerBackground,
		LevelTimerForeground,
		UtensilTimerBackground,
		UtensilTimerForeground,
		ScoreBackground,
		//----->EndState<---------
		BackgroundEndState,
		BarBackgroundEndState,
		BarEndState,
		ReplayIcon,
		NextLevelIcon,
		Star,
		YellowStar,
		LimitSign,
		//MapState
		NameAsker,
		MapStateBackground,
		MapStateHousesBackground,
		MapStateInfoBox,

		//Botones del mando
		GPad_a,
		GPad_b,
		GPad_x,
		GPad_y,
		GPad_up,
		GPad_down,
		GPad_left,
		GPad_right,
		GPad_r1,
		GPad_l1,
		GPad_r3,
		GPad_l3,
		GPad_start,
		GPad_back,

		//---->Config<---------
		SliderBackground,
		SliderMovPoint,
		ConfigBackground,
		//---->Creditos<-----
		LogoTenByTen,

		// images all
		Plato,
		Suelo,
		Hierba,
		OvenOFF,
		SkilletOFF,
		SkilletOFFEsquina,
		SkilletOFFBorde,
		Platera,
		Muro,
		ParedCocina,
		Valla,
		VallaFinal,
		VallaInicio,
		Collider,
		VallaAbajo,
		//Utensilios
		Cuchillo,
		CuchilloSucio,
		Maza,
		MazaSucia,
		Rallador,
		RalladorSucio,
		Red,
		RedSucia,
		Fregadero,
		FregaderoON,
		FregaderoFlip,
		FregaderoFlipON,
		FregaderoAbajo,
		FregaderoAbajoON,
		Panera,
		Papelera,
		CuadradoAux,
		//Barra de entregas
		BarraDcha,
		BarraIzda,
		BarraCentro,
		BarraConTimbre,
		BarraSinTimbre,
		//Menu
		level0Menu,
		level1Menu,
		level2Menu,
		level3Menu,
		level4Menu,
		barraScreenLoaderBack,
		barraScreenLoader,
		buttonGo,
		//PauseState
		pauseStateBackground,
		botonPauseState,
			//Encimeras
			EncimeraAbajoConMantel,
			EncimeraAbajoConMantelDcha,
			EncimeraAbajoConMantelIzda,
			EncimeraAbajoSinMantel,
			EncimeraAbajoSinMantelDcha,
			EncimeraAbajoSinMantelIzda,
			EncimeraHorizConMantel,
			EncimeraHorizSinMantel,
			EncimeraVertConMantelDcha,
			EncimeraVertConMantelIzda,
			EncimeraVertSinMantelDcha,
			EncimeraVertSinMantelIzda,
			EncimeraVEsquinaInferiorIzda,
			EncimeraVEsquinaInferiorDcha,
			EncimeraVEsquinaSuperiorDcha,
			EncimeraVEsquinaSuperiorIzda,
			EncimeraVConDecoracion,
			EncimeraHBordeDerecha,
			EncimeraHBordeIzquierda,
			//Esquinas
			EsquinaSupDchaCopas,
			EsquinaSupIzdaCopas,
			EsquinaSupDchaVino,
			EsquinaSupIzdaVino,
			EsquinaSupDchaAgua,
			EsquinaSupIzdaAgua,
			EsquinaSupDchaVacia,
			EsquinaSupIzdaVacia,
			EsquinaInfIzqVaciaDecoracion,
			EsquinaInfDerVaciaDecoracion,

		//Pedidos------------------------------------------------------
		Bocadillo,
		SaladOrder,
		Salad1Order,
		Salad2Order,
		Salad3Order,
		Salad4Order,
		BurgerOrder,
		Burger1Order,
		Burger2Order,
		Burger3Order,
		PizzaOrder,
		RoastOrder,
		RiceDishOrder,
		HotDogOrder,
		RisottoOrder,
		CookedFishOrder,
		FriedVegsOrder,
		FriedVegsOrder1,
		FriedVegsOrder2,
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
		Salad1T,
		Salad2T,
		Salad3T,
		Salad4T,

		BurgerT,
		Burger1T,
		Burger2T,
		Burger3T,

		PizzaT,
		RoastT,
		RiceDishT,
		HotDogT,
		RisottoT,
		CookedFishT,

		FriedVegsT,
		FriedVegs1T,
		FriedVegs2T,

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
			Salad1FeedBack,
			Salad2FeedBack,
			Salad3FeedBack,
			Salad4FeedBack,

			BurgerFeedBack,
			Burger1FeedBack,
			Burger2FeedBack,
			Burger3FeedBack,

			PizzaFeedBack,
			RoastFeedBack,
			RiceDishFeedBack,
			HotDogFeedBack,
			RisottoFeedBack,
			CookedFishFeedBack,

			FriedVegsFeedBack,
			FriedVegs1FeedBack,
			FriedVegs2FeedBack,

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
			MazoFeedBack,
			RedFeedBack,
			RalladorFeedBack,
			//General
			Panel,
			PlatoFeedBack,
			PapeleraFeedBack,
			BordeTeclaFeedBack,
			RellenoTeclaFeedBack,
		// images level specific
		Arroz,
		Aceite,
		EncimeraMasa,

		//CreditState
		woodCredits,
		//spritesheets
		Button,
		ButtonConfig,
		ButtonBin,
		CircularTimer,
		BurnedTimer,
		OvenON,
		HomeIconEndState,
		HomeIconMapState,
		MapIcon,
		SkilletON,
		SkilletONEsquina,
		SkilletONBorde,
		SmokeBurned,
		PigIdle,
        PigWalk,
		PigAttack,
		ChickenIdle,
		ChickenWalk,
		ChickenAttack,
		Tomato,
		Potato,
		Clam,
        Cheese,
		Meat,
	    Lettuce,
		Mushroom,
		Onion,
		Fish,
		Chicken,
		Carrot,
		Sausage,
		Puerta,
		FireOverHeated,
		MapRestaurantButton,
		MapStatePlayButton,

		// text
		Back,
		ToggleFullscreen,
		ToggleHelper,
		MusicVolume,
		SoundVolume,
		PickUpText,
		AttackText,
		OpenText,
		FinishText,
		NextText,
		PreviousText,


		AntonioJesus,
		Daniel,
		David,
		Felipe,
		Javier,
		Marco,
		Nicolas,
		Pablo,
		Sandra,
		Tatiana,
		MapNewGameButton,
		MapLoadGameButton,
		Go,

		//Adversities
		WarningAdversity,
		PlaneShadow,
		RainAdversity,
		HookAdversity

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
		MenuInicio,
		Level1,
		Beat,
		Cheer,
		Boooo,
		DropDish,
		CompleteDish,
		Wash,
		FrySound,
		FrySoundBurned,
		MicroWave,
		Door,
		Bin,
		PickUp,
		Drop,
		KnifeAttack,
		MaceAttack,
		AttackMiss,
		BurnedBeep,
		CookedFood,
		IngredientSpawned,
		OrderRecieved,
		PlaneSound,

		Tecla1, //Variaciones que suenan al pulsar un boton
		Tecla2,
		Tecla3,
		Tecla4,
		Tecla5,
		Tecla6,

		End_Win,
		End_Lost,
	};

	enum FontId : std::size_t {
		ARIAL12,
		ARIAL50,
		ARIAL40,
		QuarkCheese100,
		QuarkCheese200,
		QuarkCheese70,
		QuarkCheese50
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
		Salad1,
		Salad2,
		Salad3,
		Salad4,
		Burger,
		Burger1,
		Burger2,
		Burger3,
		Pizza,
		Roast,
		RiceDish,
		HotDog,
		Risotto,
		CookedFish,
		FriedVegs,
		FriedVegs1,
		FriedVegs2,
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
