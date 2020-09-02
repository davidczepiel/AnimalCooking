#include "IngredientsDeathAdversity.h"
#include "MultipleAdversityManager.h"
#include "RandomNumberGenerator.h"

IngredientsDeathAdversity::IngredientsDeathAdversity(MultipleAdversityManager* mAdvMng) :Adversity(mAdvMng)
{
	mTexture = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CuchilloSucio);
	deathTimer = new Timer();
	deathTimer->setTime(5000);
	ingredients = multipleAdversityMngr_->getIngredientsPool()->getPool();
	GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(deathTimer);
	src.w = 100; src.h = 100;
	src.x = 0; src.y = 0;
	dest.x = 0; dest.y = 0;
	dest.w = 100; dest.h = 100;

}

void IngredientsDeathAdversity::update()
{
	deathTimer->update();
	if (deathTimer->isTimerEnd()) {
		multipleAdversityMngr_->stopAdversity(ecs::AdversityID::IngredientsdeathAdversity);
		reset();
	}
}

void IngredientsDeathAdversity::draw()
{
	for (int i = 0; i < indexIngredients.size(); i++) {
		getPosIngredient(i);
		mTexture->render(dest, src);
	}
}

void IngredientsDeathAdversity::reset()
{
	deathTimer->setTime(timeToDeath);
}

void IngredientsDeathAdversity::start()
{
	ingredients = multipleAdversityMngr_->getIngredientsPool()->getPool();
	while (indexIngredients.size() < ingredients.size() / 2) {
		int i = getNumber();
		while (alreadyTaken(i)) {
			i = getNumber();
		}
		indexIngredients.push_back(i);
	}
	deathTimer->timerStart();
}

void IngredientsDeathAdversity::killIngredients()
{
	for (int i = 0; i < ingredients.size(); i++) {
		//ingPool->deleteIngredient(*(ingredients.at(i)));
	}
}

void IngredientsDeathAdversity::getPosIngredient(int i)
{
	Vector2D pos = ingredients.at(i)->getPos();
	dest.x = pos.getX();
	dest.y = pos.getY();
}

int IngredientsDeathAdversity::getNumber()
{
	return SDLGame::instance()->getRandGen()->nextInt(0, ingredients.size() - 1);
}

bool IngredientsDeathAdversity::alreadyTaken(int number)
{
	bool taken = false;
	int i = 0;
	while (i < indexIngredients.size() && !taken) {
		if (indexIngredients.at(i) == number) taken = true;
		i++;
	}
	return taken;
}
