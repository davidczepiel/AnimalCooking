#pragma once
#include "Texture.h"
#include "Entity.h"
#include "Collisions.h"
#include "Transform.h"


class Utensil :public Entity {

protected:
	//Estado
	enum  State
	{
		floor, playerHand, shelf, sink
	};
	State myState;
	//Suciedad
	int myDirt_;
	int maxDirt_;
	int getDirtSpeed_;
	//Limpieza
	int cleanUpSpeed_;
	//Ataque
	int range_;
	int attackHitBoxWidth_;
	int attackHitBoxHeight_;
	int attackRate_;
	int lastAttack_;
	//Confirmación de que se puede limpiar y que está sucio
	bool dirty_;
	bool ableToClean_;

	Vector2D pos_, vel_, size_;
	Transform* player_;
	//Mis 2 texturas
	Texture* texture_;
	Texture* secondTexture_;
	//Control animación ataque
	int frameAttack;
	int lastFrameTick;
	bool attacking_;
	//Rect que se usará para calcular las colisiones entre la hitbox de un ataque y los ingredientes
	SDL_Rect interactionTrigger_;

	Entity* onHit(Vector2D dir);
public:
	Utensil(Vector2D pos,Transform* p);
	virtual ~Utensil() {}

	virtual void render() const;
	virtual void update();
	virtual void attack() = 0;

	void drop(bool suelo);
	void pickMe();
	void inTheWasher(bool x);
	void cleanUp();
	inline void setSize(double w, double h) { size_.set(w, h); }
	inline void setPos(Vector2D pos) { pos_.set(pos); }
	inline void setVel(Vector2D vel) { vel_.set(vel); }
	void changeDirtySpeed(int speedModifier);

};