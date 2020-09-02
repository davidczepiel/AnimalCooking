#include "EnviromentViewer.h"
#include "Entity.h"

EnviromentViewer::EnviromentViewer(EnviromentPool* envP) :Component(ecs::EnviromentViewer),pool_(){
	
}

void EnviromentViewer::init() {
	pool_ = &GETCMP1_(EnviromentPool)->getPool();
}

void EnviromentViewer::draw()
{
	for (EnviromentUnit* b : *pool_) {
		b->render();
	}
}
