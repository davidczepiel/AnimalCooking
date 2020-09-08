#include "IngredientsDeathAdversity.h"
#include "MultipleAdversityManager.h"
#include "RandomNumberGenerator.h"

IngredientsDeathAdversity::IngredientsDeathAdversity(MultipleAdversityManager* mAdvMng) :Adversity(mAdvMng)
{
	preparationTexture = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Bin);
	deathTexture = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Aceite);
	deathTimer = new Timer();
	deathTimer->setTime(5000);
	ingredients = multipleAdversityMngr_->getIngredientsPool()->getPool();
	GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(deathTimer);
	src.w = 100; src.h = 100;
	src.x = 0; src.y = 0;
	dest.x = 0; dest.y = 0;
	dest.w = 100; dest.h = 100;
	timeToDeath = 3000;

}

void IngredientsDeathAdversity::update()
{
	deathTimer->update();
	inspectIngredients();
	if (deathTimer->getProgress() > ((killsDone + 1) * percentagePerKill)) {
		killIngredient();
	}
	if (deathTimer->isTimerEnd()) {
		multipleAdversityMngr_->stopAdversity(ecs::AdversityID::IngredientsdeathAdversity);
		reset();
		//killIngredients();
	}
}

void IngredientsDeathAdversity::draw()
{
	if (deathTimer->isStarted() && !deathTimer->isTimerEnd()) {
		for (int i = 0; i < ingInfo.size(); i++) {
			if (ingInfo.at(i).ing != nullptr) {
				getPosIngredient(i);
				//Dependiendo de si el contador específico de el ingrediente ha empezado o no renderizo la animacion de que va a morir o la de que está muriendo
				if (ingInfo.at(i).animationTimer->isStarted())
					deathTexture->render(dest, src);
				else
					preparationTexture->render(dest, src);
			}
		}
	}
}

void IngredientsDeathAdversity::reset()
{
	ingInfo.clear();
}

void IngredientsDeathAdversity::start()
{
	//Me quedo con la pool de los ingredientes y digo cuantos voy a matar
	ingredients = multipleAdversityMngr_->getIngredientsPool()->getPool();
	numKills = (ingredients.size() / 2);
	percentagePerKill = 1 / (numKills + 1);
	//Me quedo con unos cuants ingredientes aleatorios
	while (ingInfo.size() < numKills) {
		int i = getNumber();
		while (alreadyTaken(i)) {
			i = getNumber();
		}
		//Me quedo con la información del ingrediente escogido y me lo guardo en el vector 
		Ingredientinfo info;
		info.ing = ingredients.at(i);
		info.animationTimer = new Timer();
		info.animationTimer->setTime(deathTimer->getTime() * percentagePerKill);
		GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(info.animationTimer);
		ingInfo.push_back(info);
	}
	deathTimer->timerReset();
	deathTimer->setTime(5000);
	deathTimer->timerStart();
	killsDone = 0;
	ingInfo.at(0).animationTimer->timerStart();
}

void IngredientsDeathAdversity::killIngredients()
{
	for (int i = 0; i < ingInfo.size(); i++) {
		multipleAdversityMngr_->getIngredientsPool()->deleteIngredient(ingInfo.at(i).ing->getIt());
	}
}

void IngredientsDeathAdversity::killIngredient()
{
	if (killsDone < numKills) {
		multipleAdversityMngr_->getGhostPool()->activateGhost(ingInfo.at(killsDone).ing->getPos());
		multipleAdversityMngr_->getIngredientsPool()->deleteIngredient(ingInfo.at(killsDone).ing->getIt());
		ingInfo.at(killsDone).ing = nullptr;
		killsDone++;
		if (killsDone < ingInfo.size())
			ingInfo.at(killsDone).animationTimer->timerStart();
	}
}

void IngredientsDeathAdversity::inspectIngredients()
{
	for (int i = 0; i < ingInfo.size(); i++) {
		ingInfo.at(i).animationTimer->update();
	}
}

void IngredientsDeathAdversity::getPosIngredient(int i)
{
	Vector2D pos = ingInfo.at(i).ing->getPos();
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
	while (i < ingInfo.size() && !taken) {
		if (ingInfo.at(i).ing == ingredients.at(number)) taken = true;
		i++;
	}
	return taken;
}
