#include "EnviromentControl.h"

EnviromentControl::EnviromentControl():Component(ecs::EnviromentControl)
{
	lastP1Entered = 0;
	lastP2Entered = 0;
}

void EnviromentControl::update()
{
	if (p1Force.getX() > 0)p1Force.setX(p1Force.getX()-5); else if(p1Force.getX() < 0) p1Force.setX(p1Force.getX() + 5);
	if (p1Force.getY() > 0)p1Force.setY(p1Force.getY() - 5); else if( p1Force.getY() < 0) p1Force.setY(p1Force.getY() + 5);
	if (p2Force.getX() > 0)p2Force.setX(p2Force.getX() - 5); else if (p2Force.getX() < 0) p2Force.setX(p2Force.getX() + 5);
	if (p2Force.getY() > 0)p2Force.setY(p2Force.getY() - 5); else if (p2Force.getY() < 0) p2Force.setY(p2Force.getY() + 5);

	isThereForce();
}

void EnviromentControl::enterIceZone(int player, Vector2D vel)
{
	if (player == 0 && SDL_GetTicks()-lastP1Entered >2000) {
		p1Force.setX(vel.getX() * 1000);
		p1Force.setY(vel.getY()*1000);
		lastP1Entered = SDL_GetTicks();
	}
	else if(player==1 && SDL_GetTicks() - lastP2Entered > 2000){
		p2Force.setX(vel.getX() * 1000);
		p2Force.setY(vel.getY() * 1000);
		lastP1Entered = SDL_GetTicks();
	}
}

double EnviromentControl::getPlayerForceX(int p)
{
	if (p == 0)return (p1Force.getX()/1000);
	else return (p2Force.getX() / 1000);
}

double EnviromentControl::getPlayerForceY(int p)
{
	if (p == 0)return (p1Force.getY() / 1000);
	else return (p2Force.getY() / 1000);
}

void EnviromentControl::playerMoved(int p, double moveX, double moveY)
{
	if (p == 0) {
		if (moveX < 0) p1Force.setX(p1Force.getX()-1);
		else if (moveX>0) p1Force.setX(p1Force.getX() + 1);

		if (moveY < 0) p1Force.setY(p1Force.getY() - 1);
		else if (moveY > 0) p1Force.setY(p1Force.getY() + 1);
	}
	else
	{

	}
}

void EnviromentControl::playerExit(int p)
{
	/*if (p == 0)lastP1Entered = SDL_GetTicks();
	else lastP2Entered = SDL_GetTicks();*/
}

void EnviromentControl::isThereForce()
{
	if (p1Force.getX() > -10 && p1Force.getX() < 10) p1Force.setX(0);
	if (p1Force.getY() > -10 && p1Force.getY() < 10) p1Force.setY(0);
	if (p2Force.getX() > -10 && p2Force.getX() < 10) p2Force.setX(0);
	if (p2Force.getY() > -10 && p2Force.getY() < 10) p2Force.setY(0);

}

void EnviromentControl::playerIsMoving(int p, Vector2D v)
{
	if (p == 0) {
		double x = v.getX();
		double y = v.getY();
		if (x < 0)p1Force.setX(p1Force.getX()-30);
		else  if (x>0) p1Force.setX(p1Force.getX() + 30);

		if (y < 0)p1Force.setY(p1Force.getY() - 30);
		else if (y > 0) p1Force.setY(p1Force.getY() + 30);
	}
}
