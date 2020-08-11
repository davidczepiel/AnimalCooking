#include "PidgeonAdversity.h"
#include "MultipleAdversityManager.h"
#include "TimerViewer.h"

PidgeonAdversity::PidgeonAdversity(MultipleAdversityManager* mam) :Adversity(mam)
{
	
	positions.push_back(false);
	positions.push_back(false);
	positions.push_back(false);
	positions.push_back(false);

	coming_ = false;
	standing_ = false;
	leaving_ = false;
	durationTimer_ = new Timer();
	durationTimer_->setTime(6000);
	GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(durationTimer_);

	drawingTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PidgeonStandingAdversity);

	drawingArea_.x = 0;
	drawingArea_.y = 0;
	drawingArea_.w = SDLGame::instance()->getWindowWidth()/4;
	drawingArea_.h = SDLGame::instance()->getWindowHeight()/2;

	row = 0;
	column = 0;

	angle = 0;

	lastFrame = 0;
	frameDuration = 200;

	clipArea_.x = 48*column;
	clipArea_.y = 48*row;
	clipArea_.w = 48;
	clipArea_.h = 48;
}

void PidgeonAdversity::update()
{
	durationTimer_->update();

	//Si el pajaro esta llegando para posarse
		if (coming_ && !standing_ && hasReached(0.33)) {
			standing_ = true;
			column = 0;
			locatePidgeon();
		}
		//Si el pajaro se esta posando y preparando para irse
		else if (standing_ && !leaving_ && hasReached(0.66)) {
			leaving_ = true;
			column = 2;
			locatePidgeon();
		}
		//si el pajaro se esta llendo
		else if (leaving_ && hasReached(0.98)) {
			if (durationTimer_->isTimerEnd()) 
				multipleAdversityMngr_->stopAdversity(ecs::AdversityID::PidgeonAdversity);		
		}
		if (SDL_GetTicks() - lastFrame > frameDuration) {
			lastFrame = SDL_GetTicks();
			row++;
			row %= 3;
		}
}


void PidgeonAdversity::draw()
{
	clipArea_.x = row * 48;
	clipArea_.y = column * 48;
	drawingTexture_->render(drawingArea_,angle, clipArea_);
}

void PidgeonAdversity::reset()
{
	durationTimer_->timerReset();
	coming_ = false;
	standing_ = false;
	leaving_ = false;
	row = 0;
	column = 0;
	positions.at(0)=false; positions.at(1) = false;
	positions.at(2) = false; positions.at(3) = false;
}

void PidgeonAdversity::start()
{
	locatePidgeon();
	coming_ = true;
	durationTimer_->timerReset();
	durationTimer_->timerStart();
}

bool PidgeonAdversity::hasReached(double d)
{
	if (durationTimer_->getProgress() > d)return true;
	else return false;
}





void PidgeonAdversity::locatePidgeon()
{
	//Me indica si es horizontal o vertical su posicion
	int a =  SDLGame::instance()->getRandGen()->nextInt()%2;
	//Me indica si esta izquierda(0)/derecha(1) o abajo(0)/ arriba(1)
	int b =  SDLGame::instance()->getRandGen()->nextInt()%2;
	int pos = posibleLocation(a, b);
	//Mientras la posicion que quiero ocupar ya haya sido usada busco otra
	while (positions.at(pos)) {
		 a =  SDLGame::instance()->getRandGen()->nextInt()%2;
		 b =  SDLGame::instance()->getRandGen()->nextInt()%2;
		 pos = posibleLocation(a, b);
	}
	//ARRIBA
	if (pos == 0) {
		drawingArea_.x = SDLGame::instance()->getRandGen()->nextInt(0, SDLGame::instance()->getWindowWidth() - drawingArea_.w);
		drawingArea_.y = 0;
	}
	//DERECHA
	else if(pos==1) {
		drawingArea_.x = SDLGame::instance()->getWindowWidth() - drawingArea_.w;
		drawingArea_.y = SDLGame::instance()->getRandGen()->nextInt(0, SDLGame::instance()->getWindowHeight() - drawingArea_.h);
	}
	//ABAJO
	else if (pos == 2) {
		drawingArea_.x = SDLGame::instance()->getRandGen()->nextInt(0, SDLGame::instance()->getWindowWidth() - drawingArea_.w);
		drawingArea_.y = SDLGame::instance()->getWindowHeight() - drawingArea_.h;
	}
	//IZQUIERDA
	else if (pos == 3) {
		drawingArea_.x = 0;
		drawingArea_.y = SDLGame::instance()->getRandGen()->nextInt(0, SDLGame::instance()->getWindowHeight() - drawingArea_.h);
	}
	angle = 180 + (90 * pos);
	positions.at(pos) = true;
}

int PidgeonAdversity::posibleLocation(int a, int b)
{
	int pos = 0;
	if (a == 0 && b == 1) pos = 0;       //Arriba
	else if (a == 1 && b == 1)  pos = 1; //Derecha
	else if (a == 0 && b == 0)  pos = 2; //Abajo
	else if (a == 1 && b == 0)  pos = 3; //Izquierda

	return pos;
}
