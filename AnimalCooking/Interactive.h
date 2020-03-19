#pragma once
#include "Vector2D.h"
class Transport;
class Interactive {
public:
	void setPos(Vector2D newPos) { position_ = newPos; }
	Vector2D getPos() { return position_; }

	void setSize(Vector2D newSize) { size_ = newSize; }
	Vector2D getSize() { return size_; }

	void setRot(double newRot) { rotation_ = newRot; }
	double getRot() { return rotation_; }

	~Interactive() {}

	virtual void action1(int player) {};
	virtual void action2(int player) {};
	virtual void action3(int player) {};
	virtual void action4(int player) {};

protected:

	Interactive(Transport* p1, Transport* p2) : player1_(p1), player2_(p2), position_(), size_(), rotation_() {};

	Transport* player1_;
	Transport* player2_;
	Vector2D position_;
	Vector2D size_;
	double rotation_;
};

