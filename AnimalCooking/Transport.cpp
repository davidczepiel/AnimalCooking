#include "Transport.h"
#include "Entity.h"
#include "Dish.h"

Transport::Transport(InteractionRect* ir) : Component(ecs::Transport),
objInHands_(nullptr),
playerTransform_(nullptr),
interactionPlayerRect(ir),
objType_(objType_ = Resources::PickableType::none), dir(Vector2D())
{
}

void Transport::pick(Pickable* obj, Resources::PickableType objType, bool inFloor)
{
	if (objInHands_ == nullptr) {
		objInHands_ = obj;
		objType_ = objType;
	}
	else swap(obj, objType, inFloor);
	if (objInHands_ != nullptr)
		objInHands_->onPick();
}

void Transport::drop(bool onFloor)
{
	if (onFloor)
		objInHands_->setCanInteract(true);
	objInHands_->onDrop(onFloor);
	objInHands_ = nullptr;
	objType_ = Resources::PickableType::none;
}

void Transport::swap(Pickable* obj, Resources::PickableType objType, bool inFloor)
{
	if (objType_ != Resources::PickableType::Dish) {
		objInHands_->onDrop(inFloor);
		objInHands_ = nullptr;
		objInHands_ = obj;
		objType_ = objType;

	}
}

void Transport::init()
{
	playerTransform_ = GETCMP1_(Transform);
}

void Transport::update()
{
	if (objInHands_ != nullptr) {
		float angle;
		if (!(playerTransform_->getVel().getX() == 0 && playerTransform_->getVel().getY() == 0)) {
			angle = -((atan2(playerTransform_->getVel().getY(), playerTransform_->getVel().getX()) * 180) / M_PI);
		}
		else {
			Vector2D playerMid(playerTransform_->getPos().getX() + playerTransform_->getW() / 2, playerTransform_->getPos().getY() + playerTransform_->getH() / 2);
			Vector2D interactionMid(interactionPlayerRect->getPos().getX() + interactionPlayerRect->getW() / 2, interactionPlayerRect->getPos().getY() + interactionPlayerRect->getH() / 2);
			Vector2D dir = (interactionMid - playerMid).normalize();
			angle = -((atan2(dir.getY(), dir.getX()) * 180) / M_PI);
		}
		int centerX = playerTransform_->getPos().getX() + playerTransform_->getW() / 2;
		int centerY = playerTransform_->getPos().getY() + playerTransform_->getH() / 2;

		Vector2D objPos = Vector2D();
		double offsetX = playerTransform_->getW() / 2;
		double offsetY = playerTransform_->getH() / 2;

		Vector2D objOffset = objInHands_->getSize() / 2;

		if ((angle > (-22.5) && angle <= 22.5)) { //Derecha
			if (objType_ == Resources::PickableType::Dish) objPos = Vector2D(centerX + offsetX / 3, centerY + offsetY / 2 + offsetY / 4);
			else objPos = Vector2D(centerX + offsetX / 2, centerY + offsetY / 2);
		}
		else if ((angle > 22.5 && angle <= 67.5)) { //Arriba a la derecha
			objPos = Vector2D(centerX + offsetX / 2, centerY);
		}
		else if ((angle > 67.5 && angle <= 112.5)) { //Arriba
			objPos = Vector2D(centerX, centerY);
		}
		else if ((angle > 112.5 && angle <= 157.5)) { //Arriba a la izquierda
			objPos = Vector2D(centerX - offsetX / 2, centerY);
		}
		else if ((angle > 157.5 || angle <= (-157.5))) { //izquierda
			if (objType_ == Resources::PickableType::Dish)  objPos = Vector2D(centerX - offsetX / 3, centerY + offsetY / 2 + offsetY / 4);
			else objPos = Vector2D(centerX - offsetX / 2, centerY + offsetY / 2);
		}
		else if ((angle > (-157.5) && angle <= (-112.5))) { //Abajo a la izquierda
			if (objType_ == Resources::PickableType::Dish) objPos = Vector2D(centerX - offsetX / 2, centerY + offsetY);
			else objPos = Vector2D(centerX - offsetX / 2, centerY + offsetY / 2 + objOffset.getY() / 2);
		}
		else if ((angle > (-112.5) && angle <= (-67.5))) { //Abajo

			if (objType_ == Resources::PickableType::Dish) objPos = Vector2D(centerX + offsetX / 4, centerY + offsetY);
			else objPos = Vector2D(centerX + offsetX / 4, centerY + (offsetY - objOffset.getY()));
		}
		else if ((angle > (-67.5) && angle <= (-22.5))) { //abajo a la derecha
			if (objType_ == Resources::PickableType::Dish)  objPos = Vector2D(centerX + offsetX / 2, centerY + offsetY);
			else objPos = Vector2D(centerX + offsetX / 2, centerY + offsetY / 2 + objOffset.getY() / 2);
		}

		objInHands_->setPos(objPos - objOffset);
	}
}
