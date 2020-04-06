#pragma once

#include "Entity.h"
#include "Interactive.h"
#include "GameControl.h"

class FoodGiver : public Entity, public Interactive
{
protected:
	Texture* texture_;
	GameControl* gameControl_;

	FoodGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl)
		: Interactive(p1, p2,nullptr), gameControl_(gameControl) {
		position_ = pos;
		size_ = size;
	}

public:
	~FoodGiver() {};
	
	inline Texture* getTexture() { return texture_; }
	inline Vector2D getPos() { return position_; }
	inline Vector2D getSize() { return size_; }
};

//-----------------------------------------------------

class RiceGiver : public FoodGiver //Para arroz
{
public:
	RiceGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl);
	void action1(int player);
};

class BreadGiver : public FoodGiver //Para pan
{
public:
	BreadGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl);
	void action1(int player);
};

class DoughGiver : public FoodGiver //Para masa
{
public:
	DoughGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl);
	void action1(int player);
};

class DressingGiver : public FoodGiver //Para ali�ado/ketchup porque es lo mismo
{
public:
	DressingGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl);
	void action1(int player);
};