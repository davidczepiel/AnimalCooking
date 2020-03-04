#pragma once
#include "State.h"
#include "Transform.h"
class MapState : public State{
private:
	SDLGame* game_;

	Entity* screenLoaderButton_ = nullptr;
	Entity* backButton_ = nullptr;

	Transform* screenLoaderTr_ = nullptr;
	Transform* backTr_ = nullptr;

	static void screenLoaderCallback();
	static void backButtonCallback();

public:
	MapState();
	~MapState() {};
};

