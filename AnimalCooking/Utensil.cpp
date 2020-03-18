#include "Utensil.h"
#include "SDLGame.h"
#include "SDL_macros.h"
#include "GameLogic.h"
#include <math.h> 

Utensil::Utensil(Vector2D pos, Transport* p1, Transport* p2) : Pickable(p1, p2) {
	myDirt_ = 0;
	maxDirt_ = 100;
	getDirtSpeed_ = 10;
	range_ = 100;
	attackHitBoxWidth_ = 100;
	attackHitBoxHeight_ = 50;
	attackRate_ = 1000;
	lastAttack_ = SDL_GetTicks();
	myState = State::shelf;
	dirty_ = false;
	interactionTrigger_.x = 100;
	interactionTrigger_.y = 100;
	interactionTrigger_.w = 100;
	interactionTrigger_.h = 100;
	cleanUpSpeed_ = 25;
	position_ = pos;
	speed_ = Vector2D(0, 0);
	frameAttack = 0;
	attacking_ = false;
	lastFrameTick = 0;
	size_ = Vector2D(0, 0);
}


void Utensil::update() {

	Pickable::update();
	if (myState != State::playerHand) {
		if (myState == State::floor) {  //Si me encuentro en el suelo puedo empezar a ensuciarme
			if (myDirt_ < maxDirt_)
				myDirt_ += getDirtSpeed_;
			else {
				dirty_ = true;
				myDirt_ = maxDirt_;
			}
		}
	}
	else
	{		//En caso de que este en la mano y haya atacado, voy aumentando el frame de la animaci�n que estoy mostrando
		if (attacking_ && SDL_GetTicks() - lastFrameTick > 20) {
			frameAttack++;
			if (frameAttack >= 5) {
				frameAttack = 0;
				attacking_ = false;
			}
		}
	}
}


void Utensil::onHit(Vector2D dir) {
	if (SDL_GetTicks() > lastAttack_ + attackRate_) {  //Control de que no se pueda espamear el ataque
		lastAttack_ = SDL_GetTicks();
		if (!dirty_) {  //Solo si estoy limpio mi ataque deberia hacer algo significativo
			attacking_ = true;
			lastFrameTick = SDL_GetTicks();
			//Preparo la posici�n de donde realizo el ataque
			Vector2D velNormalizada = speed_.normalize();
			SDL_Rect ataque;
			ataque.x = position_.getX() + (velNormalizada.getX() * range_);
			ataque.y = position_.getY() + (velNormalizada.getY() * range_);
			ataque.w = attackHitBoxWidth_;
			ataque.h = attackHitBoxHeight_;
			gameLogic->hitIngredient(ataque, myType);
		}
	}
}


void Utensil::render()const {
	SDL_Rect rect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
	if (!dirty_ && !attacking_)
		cleantexture_->render(rect); //EN caso de que solo est� en la mano del jugador	
	else if ((!dirty_ && attacking_)) {
		attackTexture_->render(rect); //EN caso de estar atacando habr�a que hacer un renderFrame
	}
	else
		dirtyTexture_->render(rect); //Cambiar si los ingredientes vienen todos en una misma textura para usar el clip	

}


void Utensil::drop(bool suelo) {
	//Hay que volver a situar el trigger en la nueva zona
	interactionTrigger_.x = position_.getX() - (interactionTrigger_.w / 2);
	interactionTrigger_.y = position_.getY() - (interactionTrigger_.h / 2);

	if (suelo)
		myState = State::floor;
	else
		myState = State::shelf;
}


void Utensil::pickMe() {
	//Me cambio de estado y paso a no tener suciedad
	myState = State::playerHand;
	myDirt_ = 0;
}

void Utensil::interactive(int player) {
	pickMe();
	if (player == 0)
		player1_->pick(this);
	else
		player2_->pick(this);
}



void Utensil::changeDirtySpeed(int speedModifier) {
	getDirtSpeed_ += speedModifier;
}

void Utensil::cleanUp() {
	//Me deberia llamar el fregadero para decime que me limpie
	if (dirty_) {
		myDirt_ -= cleanUpSpeed_;
		if (myDirt_ <= 0) {
			myDirt_ = 0;
			dirty_ = false;
		}
	}
}



///////////////////////////////////////

Knife::Knife(Vector2D pos, Transport* p1, Transport* p2) :Utensil(pos, p1, p2) {
	cleantexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cuchillo);
	dirtyTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CuchilloSucio);
	attackTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cuchillo);
	myType = Resources::UtensilType::Knife;
	range_ = 100;
	attackHitBoxWidth_ = 100;
	attackHitBoxHeight_ = 50;

}


Mace::Mace(Vector2D pos, Transport* p1, Transport* p2) :Utensil(pos, p1, p2) {
	cleantexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Mace);
	dirtyTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Mace);
	attackTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cuchillo);
	myType = Resources::UtensilType::Mace;
	range_ = 100;
	attackHitBoxWidth_ = 100;
	attackHitBoxHeight_ = 50;
}


Grater::Grater(Vector2D pos, Transport* p1, Transport* p2) :Utensil(pos, p1, p2) {
	cleantexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Grater);
	dirtyTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Grater);
	attackTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cuchillo);
	myType = Resources::UtensilType::Grater;
	range_ = 100;
	attackHitBoxWidth_ = 100;
	attackHitBoxHeight_ = 50;
}


Net::Net(Vector2D pos, Transport* p1, Transport* p2) :Utensil(pos, p1, p2) {
	cleantexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Net);
	dirtyTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Net);
	attackTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cuchillo);
	myType = Resources::UtensilType::Net;
	range_ = 100;
	attackHitBoxWidth_ = 100;
	attackHitBoxHeight_ = 50;
}