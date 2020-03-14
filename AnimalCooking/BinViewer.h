#pragma once
#include "Component.h"
#include "Texture.h"
#include "Transform.h"
#include "Entity.h"

class BinViewer : public Component
{
public:
	BinViewer() : Component(ecs::BinViewer), tex_(nullptr), tr_(nullptr) {}
	~BinViewer() {}

	void init() override;
	void draw() override;
private:
	Texture* tex_;
	Transform* tr_;
};

