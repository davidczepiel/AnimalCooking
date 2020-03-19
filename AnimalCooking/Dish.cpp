#include "Dish.h"

Dish::Dish(Vector2D pos_, Transport* transPlayer1, Transport* transPlayer2) : Pickable(transPlayer1, transPlayer2)
{
	pos = pos_;
	width = 100;
	height = 50;
	vel = Vector2D();
	foods_ = vector<Food*>();
}

// si el vector estaba vacío pone el iterador al principio
void Dish::addFood(Food* f)
{
	if (f != nullptr) 
	{
		foods_.push_back(f);				
		currentFood = foods_.begin();		
	}
}

Food* Dish::takeFood()
{
	//si el vector no se ha vaciado pone el iterador al principio para evitar errores
	if (!foods_.empty()) 
	{
		Food* aux = *currentFood;
		foods_.erase(currentFood);
		if (!foods_.empty())
			currentFood = foods_.begin();
		return aux;
	}
	else return nullptr;
}
//Comprobamos que no está el vector vacío y no se ha llegado al último elemento
void Dish::nextFood() 
{
	if (!foods_.empty() && currentFood != (--foods_.end()))
		currentFood++;
}
//Comprobamos que no está el vector vacío y no estamos en el primer elemento
void Dish::previousFood() 
{
	if (!foods_.empty() && currentFood != foods_.begin())
		currentFood--;
}
void Dish::render() 
{
	int k = 0;
	//Colocamos la comida en el centro del plato y un poco más arriba del fondo del plato
	//(teniendo en cuenta el índice la comida) y renderizamos
	for (auto i = foods_.begin(); i != foods_.end(); i++)
	{		
		(*i)->setPos(Vector2D(pos.getX() + (*i)->getSize().getX() / 2,
			pos.getY() - (*i)->getSize().getY() / 4 - (int64_t)((*i)->getSize().getY() * k)));
		
		(*i)->draw();
		k++;
	}
}

void Dish::update()
{
	pos = pos + vel;
}