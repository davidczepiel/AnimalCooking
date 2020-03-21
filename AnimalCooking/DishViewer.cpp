#include "DishViewer.h"

DishViewer::DishViewer() :Component(ecs::DishViewer)
{

}

void DishViewer::init() 
{
	dish = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Plato);
	dp = GETCMP1_(DishPool);
}
void DishViewer::draw() 
{
	vector<Dish*> ls = dp->getDishes();
	for (auto i = ls.begin(); i != ls.end(); i++)
	{			
		//se renderiza la textura del plato 
		dish->render(RECT((*i)->getPos().getX(), (*i)->getPos().getY(), (*i)->getSize().getX(), (*i)->getSize().getY()));

		//se renderizan los alimentos del plato		
		//Colocamos la comida en el centro del plato y un poco más arriba del fondo del plato
		//(teniendo en cuenta el índice la comida) y renderizamos
        int k = 0;
		vector<Food*> foods= (*i)->getFoodVector();
		for (auto it =foods.begin(); it != foods.end(); it++)
		{
			(*it)->setPos(Vector2D((*i)->getPos().getX() + (*it)->getSize().getX() / 2,
				(*i)->getPos().getY() - (*it)->getSize().getY() / 4 - (int64_t)((*it)->getSize().getY() * k)));

			(*it)->setSize(Vector2D((*i)->getSize().getX() / 2, (*i)->getSize().getY()));

			(*it)->draw();
			k++;
		}		
	}
}