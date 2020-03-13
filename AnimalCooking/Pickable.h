#pragma once
#include "Vector2D.h"

class Pickable
{
public:

	void setSpeed(Vector2D newSpeed) { speed_ = newSpeed; }
	Vector2D getSpeed() { return speed_; }
	
	void setPos(Vector2D newPos) { position_ = newPos; }
	Vector2D getPos() { return position_; }

	void setSize(Vector2D newSize) { size_ = newSize; }
	Vector2D getSize() { return size_; }

protected:
	Vector2D speed_;
	Vector2D position_;
	Vector2D size_;

	Pickable(){}

	//Los updates de las clases hijas deben llamar a este update
	virtual void update() {
		position_ = position_ + speed_;
	}
};

