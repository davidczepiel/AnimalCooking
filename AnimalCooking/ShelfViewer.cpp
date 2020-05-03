#include "ShelfViewer.h"

void ShelfViewer::draw() {
	text->render(RECT(entity->getPos().getX(), entity->getPos().getY(), entity->getSize().getX(), entity->getSize().getY()));
}