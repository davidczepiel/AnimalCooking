#include "Utensil.h"
#include "SDLGame.h"
#include "SDL_macros.h"
#include "GameLogic.h"
#include <math.h> 
#include "TimerViewer.h"
#include "GPadController.h"

Utensil::Utensil(Transport* p1, Transport* p2) : Pickable(p1, p2, nullptr) {
	myDirt_ = 0;
	maxDirt_ = 100;
	maxTimeOnFloor_ = config::MAX_TIME_ON_FLOOR * 1000;
	dirtTimer_ = new UtensilTimer();
	dirtTimer_->setSize(Vector2D(100, 30));
	dirtTimer_->setTime(maxTimeOnFloor_);
	rangeX_ = 100;
	rangeY_ = 100;
	attackHitBoxWidth_ = 100;
	attackHitBoxHeight_ = 50;
	attackRate_ = 500;
	lastAttack_ = SDL_GetTicks();
	myState = State::shelf;
	dirty_ = false;
	speed_ = Vector2D(0, 0);
	frameAttack = 0;
	attacking_ = false;
	displayIcon_ = false;
	lastFrameTick = 0;
	gameLogic = nullptr;

	GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(dirtTimer_);
}


Utensil::~Utensil() {
}

void Utensil::update() {

	if (myState != State::playerHand) {
		if (myState == State::floor && !dirty_) {  //Si me encuentro en el suelo puedo empezar a ensuciarme
			dirtTimer_->update();
			if (dirtTimer_->isTimerEnd()) {
				dirty_ = true;
				myDirt_ = maxDirt_;
				dirtTimer_->timerReset();				
			}
		}
		else
			dirtTimer_->timerReset();
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
			ataque.x = position_.getX() + (velNormalizada.getX() * rangeX_);
			ataque.y = position_.getY() + (velNormalizada.getY() * rangeY_);
			ataque.w = attackHitBoxWidth_;
			ataque.h = attackHitBoxHeight_;
			gameLogic->hitIngredient(ataque, myType);
		}
	}
}


void Utensil::render()const {
	SDL_Rect rect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());

	//Si no esta en las manos del jugador,es decir en el suelo o en repsias,se renderiza
	if (myState != State::playerHand)
	{
		if (!dirty_ && !attacking_)
			cleantexture_->render(rect); //EN caso de que solo est� en la mano del jugador	
		else if (!dirty_ && attacking_) {
			attackTexture_->render(rect); //EN caso de estar atacando habr�a que hacer un renderFrame
		}
		else
			dirtyTexture_->render(rect); //Cambiar si los ingredientes vienen todos en una misma textura para usar el clip	
	}
	if (displayIcon_) {
		rect.y -= rect.h;
		iconTexture_->render(rect);
	}
}


void Utensil::onDrop(bool onFloor) {

	if (onFloor) {
		Pickable::onDrop(onFloor);
		myState = State::floor;
		dirtTimer_->timerStart();
		dirtTimer_->setPos(Vector2D(position_.getX(), position_.getY() - 50));
		SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Drop, 0);
	}
	else
		myState = State::shelf;
}


void Utensil::onPick() {
	//Me cambio de estado y desactivo el timer de suciedad
	myState = State::playerHand;
	dirtTimer_->timerReset();
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::PickUp, 0);
}

void Utensil::action1(int player) {
	//Solo me llaman a mi action1 si estoy en el suelo,
	//Porque si estoy en una repisa ya hace los ajustes necesarios ella misma
	//Y si estoy en la mano de un player no debería llamarse a esta action
	if (myState == State::floor) {
		Transport* playerT = nullptr;
		if (player == 0)
			playerT = player1_;
		else
			playerT = player2_;

		if (playerT->getObjectTypeInHands() != Resources::PickableType::Dish)
		{
			onPick();
			playerT->pick(this, Resources::PickableType::Utensil);
		}
	}
}

