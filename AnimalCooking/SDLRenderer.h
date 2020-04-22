#pragma once
#include "Component.h"
#include "Transform.h"
#include "Texture.h"

class SDLRenderer : public Component
{
public:
	SDLRenderer(Texture* t, size_t size);
	void init() override;
	void draw() override;
private:
	size_t size;
	Transform* tr;
	Texture* t;
};

