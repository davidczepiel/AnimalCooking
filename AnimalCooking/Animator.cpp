#include "Animator.h"
#include "GameConfig.h"

Animator::Animator() : Component(ecs::Animator),dt(DefaultTimer(config::ANIM_TIME))
{
}