void Utensil::feedback(int player)
{
	SDL_Rect rect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
	if (myState != State::playerHand) {
		if (SDLGame::instance()->getOptions().showKeyToPress) {
			if (GPadController::instance()->playerControllerConnected(player))
				SDLGame::instance()->renderFeedBack(position_, "Pick up", SDL_GameControllerGetStringForButton(SDLGame::instance()->getOptions().players_gPadButtons[player].PICKUP));
			else
				SDLGame::instance()->renderFeedBack(position_, "Pick up", SDL_GetKeyName(SDLGame::instance()->getOptions().players_keyboardKeys[player].PICKUP));
		}
		feedbackVisual_->render(rect);
	}
}



void Utensil::changeDirtySpeed(int speedModifier) {
	if (myState == State::floor)
		dirtTimer_->setTime(dirtTimer_->getTime() + speedModifier);
}

void Utensil::resetDirtTimer()
{
	dirtTimer_->setTime(maxTimeOnFloor_);
}

void Utensil::cleanUp() {
	//Me deberia llamar el fregadero para decime que me limpie
	if (dirty_) {
		myDirt_ = 0;
		dirty_ = false;
	}
}



///////////////////////////////////////

Knife::Knife(Transport* p1, Transport* p2) :Utensil(p1, p2) {
	cleantexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cuchillo);
	dirtyTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CuchilloSucio);
	attackTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cuchillo);
	feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CuchilloFeedBack);
	iconTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ButtonConfig);

	myType = Resources::UtensilType::Knife;
	rangeX_ = config::KNIFE_RANGE * SDLGame::instance()->getCasillaX();
	rangeY_ = config::KNIFE_RANGE * SDLGame::instance()->getCasillaY();
	attackHitBoxWidth_ = config::KNIFE_HITBOX_WIDTH * SDLGame::instance()->getCasillaX();
	attackHitBoxHeight_ = config::KNIFE_HITBOX_HEIGHT * SDLGame::instance()->getCasillaY();
}


Mace::Mace(Transport* p1, Transport* p2) :Utensil(p1, p2) {
	cleantexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Maza);
	dirtyTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::MazaSucia);
	attackTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Maza);
	feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::MazoFeedBack);
	iconTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ButtonBin);

	myType = Resources::UtensilType::Mace;
	rangeX_ = config::MACE_RANGE * SDLGame::instance()->getCasillaX();
	rangeY_ = config::MACE_RANGE * SDLGame::instance()->getCasillaY();
	attackHitBoxWidth_ = config::MACE_HITBOX_WIDTH * SDLGame::instance()->getCasillaX();
	attackHitBoxHeight_ = config::MACE_HITBOX_HEIGHT * SDLGame::instance()->getCasillaY();
}


Grater::Grater(Transport* p1, Transport* p2) :Utensil(p1, p2) {
	cleantexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Rallador);
	dirtyTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RalladorSucio);
	attackTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cuchillo);
	feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RalladorFeedBack);
	iconTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ButtonBin);

	myType = Resources::UtensilType::Grater;
	rangeX_ = config::GRATER_RANGE * SDLGame::instance()->getCasillaX();
	rangeY_ = config::GRATER_RANGE * SDLGame::instance()->getCasillaY();
	attackHitBoxWidth_ = config::GRATER_HITBOX_WIDTH * SDLGame::instance()->getCasillaX();
	attackHitBoxHeight_ = config::GRATER_HITBOX_HEIGHT * SDLGame::instance()->getCasillaY();
}


Net::Net(Transport* p1, Transport* p2) :Utensil(p1, p2) {
	cleantexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Red);
	dirtyTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RedSucia);
	attackTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cuchillo);
	feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RedFeedBack);
	iconTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ButtonBin);

	myType = Resources::UtensilType::Net;
	rangeX_ = config::NET_RANGE * SDLGame::instance()->getCasillaX();
	rangeY_ = config::NET_RANGE * SDLGame::instance()->getCasillaY();
	attackHitBoxWidth_ = config::NET_HITBOX_WIDTH * SDLGame::instance()->getCasillaX();
	attackHitBoxHeight_ = config::NET_HITBOX_HEIGHT * SDLGame::instance()->getCasillaY();
}