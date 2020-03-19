#pragma once
#include "Texture.h"
#include "Entity.h"
#include "Collisions.h"
#include "Transform.h"
#include "Transport.h"
#include "Pickable.h"

class GameLogic;
class Utensil : public Pickable{

protected:
	//Estado
	enum  State
	{
		floor, playerHand, shelf
	};
	Resources::UtensilType myType;
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
	//Confirmaci�n de que esta  sucio
	bool dirty_;

	//Mis 2 texturas
	Texture* cleantexture_;
	Texture* dirtyTexture_;
	Texture* attackTexture_;
	//Control animacion ataque
	int frameAttack;
	int lastFrameTick;
	bool attacking_;
	//Rect que se usa para calcular las colisiones entre la hitbox de un ataque y los ingredientes
	SDL_Rect interactionTrigger_;
	GameLogic* gameLogic;

	void onHit(Vector2D dir);
public:
	Utensil(Vector2D pos, Transport* p1, Transport* p2);
	virtual ~Utensil() {}
	void interactive(int player) override;

	virtual void render() const;
	virtual void update();
	virtual void attack(Vector2D dir) = 0;

	int getDirt() { return myDirt_; }
	virtual void onDrop(bool onFloor);
	virtual void onPick();
	void cleanUp();
	void changeDirtySpeed(int speedModifier);
	void setGameLogic(GameLogic* glc) {	gameLogic = glc;}

};

/////////////////////////////////////////////Utensilios//////////////////////////////

class Knife : public Utensil
{
public:
	Knife(Vector2D pos, Transport* p1, Transport* p2);
	~Knife() {}
	virtual void attack(Vector2D dir) {  onHit(dir); }

};

class Mace : public Utensil
{
public:
	Mace(Vector2D pos, Transport* p1, Transport* p2);
	~Mace() {}

	virtual void attack(Vector2D dir) {  onHit(dir); }


};


class Grater : public Utensil
{
public:
	Grater(Vector2D pos, Transport* p1, Transport* p2);
	~Grater() {}
	virtual void attack(Vector2D dir) {  onHit(dir); }

};

class Net : public Utensil
{
public:
	Net(Vector2D pos, Transport* p1, Transport* p2);
	~Net() {}
	virtual void attack(Vector2D dir) {  onHit(dir); }

};