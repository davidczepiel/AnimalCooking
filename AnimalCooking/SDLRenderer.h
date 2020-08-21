#pragma once
#include "Component.h"
#include "Transform.h"
#include "Texture.h"

class SDLRenderer : public Component
{
public:
	SDLRenderer(Texture* t, Vector2D size);
	void init() override;
	void draw() override;
private:
	void renderColumn(size_t x, size_t restX);

	Vector2D size;
	Transform* tr;
	Texture* t;
};

