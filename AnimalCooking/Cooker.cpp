#include "Cooker.h"
#include "SDLGame.h"
#include "SDL_macros.h"

Cooker::Cooker(Vector2D& pos, Vector2D& size, double rot, Texture* text) : 
		state_(CookerStates::empty), cookingTime_()
{
	setPos(pos);
	setSize(size);
	setRot(rot);
	setTexture(text);
	timer_ = new Timer();
}

Cooker::~Cooker() {
	delete timer_;
	timer_ = nullptr;
}
void Cooker::draw()
{
	SDL_Rect rect = RECT(pos_.getX(), pos_.getY(), size_.getX(), size_.getY());

	texture_->render(rect, rot_); //Cambiar para usar animaciones
}

Sarten::Sarten(Vector2D& pos, Vector2D& size, double rot, Texture* text) : Cooker(pos, size, rot, text)
{
	cookingTime_ = 10 * 1000;
	cookerType_ = CookerTypes::type2;
}
