#pragma once
#include "Component.h"
#include "Texture.h"
#include "Transform.h"
#include "Entity.h"
#include "Animator.h"

class PlayerViewer : public Component {
public:
	PlayerViewer(Texture* t,Texture* t1) : Component(ecs::PlayerViewer), texture_(t),texture1_(t1) {};
	void init() override;
	void draw() override;
private:
	Texture* texture_ = nullptr;
	Texture* texture1_ = nullptr;
	Transform* tr_ = nullptr;
	Animator* animator = nullptr;
};

