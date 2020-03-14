#pragma once
#include "Component.h"
#include "Transform.h"
#include "Entity.h"
class InteractionRect :	public Component
{
public:
	InteractionRect() : Component(ecs::InteractionRect) {};
	~InteractionRect(){}
	void init() override;

	void setPos(double x, double y) { pos_.setX(x * radius); pos_.setY(y * radius); }
	Vector2D getPos() { return pos_; }
	double getW() { return size_.getX(); }
	double getH() { return size_.getX(); }
private:
	const double radius = 10.5;
	Vector2D pos_;
	Vector2D size_;
};

