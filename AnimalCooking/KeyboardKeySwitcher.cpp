#include "KeyboardKeySwitcher.h"
#include "Entity.h"
#include "Transform.h"

void KeyboardKeySwitcher::init()
{
	config::Options::KeyboardKeys& keys = SDLGame::instance()->getOptions().players_keyboardKeys[player_];
	Transform* t = GETCMP1_(Transform);
	switchers_.reserve(6);
	switchers_.emplace_back(new SwitcherKeyboard(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() / 7), Vector2D(), keys.ATTACK, Resources::TextureId::AttackText));
	switchers_.emplace_back(new SwitcherKeyboard(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() * 2 / 7), Vector2D(), keys.OPEN, Resources::TextureId::OpenText));
	switchers_.emplace_back(new SwitcherKeyboard(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() * 3 / 7), Vector2D(), keys.PICKUP, Resources::TextureId::PickUpText));
	switchers_.emplace_back(new SwitcherKeyboard(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() * 4 / 7), Vector2D(), keys.FINISHER, Resources::TextureId::FinishText));
	switchers_.emplace_back(new SwitcherKeyboard(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() * 5 / 7), Vector2D(), keys.NEXT, Resources::TextureId::NextText));
	switchers_.emplace_back(new SwitcherKeyboard(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() * 6 / 7), Vector2D(), keys.PREVIOUS, Resources::TextureId::PreviousText));

	for (auto& s : switchers_)
		s->setSize(Vector2D(buttonWidth_, buttonHeight_));
}

void KeyboardKeySwitcher::update()
{
	for (auto* s : switchers_)
		s->update();
}
