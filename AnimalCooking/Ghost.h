#pragma once
#include "Entity.h"
#include "Manager.h"

class Ghost : public Entity
{
public:
	Ghost();

	const bool getActive() const { return active_; }
	void activate(const Vector2D& pos);
	void deActivate();
private:
	bool active_;
};

