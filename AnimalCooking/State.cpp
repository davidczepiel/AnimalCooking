#include "State.h"
State::State()
{
	stage = new EntityManager(SDLGame::instance());
}
void State::Draw() {
	stage->draw();
}
void State::Update() {
	stage->update();
}
