#pragma once
#include <ctime>

namespace ecs {

using CmpIdType = std::size_t;
using Group = std::size_t;

enum CmpId : CmpIdType {
	Transform = 0,
	ImageViewer,

	GPadController, //Controls
	KeyBoardController,
	IngredientMotion,

	AIIngredient, //AI

	GameControl, //Game
	GameLoader,
	GameLogic,
	GameSave,
	CollisionsSystem,
	FeedBack,
	TimerViewer,

	Attack, //Player
	PlayerController,
	PlayerViewer,
	PlayerMotion,
	Transport,
	Selector,
	InteractionRect,
	Animator,

	DishPool,		//Dish
	DishMotion,
	DishViewer,
	DishStack,
	DishStackViewer,
	InOutFood,		//ELIMINAR SI NO SE IMPLEMENTA
	DishFinisher,
	

	FoodMotion,		//Food
	FoodViewer,
	FoodPool,

	FoodGiverViewer, //FoodGiver


	IngredientsPool, //Pools
	UtensilsPool,


	UtensilsViewer, //Utensils
	UtensilsMotion,
	ShelfViewer,
	OrderServiceViewer,
	SinkViewer,


	CookerPool,		//Cookers
	CookerViewer,	
	FoodCooker,
	InsertExpel,

	AIClient,
	OrderManager,	//Clients
	OrderViewer,

	SDLRenderer, //Renderer
	SDLRendererFrame,
	StaticRenderer,
	IngredientViewer,
	BinViewer,
	BackGroundViewer,
	DoorRenderer,

	GameManager, //Utils
	ScoreManager,
	ScoreViewer,
	SoundManager,
	SelectorPopUp,
	SelectorPopUpEntity,
	Physics,
	PhysicsPool,

	ButtonBehaviour, //Buttons
	ButtonBehaviourNC,
	ButtonRenderer,
	ButtonRendererHouse,
	ButtonsViewer,
	ButtonDirector,
	MenuButtonRenderer,
	MenuButtonBehaviour,
	MainMenuPadNavigation,
	ButtonPadNavigation,
	ButtonChangeOnClick,

	SliderBehaviour,	//Sliders
	SliderRenderer,

	LoadingBarViewer, //Bar
	AdversityManager,
	MultipleAdversityManager,

	levelViewer,//UI
	CreditsViewer,

	KeyboardKeySwitcher, //Config
	KeyboardKeySwitcherViewer,
	GpadKeySwitcher,
	GpadKeySwitcherViewer,
	
	NameAsker,//MapState
	MapInfoBox,
	MapInfoBoxViewer,

	//
	// don't touch the rest of this enum, it is to identify the max
	// number of components
	_LastCmptId_
};

enum GroupID : Group {
	Layer1,
	Layer2,
	PlayerLayerAux,
	FeedBackLayer,
	FoodLayer,
	PlayerLayer,
	Valla,
	ui,
	topLayer,
	
	_LastGroupId_	//Identify the max number of groups
};

enum AdversityID  {
	PlaneAdversity,
	CookersAdversity,
	HookAdversity,
	RainAdversity
};

constexpr std::size_t maxComponents = _LastCmptId_;
constexpr std::size_t maxGroups = _LastGroupId_;

// these two should be used to get a component via the field
// entity_
#define GETCMP2_(id,type)  GETCMP3(entity_,id,type)
#define GETCMP1_(type)     GETCMP3(entity_,ecs::type,type)

// these two should be used to get a component via an
// entity e provided as a parameter
#define GETCMP2(e,type) GETCMP3(e,ecs::type,type)
#define GETCMP3(e,id,type) e->getComponent<type>(id)

}

