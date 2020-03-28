#pragma once

#include "State.h"
#include "EndState.h"
#include "PauseState.h"
#include "Manager.h"
#include "PlayerController.h"
#include "PlayerMotion.h"
#include "PlayerViewer.h"
#include "Entity.h"
#include "IngredientsPool.h"
#include "IngredientViewer.h"
#include "IngredientMotion.h"
#include "Ingredient.h"
#include "Shelf.h"
#include "UtensilsPool.h"
#include "UtensilsViewer.h"
#include "UtensilsMotion.h"
#include "SelectorPopUp.h"
#include "SelectorPopUpEntity.h"
#include "GameLogic.h"
#include "FoodPool.h"
#include "FoodMotion.h"
#include "FoodViewer.h"
#include "DishStack.h"
#include "DishPool.h"
#include "DishMotion.h"
#include "DishViewer.h"
#include "DishFinisher.h"


class PlayState : public State
{
public:
	PlayState() : State() {
		//Player----------------------------------------------
		Entity* player = stage->addEntity();
		stage->addToGroup(player, ecs::Layer5);
		Transform* t = player->addComponent<Transform>();
		t->setWH(64,64);
		player->addComponent<PlayerMotion>();
		player->addComponent<Selector>();
		player->addComponent<InteractionRect>();
		player->addComponent<Attack>();
		Transport* tp = player->addComponent<Transport>();
		player->addComponent<PlayerController>();
		player->addComponent<PlayerViewer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cerdo));

		//Ingredientes----------------------------------------
		Entity* ingPool = stage->addEntity();
		stage->addToGroup(ingPool, ecs::Layer3);
		IngredientsPool* pI = ingPool->addComponent<IngredientsPool>();
		ingPool->addComponent<IngredientViewer>();
		ingPool->addComponent<IngredientMotion>();

		Ingredient* i = new Tomato();
		i->setSize(32, 32);
		i->setVel(Vector2D(0, 0));
		i->setPos(Vector2D(400,60));
		pI->addIngredient(i);

		i = new Onion();
		i->setSize(32, 32);
		i->setPos(Vector2D(10,70));
		i->setVel(Vector2D(0, 0));
		pI->addIngredient(i);
		
		//EntityFoodPool----------------------------------------

		Entity* foodPool = stage->addEntity();
		stage->addToGroup(foodPool, ecs::Layer3);
		FoodPool* fp = foodPool->addComponent<FoodPool>();
		vector<Interactive*>* aux = &reinterpret_cast<vector<Interactive*>&>(fp->getPool());
		foodPool->addComponent<SelectorPopUp>(aux, GETCMP2(player, InteractionRect), GETCMP2(player, InteractionRect),
			GETCMP2(player, Selector), GETCMP2(player, Selector), GETCMP2(player, Transport), GETCMP2(player, Transport));
		foodPool->addComponent<FoodMotion>();
		foodPool->addComponent<FoodViewer>();

		//EntityUtensilPool----------------------------------------
		Entity* utensil = stage->addEntity();
		stage->addToGroup(utensil, ecs::Layer4);
		UtensilsPool* utensilpool_ = utensil->addComponent<UtensilsPool>();
		vector<Interactive*>* b = &reinterpret_cast<vector<Interactive*>&>(utensilpool_->getPool());
		utensil->addComponent<SelectorPopUp>(b, GETCMP2(player, InteractionRect), GETCMP2(player, InteractionRect),
			GETCMP2(player, Selector), GETCMP2(player, Selector), GETCMP2(player, Transport), GETCMP2(player, Transport));
		utensil->addComponent<UtensilsViewer>();
		utensil->addComponent<UtensilsMotion>();

		Knife* k = new Knife( tp, tp);
		utensilpool_->addUtensil(k);
		Mace* m = new Mace(tp,tp);
		utensilpool_->addUtensil(m);

		//Repisas----------------------------------------
		Shelf* shelf = new Shelf(Vector2D(100,100),k,tp,tp,stage);
		stage->addToGroup(shelf, ecs::Layer1);
		stage->addEntity(shelf);
		shelf->addComponent<SelectorPopUpEntity>(GETCMP2(player, InteractionRect), GETCMP2(player, InteractionRect),
												 GETCMP2(player, Selector), GETCMP2(player, Selector), shelf);

		Shelf* shelf2 = new Shelf(Vector2D(200, 100), m, tp, tp, stage);
		stage->addEntity(shelf2);
		stage->addToGroup(shelf2, ecs::Layer1);
		shelf2->addComponent<SelectorPopUpEntity>(GETCMP2(player, InteractionRect), GETCMP2(player, InteractionRect),
			GETCMP2(player, Selector), GETCMP2(player, Selector), shelf2);

		//Platera---------------------------------------
		Entity* poolPlatos = stage->addEntity();
		stage->addToGroup(poolPlatos, ecs::Layer2);
		DishPool* dp =poolPlatos->addComponent<DishPool>();
		poolPlatos->addComponent<DishMotion>();
		poolPlatos->addComponent<DishViewer>();
		/*vector<Interactive*>* d = &reinterpret_cast<vector<Interactive*>&>(dp->getDishes());
		poolPlatos->addComponent<SelectorPopUp>(d, GETCMP2(player, InteractionRect), GETCMP2(player, InteractionRect),
			GETCMP2(player, Selector), GETCMP2(player, Selector), GETCMP2(player, Transport), GETCMP2(player, Transport));*/
		DishStack* dish = new DishStack(Vector2D(300,100),10,tp,tp,stage,dp);
		dish->addComponent<SelectorPopUpEntity>(GETCMP2(player, InteractionRect), GETCMP2(player, InteractionRect),
			GETCMP2(player, Selector), GETCMP2(player, Selector), dish);
		stage->addEntity(dish);

		//GameManager------------------------------------
		Entity* gameManager = stage->addEntity();
		GameLogic* glogic =gameManager->addComponent<GameLogic>();
		gameManager->addComponent<GameControl>(tp, nullptr, utensilpool_, fp);
		glogic->setUtensilsPool(utensilpool_);
		glogic->setIngredientPool(pI);

	}



private:

	static void goToEndState();
	static void goToPauseState();
};

