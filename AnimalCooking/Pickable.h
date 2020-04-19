#pragma once
#include "Interactive.h"

class Pickable : public Interactive
{
public:

	void setSpeed(Vector2D newSpeed) { speed_ = newSpeed; }
	Vector2D getSpeed() { return speed_; }
	
	virtual void onDrop(bool onFloor);
	virtual void onPick() = 0;

protected:
	Vector2D speed_;
	Pickable() : Interactive(nullptr, nullptr, nullptr) {}
	Pickable(Transport* p1, Transport* p2, Texture* t): Interactive(p1,p2,t) {}
	~Pickable() {};
	//Los updates de las clases hijas deben llamar a este update
	virtual void update() {
		position_ = position_ + speed_;
	}
};

