#include "OrderServiceViewer.h"

void OrderServiceViewer::init()
{
	textLeft = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BarraConTimbre);
	textMid = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BarraSinTimbre);
	textRight = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BarraSinTimbre);
	position = RECT(entity->getPos().getX(), entity->getPos().getY(), entity->getSize().getX(), entity->getSize().getY());
}

void OrderServiceViewer::draw()
{
	SDL_Rect dest = position;
	dest.w = 160;
	dest.h = 128;
	textLeft->render(dest);

	//Medio
	int actualPos = 160;
	int resto = position.w-dest.w - actualPos;
	while (resto>=160) {
		dest.x = actualPos;
		textMid->render(dest);
		actualPos += 160;
		resto = position.w-dest.w - actualPos;
	}
	//Hay que dibujar un poco de relleno para que el ultimo cuadrado no este separado de los del centro
	if (resto>0 && resto <dest.w) {
		dest.w = resto;
		textMid->render(dest);
		actualPos = dest.x + dest.w;
		dest.w = 160;
	}
	//Final
	dest.x = actualPos;
	textRight->render(dest);


}
