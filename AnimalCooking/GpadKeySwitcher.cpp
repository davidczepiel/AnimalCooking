#include "GpadKeySwitcher.h"
#include "Entity.h"
#include "Transform.h"
#include "GPadController.h"
#include "ConfigState.h"

void GpadKeySwitcher::init()
{
	config::Options::GPadButtons& keys = SDLGame::instance()->getOptions().players_gPadButtons[player_];
	Transform* t = GETCMP1_(Transform);
	switchers_.reserve(7);
	switchers_.emplace_back(new SwitcherGPad_Boolean(Vector2D(t->getPos().getX() + 310, t->getPos().getY() - t->getH() / 6), Vector2D(), SDLGame::instance()->getOptions().usePS4_symbols_[player_], Resources::TextureId::Config_XBoxOrPs4Icon, player_));
	switchers_.emplace_back(new SwitcherGPad(Vector2D(t->getPos().getX(), t->getPos().getY()), Vector2D(), keys.ATTACK, Resources::TextureId::AttackText, player_));
	switchers_.emplace_back(new SwitcherGPad(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() / 6), Vector2D(), keys.OPEN, Resources::TextureId::OpenText, player_));
	switchers_.emplace_back(new SwitcherGPad(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() * 2 / 6), Vector2D(), keys.PICKUP, Resources::TextureId::PickUpText, player_));
	switchers_.emplace_back(new SwitcherGPad(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() * 3 / 6), Vector2D(), keys.FINISHER, Resources::TextureId::FinishText, player_));
	switchers_.emplace_back(new SwitcherGPad(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() * 4 / 6), Vector2D(), keys.NEXT, Resources::TextureId::NextText, player_));
	switchers_.emplace_back(new SwitcherGPad(Vector2D(t->getPos().getX(), t->getPos().getY() + t->getH() * 5 / 6), Vector2D(), keys.PREVIOUS, Resources::TextureId::PreviousText, player_));

	for (auto& s : switchers_)
		s->setSize(Vector2D(buttonWidth_, buttonHeight_));

	//Symbol 1 button con entity
	/*
	//Symbol 1 button
	GPadController* gpCont = GPadController::instance();
	if (gpCont->playerControllerConnected(0)) {
		symbolPlayer1 = stage->addEntity();
		stage->addToGroup(symbolPlayer1, ecs::GroupID::ui);
		symbolPlayer1->addComponent<Transform>(
			Vector2D(1200, 290),
			Vector2D(), 94, 74, 0);
		bb = symbolPlayer1->addComponent<ButtonBehaviour>(symbolCallback1, app);
		symbolPlayer1->addComponent<ButtonChangeOnClick>(game_->getOptions().usePS4_symbols_[0]);
		bcr = symbolPlayer1->addComponent<ButtonCheckRenderer>(nullptr, nullptr);
		bcr->setCheckedAndUncheckedTextures(Resources::TextureId::Config_XBoxIcon, Resources::TextureId::Config_Ps4Icon);
		bb->setButtonCheckRenderer(bcr);
	}

	//Symbol 2 button
	symbolPlayer2 = nullptr;
	if (gpCont->playerControllerConnected(1)) {
		symbolPlayer2 = stage->addEntity();
		stage->addToGroup(symbolPlayer2, ecs::GroupID::ui);
		symbolPlayer2->addComponent<Transform>(
			Vector2D(1770, 290),
			Vector2D(), 94, 74, 0);
		bb = symbolPlayer2->addComponent<ButtonBehaviour>(symbolCallback2, app);
		symbolPlayer2->addComponent<ButtonChangeOnClick>(game_->getOptions().usePS4_symbols_[1]);
		bcr = symbolPlayer2->addComponent<ButtonCheckRenderer>(nullptr, nullptr);
		bcr->setCheckedAndUncheckedTextures(Resources::TextureId::Config_XBoxIcon, Resources::TextureId::Config_Ps4Icon);
		bb->setButtonCheckRenderer(bcr);
	}
	*/

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
			else if (focus > 6) focus = 6;
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
		focus = (focus + 7 + delta) % 7;
}
