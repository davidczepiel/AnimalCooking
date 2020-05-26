#include "DishViewer.h"
#include "Dish.h"

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
	for (auto &i : dp->getDishes())
	{			
		//se renderiza la textura del plato 
		dish->render(RECT((i)->getPos().getX(), (i)->getPos().getY(), (i)->getSize().getX(), (i)->getSize().getY()));

		//se renderizan los alimentos del plato		
		//Colocamos la comida formando un circulo dentro del plato
		//Si solo hay una comida se coloca en el centro
		int k = 180;
		vector<Food*>& foods = (i)->getFoodVector();		
		
		for (auto &it : (i)->getFoodVector())
		{								
			if (foods.size() == 1) 
			{ 
				(it)->setSize(Vector2D((i)->getSize().getX() / 1.4, (i)->getSize().getY() / 1.4));
				(it)->setPos(Vector2D((i)->getPos().getX()+(i)->getSize().getX() / 7, (i)->getPos().getY()+ (i)->getSize().getY() / 7));
			}
			else if(foods.size()>1)
			{ 
				double rx = (i)->getSize().getX() / 6 * cos((k * M_PI) / 180) + (i)->getSize().getX() / 5;
				double ry = (i)->getSize().getY() / 6 * sin((k * M_PI) / 180) + (i)->getSize().getY() / 5;

				double x = (i)->getPos().getX() + rx;
				double y = (i)->getPos().getY() + ry;

				(it)->setSize(Vector2D((i)->getSize().getX() / 1.8, (i)->getSize().getY() / 1.8)); 
				(it)->setPos(Vector2D(x, y));
			}

			k += 360 / foods.size();
		}				
	}
}