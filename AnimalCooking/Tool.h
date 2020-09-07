#pragma once
#include "Pickable.h"
#include "Entity.h"

class GameLogic;

class Tool : public Pickable
{
public:
	virtual void attack(Vector2D dir) = 0;
	void setGameLogic(GameLogic* glc) { gameLogic = glc; }
	virtual void onDrop(bool onFloor) = 0;
	virtual void onPick() = 0;
protected:
	//Estado
	enum  State
	{
		floor, playerHand, shelf
	};
	Tool(Transport* p1, Transport* p2) : Pickable(p1, p2, nullptr) {}
	Tool() : Pickable(nullptr, nullptr, nullptr) {}
	~Tool() {}

	GameLogic* gameLogic;
	State myState;
};

class Bucket : public Entity, public Tool
{
public:
	Bucket(Transport* p1, Transport* p2);
	Bucket() : Tool() {}
	~Bucket() {}

	void attack(Vector2D dir) override;
	void fillBucket();
	void onPick() override;
	void action1(int player) override;
	void feedback(int player) override;
	void onDrop(bool onFloor) override;
	void updating() { Pickable::update(); }
	void render();
	int getwaterStacks() { return waterStacks_; }
protected:
	int waterStacks_, maxStacks_;

	int lastAttack_;
	int attackRate_;
	int attackHitBoxWidth_;
	int attackHitBoxHeight_;
	int rangeX_;
	int rangeY_;

	Texture* bucketTexture;
};

