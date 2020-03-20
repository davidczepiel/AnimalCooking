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


class PlayState : public State
{
public:
	PlayState() : State() {
		//Player----------------------------------------------
		Entity* player = stage->addEntity();
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
		IngredientsPool* pI = ingPool->addComponent<IngredientsPool>();
		ingPool->addComponent<IngredientViewer>();
		ingPool->addComponent<IngredientMotion>();

		Ingredient* i = new Tomato();
		i->setSize(32, 32);
		i->setVel(Vector2D(0, 0));
		i->setPos(Vector2D(60,60));
		pI->addIngredient(i);

		i = new Onion();
		i->setSize(32, 32);
		i->setPos(Vector2D(10,70));
		i->setVel(Vector2D(0, 0));
		pI->addIngredient(i);

		//-----------------------------------------------------
		Entity* utensil = stage->addEntity();
		UtensilsPool* utensilpool_ = utensil->addComponent<UtensilsPool>();
		utensil->addComponent<UtensilsViewer>();
		utensil->addComponent<UtensilsMotion>();

		Knife* k = new Knife(Vector2D(100, 100), tp, tp);
		utensilpool_->addUtensil(k);

		Shelf* shelf = new Shelf(k,tp,tp,stage);
		shelf->addComponent<SelectorPopUpEntity>(GETCMP2(player, InteractionRect), GETCMP2(player, InteractionRect),
												 GETCMP2(player, Selector), GETCMP2(player, Selector), shelf);
		shelf->setPos(Vector2D(100, 100));
		shelf->setSize(Vector2D(100, 100));
		stage->addEntity(shelf);
		
	}



private:

	static void goToEndState();
	static void goToPauseState();
};

