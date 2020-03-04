#include "MapState.h"
#include "ScreenLoader.h"
#include "FSM.h"
#include "ButtonRenderer.cpp"
#include "ButtonBehaviour.h"

static void screenLoaderCallback() {
	SDLGame::instance()->getFSM()->pushState(new ScreenLoader(Resources::Level::Nivel1));
	cout << "screenLoader" << endl;
}
static void backButtonCallback() {
	SDLGame::instance()->getFSM()->popState();
}
MapState::MapState(): State() {
	cout << "Map State" << endl;
	game_ = SDLGame::instance();

	screenLoaderButton_ = stage->addEntity();
	backButton_ = stage->addEntity();

	screenLoaderButton_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2, (game_->getWindowHeight() / 3) * 0), Vector2D(0, 0), 200.0, 100, 0);
	screenLoaderButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Test), nullptr);
	screenLoaderButton_->addComponent<ButtonBehaviour>(screenLoaderCallback);

	backButton_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2, (game_->getWindowHeight() / 3) * 0), Vector2D(0, 0), 200.0, 100, 0);
	backButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Test), nullptr);
	backButton_->addComponent<ButtonBehaviour>(backButtonCallback);
}