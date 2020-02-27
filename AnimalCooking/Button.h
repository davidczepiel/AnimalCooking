#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "AnimalCooking.h"
class Button
{
	using CallBackOnClick = void(AnimalCooking* app);
private:
	Vector2D pos_;
	Vector2D size_;
	Texture* background_;
	Texture* text_;
	
	AnimalCooking* app_;
	CallBackOnClick* callback_;
	bool inUse_;

public:
	Button();
	void configureButton(Vector2D pos, Vector2D size, Texture* background, Texture* text, AnimalCooking* app, CallBackOnClick* callback);
	bool inUse() { return inUse_; }
};

