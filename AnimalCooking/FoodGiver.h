#pragma once

#include "Entity.h"
#include "Interactive.h"
#include "GameControl.h"

class FoodGiver : public Entity, public Interactive
{
public:
	~FoodGiver() {};
	void feedback(int player) override;

	inline Texture* getTexture() { return texture_; }
	inline Vector2D getPos() { return position_; }
	inline Vector2D getSize() { return size_; }

protected:
	FoodGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl,Texture* t);

	Texture* texture_;
	GameControl* gameControl_;
};

//-----------------------------------------------------

class RiceGiver : public FoodGiver //Para arroz
{
public:
	RiceGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl, Texture* t);
	void action1(int player);
};

class BreadBurgerGiver : public FoodGiver //Para pan de hamburguesa
{
public:
	BreadBurgerGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl, Texture* t);
	void action1(int player);
};

class BreadHotDogGiver : public FoodGiver //Para pan de perrito
{
public:
	BreadHotDogGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl, Texture* t);
	void action1(int player);
};


class DoughGiver : public FoodGiver //Para masa
{
public:
	DoughGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl, Texture* t);
	void action1(int player);
};

class DressingGiver : public FoodGiver //Para ali�ado/ketchup porque es lo mismo
{
public:
	DressingGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl, Texture* t);
	void action1(int player);
};