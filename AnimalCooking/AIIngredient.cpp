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
	Timer& wallscapingTimer = i->getWallScapingTimer();
	if (state == IngredientState::WallScaping) {
		wallscapingTimer.update();
	}
	Vector2D vel = { 0, 0 };
	double distance1 = (t1_->getPos() - i->getPos()).magnitude();
	double distance2 = (t2_->getPos() - i->getPos()).magnitude();

	timer.update();

	//Primero se mira si algun player esta en rango y se calcula la direccion de huida
	if (distance1 < rangeX && distance1 < rangeY && state != IngredientState::WallScaping) {
		i->setState(Escaping);
		vel = Vector2D((i->getPos() - t1_->getPos()).normalize() * i->getMaxVel());
		i->setLastVel(vel);
	}
	else if (distance2 < rangeX && distance2 < rangeY && state != IngredientState::WallScaping) {
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
	else if (state == IngredientState::WallScaping && wallscapingTimer.isTimerEnd()) {
		i->setState(IngredientState::Escaping);
		wallscapingTimer.timerReset();
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

void AIIngredient::NotCorner(Vector2D p1toIngredient, Vector2D p2toIngredient, Ingredient* ing)
{
	if (ing->getIngredientState() != IngredientState::WallScaping) {
		int winh = SDLGame::instance()->getWindowHeight();
		int winw = SDLGame::instance()->getWindowWidth();
		int casillaX = SDLGame::instance()->getCasillaX();
		int casillaY = SDLGame::instance()->getCasillaY();
		Vector2D player1Pos = t1_->getPos();
		Vector2D player2Pos = t2_->getPos();
		Vector2D ingPos = ing->getPos();
		Vector2D ingVel = ing->getVel();
		Vector2D fleeDir(ingVel.normalize());
		//int UpDistance = ingPos.getY() - casillaY;
		//int DownDistance = 6 * casillaY - ingPos.getY();
		double distance1 = (player1Pos - ing->getPos()).magnitude();
		double distance2 = (player2Pos - ing->getPos()).magnitude();
		if (ingPos.getX() >= 8 * casillaX && ingPos.getX() <= 9 * casillaX)//a la izquierda
		{
			if (((player1Pos.getX() >= ingPos.getX() && player1Pos.getY() <= ingPos.getY()) && (distance1 <= rangeX && distance1 <= rangeY)))//el player 1 bloquea arriba a la derecha
			{
				Vector2D abajo(0, 1);
				fleeDir.set(abajo.normalize() + (p1toIngredient * -1).normalize());//bisectriz entre abajo y la dirección hacia el player
			}
			else if ((player2Pos.getX() >= ingPos.getX() && player2Pos.getY() <= ingPos.getY()) && (distance2 <= rangeX && distance2 <= rangeY))	//el player 2 bloquea arriba a la derecha
			{
				Vector2D abajo(0, 1);
				fleeDir.set(abajo.normalize() + (p2toIngredient * -1).normalize());//bisectriz entre abajo y la dirección hacia el player

			}
			else if (((player1Pos.getX() >= ingPos.getX() && player1Pos.getY() >= ingPos.getY()) && (distance1 <= rangeX && distance1 <= rangeY))) //el player 1 bloquea abajo a la derecha
			{
				Vector2D arriba(0, -1);
				fleeDir.set(arriba.normalize() + (p1toIngredient * -1).normalize());//bisectriz entre arriba y la dirección hacia el player
			}
			else if ((player2Pos.getX() >= ingPos.getX() && player2Pos.getY() >= ingPos.getY()) && (distance2 <= rangeX && distance2 <= rangeY))	//el player 2 bloquea abajo a la derecha
			{
				Vector2D arriba(0, -1);
				fleeDir.set(arriba.normalize() + (p2toIngredient * -1).normalize());//bisectriz entre arriba y la dirección hacia el player

			}
		}
		else if (ingPos.getX() >= winw - casillaX && ingPos.getX() <= winw)//a la derecha
		{
			if (((player1Pos.getX() <= ingPos.getX() && player1Pos.getY() <= ingPos.getY()) && (distance1 <= rangeX && distance1 <= rangeY)))//el player 1 bloquea arriba a la izquierda
			{
				Vector2D abajo(0, 1);
				fleeDir.set(abajo.normalize() + (p1toIngredient * -1).normalize());//bisectriz entre abajo y la dirección hacia el player
			}
			else if ((player2Pos.getX() <= ingPos.getX() && player2Pos.getY() <= ingPos.getY()) && (distance2 <= rangeX && distance2 <= rangeY))	//el player 2 bloquea arriba a la izquierda
			{
				Vector2D abajo(0, 1);
				fleeDir.set(abajo.normalize() + (p2toIngredient * -1).normalize());//bisectriz entre abajo y la dirección hacia el player

}
			else if (((player1Pos.getX() <= ingPos.getX() && player1Pos.getY() >= ingPos.getY()) && (distance1 <= rangeX && distance1 <= rangeY)))//el player 1 bloquea abajo a la izquierda
			{
				Vector2D arriba(0, -1);
				fleeDir.set(arriba.normalize() + (p1toIngredient * -1).normalize());//bisectriz entre arriba y la dirección hacia el player
			}
			else if ((player2Pos.getX() <= ingPos.getX() && player2Pos.getY() >= ingPos.getY()) && (distance2 <= rangeX && distance2 <= rangeY))	//el player 2 bloquea abajo a la izquierda
			{
				Vector2D arriba(0, -1);
				fleeDir.set(arriba.normalize() + (p2toIngredient * -1).normalize());//bisectriz entre arriba y la dirección hacia el player

			}

		}
		else if (ingPos.getY() < casillaY)//arriba
		{
			if (((player1Pos.getX() <= ingPos.getX() && player1Pos.getY() >= ingPos.getY()) && (distance1 <= rangeX && distance1 <= rangeY)))//el player 1 bloquea abajo a la izquierda
			{
				Vector2D derecha(1, 0);
				fleeDir.set(derecha.normalize() + (p1toIngredient * -1).normalize());//bisectriz entre derecha y la dirección hacia el player
			}
			else if ((player2Pos.getX() <= ingPos.getX() && player2Pos.getY() >= ingPos.getY()) && (distance2 <= rangeX && distance2 <= rangeY))	//el player 2 bloquea abajoa la izquierda
			{
				Vector2D derecha(1, 0);
				fleeDir.set(derecha.normalize() + (p2toIngredient * -1).normalize());//bisectriz entre derecha y la dirección hacia el player
			}
			else if (((player1Pos.getX() >= ingPos.getX() && player1Pos.getY() >= ingPos.getY()) && (distance1 <= rangeX && distance1 <= rangeY))) //el player 1 bloquea abajo a la derecha
			{
				Vector2D izquierda(-1, 0);
				fleeDir.set(izquierda.normalize() + (p1toIngredient * -1).normalize());//bisectriz entre izquierda y la dirección hacia el player
			}
			else if ((player2Pos.getX() >= ingPos.getX() && player2Pos.getY() >= ingPos.getY()) && (distance2 <= rangeX && distance2 <= rangeY)) {	//el player 2 bloquea abajo a la derecha
				{
					Vector2D izquierda(-1, 0);
					fleeDir.set(izquierda.normalize() + (p2toIngredient * -1).normalize());//bisectriz entre izquierda y la dirección hacia el playe
				}
			}
		}
		else if (ingPos.getY() > 6 * casillaY)//abajo
		{
			if (((player1Pos.getX() <= ingPos.getX() && player1Pos.getY() <= ingPos.getY()) && (distance1 <= rangeX && distance1 <= rangeY)))//el player 1 bloquea arriba a la izquierda
			{
				Vector2D derecha(1, 0);
				fleeDir.set(derecha.normalize() + (p1toIngredient * -1).normalize());//bisectriz entre derecha y la dirección hacia el player
			}
			else if ((player2Pos.getX() <= ingPos.getX() && player2Pos.getY() <= ingPos.getY()) && (distance2 <= rangeX && distance2 <= rangeY))	//el player 2 bloquea arriba ala izquierda
			{
				Vector2D derecha(1, 0);
				fleeDir.set(derecha.normalize() + (p2toIngredient * -1).normalize());//bisectriz entre derecha y la dirección hacia el player

			}
			else if (((player1Pos.getX() >= ingPos.getX() && player1Pos.getY() <= ingPos.getY()) && (distance1 <= rangeX && distance1 <= rangeY))) //el player 1 bloquea arriba a la derecha
			{
				Vector2D izquierda(-1, 0);
				fleeDir.set(izquierda.normalize() + (p1toIngredient * -1).normalize());//bisectriz entre izquierda y la dirección hacia el player
			}
			else if ((player2Pos.getX() >= ingPos.getX() && player2Pos.getY() <= ingPos.getY()) && (distance2 <= rangeX && distance2 <= rangeY)) { //el player 2 bloquea arriba a la derecha

				Vector2D izquierda(-1, 0);
				fleeDir.set(izquierda.normalize() + (p2toIngredient * -1).normalize());//bisectriz entre izquierda y la dirección hacia el player

			}
		}
		ing->setState(WallScaping);
		ing->getWallScapingTimer().timerStart();
		ing->setVel(fleeDir * ing->getVel().magnitude());
	}
}

void AIIngredient::Corner(Ingredient* ing)
{
		Vector2D fleeDir(ing->getVel().normalize());
		Vector2D p1Pos = t1_->getPos();
		Vector2D p2Pos = t2_->getPos();
		Vector2D ingPos = ing->getPos();
		double distance1 = (p1Pos - ing->getPos()).magnitude();
		double distance2 = (p2Pos - ing->getPos()).magnitude();
		double casillaY = SDLGame::instance()->getCasillaY();
		double casillaX = SDLGame::instance()->getCasillaX();
		int winw = SDLGame::instance()->getWindowWidth();
		//ingrediente esquina de arriba y el jugador tapa el acceso a la otra esquina de arriba
		if (ingPos.getY() < casillaY && ((distance1 <= rangeX && distance1 <= rangeY) || (distance2 <= rangeX && distance2 <= rangeY)) && (p1Pos.getY() < 1.5 * casillaY || p2Pos.getY() < 1.5 * casillaY))
			fleeDir.set(0, 1);
		//ingrediente esquina de abajo y el jugador tapa el acceso a la otra esquina de abajo
		else if (ingPos.getY() < casillaY && ((distance1 <= rangeX && distance1 <= rangeY) || (distance2 <= rangeX && distance2 <= rangeY)) && (p1Pos.getY() > 5.5 * casillaY || p2Pos.getY() > 5.5 * casillaY))
			fleeDir.set(0, -1);
		//íngrediente esquina izquierda y player en pared izquierda
		else if ((ingPos.getX() >= 8 * casillaX && ingPos.getX() <= 9 * casillaX) && ((distance1 <= rangeX && distance1 <= rangeY) || (distance2 <= rangeX && distance2 <= rangeY))
			&& ((p1Pos.getX() >= 8 * casillaX && p1Pos.getX() <= 9 * casillaX) || (p2Pos.getX() >= 8 * casillaX && p2Pos.getX() <= 9 * casillaX)))
			fleeDir.set(1, 0);
		//íngrediente esquina derecha y player en pared derecha
		else if ((ingPos.getX() >= winw - casillaX && ingPos.getX() <= winw) && ((distance1 <= rangeX && distance1 <= rangeY) || (distance2 <= rangeX && distance2 <= rangeY))
			&& ((p1Pos.getX() >= winw - casillaX && p1Pos.getX() <= winw) || (p2Pos.getX() >= winw - casillaX && p2Pos.getX() <= winw)))
			fleeDir.set(-1, 0);
		
		ing->setState(WallScaping);
		ing->getWallScapingTimer().timerStart();
		ing->setVel(fleeDir * ing->getVel().magnitude());
		cout << "hey" << endl;
}

