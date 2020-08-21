#pragma once
#include "Component.h"
#include "IngredientsPool.h"
#include "SDLRenderer.h"
class WallOpacityManager : public Component
{
public:
	WallOpacityManager(IngredientsPool* ingPool) : Component(ecs::WallOpacityManager), ingPool_(ingPool), renderer_(nullptr), tr_(nullptr){}
	void init() override;
	void update() override;
private:
	IngredientsPool* ingPool_;
	SDLRenderer* renderer_;
	Transform* tr_;
};

