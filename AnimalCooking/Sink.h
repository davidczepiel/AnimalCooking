#pragma once
#include "Component.h"
#include <vector>
#include "GPadController.h"
#include "Utensil.h"
#include "SDL_macros.h"
#include "Entity.h"
#include "Transport.h"
#include "SinkViewer.h"
using namespace std;

class Sink :public Entity, public Interactive
{
public:
	Sink(Transport* p1, Transport* p2);
	void draw() ;
	virtual ~Sink() {}
	virtual void interactive(int player);
private:
	int lastClean;
	int cadence;

};
