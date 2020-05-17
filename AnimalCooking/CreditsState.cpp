#include "CreditsState.h"
#include "CreditsViewer.h"




CreditsState::CreditsState(AnimalCooking* ac) :State(ac) {
	double casillaX = SDLGame::instance()->getCasillaX();
	double casillaY = SDLGame::instance()->getCasillaY();

	Entity* returnToMenuState = stage->addEntity();
	stage->addToGroup(returnToMenuState, ecs::GroupID::ui);
	returnToMenuState->addComponent<Transform>(Vector2D(
		0.1 * casillaX,
		casillaY * 7.9),
		Vector2D(0, 0),
		casillaX,
		casillaY,
		0);
	returnToMenuState->addComponent<ButtonBehaviour>(GoBackMenu, app);
	//Aquí debería ir el botón de la casa, pero no sé cómo se pone :P
	returnToMenuState->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button), nullptr);

	Entity* nombres = stage->addEntity();
	stage->addToGroup(nombres, ecs::GroupID::ui);
	nombres->addComponent<CreditsViewer>();
}


void CreditsState::GoBackMenu(AnimalCooking* ac) {
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	SDLGame::instance()->getFSM()->popState();


}