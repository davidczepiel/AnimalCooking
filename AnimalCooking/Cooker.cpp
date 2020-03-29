#include "Cooker.h"
#include "SDLGame.h"
#include "SDL_macros.h"
#include "InsertExpel.h"

Cooker::Cooker(Vector2D& pos, Vector2D& size, double rot, Texture* text, Transport* t1, Transport* t2,Entity* e) : Interactive(t1,t2),
	state_(CookerStates::empty), cookingTime_(5),entity_(e)
{
	setPos(pos);
	setSize(size);
	setRot(rot);
	setEmptyTexture();
	timer_ = new Timer();
}

Cooker::~Cooker() {
	delete timer_;
	timer_ = nullptr;
}

void Cooker::setCookerState(CookerStates s) { 
	switch (s) {
		case CookerStates::empty:  setEmptyTexture(); break;
		case CookerStates::cooking: setCookingTexture(); break;
		case CookerStates::cooked:  setCookedTexture(); break;
		case CookerStates::burned:  setFullTexture(); break;
	}
	state_ = s; 
};

void Cooker::draw()
{
	SDL_Rect rect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());

	texture_->render(rect, rotation_); //Cambiar para usar animaciones
}

void Cooker::action1(int player)
{
	InsertExpel* ie = entity_->getComponent<InsertExpel>(ecs::InsertExpel);
	if (this->getCookerState() == CookerStates::empty)
	{
		ie->insertFood(this);
	}
	else 
	{
		ie->extractFood(this);
	}
}

Skillet::Skillet(Vector2D& pos, Vector2D& size, double rot, Texture* text,Transport* t1,Transport* t2, Entity* e) : Cooker(pos, size, rot, text,t1,t2,e)
{
	cookingTime_ = 10 * 1000;
	cookerType_ = Resources::Cookers::Skillet;
}

Oven::Oven(Vector2D& pos, Vector2D& size, double rot, Texture* text, Transport* t1, Transport* t2, Entity* e) : Cooker(pos, size, rot, text,t1,t2,e)
{
	cookingTime_ = 15 * 1000;
	cookerType_ = Resources::Cookers::Oven;
}