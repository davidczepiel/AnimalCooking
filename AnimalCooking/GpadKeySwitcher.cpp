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
	switchers_.emplace_back(new SwitcherGPad(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() / 7), Vector2D(), keys.ATTACK, "Attack", player_));
	switchers_.emplace_back(new SwitcherGPad(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() * 2 / 7), Vector2D(), keys.OPEN, "open", player_));
	switchers_.emplace_back(new SwitcherGPad(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() * 3 / 7), Vector2D(), keys.PICKUP, "Pick-up", player_));
	switchers_.emplace_back(new SwitcherGPad(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() * 4 / 7), Vector2D(), keys.FINISHER, "Finish dish", player_));
	switchers_.emplace_back(new SwitcherGPad(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() * 5 / 7), Vector2D(), keys.NEXT, "Next", player_));
	switchers_.emplace_back(new SwitcherGPad(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() * 6 / 7), Vector2D(), keys.PREVIOUS, "Previous", player_));

	for (auto& s : switchers_)
		s->setSize(Vector2D(buttonWidth_, buttonHeight_));
}

void GpadKeySwitcher::update()
{
	if (navEnabled) {
		GPadController* gpad = GPadController::instance();
		if (gpad->isAnyButtonJustPressed()) {
			if (gpad->playerPressed(player_, SDL_CONTROLLER_BUTTON_DPAD_DOWN)) focus++;
			else if (gpad->playerPressed(player_, SDL_CONTROLLER_BUTTON_DPAD_UP)) focus--;
			if (focus < 0) focus = 0;
			else if (focus > 5) focus = 5;
		}
	}
	if(focus >= 0) switchers_[focus]->update();
}

void GpadKeySwitcher::addFocushed(const int& delta)
{
	if (focus < 0) focus++;
	if (!switchers_[focus]->getPlayerIsChoosing()) 
		focus = (focus + delta) % 6;
}
