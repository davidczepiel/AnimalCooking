#include "CreditsState.h"
#include "CreditsViewer.h"




CreditsState::CreditsState(AnimalCooking* ac) :State(ac) {
	double casillaX = SDLGame::instance()->getCasillaX();
	double casillaY = SDLGame::instance()->getCasillaY();

	Entity* returnToMenuState = stage->addEntity();
	stage->addToGroup(returnToMenuState, ecs::GroupID::ui);
	returnToMenuState->addComponent<Transform>(Vector2D(
		0.7 * casillaX,
		casillaY * 7.2),
		Vector2D(0, 0),
		casillaX,
		casillaY,
		0);
	returnToMenuState->addComponent<ButtonBehaviour>(GoBackMenu, app);
	//Aquí debería ir el botón de la casa, pero no sé cómo se pone :P
	returnToMenuState->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::HomeIconMapState), nullptr);

	Entity* nombres = stage->addEntity();
	stage->addToGroup(nombres, ecs::GroupID::ui);
	nombres->addComponent<CreditsViewer>();
}


void CreditsState::GoBackMenu(AnimalCooking* ac) {
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	SDLGame::instance()->getFSM()->popState();


}

void CreditsState::draw()
{
	SDLGame::instance()->getTextureMngr()->getTexture(Resources::pauseStateBackground)->render(RECT(0, 0, SDLGame::instance()->getWindowWidth(), SDLGame::instance()->getWindowHeight()));
	State::draw();
	SDLGame::instance()->getTextureMngr()->getTexture(Resources::woodCredits)->render(RECT(0, 0, SDLGame::instance()->getWindowWidth(), SDLGame::instance()->getWindowHeight()));
}

void CreditsState::update()
{
	GPadController* gpad = GPadController::instance();
	if ((gpad->playerControllerConnected(0) || gpad->playerControllerConnected(1)) && gpad->isAnyButtonJustPressed()) {

		if ((gpad->playerPressed(0, SDL_CONTROLLER_BUTTON_B) || gpad->playerPressed(1, SDL_CONTROLLER_BUTTON_B))) {
			GoBackMenu(getAnimalCooking());
		}
	}
	State::update();
}
