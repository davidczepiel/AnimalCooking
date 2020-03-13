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
protected:

	Interactive(Transport* p1, Transport* p2) : player1_(p1), player2_(p2), position_(), size_(), rotation_() {};
	~Interactive() { delete player1_;  delete player1_; }

	void interactive() {};

	Transport* player1_;
	Transport* player2_;
	Vector2D position_;
	Vector2D size_;
	double rotation_;
};

