#pragma once
#include "Component.h"
#include "Texture.h"
#include "Transform.h"
#include "Entity.h"
#include "Animator.h"

class PlayerViewer : public Component {
public:
	PlayerViewer(Texture* t) : Component(ecs::PlayerViewer), texture_(t) {};
	void init() override;
	void draw() override;
private:
	Texture* texture_ = nullptr;
	Transform* tr_ = nullptr;
	Animator* animator = nullptr;

	void setWalkOrAttack(SDL_Rect dest,Texture* spriteSheet,int fil1,int fil2);
	void setIdle(SDL_Rect dest,int fil1,int fil2);
};

