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
	void setOpacity(Uint8 opacity) { alpha_ = opacity; }
private:
	void renderColumn(size_t x, size_t restX);

	Uint8 alpha_;
	Vector2D size;
	Transform* tr;
	Texture* t;
};

