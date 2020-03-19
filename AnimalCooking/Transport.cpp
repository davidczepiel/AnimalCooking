#include "Transport.h"
#include "Entity.h"
#include "Dish.h"

Transport::Transport() : Component(ecs::Transport), 
objInHands_(nullptr), 
playerTransform_(nullptr), 
objType_(objType_ = Resources::PickableType::none)
{
}

void Transport::pick(Pickable* obj, Resources::PickableType objType)
{
	if (objInHands_ == nullptr) {
		objInHands_ = obj;
		 objType_ = objType;
	}	
	else swap(obj, objType);
	objInHands_->onPick();
}

void Transport::drop(bool onFloor)
{
	objInHands_->onDrop(onFloor);
	objInHands_ = nullptr;
	objType_ = Resources::PickableType::none;
}

void Transport::swap(Pickable* obj, Resources::PickableType objType)
{
	objInHands_ = nullptr;
	objInHands_ = obj;
	objType_ = objType;
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
}
