#include "BinEntity.h"

void BinEntity::action1(int player)
{
	Transport* playerTransport;

	player == Resources::Player1 ? playerTransport = player1_ : playerTransport = player2_;	//Se asigna el player correspondiente

	if (playerTransport->getObjectInHands() != nullptr && playerTransport->getObjectTypeInHands() == Resources::Dish) {
		//Limpiar el plato

		for (auto& i : static_cast<Dish*>(playerTransport->getObjectInHands())->getFoodVector()) {
			i->Destroy();
		}
		static_cast<Dish*>(playerTransport->getObjectInHands())->getFoodVector().clear();
		SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Bin,0);
	}

	playerTransport = nullptr;
}

void BinEntity::feedback(int player)
{
	SDL_Rect rect;
	rect.x = position_.getX(); rect.y = position_.getY(); rect.w = size_.getX(); rect.h = size_.getY();

	feedbackVisual_->render(rect);
}
