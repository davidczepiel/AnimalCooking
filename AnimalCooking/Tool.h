#pragma once
#include "Pickable.h"

class GameLogic;

class Tool : public Pickable
{
public:
	virtual void attack(Vector2D dir) = 0;
protected:
	Tool(Transport* p1, Transport* p2, Texture* t) : Pickable(p1, p2, t) {}
	Tool() : Pickable(nullptr, nullptr, nullptr) {}
	~Tool() {}
};

class Bucket : public Tool 
{
public:
	void attack(Vector2D dir) override;
protected:
	Bucket(Transport* p1, Transport* p2, Texture* t) : Tool(p1, p2, t) {}
	Bucket() : Tool() {}
	~Bucket() {}

	GameLogic* gameLogic_;
};

