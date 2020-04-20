#include "OrderViewer.h"
#include "SDL_macros.h"
#include "Entity.h"

OrderViewer::OrderViewer() : OrderViewer(80, 50, {5, 5})
{
}

OrderViewer::OrderViewer(size_t width, size_t height, Vector2D margin) : Component(ecs::OrderViewer),
		width_(width), height_(height), margin_(margin)
{
}

void OrderViewer::init()
{
	om_ = GETCMP1_(OrderManager);
	backGroundTexture_ = game_->getTextureMngr()->getTexture(Resources::TextureId::Bocadillo);
}

void OrderViewer::draw()
{
	for (auto o : om_->getOrders()) {
		if (o != nullptr) { //Si esta el pedido
			Texture* orText = o->getOrderText();
		
			double anger = o->getAnger() - 0.25;
			if (anger < 0) anger = 0;
			else if (anger > 0.5) anger = 0.5; //Maximo anger de 0.5
			
			//// Fondo
			//backGroundTexture_->render(RECT(o->getPos().getX(), o->getPos().getY(), width_, height_)/*,  //Usa getAnger() para determinar que zona usar de la textura
			//						   RECT(anger * (backGroundTexture_->getWidth() / 5), 0, backGroundTexture_->getWidth() / 5, backGroundTexture_->getHeight())*/);

			backGroundTexture_->renderWithTint(RECT(o->getPos().getX(), o->getPos().getY(), width_, height_), 255, (1 - anger) * 255, (1 - anger) * 255);

			// El pedido final
			orText->render(RECT(o->getPos().getX() + margin_.getX(), o->getPos().getY() + margin_.getY(), width_ - margin_.getX() * 2, height_ - margin_.getY() * 2));
		}
	}
}
