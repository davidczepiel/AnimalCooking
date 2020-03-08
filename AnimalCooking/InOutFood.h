#pragma once
#include "Component.h"
#include "Food.h"
#include <list>
using namespace std;
class InOutFood : public Component
{
 public:
	InOutFood();
	~InOutFood() { }
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
	inline void setEmpty(bool b);
	inline bool isEmpty();
	
 private:
	 list<Food*>::iterator currentFood;
	 bool empty = true;
	 list<Food*> foods_;
};

