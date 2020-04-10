#pragma once

#include "Vector2D.h"
#include "Texture.h"
#include "SDLGame.h"
#include "IngredientsPool.h"

class Ingredient
{
public:
	Ingredient(Resources::IngredientType type) : size_(0, 0), pos_(0, 0), vel_(0, 0), texture_(nullptr), escapeRadius_(0), maxVel_(2), ingredientPool_(nullptr), type_(type) { } //2 de prueba
	virtual ~Ingredient() {}; //Todos a virtual aunque luego no sea necesario

	virtual void update();
	virtual void render() const;
	virtual void onHit() {};
	virtual void onCollisionX(); //Llamado por game manager
	virtual void onCollisionY(); //Llamado por game manager
	virtual void escape(Vector2D pos); //Llamado por game manager si el jugador esta en la zona de caza

	void setTransform(double w, double h, Vector2D pos, Vector2D vel) {
		size_.set(w, h);
		pos_.set(pos);
		vel_.set(vel);
	}
	inline void setEscapeRad(double rad) { escapeRadius_ = rad; }
	inline void setMaxVel(double maxVel) { maxVel_ = maxVel; }

	//No se si van a hacer falta todos pero por si acaso, si no se borran
	inline void setSize(double w, double h) { size_.set(w, h); }
	inline void setPos(Vector2D pos) { pos_.set(pos); }
	inline void setVel(Vector2D vel) { vel_.set(vel); }
	inline void setTexture(Texture* tex) { texture_ = tex; }

	inline double getWidth() { return size_.getX(); }
	inline double getHeight() { return size_.getY(); }
	inline Vector2D getPos() { return pos_; }
	Vector2D& getPosReference() { return pos_; }
	inline Vector2D getVel() { return vel_; }
	inline Resources::IngredientType getType() { return type_; }

	void setInVector(std::vector<Ingredient*>::iterator i, IngredientsPool* pool) { it_ = i; ingredientPool_ = pool; }
	void setIt(std::vector<Ingredient*>::iterator i) { it_ = i; }
	virtual Resources::FoodType destroy(Resources::UtensilType utensilio) = 0;	//utensilio es un enum y debe devolver otro enum (pendiente de hacer)
protected:
	Vector2D size_, pos_, vel_;
	Texture* texture_;
	double escapeRadius_, maxVel_; //Si escapeRad o maxVel es para todos el mismo se pone en los personajes y se pasa como parametro
	IngredientsPool* ingredientPool_;
	std::vector<Ingredient*>::iterator it_;
	Resources::IngredientType type_;
};

//<----------------------------------------------------------Clases Ingredientes-------------------------------------------------------------------------->

class Tomato : public Ingredient 
{
public:
	Tomato() : Ingredient(Resources::tomato) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Ingrediente); }
	~Tomato() {}

	Resources::FoodType destroy(Resources::UtensilType utensilio) {		//Cambiar cada int por su enum
		ingredientPool_->deleteIngredient(it_);

		switch (utensilio) {
		case Resources::Knife:
			return Resources::SlicedTomato;
			break;
		case Resources::Mace:
			return Resources::MashedTomato;
			break;
		case Resources::Grater:
			return Resources::Empty;
			break;
		case Resources::Net:
			return Resources::Empty;
			break;
		}
	}
};

class Carrot : public Ingredient
{
public:
	Carrot() : Ingredient(Resources::carrot) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Ingrediente); }
	~Carrot() {}

	Resources::FoodType destroy(Resources::UtensilType utensilio) {
		ingredientPool_->deleteIngredient(it_);

		switch (utensilio) {
		case Resources::Knife:
			return Resources::SlicedCarrot;
			break;
		case Resources::Mace:
			return Resources::Empty;
			break;
		case Resources::Grater:
			return Resources::Empty;
			break;
		case Resources::Net:
			return Resources::Empty;
			break;
		}
	}
};

class Lettuce : public Ingredient
{
public:
	Lettuce() : Ingredient(Resources::lettuce) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Ingrediente); }
	~Lettuce() {}

	Resources::FoodType destroy(Resources::UtensilType utensilio) {
		ingredientPool_->deleteIngredient(it_);

		switch (utensilio) {
		case Resources::Knife:
			return Resources::SlicedLettuce;
			break;
		case Resources::Mace:
			return Resources::Empty;
			break;
		case Resources::Grater:
			return Resources::Empty;
			break;
		case Resources::Net:
			return Resources::Empty;
			break;
		}
	}
};

class Mushroom : public Ingredient
{
public:
	Mushroom() : Ingredient(Resources::mushroom) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Ingrediente); }
	~Mushroom() {}

	Resources::FoodType destroy(Resources::UtensilType utensilio) {
		ingredientPool_->deleteIngredient(it_);

		switch (utensilio) {
		case Resources::Knife:
			return Resources::SlicedMushroom;
			break;
		case Resources::Mace:
			return Resources::MashedMushroom;
			break;
		case Resources::Grater:
			return Resources::Empty;
			break;
		case Resources::Net:
			return Resources::Empty;
			break;
		}
	}
};

