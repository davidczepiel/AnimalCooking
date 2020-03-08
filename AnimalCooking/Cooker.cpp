#include "Cooker.h"
#include "SDLGame.h"
#include "SDL_macros.h"

Cooker::Cooker(Vector2D& pos, Vector2D& size, double rot, Texture* text) : 
		imCooking(nullptr), imBurning(nullptr), 
		startTime(), cookingTime(), burningTime(), 
		isBurned(false)
{
	setPos(pos);
	setSize(size);
	setRot(rot);
	setTexture(text);
}

void Cooker::stopCooking()
{
	imCooking = nullptr;
	imBurning = nullptr;
}

void Cooker::update()
{
	//TODO: Cambiar de comida
	if (imCooking != nullptr && startTime - SDLGame::instance()->getTime() < cookingTime * 1000) {
		imBurning = imCooking;
		imCooking = nullptr;
		startTime = SDLGame::instance()->getTime();
	}
	if (imBurning != nullptr && startTime - SDLGame::instance()->getTime() < burningTime) {
		isBurned = true;
		imBurning = nullptr;
	}
}

void Cooker::draw()
{
	SDL_Rect rect = RECT(pos_.getX(), pos_.getY(), size_.getX(), size_.getY());

	texture_->render(rect, rot_); //Cambiar para usar animaciones
}

void Cooker::startCooking(Food* food)
{
	startTime = SDLGame::instance()->getTime();
	imCooking = food;
	isBurned = false;
	imBurning = nullptr;
}

Food* Cooker::getCooking()
{
	Food* f = imCooking;
	if (f == nullptr) f = imBurning;
	stopCooking();

	return f;
}

Sarten::Sarten(Vector2D& pos, Vector2D& size, double rot, Texture* text) : Cooker(pos, size, rot, text)
{
}
