#pragma once
#include "Component.h"

class Transform;

class ImageViewer : public Component
{
public:
	ImageViewer(Texture* texture) : Component(ecs::ImageViewer), texture_(texture) {}
	ImageViewer(): Component(ecs::ImageViewer), texture_(nullptr){}

	void setTexture(Texture* texture) { texture_ = texture; }

	virtual void init() override;
	virtual void draw() override;
private:
	Texture* texture_;
	Transform* transform_;
};

