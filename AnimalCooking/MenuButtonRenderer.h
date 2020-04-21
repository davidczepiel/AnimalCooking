#pragma once
#include "Component.h"
#include "Transform.h"

class MenuButtonRenderer : public Component
{
private:
	Transform* tr_;
	Texture* texture;
public:
	MenuButtonRenderer(Texture* t) : Component(ecs::MenuButtonRenderer), texture(t) {}
	~MenuButtonRenderer() { texture = nullptr; }

	void init() override;
	void draw() override;
};

