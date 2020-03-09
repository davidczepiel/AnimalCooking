#pragma once
#include "Food.h"
#include <list>
using namespace std;
class Dish
{
 public:
	Dish();
	~Dish() { }
	//Añade un ingrediente al plato	
	void addFood(Food* f);
	
	//Quita del plato el ingrediente seleccionado y lo devuelve para que pase al jugador
	//Si no hay nada seleccionado devuelve nullptr
	Food* takeFood();
	
	//Mueve el selector de comida adelante
	void nextFood();
	
	//Mueve el selector de comida atrás
	void previousFood();
	
	list<Food*> getList();
	inline bool isEmpty();
	
 private:
	 list<Food*>::iterator currentFood;
	 list<Food*> foods_;
};

