#pragma once
#include "Component.h"
#include "Entity.h"
#include "Transport.h"
class Attack : public Component
{
public:
	Attack();

	void init();
	void attack();
private:
	Transform* tr_ = nullptr;
};

