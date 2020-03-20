#pragma once
#include "Component.h"
#include <vector>
#include "GPadController.h"
#include "Utensil.h"
#include "SDL_macros.h"
#include "Entity.h"
#include "Transport.h"
#include "SinkViewer.h"
#include "Manager.h"
#include "SDLGame.h"
#include "Timer.h"
using namespace std;

class Sink :public Entity, public Interactive
{
public:
	Sink(Transport* p1, Transport* p2, EntityManager* mng);
	void draw() ;
	void update();
	virtual ~Sink();
	virtual void action1(int player);
private:
	Timer* cleanTimer;
	bool canClean;
	int cadence;

};
