#pragma once
#include "Component.h"
#include "Transform.h"

class MenuButtonRenderer : public Component
{
private:
	Transform* tr_;
	Texture* texture;
	bool focused;

public:
	MenuButtonRenderer(Texture* t) : Component(ecs::MenuButtonRenderer), texture(t),focused(false) {}
	~MenuButtonRenderer() { texture = nullptr; }
	void setFocused(bool f) { focused = f; }
	void init() override;
	void draw() override;

	void setTexture(Texture* t) { texture = t; }
};

