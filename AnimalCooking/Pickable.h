#pragma once
#include "Vector2D.h"

class Pickable
{
public:

	void setSpeed(Vector2D newSpeed) { speed_ = newSpeed; }
	
	void setPos(Vector2D newPos) { position_ = newPos; }
	Vector2D getPos() { return position_; }

protected:
	Vector2D speed_;
	Vector2D position_;

	//Los updates de las clases hijas deben llamar a este update
	virtual void update() {
		position_ = position_ + speed_;
	}
};

