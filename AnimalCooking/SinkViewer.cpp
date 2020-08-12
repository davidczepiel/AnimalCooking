#include "SinkViewer.h"
#include "GameConfig.h"



SinkViewer::SinkViewer(Interactive* i) :Component(ecs::SinkViewer), entity(i), onAction(false),text(nullptr),textOn(nullptr) {
	recoverNormalState.setTime(2*config::SINK_CADENCE);
}


void SinkViewer::init() {
	text = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Fregadero);
	textOn = SDLGame::instance()->getTextureMngr()->getTexture(Resources::FregaderoON);

}

void SinkViewer::draw() {
	if (!onAction)
		text->render(RECT(entity->getPos().getX(), entity->getPos().getY(), entity->getSize().getX(), entity->getSize().getY()));
	else
		textOn->render(RECT(entity->getPos().getX(), entity->getPos().getY(), entity->getSize().getX(), entity->getSize().getY()));

}

void SinkViewer::update() {
	//Si estoy siendo usado actualizo el timer, y si ya han pasado los segundos del timer vuelvo al estado "no usado"
	if (onAction) {
		recoverNormalState.update();
		if (recoverNormalState.isTimerEnd()) {
			recoverNormalState.timerReset();
			onAction = false;
		}
	}
}

void SinkViewer::setOnAction(bool b) {
	 onAction = b; 
	 if (onAction) {
		 recoverNormalState.timerStart();
	 }
}
