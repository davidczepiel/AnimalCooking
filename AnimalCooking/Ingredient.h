#pragma once

#pragma once

#include "Vector2D.h"
#include "Texture.h"

class Ingredient
{
private:
	bool inUse_;
	Vector2D size_, pos_, vel_;
	Texture* texture_;
	double escapeRadius_, maxVel_; //Si escapeRad o maxVel es para todos el mismo se pone en los personajes y se pasa como parametro

	Ingredient() : inUse_(false), size_(0, 0), pos_(0, 0), vel_(0, 0), texture_(nullptr), escapeRadius_(0), maxVel_(2) {} //2 de prueba

protected:
	virtual ~Ingredient() {}; //Todos a virtual aunque luego no sea necesario
	virtual void update();
	virtual void render() const;
	virtual void onHit() = 0; //Abstracto porque aun no necesita el switch
	virtual void onCollisionX();
	virtual void onCollisionY();
	virtual void escape(Vector2D pos);

	bool inUse() { return inUse_; } //para pool

	void setTransform(double w, double h, Vector2D pos, Vector2D vel) {
		size_.set(w, h);
		pos_.set(pos);
		vel_.set(vel);
	}
	void setEscapeRad(double rad) { escapeRadius_ = rad; }
	void setMaxVel(double maxVel) { maxVel_ = maxVel; }
	inline void setInUse(bool inUse) { inUse_ = inUse; }

	//No se si van a hacer falta todos pero por si acaso, si no se borran
	inline void setSize(double w, double h) { size_.set(w, h); }
	inline void setPos(Vector2D pos) { pos_.set(pos); }
	inline void setVel(Vector2D vel) { vel_.set(vel); }

	inline double getWidth() { return size_.getX(); }
	inline double getHeight() { return size_.getY(); }
	inline Vector2D getPos() { return pos_; }
	inline Vector2D getVel() { return vel_; }
};