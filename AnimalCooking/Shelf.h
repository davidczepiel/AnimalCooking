#pragma once
#include "Component.h"
#include "Interactive.h"
#include "Transport.h"
#include "Pickable.h"
#include "Entity.h"
class Shelf :
	public Component, public Interactive
{
	Pickable* content;
	Transform* tr;
public:
	Shelf(Transport* p1, Transport* p2);
	void Swap(int id);
	virtual void interactive(int id);
	Pickable* getContent() { return content; }
};

