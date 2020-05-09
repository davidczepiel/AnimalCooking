#pragma once
#include "Food.h"
#include "Pickable.h"
#include <list>
#include "FoodPool.h"
class Dish : public Pickable
{
 public:
	Dish(Vector2D pos_, Transport* transPlayer1, Transport* transPlayer2, int maxFood,FoodPool* fp);
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

	//Mueve el selector de comida a la primera posición
	void firstFood();

	void clearFoods();

	//Getters y setters
	inline vector<Food*>& getFoodVector() { return foods_; }
	inline bool isEmpty() { return foods_.empty(); }

	virtual void onDrop(bool onFloor) { inHands = false; }
	virtual void feedback(int id);

	virtual void onPick();
	inline void setInHands(bool b) { inHands = b; }
	inline bool getInHands() { return inHands; }
	inline void setIsViewingContent(bool value) { isViewingContent = value; }
	inline bool getIsViewingContent() { return isViewingContent; }
	  void addFinalFood(Food* f) { 
		  addFood(f);
		  foodPool->AddFood(f);
	  }

	  inline vector<Food*>::reverse_iterator getCurrentFood() { return currentFood; }

 private:
	 vector<Food*>::reverse_iterator currentFood;
	 vector<Food*> foods_;
	 FoodPool* foodPool;
	 bool inHands;
	 bool isViewingContent;
};

