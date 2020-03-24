#pragma once
#include "Food.h"
#include "Pickable.h"
#include <list>

class Dish : public Pickable
{
 public:
	Dish(Vector2D pos_, Transport* transPlayer1, Transport* transPlayer2);
	~Dish() { }
	//Añade un alimento al plato	
	void addFood(Food* f);
	
	//Quita del plato el alimento seleccionado y lo devuelve para que pase al jugador
	//Si no hay nada seleccionado devuelve nullptr
	Food* takeFood();
	
	//Mueve el selector de comida adelante
	void nextFood();
	
	//Mueve el selector de comida atrás
	void previousFood();

	void clearFoods();

	//Getters y setters
	inline vector<Food*>& getFoodVector() { return foods_; }
	inline bool isEmpty() { return foods_.empty(); }

	virtual void onDrop(bool onFloor) { inHands = false; }
	virtual void onPick() { inHands = true; }
	
	inline void setInHands(bool b) { inHands = b; }
	inline bool getInHands() { return inHands; }

 private:
	 vector<Food*>::iterator currentFood;
	 vector<Food*> foods_;
	 bool inHands;
};

