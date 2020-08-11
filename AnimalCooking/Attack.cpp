#include "Attack.h"
#include "Tool.h"
#include "InteractionRect.h"

Attack::Attack(): Component(ecs::Attack)
{
}

void Attack::init()
{
	tr_ = GETCMP1_(Transform);
}

void Attack::attack()
{
	Pickable* p = GETCMP1_(Transport)->getObjectInHands();

	if (p == nullptr) return;

	if (GETCMP1_(Transport)->getObjectTypeInHands() == Resources::PickableType::Utensil || GETCMP1_(Transport)->getObjectTypeInHands() == Resources::PickableType::Bucket) {
		static_cast<Tool*>(p)->attack(Vector2D(GETCMP1_(InteractionRect)->getdir()));
	}
}
