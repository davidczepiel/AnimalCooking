#pragma once
#include "Component.h"
#include "Interactive.h"
#include "Transport.h"
#include "Pickable.h"
#include "ShelfViewer.h"
#include "Entity.h"
#include "ShelfViewer.h"
#include "Utensil.h"
#include "Dish.h"
class Shelf :
	public Entity, public Interactive
{
	Pickable* content;
	Resources::PickableType contentType;

public:
	Shelf(Pickable* c,Transport* p1, Transport* p2);
	void Swap(Transport* player, Resources::PickableType onPlayerHands);
	virtual void action1(int id);
	Pickable* getContent() { return content; }
};

