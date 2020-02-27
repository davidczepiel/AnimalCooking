#include "Button.h"

Button::Button()
{
	pos_ = Vector2D();
	size_ = Vector2D();
	background_ = nullptr;
	text_ = nullptr;
	app_ = nullptr;
	callback_ = nullptr;
}

void Button::configureButton(Vector2D pos, Vector2D size, Texture* background, Texture* text, AnimalCooking* app, CallBackOnClick* callback)
{
	pos_ = pos;
	size_ = size;
	background_ = background;
	text_ = text;
	app_ = app;
	callback_ = callback;
}
