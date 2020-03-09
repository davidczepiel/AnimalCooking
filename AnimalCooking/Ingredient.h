#pragma once

#include "Vector2D.h"
#include "Texture.h"
#include "SDLGame.h"
#include "IngredientsPool.h"

class Ingredient
{
public:
	Ingredient(Resources::IngredientType type) : size_(0, 0), pos_(0, 0), vel_(0, 0), texture_(nullptr), escapeRadius_(0), maxVel_(2), ingredientPool_(nullptr), type_(type) { cout << type << endl; } //2 de prueba
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
	inline Vector2D getVel() { return vel_; }
	inline Resources::IngredientType getType() { return type_; }

	void setInVector(std::vector<Ingredient*>::iterator i, IngredientsPool* pool) { it_ = i; ingredientPool_ = pool; }
	virtual int destroy(int utensilio) = 0;	//utensilio es un enum y debe devoñver otro enum (pendiente de hacer)
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

	int destroy(int utensilio) {		//Cambiar cada int por su enum
		ingredientPool_->deleteIngredient(it_);

		switch (utensilio) {
		case 0:
			return 0;
			break;
		case 1:
			return 1;
			break;
		case 2:
			return 2;
			break;
		}
	}
};

class Carrot : public Ingredient
{
public:
	Carrot() : Ingredient(Resources::carrot) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Ingrediente); }
	~Carrot() {}

	int destroy(int utensilio) {
		ingredientPool_->deleteIngredient(it_);

		switch (utensilio) {
		case 0:
			return 0;
			break;
		case 1:
			return 1;
			break;
		case 2:
			return 2;
			break;
		}
	}
};

class Lettuce : public Ingredient
{
public:
	Lettuce() : Ingredient(Resources::lettuce) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Ingrediente); }
	~Lettuce() {}

	int destroy(int utensilio) {
		ingredientPool_->deleteIngredient(it_);

		switch (utensilio) {
		case 0:
			return 0;
			break;
		case 1:
			return 1;
			break;
		case 2:
			return 2;
			break;
		}
	}
};

class Mushroom : public Ingredient
{
public:
	Mushroom() : Ingredient(Resources::mushroom) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Ingrediente); }
	~Mushroom() {}

	int destroy(int utensilio) {
		ingredientPool_->deleteIngredient(it_);

		switch (utensilio) {
		case 0:
			return 0;
			break;
		case 1:
			return 1;
			break;
		case 2:
			return 2;
			break;
		}
	}
};

class Sausage : public Ingredient
{
public:
	Sausage() : Ingredient(Resources::sausage) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Ingrediente); }
	~Sausage() {}

	int destroy(int utensilio) {
		ingredientPool_->deleteIngredient(it_);

		switch (utensilio) {
		case 0:
			return 0;
			break;
		case 1:
			return 1;
			break;
		case 2:
			return 2;
			break;
		}
	}
};