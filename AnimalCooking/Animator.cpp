#include "Animator.h"

Animator::Animator() : Component(ecs::Animator),dt(DefaultTimer(config::ANIM_TIME)),dir(Vector2D(0,0))
{
}
