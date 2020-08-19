#pragma once
#include "Component.h"
#include "Transform.h"
#include "SliderBehaviour.h"

class SliderRenderer : public Component
{
public:
	SliderRenderer() : Component(ecs::SliderRenderer), 
		sliderBackground_(nullptr), sliderSelectedBackground_(nullptr), 
		sliderMovePoint_(nullptr), sliderSelectedMovePoint_(nullptr),
		transform_(nullptr), sliderBehav_(nullptr) {}
	void init() override;
	void draw() override;

private:
	Texture* sliderBackground_;
	Texture* sliderSelectedBackground_;
	Texture* sliderMovePoint_;
	Texture* sliderSelectedMovePoint_;
	Transform* transform_;
	SliderBehaviour* sliderBehav_;
};

