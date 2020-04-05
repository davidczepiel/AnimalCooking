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
#include "FoodGiver.h"
#include "FoodGiverViewer.h"
#include "Cooker.h"
#include "CookerViewer.h"
#include "CookerPool.h"
#include "FoodCooker.h"
#include "InsertExpel.h"
#include "Sink.h"
#include "BinEntity.h"
#include "BinViewer.h"
#include "CollisionsSystem.h"
#include "Physics.h"

class PlayState : public State
{
public:
	PlayState() : State() {
		//Player----------------------------------------------
		Entity* player = stage->addEntity();
		stage->addToGroup(player, ecs::Layer5);
		Transform* t = player->addComponent<Transform>();
		t->setWH(128,128);
		t->setPos(Vector2D(2*128,128));
		Physics* ph =player->addComponent<Physics>();
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
		Physics* phIng =ingPool->addComponent<Physics>();
		ingPool->addComponent<IngredientMotion>();

		Ingredient* i = new Tomato();
		i->setSize(128, 128);
		i->setVel(Vector2D(-1, 0));
		i->setPos(Vector2D(400 ,300));
		pI->addIngredient(i);

		i = new Onion();
		i->setSize(32, 32);
		i->setPos(Vector2D(1200,540));
		i->setVel(Vector2D(0, 0));
		pI->addIngredient(i);

		i = new Onion();
		i->setSize(32, 32);
		i->setPos(Vector2D(1500, 540));
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

		//Cookers---------------------------------------
		Entity* cookerPool = stage->addEntity();
		stage->addToGroup(cookerPool, ecs::Layer1);
		CookerPool* cp =cookerPool->addComponent<CookerPool>();
		cookerPool->addComponent<FoodCooker>(fp);
		cookerPool->addComponent<CookerViewer>();
		cookerPool->addComponent<InsertExpel>(tp);
		Vector2D pos = Vector2D(128, 0);
		Vector2D size = Vector2D(128, 128);
		Oven* oven = new Oven(pos, size, 0, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cooker), tp, tp, cookerPool);
		cp->addCooker(oven);

