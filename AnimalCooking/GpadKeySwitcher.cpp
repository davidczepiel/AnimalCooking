#include "GpadKeySwitcher.h"
#include "Entity.h"
#include "Transform.h"
#include "GPadController.h"
#include "ConfigState.h"

void GpadKeySwitcher::init()
{
	config::Options::GPadButtons& keys = SDLGame::instance()->getOptions().players_gPadButtons[player_];
	Transform* t = GETCMP1_(Transform);
	switchers_.reserve(6);
	switchers_.emplace_back(new SwitcherGPad(Vector2D(t->getPos().getX(), t->getPos().getY()), Vector2D(), keys.ATTACK, Resources::TextureId::AttackText, player_));
	switchers_.emplace_back(new SwitcherGPad(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() / 6), Vector2D(), keys.OPEN, Resources::TextureId::OpenText, player_));
	switchers_.emplace_back(new SwitcherGPad(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() * 2 / 6), Vector2D(), keys.PICKUP, Resources::TextureId::PickUpText, player_));
	switchers_.emplace_back(new SwitcherGPad(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() * 3 / 6), Vector2D(), keys.FINISHER, Resources::TextureId::FinishText, player_));
	switchers_.emplace_back(new SwitcherGPad(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() * 4 / 6), Vector2D(), keys.NEXT, Resources::TextureId::NextText, player_));
	switchers_.emplace_back(new SwitcherGPad(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() * 5 / 6), Vector2D(), keys.PREVIOUS, Resources::TextureId::PreviousText, player_));

	for (auto& s : switchers_)
		s->setSize(Vector2D(buttonWidth_, buttonHeight_));
}

void GpadKeySwitcher::update()
{
	if (!update_)
		return;

	if (navEnabled) {
		GPadController* gpad = GPadController::instance();
		if (gpad->isAnyButtonJustPressed()) {
			if (gpad->playerPressed(player_, SDL_CONTROLLER_BUTTON_DPAD_DOWN)) focus++;
			else if (gpad->playerPressed(player_, SDL_CONTROLLER_BUTTON_DPAD_UP)) focus--;
			if (focus < 0) focus = 0;
			else if (focus > 5) focus = 5;
		}
	}
	if (focus >= 0) switchers_[focus]->update();
}

void GpadKeySwitcher::setFocushed(const int& delta)
{
	if (delta == -1) update_ = !update_;
	else focus = delta;
}

void GpadKeySwitcher::addFocushed(const int& delta)
{
	if (!switchers_[focus]->getPlayerIsChoosing())
		focus = (focus + 6 + delta) % 6;
}
