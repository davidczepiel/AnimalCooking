#include "DirtyUtensilsAttackEvent.h"

DirtyUtensilsAttackEvent::DirtyUtensilsAttackEvent() : GameEvent()
{
	_myType = "DirtyUtensilsAttackEvent";
}

DirtyUtensilsAttackEvent::~DirtyUtensilsAttackEvent()
{
}

std::string DirtyUtensilsAttackEvent::toJson()
{
	return GameEvent::toJson() + ",\"_ingredient\":" + std::to_string(_utensil) + "},";
}
