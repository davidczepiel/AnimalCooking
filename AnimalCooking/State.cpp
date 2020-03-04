#include "State.h"
#include "AnimalCooking.h"

State::State(AnimalCooking* app) {
	app_ = app;
	stage = new EntityManager(SDLGame::instance());
}

void State::draw() {
	stage->draw();
}

void State::update() {
	stage->update();
}
