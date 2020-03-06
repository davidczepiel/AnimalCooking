#pragma once
#include "Texture.h"
#include "Entity.h"



class Utensilio:public Entity {

	enum  State
	{
		floor,playerHand,shelf
	};
	State myState;
	int myDirt;
	int maxDirt;
	int getDirtSpeed;
	int cleanUpSpeed;
	int range;
	int attackHitBoxWidth;
	int attackHitBoxHeight;
	int attackRate;
	int lastAttack;
	bool dirty;
	bool ableToClean;
	Entity* player;
	Texture* clean;
	Texture* dirty;
	SDL_Rect interactionTrigger;

public:
	Utensilio(Entity* p,Texture* c, Texture* d) {
		
		myDirt = 0;
		maxDirt = 100;
		getDirtSpeed = 10;
		range = 100;
		attackHitBoxWidth = 100;
		attackHitBoxHeight = 50;
		attackRate = 1000;
		lastAttack = SDL_GetTicks();
		player = p;
		clean = c;
		dirty = d;
		myState = State::shelf;
		dirty = false;
		ableToClean = false;
		interactionTrigger.x = 100;
		interactionTrigger.y = 100;
		interactionTrigger.w = 100;
		interactionTrigger.h = 100;
	}

	void update() {
		if(myState != State::playerHand){

		if(myState == State::floor)  //Si me encuentro en el suelo puedo empezar a ensuciarme
		myDirt += getDirtSpeed;

		/* Hay que comprobar todo el rato SI NO ESTOY EN LA MANO DEL JUGADOR, comprobar si está cerca para interactuar conmig
		if(Collisions::collides(player->getPos(), player->getW(), player->getH(), pos, width, height) && SDLGame::instance()->getInputHandler()->isKeyDown(SDL_Scancode(0)){
		pickMe();
		}
		*/
		}
		else {

		}
	}

	void dropped(bool suelo) {
		//Hay que volver a situar el trigger en la nueva zona
		/*interactionTrigger.x = pos.getX()- (interactionTrigger.w/2);
		interactionTrigger.y = pos.getY()- (interactionTrigger.h/2);
		*/
		if (suelo)
			myState = State::floor;
		else
			myState = State::shelf;
	}

	void render() {

	}

	void pickMe() {
		myState = State::playerHand;
	}
	void attack() {
		if (SDL_GetTicks() > lastAttack + attackRate) {
			lastAttack = SDL_GetTicks();
		cout << "ataque";
		}
	}
	
	void onHit() {
		
	}


	void inTheWasher(bool x) {
		ableToClean = x;
	}
	void cleanUp() {

		if (dirty && ableToClean && SDLGame::instance()->getInputHandler()->isKeyDown(SDL_Scancode(0))) {
			myDirt -= cleanUpSpeed;
			if (myDirt <= 0)dirty = false;
		}


	}

	void changeDirtySpeed(int speedModifier)
	{
		getDirtSpeed += speedModifier;
	}

};