#include "Transport.h"
#include "Entity.h"

Transport::Transport() : Component(ecs::Transport)
{
	objInHands_ = nullptr;
	playerTransform_ = nullptr;
}

void Transport::pick(Pickable* obj)
{
	if (objInHands_ == nullptr)
		objInHands_ = obj;
	else swap(obj);
}

void Transport::drop()
{
	objInHands_ = nullptr;
}

void Transport::swap(Pickable* obj)
{
	objInHands_ = nullptr;
	objInHands_ = obj;
}

void Transport::init()
{
	playerTransform_ = GETCMP1_(Transform);
}

void Transport::update()
{	
	if (objInHands_ != nullptr && !(playerTransform_->getVel().getX() == 0 && playerTransform_->getVel().getY() == 0)) {

		float angle = -((atan2(playerTransform_->getVel().getY(), playerTransform_->getVel().getX()) * 180)/M_PI);
		int centerX = playerTransform_->getPos().getX() + playerTransform_->getW() / 2;
		int centerY = playerTransform_->getPos().getY() + playerTransform_->getH() / 2;

		Vector2D objPos = Vector2D();
		double offsetX = playerTransform_->getW()/2;
		double offsetY = playerTransform_->getH()/2;

		Vector2D objOffset = objInHands_->getSize()/2;

		if ((angle > (-22.5) && angle <= 22.5)) { //Derecha
			cout << "Derecha" << endl;
			objPos = Vector2D(centerX + offsetX, centerY);
		}
		else if((angle > 22.5 && angle <= 67.5)) { //Arriba a la derecha
			cout << "Arriba a la derecha" << endl;
			objPos = Vector2D(centerX + offsetX, centerY - offsetY);
		}
		else if ((angle > 67.5 && angle <= 112.5)) { //Arriba
			cout << "Arriba" << endl;
			objPos = Vector2D(centerX, centerY - offsetY);
		}
		else if ((angle > 112.5 && angle <= 157.5)) { //Arriba a la izquierda
			cout << "Arriba a la izquierda" << endl;
			objPos = Vector2D(centerX - offsetX, centerY - offsetY);
		}
		else if ((angle > 157.5 || angle <= (-157.5))) { //izquierda
			cout << "izquierda" << endl;
			objPos = Vector2D(centerX - offsetX, centerY);
		}
		else if ((angle > (-157.5) && angle <= (-112.5))) { //Abajo a la izquierda
			cout << "Abajo a la izquierda" << endl;
			objPos = Vector2D(centerX - offsetX, centerY + offsetY);
		}
		else if ((angle > (-112.5) && angle <= (-67.5))) { //Abajo
			cout << "Abajo" << endl;
			objPos = Vector2D(centerX, centerY + offsetY);
		}
		else if ((angle > (-67.5) && angle <= (-22.5))) { //abajo a la derecha
			cout << "abajo a la derecha" << endl;
			objPos = Vector2D(centerX + offsetX, centerY + offsetY);
		}

		objInHands_->setPos(objPos - objOffset);
	}

	/*if (objInHands_ != nullptr && !(playerTransform_->getVel().getX() == 0 && playerTransform_->getVel().getY() == 0)) {
		
		objInHands_->setPos(Vector2D(playerTransform_->getPos().getX() + playerTransform_->getW()/2 + playerTransform_->getVel().getX() * playerTransform_->getW()/2,
			playerTransform_->getPos().getY() + playerTransform_->getH()/2 + playerTransform_->getVel().getY() * playerTransform_->getH()/2));
	}*/
}

bool Transport::hasEmptyDish()
{
	/*if (dynamic_cast<Dish*>(objInHands_) != nullptr) {
		return static_cast<Dish*>(objInHands_)->isEmpty();
	}
	else return false;*/
	return false;
}
