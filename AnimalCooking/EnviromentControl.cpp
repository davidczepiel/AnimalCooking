#include "EnviromentControl.h"

EnviromentControl::EnviromentControl() :Component(ecs::EnviromentControl), accelerationIce(30), p1NumBlocksStepping(0), p2NumBlocksStepping(0)
{

}


//Cada tick le quitamos para que vayan perdiendo inercia y en caso de que no tenga o sea insigniicante se pone a 0
void EnviromentControl::update()
{
	if (p1Force.getX() > 0)p1Force.setX(p1Force.getX() - 5); else if (p1Force.getX() < 0) p1Force.setX(p1Force.getX() + 5);
	if (p1Force.getY() > 0)p1Force.setY(p1Force.getY() - 5); else if (p1Force.getY() < 0) p1Force.setY(p1Force.getY() + 5);
	if (p2Force.getX() > 0)p2Force.setX(p2Force.getX() - 5); else if (p2Force.getX() < 0) p2Force.setX(p2Force.getX() + 5);
	if (p2Force.getY() > 0)p2Force.setY(p2Force.getY() - 5); else if (p2Force.getY() < 0) p2Force.setY(p2Force.getY() + 5);

	isThereForce();
}


//Si el entra el jugador pero hace poco ha estado en en hielo significa que ha pasado de un bloque de hielo a otro
//Sino acaba de entrar al hielo
void EnviromentControl::enterIceZone(int player, Vector2D vel)
{
	if (player == 0) {
		if (p1NumBlocksStepping==0) {
			p1Force.setX(vel.getX() * 1000);
			p1Force.setY(vel.getY() * 1000);
		}
		p1NumBlocksStepping++;
	}
	else if (player == 1) {
		if (p2NumBlocksStepping == 0) {
			p2Force.setX(vel.getX() * 1000);
			p2Force.setY(vel.getY() * 1000);
		}
		p2NumBlocksStepping++;
	}
}

void EnviromentControl::exitedIceZone(int p)
{
	if (p == 0) {
		p1NumBlocksStepping--;
		if (p1NumBlocksStepping <= 0) {
			p1Force.setX(0);
			p1Force.setY(0);
			p1NumBlocksStepping = 0;
		}
	}
	else {
		p2NumBlocksStepping--;
		if (p2NumBlocksStepping <= 0) {
			p2Force.setX(0);
			p2Force.setY(0);
			p2NumBlocksStepping = 0;
		}
	}
}


//Obtener las "velocidades de cada player en cada direccion
double EnviromentControl::getPlayerForceX(int p)
{
	if (p == 0) {
		if (p1Force.getX() > 1000)return 1;
		else return (p1Force.getX() / 1000);
	}
	else {
		if (p2Force.getX() > 1000)return 1;
		else return (p2Force.getX() / 1000);
	}
}

double EnviromentControl::getPlayerForceY(int p)
{
	if (p == 0) {
		if (p1Force.getY() > 1000)return 1;
		else return (p1Force.getY() / 1000);
	}
	else {
		if (p2Force.getY() > 1000)return 1;
		else return (p2Force.getY() / 1000);
	}
}


//Si la fuerza es insignificante la pongo a 0
void EnviromentControl::isThereForce()
{
	if (p1Force.getX() > -10 && p1Force.getX() < 10) p1Force.setX(0);
	if (p1Force.getY() > -10 && p1Force.getY() < 10) p1Force.setY(0);
	if (p2Force.getX() > -10 && p2Force.getX() < 10) p2Force.setX(0);
	if (p2Force.getY() > -10 && p2Force.getY() < 10) p2Force.setY(0);

}

//Si el player se ha movido en el hielo vamos a aplicar una fuerza en la direccion en la que se ha movido
//asi acumulamos inercia
void EnviromentControl::playerIsMoving(int p, Vector2D v)
{
	//Player 1
	if (p == 0) {
		double x = v.getX();
		double y = v.getY();
		if (x < 0)p1Force.setX(p1Force.getX() - accelerationIce);
		else  if (x > 0) p1Force.setX(p1Force.getX() + accelerationIce);

		if (y < 0)p1Force.setY(p1Force.getY() - accelerationIce);
		else if (y > 0) p1Force.setY(p1Force.getY() + accelerationIce);
	}
	//PLayer 2
	else {
		double x = v.getX();
		double y = v.getY();
		if (x < 0)p2Force.setX(p2Force.getX() - accelerationIce);
		else  if (x > 0) p2Force.setX(p2Force.getX() + accelerationIce);

		if (y < 0)p2Force.setY(p2Force.getY() - accelerationIce);
		else if (y > 0) p2Force.setY(p2Force.getY() + accelerationIce);
	}
}
