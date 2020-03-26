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
	backGroundTexture_ = game_->getTextureMngr()->getTexture(Resources::TextureId::Pedido);
}

void OrderViewer::draw()
{
	for (auto o : om_->getOrders()) {
		if (o != nullptr) { //Si esta el pedido
			vector<Texture*> ings = o->getIngsText();
			Texture* orText = o->getOrderText();
		
			double anger = o->getAnger();
			if (anger > 0.8) anger = 0.8; //Maximo anger de 0.8 

			// Fondo
			backGroundTexture_->render(RECT(o->getPos().getX(), o->getPos().getY(), width_, height_),  //Usa getAnger() para determinar que zona usar de la textura
									   RECT(anger * (backGroundTexture_->getWidth() / 5), 0, backGroundTexture_->getWidth() / 5, backGroundTexture_->getHeight()));

			// Las texturas de en medio
			int ingWidth = width_ - 2 * margin_.getX();
			int ingHeight = height_ - (2 * margin_.getY()) / (ings.size() + 1); //ingHeight justo para que quepan todos los ings y dejen un margen en Y por ambos lados
			size_t i = 0;
			for (auto t : ings) {
				t->render(RECT(o->getPos().getX() + margin_.getX(), o->getPos().getY() + margin_.getY() + ingHeight * i, ingWidth, ingHeight));
				++i;
			}

			// El pedido final
			orText->render(RECT(o->getPos().getX() + margin_.getX(), o->getPos().getY() + height_ - ingHeight - margin_.getY(), ingWidth, ingHeight));
		}
	}
}
