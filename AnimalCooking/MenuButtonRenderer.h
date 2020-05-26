#pragma once
#include "Component.h"
#include "Transform.h"

class MenuButtonRenderer : public Component
{
public:
	MenuButtonRenderer(Texture* t);
	~MenuButtonRenderer() { texture = nullptr; }
	void setFocused(bool f) { focused = f; }
	void init() override;
	void draw() override;

	void setTexture(Texture* t) { texture = t; }

private:
	Transform* tr_;
	Texture* texture;

	bool focused;
};

