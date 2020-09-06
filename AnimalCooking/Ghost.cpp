#include "Ghost.h"
#include "Transform.h"
#include "WallOpacityManager.h"
#include "SDLRendererFrame.h"
#include "GhostLife.h"

Ghost::Ghost() : Entity(SDLGame::instance(), nullptr), active_(false)
{
	Transform* t = addComponent<Transform>(Vector2D(), Vector2D(), 32, 64);

	addComponent<SDLRendererFrame>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Ghost), 150);
	addComponent<GhostLife>();
}

void Ghost::activate(const Vector2D& pos)
{
	active_ = true;
	getComponent<Transform>(ecs::Transform)->setPos(pos);
	getComponent<GhostLife>(ecs::GhostLife)->restart();
}

void Ghost::deActivate()
{
	active_ = false;
}
