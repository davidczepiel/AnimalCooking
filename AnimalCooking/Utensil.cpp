#include "Utensil.h"
#include "SDLGame.h"
#include "SDL_macros.h"




Utensil::Utensil(Entity* p, Texture* c, Texture* d) {
	myDirt_ = 0;
	maxDirt_ = 100;
	getDirtSpeed_ = 10;
	range_ = 100;
	attackHitBoxWidth_ = 100;
	attackHitBoxHeight_ = 50;
	attackRate_ = 1000;
	lastAttack_ = SDL_GetTicks();
	player_ = p;
	texture_ = c;
	secondTexture_ = d;
	myState= State::shelf;
	dirty_ = false;
	ableToClean_ = false;
	interactionTrigger_.x = 100;
	interactionTrigger_.y = 100;
	interactionTrigger_.w = 100;
	interactionTrigger_.h = 100;
	cleanUpSpeed_ = 25;
}


void Utensil::update() {

	if (myState != State::playerHand) {

		if (myState == State::floor)  //Si me encuentro en el suelo puedo empezar a ensuciarme
			myDirt_ += getDirtSpeed_;

		// Hay que comprobar todo el rato SI NO ESTOY EN LA MANO DEL JUGADOR, comprobar si está cerca para interactuar conmig
		//	Transform* tr =GETCMP2_(player,Transform);   // Este transform no es definitivo, es para salir del paso rápido
		//if(Collisions::collides(tr->getPos(), tr->getW(), tr->getH(), pos_, size_.getX(),size_.getY()) && SDLGame::instance()->getInputHandler()->isKeyDown(SDL_Scancode(0))){
		//Posiblemente hacer que salga un brilli brilli
		//}
		
	}
}

void Utensil::render()const {
		SDL_Rect rect = RECT(pos_.getX(), pos_.getY(), size_.getX(), size_.getY());
		texture_->render(rect); //Cambiar si los ingredientes vienen todos en una misma textura para usar el clip	
}


void Utensil::drop(bool suelo) {
	//Hay que volver a situar el trigger en la nueva zona
interactionTrigger_.x = pos_.getX()- (interactionTrigger_.w/2);
interactionTrigger_.y = pos_.getY()- (interactionTrigger_.h/2);

	if (suelo)
		myState = State::floor;
	else
		myState= State::shelf;
}


void Utensil::pickMe(){
		myState = State::playerHand;
}

void Utensil::attack(Vector2D dir){
		if (SDL_GetTicks() > lastAttack_ + attackRate_) {
			lastAttack_ = SDL_GetTicks();
			cout << "ataque";
		}
}

void Utensil::inTheWasher(bool x) {
	ableToClean_ = x;
}

void Utensil::changeDirtySpeed(int speedModifier) {
	getDirtSpeed_ += speedModifier;
}

void Utensil::cleanUp() {
	//Transform* tr = GETCMP2(player, Transform);
	if (dirty_ && ableToClean_ /*&& Collisions::collides(tr->getPos(), tr->getW(), tr->getH(), pos_, size_.getX(), size_.getY())*/ && SDLGame::instance()->getInputHandler()->isKeyDown(SDL_Scancode(0))) {
		myDirt_ -= cleanUpSpeed_;
		if (myDirt_ <= 0)dirty_ = false;
	}


}