		pos = Vector2D(0, 128);
		Skillet* skillet = new Skillet(pos, size, 0, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cooker), tp, tp, cookerPool);
		cp->addCooker(skillet);

		vector<Interactive*>* c = &reinterpret_cast<vector<Interactive*>&>(cp->getPool());
		cookerPool->addComponent<SelectorPopUp>(c, GETCMP2(player, InteractionRect), GETCMP2(player, InteractionRect),
			GETCMP2(player, Selector), GETCMP2(player, Selector), GETCMP2(player, Transport), GETCMP2(player, Transport));




		//-------------------------Repisas----------------------------------------
		Shelf* knifeShelf = new Shelf(Vector2D(3*128,5*128),k,tp,tp,stage);
		stage->addToGroup(knifeShelf, ecs::Layer1);
		stage->addEntity(knifeShelf);
		knifeShelf->addComponent<SelectorPopUpEntity>(GETCMP2(player, InteractionRect), GETCMP2(player, InteractionRect),
												 GETCMP2(player, Selector), GETCMP2(player, Selector), knifeShelf);

		Shelf* maceShelf = new Shelf(Vector2D(4 * 128, 5 * 128), m, tp, tp, stage);
		stage->addEntity(maceShelf);
		stage->addToGroup(maceShelf, ecs::Layer1);
		maceShelf->addComponent<SelectorPopUpEntity>(GETCMP2(player, InteractionRect), GETCMP2(player, InteractionRect),
			GETCMP2(player, Selector), GETCMP2(player, Selector), maceShelf);
		
		Shelf* shelfTercerUtensilio = new Shelf(Vector2D(5 * 128, 5 * 128), nullptr, tp, tp, stage);
		stage->addEntity(shelfTercerUtensilio);
		stage->addToGroup(shelfTercerUtensilio, ecs::Layer1);
		shelfTercerUtensilio->addComponent<SelectorPopUpEntity>(GETCMP2(player, InteractionRect), GETCMP2(player, InteractionRect),
			GETCMP2(player, Selector), GETCMP2(player, Selector), shelfTercerUtensilio);

		Shelf* shelf1 = new Shelf(Vector2D(0, 2 * 128), nullptr, tp, tp, stage);
		stage->addEntity(shelf1);
		stage->addToGroup(shelf1, ecs::Layer1);
		shelf1->addComponent<SelectorPopUpEntity>(GETCMP2(player, InteractionRect), GETCMP2(player, InteractionRect),
			GETCMP2(player, Selector), GETCMP2(player, Selector), shelf1);

		Sink* sink = new Sink(Vector2D(0,3*128),tp,tp,stage);
		stage->addEntity(sink);
		stage->addToGroup(sink, ecs::Layer1);

		Shelf* shelf0 = new Shelf(Vector2D(0, 0), nullptr, tp, tp, stage);
		stage->addEntity(shelf0);
		stage->addToGroup(shelf0, ecs::Layer1);
		maceShelf->addComponent<SelectorPopUpEntity>(GETCMP2(player, InteractionRect), GETCMP2(player, InteractionRect),
			GETCMP2(player, Selector), GETCMP2(player, Selector), shelf0);

		//--------------------------------PAPELERA------------------------------------
		BinEntity* bin = new BinEntity(stage,tp,tp);
		bin->addComponent<BinViewer>(bin);
		bin->addComponent<SelectorPopUpEntity>(GETCMP2(player, InteractionRect), GETCMP2(player, InteractionRect),
			GETCMP2(player, Selector), GETCMP2(player, Selector), bin);
		bin->setSize(Vector2D(128, 128));
		bin->setPos(Vector2D(0,128*4));
		stage->addEntity(bin);
		stage->addToGroup(bin,ecs::Layer1);

		//Platera---------------------------------------
		Entity* poolPlatos = stage->addEntity();
		stage->addToGroup(poolPlatos, ecs::Layer2);
		DishPool* dp =poolPlatos->addComponent<DishPool>();
		poolPlatos->addComponent<DishMotion>();
		poolPlatos->addComponent<DishViewer>();
		/*vector<Interactive*>* d = &reinterpret_cast<vector<Interactive*>&>(dp->getDishes());
		poolPlatos->addComponent<SelectorPopUp>(d, GETCMP2(player, InteractionRect), GETCMP2(player, InteractionRect),
			GETCMP2(player, Selector), GETCMP2(player, Selector), GETCMP2(player, Transport), GETCMP2(player, Transport));*/
		DishStack* dish = new DishStack(Vector2D(128*4,0),10,tp,tp,stage,dp);
		dish->addComponent<SelectorPopUpEntity>(GETCMP2(player, InteractionRect), GETCMP2(player, InteractionRect),
			GETCMP2(player, Selector), GETCMP2(player, Selector), dish);
		stage->addEntity(dish);
		stage->addToGroup(dish, ecs::GroupID::Layer1);

		//GameManager------------------------------------
		Entity* gameManager = stage->addEntity();
		GameLogic* glogic =gameManager->addComponent<GameLogic>();
		gameManager->addComponent<GameControl>(tp, tp, utensilpool_, fp);
		glogic->setUtensilsPool(utensilpool_);
		glogic->setIngredientPool(pI);
		CollisionsSystem* colSystem =gameManager->addComponent<CollisionsSystem>();


		//Arrocera-------------------
		/*RiceGiver* riceGiver = new RiceGiver(Vector2D(500, 500), Vector2D(128, 128), GETCMP2(player, Transport), GETCMP2(player, Transport), GETCMP2(gameManager, GameControl));
		riceGiver->addComponent<FoodGiverViewer>(riceGiver);
		riceGiver->addComponent<SelectorPopUpEntity>(GETCMP2(player, InteractionRect), GETCMP2(player, InteractionRect),
			GETCMP2(player, Selector), GETCMP2(player, Selector), riceGiver);
		stage->addEntity(riceGiver);
		stage->addToGroup(riceGiver, ecs::Layer1);*/
		//Panera--------------------
		BreadGiver* breadGiver = new BreadGiver(Vector2D(128*3, 0), Vector2D(128, 128), GETCMP2(player, Transport), GETCMP2(player, Transport), GETCMP2(gameManager, GameControl));
		breadGiver->addComponent<FoodGiverViewer>(breadGiver);
		breadGiver->addComponent<SelectorPopUpEntity>(GETCMP2(player, InteractionRect), GETCMP2(player, InteractionRect),
			GETCMP2(player, Selector), GETCMP2(player, Selector), breadGiver);
		stage->addEntity(breadGiver);
		stage->addToGroup(breadGiver, ecs::Layer1);
		//Mesa de aliñado
		DressingGiver* dressGiver = new DressingGiver(Vector2D(2*128,0),Vector2D(128,128),tp,tp,GETCMP2(gameManager,GameControl));
		dressGiver->addComponent<FoodGiverViewer>(dressGiver);
		dressGiver->addComponent<SelectorPopUpEntity>(GETCMP2(player, InteractionRect), GETCMP2(player, InteractionRect),
			GETCMP2(player, Selector), GETCMP2(player, Selector), dressGiver);
		stage->addEntity(dressGiver);
		stage->addToGroup(dressGiver, ecs::Layer1);
			
		colSystem->addCollider(t);
		colSystem->addCollider(shelf1);
		colSystem->addCollider(shelf0);
		colSystem->addCollider(knifeShelf);
		colSystem->addCollider(maceShelf);
		colSystem->addCollider(sink);
		colSystem->addCollider(bin);
		colSystem->addCollider(breadGiver);
		colSystem->addCollider(dressGiver);
		ph->setCollisionSystem(colSystem);
		phIng->setCollisionSystem(colSystem);

	}



private:

	static void goToEndState();
	static void goToPauseState();
};

