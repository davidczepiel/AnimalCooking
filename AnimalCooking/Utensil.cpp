#include "Utensil.h"
#include "SDLGame.h"
#include "SDL_macros.h"
#include "GameLogic.h"
#include <math.h> 

Utensil::Utensil(Transport* p1, Transport* p2) : Pickable(p1, p2, nullptr) {
	myDirt_ = 0;
	maxDirt_ = 100;
	maxTimeOnFloor_ = 10;
	dirtTimer_ = new Timer();
	dirtTimer_->setTime(maxTimeOnFloor_);
	range_ = 100;
	attackHitBoxWidth_ = 100;
	attackHitBoxHeight_ = 50;
	attackRate_ = 1000;
	lastAttack_ = SDL_GetTicks();
	myState = State::shelf;
	dirty_ = false;
	cleanUpSpeed_ = 25;
	speed_ = Vector2D(0, 0);
	frameAttack = 0;
	attacking_ = false;
	lastFrameTick = 0;
	gameLogic = nullptr;
	size_ = Vector2D(50, 50);
}


Utensil::~Utensil() {
	delete dirtTimer_;
	dirtTimer_ = nullptr;
}

void Utensil::update() {

	if (myState != State::playerHand) {
		if (myState == State::floor) {  //Si me encuentro en el suelo puedo empezar a ensuciarme
			dirtTimer_->update();
			if (dirtTimer_->isTimerEnd()) {
				dirty_ = true;
				myDirt_ = maxDirt_;
				dirtTimer_->timerReset();
			}
		}
	}
	else
	{
		Pickable::update();
		//En caso de que este en la mano y haya atacado, voy aumentando el frame de la animaci�n que estoy mostrando
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
		if (!dirty_ && gameLogic != nullptr) {  //Solo si estoy limpio mi ataque deberia hacer algo significativo
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


void Utensil::onDrop(bool onFloor) {

	if (onFloor) {
		Pickable::onDrop(onFloor);
		myState = State::floor;
		dirtTimer_->timerStart();
	}
	else
		myState = State::shelf;
}


void Utensil::onPick() {
	//Me cambio de estado y desactivo el timer de suciedad
	myState = State::playerHand;
	dirtTimer_->timerReset();
}

void Utensil::action1(int player) {
	//Solo me llaman a mi action1 si estoy en el suelo,
	//Porque si estoy en una repisa ya hace los ajustes necesarios ella misma
	//Y si estoy en la mano de un player no debería llamarse a esta action
	if (myState == State::floor) {
		onPick();
		if (player == 0)
			player1_->pick(this, Resources::PickableType::Utensil);
		else
			player2_->pick(this, Resources::PickableType::Utensil);
	}
}

void Utensil::feedback()
{
	SDL_Rect rect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
	feedbackVisual_->render(rect);
}



void Utensil::changeDirtySpeed(int speedModifier) {
	//Este método es parte de las adversidades, hay que ver
	//cómo se administra esto, como se le quita tiempo al timer de ensuciarse
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

Knife::Knife(Transport* p1, Transport* p2) :Utensil(p1, p2) {
	cleantexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cuchillo);
	dirtyTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CuchilloSucio);
	attackTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cuchillo);
	feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CuchilloFeedBack);
	myType = Resources::UtensilType::Knife;
	range_ = 100;
	attackHitBoxWidth_ = 100;
	attackHitBoxHeight_ = 50;

}


Mace::Mace(Transport* p1, Transport* p2) :Utensil(p1, p2) {
	cleantexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CuchilloSucio);
	dirtyTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Mace);
	attackTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cuchillo);
	feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CuchilloFeedBack);
	myType = Resources::UtensilType::Mace;
	range_ = 100;
	attackHitBoxWidth_ = 100;
	attackHitBoxHeight_ = 50;
}


Grater::Grater(Transport* p1, Transport* p2) :Utensil(p1, p2) {
	cleantexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Grater);
	dirtyTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Grater);
	attackTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cuchillo);
	feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CuchilloFeedBack);
	myType = Resources::UtensilType::Grater;
	range_ = 100;
	attackHitBoxWidth_ = 100;
	attackHitBoxHeight_ = 50;
}


Net::Net(Transport* p1, Transport* p2) :Utensil(p1, p2) {
	cleantexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Net);
	dirtyTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Net);
	attackTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cuchillo);
	feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CuchilloFeedBack);
	myType = Resources::UtensilType::Net;
	range_ = 100;
	attackHitBoxWidth_ = 100;
	attackHitBoxHeight_ = 50;
}