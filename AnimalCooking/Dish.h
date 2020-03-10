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
	void render();


	//Getters y setters
	inline list<Food*> getFoodList() { return foods_; }
	inline bool isEmpty() { return foods_.empty(); }
	inline Vector2D getPos() { return pos; }
	inline Vector2D getVel() { return vel; }
	inline int getHeight() { return height; }
	inline int getWidth() { return width; }
	inline void setPos(Vector2D value) { pos = value; }
	inline void setVel(Vector2D value) { vel = value; }
	
 private:
	 list<Food*>::iterator currentFood;
	 list<Food*> foods_;
	 Vector2D pos;
	 Vector2D vel;
	 int height;
	 int width;
};

