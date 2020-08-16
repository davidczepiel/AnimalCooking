#include "AIIngredient.h"
#include "Ingredient.h"
#include "GameConfig.h"

AIIngredient::AIIngredient(IngredientsPool* ip, Transform* t1, Transform* t2) :
	Component(ecs::AIIngredient),
	ip_(ip), t1_(t1),
	t2_(t2),
	rangeX(config::AI_INGREDIENT_RANGE* SDLGame::instance()->getCasillaX()),
	rangeY(config::AI_INGREDIENT_RANGE* SDLGame::instance()->getCasillaY()) {
}

void AIIngredient::update()
{
	for (Ingredient* i : ip_->getPool()) {
		updateIngredientState(i);
	}
}

void AIIngredient::updateIngredientState(Ingredient* i) {
	IngredientState state = i->getIngredientState();
	Timer& timer = i->getInternalTimer();
	Vector2D vel = { 0, 0 };
	double distance1 = (t1_->getPos() - i->getPos()).magnitude();
	double distance2 = (t2_->getPos() - i->getPos()).magnitude();

	timer.update();

	//Primero se mira si algun player esta en rango y se calcula la direccion de huida
	if (distance1 < rangeX && distance1 < rangeY) {
		i->setState(Escaping);
		vel = Vector2D((i->getPos() - t1_->getPos()).normalize() * i->getMaxVel());
		i->setLastVel(vel);
	}
	else if (distance2 < rangeX && distance2 < rangeY) {
		i->setState(Escaping);
		vel = vel + Vector2D((i->getPos() - t2_->getPos()).normalize() * i->getMaxVel());
		i->setLastVel(vel);
	}

	if (state == IngredientState::Idle && timer.isTimerEnd()) {
		i->setState(Walking);
		i->setVel(calculateNewVel(i));
		i->setLastVel(calculateNewVel(i));
		timer.timerReset();
		timer.setTime(SDLGame::instance()->getRandGen()->nextInt(config::AI_INGREDIENT_MIN_TIME_WALKING, config::AI_INGREDIENT_MAX_TIME_WALKING));
		timer.timerStart();
	}
	else if (state == IngredientState::Walking && timer.isTimerEnd()) {
		i->setState(Idle);
		i->setVel(Vector2D(0, 0));
		timer.timerReset();
		timer.setTime(SDLGame::instance()->getRandGen()->nextInt(config::AI_INGREDIENT_MIN_TIME_IDLE, config::AI_INGREDIENT_MAX_TIME_IDLE));
		timer.timerStart();
	}
	else if (state == IngredientState::Escaping) {
		if (distance1 > rangeX&& distance1 > rangeY&& distance2 > rangeX&& distance2 > rangeY) {	//fuera de rango los dos players
			i->setState(Idle);
			timer.timerReset();
			timer.setTime(SDLGame::instance()->getRandGen()->nextInt(config::AI_INGREDIENT_MIN_TIME_IDLE, config::AI_INGREDIENT_MAX_TIME_IDLE));
			timer.timerStart();
		}
		else {	//alguno est� en rango
			i->setVel(vel);
			i->setLastVel(vel);
		}
	}
}

Vector2D AIIngredient::calculateNewVel(Ingredient* i) {
	Vector2D newVel;
	Vector2D orientation;

	orientation = Vector2D((SDLGame::instance()->getWindowWidth() * 0.65) - i->getPos().getX(), (SDLGame::instance()->getWindowHeight() * 0.4) - i->getPos().getY()).normalize() / 4;

	newVel = Vector2D(SDLGame::instance()->getRandGen()->nextInt(-5, 6), SDLGame::instance()->getRandGen()->nextInt(-5, 6)).normalize();
	newVel = newVel + orientation;
	newVel = newVel.normalize() * i->getMaxVel();

	return newVel;
}

