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
class Shelf :
	public Entity, public Interactive
{

private:
	DishFinisher* dishFinisher;
	Pickable* content;
	Resources::PickableType contentType;
public:
	Shelf(Vector2D pos ,Pickable* c,Transport* p1, Transport* p2, EntityManager* mng);
	
	void Swap(Transport* player, Resources::PickableType onPlayerHands);
	virtual void action1(int id);
	virtual void action2(int id);
	virtual void action3(int id);
	virtual void action4(int id);
	virtual void action5(int id);
	virtual void feedback(int player);
	void onMoved(int id);
	Pickable* getContent() { return content; }
};

