#include "State.h"
#include "AnimalCooking.h"

State::State(AnimalCooking* ac) {
	stage = new EntityManager(SDLGame::instance());
	app = ac;
}

State::State(EntityManager* em, AnimalCooking* ac)
{
	stage = em;
	em = nullptr;
	app = ac;

}

void State::draw() {
	stage->draw();
}

void State::update() {
	stage->update();
}
