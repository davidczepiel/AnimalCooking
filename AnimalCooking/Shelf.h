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
	bool utensil;
	bool dish;
public:
	Shelf(Pickable* c,Transport* p1, Transport* p2);
	void SwapUtensil(int id);
	void SwapDish(int id);
	void Save(int id);
	virtual void action1(int id);
	Pickable* getContent() { return content; }
};

