#pragma once

#include "Vector2D.h"
#include "Texture.h"
#include "SDLGame.h"
#include "IngredientsPool.h"
#include "Timer.h"
#include "Transform.h"
#include "AIIngredient.h"

enum IngredientState { Idle, Walking, Escaping, WallScaping };

class Ingredient
{
public:
	Ingredient(Resources::IngredientType type, Transform* p1, Transform* p2) : size_(0, 0), pos_(0, 0), vel_(0, 0), lastVel_(0, 0), texture_(nullptr), maxVel_(2), ingredientPool_(nullptr), aiIngredient_(nullptr), type_(type), state(Walking)
		, trPlayer1(p1), trPlayer2(p2) {
		internalTimer.setTime(5000);
		internalTimer.timerStart();
		wallScapingTimer_.setTime(1000);
	} //2 de prueba
	virtual ~Ingredient() {}; //Todos a virtual aunque luego no sea necesario

	virtual void update();
	virtual void render() const;
	virtual void onHit() {};
	virtual void onCollisionX(); //Llamado por game manager
	virtual void onCollisionY(); //Llamado por game manager
	virtual void onCollisionXY(); //Llamado por game manager

	void setTransform(double w, double h, Vector2D pos, Vector2D vel) {
		size_.set(w, h);
		pos_.set(pos);
		vel_.set(vel);
	}
	virtual void destroy();	

	//No se si van a hacer falta todos pero por si acaso, si no se borran
	inline void setPos(Vector2D pos) { pos_.set(pos); }
	inline void setVel(Vector2D vel) { vel_.set(vel); }
	inline void setTexture(Texture* tex) { texture_ = tex; }
	inline void setLastVel(Vector2D v) { lastVel_ = v; }
	void setInVector(std::vector<Ingredient*>::iterator i, IngredientsPool* pool, AIIngredient* ai) { it_ = i; ingredientPool_ = pool; aiIngredient_ = ai; }
	void setIt(std::vector<Ingredient*>::iterator i) { it_ = i; }
	void setState(IngredientState s) { state = s; }
	inline void setMaxVel(double maxVel) { maxVel_ = maxVel; }
	inline void setSize(double w, double h) { size_.set(w, h); }

	inline auto getIt() { return it_; }
	inline Vector2D getPos() { return pos_; }
	Vector2D& getPosReference() { return pos_; }
	inline Vector2D getVel() { return vel_; }
	inline Resources::IngredientType getType() { return type_; }
	inline Timer& getInternalTimer() { return internalTimer; }
	inline Timer& getWallScapingTimer() { return wallScapingTimer_; }
	inline IngredientState getIngredientState() { return state; }
	inline double getWidth() { return size_.getX(); }
	inline double getHeight() { return size_.getY(); }
	inline double getMaxVel() { return maxVel_; }


protected:
	Vector2D size_, pos_, vel_, lastVel_;
	Texture* texture_;
	IngredientsPool* ingredientPool_;
	AIIngredient* aiIngredient_;
	std::vector<Ingredient*>::iterator it_;
	Resources::IngredientType type_;
	Timer internalTimer;
	Timer wallScapingTimer_;
	IngredientState state;
	Transform* trPlayer1;
	Transform* trPlayer2;
	double maxVel_; //si maxVel es para todos el mismo se pone en los personajes y se pasa como parametro
};

//<----------------------------------------------------------Clases Ingredientes-------------------------------------------------------------------------->

class Tomato : public Ingredient
{
public:
	Tomato(Transform* p1, Transform* p2) : Ingredient(Resources::tomato, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);

	}
	~Tomato() {}
};

class Carrot : public Ingredient
{
public:
	Carrot(Transform* p1, Transform* p2) : Ingredient(Resources::carrot, p1, p2) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Carrot); }
	~Carrot() {}
};

class Lettuce : public Ingredient
{
public:
	Lettuce(Transform* p1, Transform* p2) : Ingredient(Resources::lettuce, p1, p2) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Lettuce); }
	~Lettuce() {}
};

class Mushroom : public Ingredient
{
public:
	Mushroom(Transform* p1, Transform* p2) : Ingredient(Resources::mushroom, p1, p2) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Mushroom); }
	~Mushroom() {}
};

class Sausage : public Ingredient
{
public:
	Sausage(Transform* p1, Transform* p2) : Ingredient(Resources::sausage, p1, p2) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Sausage); }
	~Sausage() {}
};

class Chicken : public Ingredient
{
public:
	Chicken(Transform* p1, Transform* p2) : Ingredient(Resources::chicken, p1, p2) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Chicken); }
	~Chicken() {}
};

class Meat : public Ingredient
{
public:
	Meat(Transform* p1, Transform* p2) : Ingredient(Resources::meat, p1, p2) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Meat); }
	~Meat() {}
};

class Potato : public Ingredient
{
public:
	Potato(Transform* p1, Transform* p2) : Ingredient(Resources::potato, p1, p2) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Potato); }
	~Potato() {}
};

class Onion : public Ingredient
{
public:
	Onion(Transform* p1, Transform* p2) : Ingredient(Resources::onion, p1, p2) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Onion); }
	~Onion() {}
};

class Cheese : public Ingredient
{
public:
	Cheese(Transform* p1, Transform* p2) : Ingredient(Resources::cheese, p1, p2) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cheese); }
	~Cheese() {}
};

class Clam : public Ingredient
{
public:
	Clam(Transform* p1, Transform* p2) : Ingredient(Resources::clam, p1, p2) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Clam); }
	~Clam() {}
};

class Fish : public Ingredient
{
public:
	Fish(Transform* p1, Transform* p2) : Ingredient(Resources::fish, p1, p2) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Fish); }
	~Fish() {}
};
class SnowMan : public Ingredient
{
public:
	SnowMan(Transform* p1, Transform* p2) : Ingredient(Resources::snowman, p1, p2) { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Snowman); }
	~SnowMan() {}
};

