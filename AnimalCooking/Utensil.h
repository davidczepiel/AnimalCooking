#pragma once
#include "Texture.h"
#include "Entity.h"
#include "Collisions.h"
#include "Transform.h"


class Utensil :public Entity {

protected:
	enum  State
	{
		floor, playerHand, shelf
	};
	State myState;
	int myDirt_;
	int maxDirt_;
	int getDirtSpeed_;
	int cleanUpSpeed_;
	int range_;
	int attackHitBoxWidth_;
	int attackHitBoxHeight_;
	int attackRate_;
	int lastAttack_;
	bool dirty_;
	bool ableToClean_;
	Vector2D pos_, vel_, size_;
	Entity* player_;
	Texture* texture_;
	Texture* secondTexture_;
	SDL_Rect interactionTrigger_;

public:
	Utensil(Entity* p, Texture* c, Texture* d);
	virtual ~Utensil() {}
	virtual void render() const;
	virtual void update();
	virtual void onHit() = 0;

	void drop(bool suelo);
	void pickMe();
	void attack(Vector2D dir);
	void inTheWasher(bool x);
	void cleanUp();
	inline void setSize(double w, double h) { size_.set(w, h); }
	inline void setPos(Vector2D pos) { pos_.set(pos); }
	inline void setVel(Vector2D vel) { vel_.set(vel); }
	void changeDirtySpeed(int speedModifier);

};