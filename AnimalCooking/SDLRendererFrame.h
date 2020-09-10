#pragma once
#include "Component.h"
#include "Texture.h"
#include "Transform.h"

class SDLRendererFrame : public Component
{
public:
	SDLRendererFrame(Texture* t, Uint8 alpha);

	void init() override;
	void draw() override;

private:
	Transform* tr;
	Texture* t_;
};

