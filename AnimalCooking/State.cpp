#include "State.h"
#include "AnimalCooking.h"

State::State() {
	stage = new EntityManager(SDLGame::instance());
}

State::State(EntityManager* em)
{
	stage = em;
	em = nullptr;
}

void State::draw() {
	stage->draw();
}

void State::update() {
	stage->update();
}
