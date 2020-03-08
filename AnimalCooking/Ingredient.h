#pragma once

#include "Vector2D.h"
#include "Texture.h"
#include "SDLGame.h"
#include "IngredientsPool.h"

class Ingredient
{
protected:
	bool inUse_;
	Vector2D size_, pos_, vel_;
	Texture* texture_;
	double escapeRadius_, maxVel_; //Si escapeRad o maxVel es para todos el mismo se pone en los personajes y se pasa como parametro
	IngredientsPool* ingredientPool_;
	std::vector<Ingredient*>::iterator it_;

public:
	Ingredient() : inUse_(false), size_(0, 0), pos_(0, 0), vel_(0, 0), texture_(nullptr), escapeRadius_(0), maxVel_(2) {} //2 de prueba
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

	void setInVector(std::vector<Ingredient*>::iterator i, IngredientsPool* pool) { it_ = i; ingredientPool_ = pool; }
	void destroy() { ingredientPool_->deleteIngredient(it_); }
};

//<----------------------------------------------------------Clases Ingredientes-------------------------------------------------------------------------->

class Tomato : public Ingredient 
{
public:
	Tomato() : Ingredient() { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Ingrediente); }
	~Tomato() {}
};

class Carrot : public Ingredient
{
public:
	Carrot() : Ingredient() { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Ingrediente); }
	~Carrot() {}
};

class Lettuce : public Ingredient
{
public:
	Lettuce() : Ingredient() { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Ingrediente); }
	~Lettuce() {}
};

class Mushroom : public Ingredient
{
public:
	Mushroom() : Ingredient() { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Ingrediente); }
	~Mushroom() {}
};

class Sausage : public Ingredient
{
public:
	Sausage() : Ingredient() { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Ingrediente); }
	~Sausage() {}
};