class Sausage : public Ingredient
{
public:
	Sausage() : Ingredient(Resources::sausage) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Ingrediente); }
	~Sausage() {}

	Resources::FoodType destroy(Resources::UtensilType utensilio) {
		ingredientPool_->deleteIngredient(it_);

		switch (utensilio) {
		case Resources::Knife:
			return Resources::SlicedSausage;
			break;
		case Resources::Mace:
			return Resources::Empty;
			break;
		case Resources::Grater:
			return Resources::Empty;
			break;
		case Resources::Net:
			return Resources::CaughtSausage;
			break;
		}
	}
};

class Chicken : public Ingredient
{
public:
	Chicken() : Ingredient(Resources::chicken) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Ingrediente); }
	~Chicken() {}

	Resources::FoodType destroy(Resources::UtensilType utensilio) {
		ingredientPool_->deleteIngredient(it_);

		switch (utensilio) {
		case Resources::Knife:
			return Resources::SlicedChicken;
			break;
		case Resources::Mace:
			return Resources::Empty;
			break;
		case Resources::Grater:
			return Resources::Empty;
			break;
		case Resources::Net:
			return Resources::Empty;
			break;
		}
	}
};

class Meat : public Ingredient
{
public:
	Meat() : Ingredient(Resources::meat) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Ingrediente); }
	~Meat() {}

	Resources::FoodType destroy(Resources::UtensilType utensilio) {
		ingredientPool_->deleteIngredient(it_);

		switch (utensilio) {
		case Resources::Knife:
			return Resources::SlicedMeat;
			break;
		case Resources::Mace:
			return Resources::MashedMeat;
			break;
		case Resources::Grater:
			return Resources::Empty;
			break;
		case Resources::Net:
			return Resources::Empty;
			break;
		}
	}
};

class Potato : public Ingredient
{
public:
	Potato() : Ingredient(Resources::potato) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Ingrediente); }
	~Potato() {}

	Resources::FoodType destroy(Resources::UtensilType utensilio) {
		ingredientPool_->deleteIngredient(it_);

		switch (utensilio) {
		case Resources::Knife:
			return Resources::SlicedPotato;
			break;
		case Resources::Mace:
			return Resources::Empty;
			break;
		case Resources::Grater:
			return Resources::Empty;
			break;
		case Resources::Net:
			return Resources::Empty;
			break;
		}
	}
};

class Onion : public Ingredient
{
public:
	Onion() : Ingredient(Resources::onion) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Ingrediente); }
	~Onion() {}

	Resources::FoodType destroy(Resources::UtensilType utensilio) {
		ingredientPool_->deleteIngredient(it_);

		switch (utensilio) {
		case Resources::Knife:
			return Resources::SlicedOnion;
			break;
		case Resources::Mace:
			return Resources::Empty;
			break;
		case Resources::Grater:
			return Resources::GratedCheese;
			break;
		case Resources::Net:
			return Resources::Empty;
			break;
		}
	}
};

class Cheese : public Ingredient
{
public:
	Cheese() : Ingredient(Resources::cheese) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Ingrediente); }
	~Cheese() {}

	Resources::FoodType destroy(Resources::UtensilType utensilio) {
		ingredientPool_->deleteIngredient(it_);

		switch (utensilio) {
		case Resources::Knife:
			return Resources::SlicedCheese;
			break;
		case Resources::Mace:
			return Resources::Empty;
			break;
		case Resources::Grater:
			return Resources::GratedCheese;
			break;
		case Resources::Net:
			return Resources::Empty;
			break;
		}
	}
};

class Clam : public Ingredient
{
public:
	Clam() : Ingredient(Resources::clam) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Ingrediente); }
	~Clam() {}

	Resources::FoodType destroy(Resources::UtensilType utensilio) {
		ingredientPool_->deleteIngredient(it_);

		switch (utensilio) {
		case Resources::Knife:
			return Resources::Empty;
			break;
		case Resources::Mace:
			return Resources::Empty;
			break;
		case Resources::Grater:
			return Resources::Empty;
			break;
		case Resources::Net:
			return Resources::CaughtClam;
			break;
		}
	}
};

class Fish : public Ingredient
{
public:
	Fish() : Ingredient(Resources::fish) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Ingrediente); }
	~Fish() {}

	Resources::FoodType destroy(Resources::UtensilType utensilio) {
		ingredientPool_->deleteIngredient(it_);

		switch (utensilio) {
		case Resources::Knife:
			return Resources::Empty;
			break;
		case Resources::Mace:
			return Resources::Empty;
			break;
		case Resources::Grater:
			return Resources::Empty;
			break;
		case Resources::Net:
			return Resources::CaughtFish;
			break;
		}
	}
};

