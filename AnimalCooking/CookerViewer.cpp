#include "CookerViewer.h"

CookerViewer::CookerViewer() :
	Component(ecs::CookerViewer),
	pool_(nullptr){
}

CookerViewer::~CookerViewer() {
}

void CookerViewer::init() {
	pool_ = &GETCMP1_(CookerPool)->getPool();
}

void CookerViewer::draw() {
	for (Cooker* c : *pool_) {
		c->draw();
	}
}