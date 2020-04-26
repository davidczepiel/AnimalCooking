#include "AIIngredient.h"
#include "Ingredient.h"

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
	if (distance1 < range) {
		i->setState(Scaping);
		vel = Vector2D((i->getPos() - t1_->getPos()).normalize() * i->getMaxVel());
	}
	else if (distance2 < range) {
		i->setState(Scaping);
		vel = vel + Vector2D((i->getPos() - t2_->getPos()).normalize() * i->getMaxVel());
	}

	if (state == IngredientState::Idle && timer.isTimerEnd()) {
		i->setState(Walking);
		i->setVel(calculateNewVel(i));
		timer.timerReset();
		timer.setTime(SDLGame::instance()->getRandGen()->nextInt(0,maxTimeWalking));
		timer.timerStart();
	}
	else if (state == IngredientState::Walking && timer.isTimerEnd()) {
		i->setState(Idle);
		i->setVel(Vector2D(0, 0));
		timer.timerReset();
		timer.setTime(SDLGame::instance()->getRandGen()->nextInt(0, maxTimeIdle));
		timer.timerStart();
	}
	else if (state == IngredientState::Scaping) {
		if (distance1 > range && distance2 > range) {	//fuera de rango los dos players
			i->setState(Idle);
			timer.timerReset();
			timer.setTime(SDLGame::instance()->getRandGen()->nextInt(0, maxTimeIdle));
			timer.timerStart();
		}
		else {	//alguno está en rango
			i->setVel(vel);
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
