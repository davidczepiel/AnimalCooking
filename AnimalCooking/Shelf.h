#pragma once
#include "Component.h"
#include "Interactive.h"
#include "Transport.h"
#include "Pickable.h"
#include "ShelfViewer.h"
#include "Entity.h"
#include "SDLGame.h"
#include "ShelfViewer.h"
#include "Utensil.h"
#include "Dish.h"
#include "Manager.h"
#include "DishFinisher.h"

enum Orientation : size_t {
	Down,
	Top,
	Left,
	Right,

	DownLeft,
	DownRight,
	TopLeft,
	TopRight
};

class Shelf : public Entity, public Interactive	
{

public:
	Shelf(Vector2D pos ,Pickable* c,Transport* p1, Transport* p2, EntityManager* mng, Texture* texture);
	~Shelf() {}

	void Swap(Transport* player, Resources::PickableType onPlayerHands);
	virtual void action1(int id) override;
	virtual void action2(int id) override;
	virtual void action3(int id) override;
	virtual void action4(int id) override;
	virtual void action5(int id) override;
	virtual void feedback(int player) override;
	void onCollisionExit(int id) override;

	void setContentPos();
	Pickable* getContent() { return content; }

	void setOrientation(const Orientation& lookingAt) {
		lookingAt_ = lookingAt;
	}

private:

	Orientation lookingAt_;

	DishFinisher* dishFinisher;
	Pickable* content;
	Resources::PickableType contentType;
};

