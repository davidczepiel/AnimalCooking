#pragma once

#include "State.h"
#include "IngredientsPool.h"
#include "IngredientViewer.h"
#include "Ingredient.h"
#include "IngredientMotion.h"

class PlayState : public State
{
public:
	PlayState() : State() {
		cout << "PlayState" << endl;
		Entity* e = stage->addEntity();
		e->addComponent<IngredientsPool>();
		e->addComponent<IngredientViewer>();
		e->addComponent<IngredientMotion>();
		Tomato* t = new Tomato();
		
		t->setTransform(50, 50, Vector2D(100, 100), Vector2D(1, 1));
		e->getComponent<IngredientsPool>(ecs::IngredientsPool)->addIngredient(t);
		t = new Tomato();
		t->setTransform(50, 50, Vector2D(400, 100), Vector2D(-1, 1));
		e->getComponent<IngredientsPool>(ecs::IngredientsPool)->addIngredient(t);
	}
	void update() override {
		stage->update();
	};
	void draw() override {
		stage->draw();
	};

	//virtual void handleEvent();
private:

};
