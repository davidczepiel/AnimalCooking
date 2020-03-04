#pragma once
#include "Component.h"
#include "Transform.h"
#include "ButtonBehaviour.h"
class ButtonRenderer : public Component
{
private:
	Transform* ownerTransform_;
	ButtonBehaviour* buttonBehaviour_;

	Texture* background_;
	Texture* text_;
public:
	ButtonRenderer(Texture* background, Texture* text);
	void init() override;
	void draw() override;
};

