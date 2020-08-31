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
		PingUtensil,
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
		MapState2Background,
		MapState3Background,
		MapStateInfoBox,
		ButtonNext,
		ButtonPrev,

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
		Config_BackButton,
		Config_Background,
		Config_CerdoClick,
		Config_ChickenClick,
		Config_FullscreenFocusedText,
		Config_FullscreenUnFocusedText,
		Config_ReminderFocusedText,
		Config_ReminderUnFocusedText,
		Config_Tick,
		Config_UnTicked,
		Config_MusicIcon,
		Config_MusicVolumeTitle,
		Config_OptionsTitle,
		Config_Panel,
		Config_Player1,
		Config_Player2,
		Config_SliderMovPoint,
		Config_SliderMovPointSelected,
		Config_Slider,
		Config_SliderSelected,
		Config_SoundIcon,
		Config_SoundVolumeTitle,


		//---->Creditos<-----
		LogoTenByTen,

		// images all
		Plato,
		Suelo,
		Hierba,
		OvenOFF,
		OvenDerOFF,
		OvenIzqOFF,
		OvenOFFBordes,
		SkilletOFF,
		SkilletOFFEsquina,
		SkilletOFFBorde,
		SkilletOFFArribaDecoracion,
		SkilletOFFArriba,
		SkilletOFFBordeAmbos,
		Platera,
		PlateraBordeDerecha,
		PlateraBordeSoloDerecha,
		PlatosBordes,
		PlatosVer,
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
		Cubo,
		Fregadero,
		FregaderoON,
		FregaderoFlip,
		FregaderoFlipON,
		FregaderoAbajo,
		FregaderoAbajoON,
		FregaderoBordeIzq,
		FregaderoBordeIzqON,
		FregaderoEsqDchaArr,
		FregaderoEsqDchaArrON,
		FregaderoFlipBordeArriba,
		FregaderoFlipONBordeArriba,
		FregaderoFlipSinIzq,
		FregaderoFlipSinIzqON,
		Panera,
		PaneraVerSinDer,
		PaneraBordeDer,
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
		levelExtra1,
		level5Menu,
		level6Menu,
		level7Menu,
		level8Menu,
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
			EncimeraVertAbajo,
			EncimeraVertSin_SinBordeIzq,
			EncimeraVertSin_SinBordeDer,
			EncimeraVEsquinaSuperior_SinBordeIzq,
			EncimeraVEsquinaSuperior_SinBordeDer,
			EncimeraHorizConBordes,
			EncimeraDerVertCon,
			EncimeraIzqVertCon,
			EncimeraVEsquinaSuperior_SinBordes,
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
			EsquinaSupIzqSinBordeDer,

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
		Roast1Order,
		Roast2Order,
		Roast3Order,
		RiceDishOrder,
		HotDogOrder,
		RisottoOrder,
		CookedFishOrder,
		FriedVegsOrder,
		FriedVegsOrder1,
		FriedVegsOrder2,
		BakedChickenOrder,
		BakedChicken1Order,
		BakedChicken2Order,
		FrenchFriesOrder,
		CookedClamsOrder,
		RiceAndClamsOrder,
		FishOnStickOrder,
		FishAndChipsOrder,
		FishBurgerOrder,
		Rice1Order,
		Rice2Order,
		IcedCookedFishOrder,
		IcedFishOnStickOrder,
		IcedFishAndChipsOrder,
		IcedFishBurgerOrder,
		IcedRice1Order,
		IcedRice2Order,
		IcedRiceAndClamsOrder,
		IcedRiceDishOrder,
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
		SlicedFishT,
		IceT, 
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
		Roast1T,
		Roast2T,
		Roast3T,

		RiceDishT,
		HotDogT,
		RisottoT,
		CookedFishT,

		FriedVegsT,
		FriedVegs1T,
		FriedVegs2T,

		BakedChickenT,
		BakedChicken1T,
		BakedChicken2T,

		FrenchFriesT,
		CookedClamsT,
		RiceAndClamsT,
		MashedMeatSkilletT,
		CaughtSausageSkilletT,
		SlicedPotatoSkilletT,
		DressT,
		MashedTomatoT,
		FishSkilletT,
		FishOnStickT,
		FishAndChipsT,
		FishBurgerT,
		Rice1T,
		Rice2T,
		IcedCookedFishT,
		IcedFishOnStickT,
		IcedFishAndChipsT,
		IcedFishBurgerT,
		IcedRice1T,
		IcedRice2T, 
		IcedRiceAndClamsT,
		IcedRiceDishT,

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
			SlicedFishFeedBack,
			IceFeedBack, 
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
			Roast1FeedBack,
			Roast2FeedBack,
			Roast3FeedBack,

			RiceDishFeedBack,
			HotDogFeedBack,
			RisottoFeedBack,
			CookedFishFeedBack,

			FriedVegsFeedBack,
			FriedVegs1FeedBack,
			FriedVegs2FeedBack,

			BakedChickenFeedBack,
			BakedChicken1FeedBack,
			BakedChicken2FeedBack,

			FrenchFriesFeedBack,
			CookedClamsFeedBack,
			RiceAndClamsFeedBack,

			FishSkilletFeedBack,
			FishOnStickFeedBack,
			FishAndChipsFeedBack,
			FishBurgerFeedBack,
			
			Rice1FeedBack,
			Rice2FeedBack,

			IcedCookedFishFeedBack, 
			IcedFishOnStickFeedBack,
			IcedFishAndChipsFeedBack,
			IcedFishBurgerFeedBack,
			IcedRice1FeedBack,
			IcedRice2FeedBack,
			IcedRiceAndClamsFeedBack,
			IcedRiceDishFeedBack,

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
		ArrozBordeSup,
		ArrozSinBordeDer,
		Aceite,
		AceiteBordeDer,
		AceiteBordeIzq,
	    AceiteVertical,
		AceiteVerSinIzq,
		AceiteVerSinDer,
		AceiteSin,
		AceiteVerticalBordeSup,
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
		OvenDerON,
		OvenIzqON,
		OvenONBordes,
		HomeIconEndState,
		HomeIconMapState,
		MapIcon,
		SkilletON,
		SkilletONEsquina,
		SkilletONBorde,
		SkilletONArribaDecoracion,
		SkilletONArriba,
		SkilletONBordeAmbos,
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
		Snowman,
		Puerta,
		FireOverHeated,
		LightingStrike,
		LightingExplosion,
		MapRestaurantButton,
		MapStatePlayButton,
		Explosion,
		// text
		Back,
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
		HookAdversity,
		PidgeonAdversity

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
		fish,
		snowman
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
		QuarkCheese62,
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
		SlicedFish,
		Ice,
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
		FishSkillet,
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
		Roast1,
		Roast2,
		Roast3,
		RiceDish,
		HotDog,
		Risotto,
		CookedFish,
		FriedVegs,
		FriedVegs1,
		FriedVegs2,
		BakedChicken,
		BakedChicken1,
		BakedChicken2,
		FrenchFries,
		CookedClams,
		RiceAndClams,
		FishOnStick,
		FishAndChips,
		FishBurger,
		Rice1,
		Rice2, 
		IcedCookedFish,
		IcedFishOnStick,
		IcedFishAndChips,
		IcedFishBurger, 
		IcedRice1,
		IcedRice2,
		IcedRiceAndClams,
		IcedRiceDish,
		///

	};

	enum PickableType : std::size_t {
		Food,
		Dish,
		Utensil,
		Bucket,
		none
	};

	enum Cookers : std::size_t {
		Oven,
		Skillet,
		Hands		//Hands represents the action of finishing a recipe from the dish
	};
};