void AIIngredient::NotCorner(double player1Angle, double player2Angle, Vector2D p1toIngredient, Vector2D p2toIngredient, Vector2D player1Pos, Vector2D player2Pos, Vector2D ingPos, Vector2D ingVel, Ingredient* ing)
{
	int winh = SDLGame::instance()->getWindowHeight();
	int winw = SDLGame::instance()->getWindowWidth();
	int casillaX = SDLGame::instance()->getCasillaX();
	int casillaY = SDLGame::instance()->getCasillaY();
	Vector2D fleeDir(ingVel);
	int UpDistance = ingPos.getY() - casillaY;
	int DownDistance = 6 * casillaY - ingPos.getY();
	if (ingPos.getX() >= 8 * casillaX && ingPos.getX() <= 9 * casillaX)//a la izquierda
	{
		if (((player1Angle >= 125 && player1Angle <= 150) && !(player2Angle > -150 && player2Angle < -125)) ||//el player 1 bloquea arriba a la derecha
			((player2Angle >= 125 && player2Angle <= 150) && !(player1Angle > -150 && player1Angle < -125)))	//el player 2 bloquea arriba a la derecha
		{
			cout << "abajoderecha" << endl;
			Vector2D abajo(0, DownDistance);
			fleeDir.set(abajo.normalize() + (p1toIngredient * -1).normalize());//bisectriz entre abajo y la dirección hacia el player

		}
		else if (((player1Angle >= -150 && player1Angle <= -125) && !(player2Angle >= 125 && player2Angle <= 150)) || //el player 1 bloquea abajo a la derecha
			((player2Angle >= -150 && player2Angle <= -125) && !(player1Angle >= 125 && player1Angle <= 150)))	//el player 2 bloquea abajo a la derecha
		{
			cout << "arribaderecha" << endl;
			Vector2D arriba(0, -UpDistance);
			fleeDir.set(arriba.normalize() + (p1toIngredient * -1).normalize());//bisectriz entre arriba y la dirección hacia el player

		}
		else if (((player1Angle >= 125 && player1Angle <= 150) &&( player2Angle >= -150 && player2Angle <= -125)) || ( //un player bloquea arriba a la derecha y el otro 
			(player2Angle >= 125 && player2Angle <= 150) && (player1Angle >= -150 && player1Angle <= -125)))		   //bloquea abajo a la derecha 
		{
			cout << "derecha" << endl;
			fleeDir.set(1, 0);
		}

	}
	else if (ingPos.getX() >= winw - casillaX && ingPos.getX() <= winw)//a la derecha
	{
		if (((player1Angle >= 35 && player1Angle <= 65) && !(player2Angle > -65 && player2Angle < -35)) ||//el player 1 bloquea arriba a la izquierda
			((player2Angle >= 35 && player2Angle <= 65) && !(player1Angle > -65 && player1Angle < -35)))	//el player 2 bloquea arriba a la izquierda
		{
			cout << "abajoizquierda" << endl;
			Vector2D abajo(0, DownDistance);
			fleeDir.set(abajo.normalize() + p1toIngredient.normalize());//bisectriz entre abajo y la dirección hacia el player

		}
		else if (((player1Angle >= -65 && player1Angle <= -35) && !(player2Angle >= 35 && player2Angle <= 65)) || //el player 1 bloquea abajo a la izquierda
			((player2Angle >= -65 && player2Angle <= -35) && !(player1Angle >= 35 && player1Angle <= 65)))	//el player 2 bloquea abajo a la izquierda
		{
			cout << "arribaizquierda" << endl;
			Vector2D arriba(0, -UpDistance);
			fleeDir.set(arriba.normalize() + p1toIngredient.normalize());//bisectriz entre arriba y la dirección hacia el player

		}
		else if (((player1Angle >= 35 && player1Angle <= 65) && (player2Angle >= -65 && player2Angle <= -35)) || ( //un player bloquea arriba a la izquierda y el otro 
			(player2Angle >= 35 && player2Angle <= 65) && (player1Angle >= -65 && player1Angle <= -35)))		   //bloquea abajo a la izquierda
		{
			cout << "izquierda" << endl;
			fleeDir.set(-1, 0);
		}

	}
	else if (ingPos.getY() < casillaY)//arriba
	{
	}
	else if (ingPos.getY() > 6 * casillaY)//abajo
	{
	}
}

void AIIngredient::Corner()
{
}
