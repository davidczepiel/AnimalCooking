#pragma once
#include "Vector2D.h"
#include "Texture.h"
class Transport;
class Interactive {
public:
	void setPos(Vector2D newPos) { position_ = newPos; }
	Vector2D getPos() { return position_; }

	void setSize(Vector2D newSize) { size_ = newSize; }
	Vector2D getSize() { return size_; }

	void setRot(double newRot) { rotation_ = newRot; }
	double getRot() { return rotation_; }

	void setCanInteract(bool value) { canInteract = value; }
	bool isInteractive() { return canInteract; }

	void setTexture(Texture* t) { feedbackVisual_ = t; }
	Texture* getTexture() { return feedbackVisual_; }
	~Interactive() {}

	virtual void action1(int player) {};
	virtual void action2(int player) {};
	virtual void action3(int player) {};
	virtual void action4(int player) {};
	virtual void action5(int player) {};
	virtual void feedback(int player) {};
	virtual void onMoved(int player) {};

	void setTransports(Transport* transportP1, Transport* transportP2) {
		player1_ = transportP1;
		player2_ = transportP2;
	}

protected:

	Interactive(Transport* p1, Transport* p2, Texture* t) : player1_(p1), player2_(p2), position_(), size_(), rotation_(), feedbackVisual_(t){};
	bool canInteract= true;
	Transport* player1_;
	Texture* feedbackVisual_;
	Transport* player2_;
	Vector2D position_;
	Vector2D size_;
	double rotation_;
};

