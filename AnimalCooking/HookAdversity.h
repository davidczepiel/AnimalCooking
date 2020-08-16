#pragma once
#include "Adversity.h"
#include "Transform.h"
#include"Texture.h"
class HookAdversity : public Adversity
{
public:
	HookAdversity(MultipleAdversityManager* mam);
	virtual void update();
	virtual void draw();
	virtual void reset();
	void start();

private:
	void GoingUp();
	void GoingDown();
	void StartAdversity();
	void Move(bool down);

	Transform* tP1;
	Transform* tP2;

	//Dibujo
	Texture* hookTexture;
	SDL_Rect drawingAreaHook1;
	SDL_Rect drawingAreaHook2;
	SDL_Rect clipArea;

	//Posiciones y tama�o de los players
	Vector2D p1OriginalPos;
	Vector2D p2OriginalPos;
	Vector2D playerSize;

	//Animacion
	int frameTime;
	int lastFrame;
	int animationFrame;

	//Velocidad del proceso
	double hook1Vel;
	double hook2Vel;
	int lastTick;
	int speed;

	//Flags para el proceso
	bool catched;
	bool changedPositions;
	bool droped;
	bool playersVisible;
};

