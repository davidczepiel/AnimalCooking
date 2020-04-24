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
	double distance1 = (t1_->getPos() - i->getPos()).magnitude();
	double distance2 = (t2_->getPos() - i->getPos()).magnitude();

	if (i->getIngredientState() != Scaping && distance1 < range)
		i->setState(Scaping);
	else if (i->getIngredientState() != Scaping && distance2 < range)
		i->setState(Scaping);

	if (state == IngredientState::Idle && timer.isTimerEnd()) {
		i->setState(Walking);
		timer.timerReset();
		timer.setTime(timeWalking);
	}
	else if (state == IngredientState::Walking && timer.isTimerEnd()) {
		i->setState(Idle);
		timer.timerReset();
		timer.setTime(timeIdle);
	}
	else if (state == IngredientState::Scaping) {
		if (distance1 < range) {
			i->setVel(Vector2D((i->getPos() - t1_->getPos()).normalize() * i->getMaxVel()));
		}
		else if (distance2 < range) {
			i->setVel(Vector2D((i->getPos() - t2_->getPos()).normalize() * i->getMaxVel()));
		}
		else {
			i->setState(Idle);
			timer.timerReset();
			timer.setTime(timeIdle);
		}
	}
	timer.update();
}
