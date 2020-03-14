#include "Utensil.h"
#include "SDLGame.h"
#include "SDL_macros.h"
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
	ableToClean_ = false;
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

	if (isInUse) {

		Pickable::update();

		if (myState != State::playerHand) {
			if (myState == State::floor && myDirt_<maxDirt_) {  //Si me encuentro en el suelo puedo empezar a ensuciarme
				myDirt_ += getDirtSpeed_;
				if (myDirt_ >= maxDirt_)
					dirty_ = true;
			}
		}
	}
	else
	{		//En caso de que este en la mano y haya atacado, voy aumentando el frame de la animaci�n que estoy mostrando
		if (attacking_ && SDL_GetTicks() - lastFrameTick > 20) {
			frameAttack++;
			if (frameAttack >= 5)
				frameAttack = 0;
		}
	}
}

void Utensil::onHit(Vector2D dir) {
	/*if (SDLGetTicks() > lastAttack_ + attackRate_) {  //Control de que no se pueda espamear el ataque
		lastAttack_ = SDLGetTicks();
		if (!dirty_) {  //Solo si estoy limpio mi ataque deber�a hacer algo significativo
			lastFrameTick = SDLGetTicks();
			//Preparo la posici�n de donde realizo el ataque
			Vector2D velNormalizada = vel_.normalize();
			SDLRect ataque;
			ataque.x = pos.getX() + (velNormalizada.getX() * range_);
			ataque.y = pos.getY() + (velNormalizada.getY() * range_);
			ataque.w = attackHitBoxWidth_;
			ataque.h = attackHitBoxHeight_;
			//ingrediente = gameCtrl->AtaqueIngredientes(ataque);
		}
	}*/
}
void Utensil::render()const {
	SDL_Rect rect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
	if (!dirty_ && !attacking_)
		texture_->render(rect); //EN caso de que solo est� en la mano del jugador	
	else if ((!dirty_ && attacking_)) {
		texture_->render(rect); //EN caso de estar atacando habr�a que hacer un renderFrame
	}
	else
		secondTexture_->render(rect); //Cambiar si los ingredientes vienen todos en una misma textura para usar el clip	

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




void Utensil::inTheWasher(bool x) {
	ableToClean_ = x;
}

void Utensil::changeDirtySpeed(int speedModifier) {
	getDirtSpeed_ += speedModifier;
}

void Utensil::cleanUp() {
	//Me deber�a llamar el fregadero para decime que me limpie
	if (dirty_ && ableToClean_) {
		myDirt_ -= cleanUpSpeed_;
		if (myDirt_ <= 0) {
			myDirt_ = 0;
			dirty_ = false;
		}
	}


}



///////////////////////////////////////

Knife::Knife(Vector2D pos, Transport* p1, Transport* p2) :Utensil(pos, p1, p2) {
	texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cuchillo);
	myType = Resources::UtensilType::Knife;
	range_ = 100;
	attackHitBoxWidth_ = 100;
	attackHitBoxHeight_ = 50;

}

Mace::Mace(Vector2D pos, Transport* p1, Transport* p2) :Utensil(pos, p1, p2){
	texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cuchillo);
	myType = Resources::UtensilType::Mace;
	range_ = 100;
	attackHitBoxWidth_ = 100;
	attackHitBoxHeight_ = 50;
}


Grater::Grater(Vector2D pos, Transport* p1, Transport* p2) :Utensil(pos, p1, p2) {
	texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cuchillo);
	myType = Resources::UtensilType::Grater;
	range_ = 100;
	attackHitBoxWidth_ = 100;
	attackHitBoxHeight_ = 50;
}


Net::Net(Vector2D pos, Transport* p1, Transport* p2) :Utensil(pos, p1, p2) {
	texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cuchillo);
	myType = Resources::UtensilType::Net;
	range_ = 100;
	attackHitBoxWidth_ = 100;
	attackHitBoxHeight_ = 50;
}