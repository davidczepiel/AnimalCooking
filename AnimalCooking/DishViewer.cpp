#include "DishViewer.h"

DishViewer::DishViewer() :Component(ecs::DishViewer)
{

}

void DishViewer::init() {
	dish = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Plato);
	dp = GETCMP1_(DishPool);
}
void DishViewer::draw() {
	list<Dish*> ls = dp->getDishes();
	for (auto i = ls.begin(); i != ls.end(); i++)
	{
		
		dish->render(RECT((*i)->getPos().getX(), (*i)->getPos().getY(), (*i)->getWidth(), (*i)->getHeight()));
		(*i)->render();

	}
}