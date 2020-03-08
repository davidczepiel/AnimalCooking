#include "CookerViewer.h"

CookerViewer::CookerViewer() :
	Component(ecs::CookerViewer) {

}

CookerViewer::~CookerViewer(){
}

void CookerViewer::init() {
	pool_ = GETCMP1_(CookerPool)->getPool();
}

void CookerViewer::draw() {
	for (Cooker* c : pool_) {
		switch (c->getCookerState()) {
		case CookerStates::empty: c->setTexture(c->getEmptyTexture()); break;
		case CookerStates::full: c->setTexture(c->getFullTexture()); break;
		case CookerStates::cooking: c->setTexture(c->getCookingTexture()); break;
		case CookerStates::cooked: c->setTexture(c->getCookedTexture()); break;
		}
		c->draw();
	}
}