#include "IngredientsDeathAdversity.h"
#include "MultipleAdversityManager.h"
#include "RandomNumberGenerator.h"

IngredientsDeathAdversity::IngredientsDeathAdversity(MultipleAdversityManager* mAdvMng) :Adversity(mAdvMng)
{
	deathTexture = SDLGame::instance()->getTextureMngr()->getTexture(Resources::FlowerAdversity);
	deathTimer = new Timer();
	deathTimer->setTime(5000);
	ingredients = multipleAdversityMngr_->getIngredientsPool()->getPool();
	GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(deathTimer);
	src.w = 116; src.h = 116;
	src.x = 0; src.y = 116;
	dest.x = 0; dest.y = 0;
	dest.w = 150; dest.h = 150;
	animationSpeed = 1000;
	killsStarted = 0;
	gl = multipleAdversityMngr_->getGameLogic();
}

void IngredientsDeathAdversity::update()
{
	deathTimer->update();
	//Avanzo el timer de cada ingrediente
	inspectIngredients();
	//Voy activando los timers de cada ingrediente a medida que pasa el tiempo
	if (deathTimer->getProgress() > ((killsStarted) * percentagePerKill)) {
		startIngredient(killsStarted);
	}
	if (deathTimer->isTimerEnd()) {
		if (allCompleted()) {
			multipleAdversityMngr_->stopAdversity(ecs::AdversityID::IngredientsdeathAdversity);
			reset();
		}
	}
}

void IngredientsDeathAdversity::draw()
{
	if (deathTimer->isStarted()) {
		for (int i = 0; i < ingInfo.size(); i++) {
			if (ingInfo.at(i).ing != nullptr)
				getPosIngredient(i);

				//Dependiendo de si el contador específico de el ingrediente ha empezado o no renderizo la animacion de que va a morir o la de que está muriendo
			if ( ingInfo.at(i).animationTimer->isStarted()) {
				dest.x = ingInfo.at(i).pos.getX() ;
				dest.y = ingInfo.at(i).pos.getY()  ;
				deathTexture->renderFrame(dest, ingInfo.at(i).row, ingInfo.at(i).col, 0);
			}
		}
	}
}

void IngredientsDeathAdversity::reset()
{
	killsDone = 0;
	numKills = 0;
	killsStarted = 0;
	ingInfo.clear();
}

void IngredientsDeathAdversity::start()
{
	reset();
	//Me quedo con la pool de los ingredientes y digo cuantos voy a matar
	ingredients = multipleAdversityMngr_->getIngredientsPool()->getPool();
	numKills = (ingredients.size()/2);
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
		info.animationTimer->setTime(animationSpeed);
		info.col = 0;
		info.row = 0;
		info.dead = false;
		info.end = false;
		GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(info.animationTimer);
		ingInfo.push_back(info);
	}
	deathTimer->timerReset();
	deathTimer->setTime(5000);
	deathTimer->timerStart();
	killsDone = 0;
	ingInfo.at(0).animationTimer->timerStart();
	killsStarted = 1;
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
		if (ingInfo.at(killsDone).ing != nullptr) {
			gl->ingredientDeath(ingInfo.at(killsDone).ing);
			ingInfo.at(killsDone).ing = nullptr;
		}
		ingInfo.at(killsDone).dead = true;
		ingInfo.at(killsDone).row = 1;
		killsDone++;
	}
}

void IngredientsDeathAdversity::inspectIngredients()
{
	for (int i = 0; i < ingInfo.size(); i++) {
		//Me quedo con el frame que le corresponda segun como vaya de avanzado su timer
		ingInfo.at(i).animationTimer->update();
		ingInfo.at(i).col = 14* ingInfo.at(i).animationTimer->getProgress();
		ingInfo.at(i).col %= 7;
		//Si el timer ya está contando y ha sobrepasado la mitad de su tiempo este ingrediente ha muerto
		if (!ingInfo.at(i).dead && ingInfo.at(i).animationTimer->isStarted() && ingInfo.at(i).animationTimer->getProgress() > 0.50) {
			killIngredient();
		}
		if (ingInfo.at(i).animationTimer->isTimerEnd()) {
			ingInfo.at(i).animationTimer->timerReset();
			ingInfo.at(i).end = true;
		}
	}
}

void IngredientsDeathAdversity::getPosIngredient(int i)
{
	if(ingInfo.at(i).ing!=nullptr)
	ingInfo.at(i).pos = ingInfo.at(i).ing->getPos() - Vector2D(dest.w/4,dest.h/4);
}

int IngredientsDeathAdversity::getNumber()
{
	return SDLGame::instance()->getRandGen()->nextInt(0, ingredients.size() - 1);
}

//Compruebo que todos los ingredientes han muerto y luego si sus timers se han acabado para verificar el fin de la adversidad
bool IngredientsDeathAdversity::allCompleted()
{
	bool completed = true;
	int i = 0;
	while (i < ingInfo.size() && completed ) {
		if (!ingInfo.at(i).dead || !ingInfo.at(i).animationTimer->isTimerEnd()) completed = false;
		i++;
	}
	return completed;
}

void IngredientsDeathAdversity::startIngredient(int i)
{
	if (killsStarted < numKills) {
		if (killsStarted < ingInfo.size()) {
			ingInfo.at(killsStarted).animationTimer->timerStart();
			killsStarted++;
		}
	}
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
