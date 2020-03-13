#pragma once
#include"Component.h"
class Pickable;

class Transport : public Component {
public:
	void Take(Pickable* obj);
	void Drop();
private:
	Pickable* objInHands_;
};