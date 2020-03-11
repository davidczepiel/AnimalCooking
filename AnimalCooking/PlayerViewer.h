#pragma once
#include "Component.h"
#include "Texture.h"
#include "Transform.h"
#include "Entity.h"

class PlayerViewer : public Component {
public:
	PlayerViewer(Texture* t) : Component(ecs::PlayerViewer), texture_(t) {};
	void init() override;
	void draw() override;
private:
	Texture* texture_ = nullptr;
	Transform* tr_ = nullptr;
};

