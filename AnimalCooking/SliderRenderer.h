#pragma once
#include "Component.h"
#include "Transform.h"
#include "SliderBehaviour.h"

class SliderRenderer : public Component
{
private:
	Texture* sliderBackground_;
	Texture* sliderMovePoint_;

	Transform* transform_;
	SliderBehaviour* sliderBehav_;

public:
	SliderRenderer() : Component(ecs::SliderRenderer), transform_(nullptr), sliderBehav_(nullptr), sliderBackground_(nullptr), sliderMovePoint_(nullptr) {}

	void init() override;
	void draw() override;
};

