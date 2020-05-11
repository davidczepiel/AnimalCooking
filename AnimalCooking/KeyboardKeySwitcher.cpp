#include "KeyboardKeySwitcher.h"
#include "Entity.h"
#include "Transform.h"

void KeyboardKeySwitcher::init()
{
	config::Options::KeyboardKeys& keys = SDLGame::instance()->getOptions().players_keys[player_];
	Transform* t = GETCMP1_(Transform);
	switchers_.reserve(6);
	switchers_.emplace_back(new SwitcherKeyboard(Vector2D(t->getPos().getX(), t->getPos().getY()), Vector2D(), keys.ATTACK));
	switchers_.emplace_back(new SwitcherKeyboard(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() / 6), Vector2D(), keys.OPEN));
	switchers_.emplace_back(new SwitcherKeyboard(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() * 2 / 6), Vector2D(), keys.PICKUP));
	switchers_.emplace_back(new SwitcherKeyboard(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() * 3 / 6), Vector2D(), keys.FINISHER));
	switchers_.emplace_back(new SwitcherKeyboard(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() * 4 / 6), Vector2D(), keys.NEXT));
	switchers_.emplace_back(new SwitcherKeyboard(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() * 5 / 6), Vector2D(), keys.PREVIOUS));

	for (auto& s : switchers_)
		s->setSize(Vector2D(buttonWidth_, buttonHeight_));
}

void KeyboardKeySwitcher::update()
{
	for (auto* s : switchers_)
		s->update();
}
