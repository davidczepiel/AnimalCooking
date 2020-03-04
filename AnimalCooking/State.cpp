#include "State.h"
#include "AnimalCooking.h"

State::State() {
	stage = new EntityManager(SDLGame::instance());
}

void State::draw() {
	stage->draw();
}

void State::update() {
	stage->update();
}
