#pragma once
#include "Component.h"
#include "Interactive.h"
#include "Transport.h"
#include "Pickable.h"
#include "ShelfViewer.h"
#include "Entity.h"
#include "ShelfViewer.h"
#include "Utensil.h"
class Shelf :
	public Entity, public Interactive
{
	Pickable* content;
public:
	Shelf(Pickable* c,Transport* p1, Transport* p2);
	void Swap(int id);
	virtual void interactive(int id);
	Pickable* getContent() { return content; }
};

