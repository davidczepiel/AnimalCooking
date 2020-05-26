#pragma once
#include "Component.h"
#include "Transform.h"
#include "SliderBehaviour.h"

class SliderRenderer : public Component
{
public:
	SliderRenderer() : Component(ecs::SliderRenderer), transform_(nullptr), sliderBehav_(nullptr), sliderBackground_(nullptr), sliderMovePoint_(nullptr) {}
	void init() override;
	void draw() override;

private:
	Texture* sliderBackground_;
	Texture* sliderMovePoint_;

	Transform* transform_;
	SliderBehaviour* sliderBehav_;
};

