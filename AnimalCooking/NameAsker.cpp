#include "NameAsker.h"

void NameAsker::draw()
{
	bg->render(RECT(casillaX, casillaY, 14 * casillaX, 7 * casillaY));

	Texture(SDLGame::instance()->getRenderer(), nameStream.str(),
			SDLGame::instance()->getFontMngr()->getFont(Resources::FontId::QuarkCheese70), hex2sdlcolor(
				"#FFFFFFFF")).render(RECT(
					3 * casillaX,
					casillaY * 3,
					2 * casillaX,
					casillaY),0);

}

void NameAsker::init()
{
	bg = SDLGame::instance()->getTextureMngr()->getTexture(Resources::NameAsker);
	casillaX = SDLGame::instance()->getCasillaX();
	casillaY = SDLGame::instance()->getCasillaY();
}

void NameAsker::update()
{
	SDL_Keycode keycode = ih->getLastKeyPressed();
	if (ih->isKeyDown(keycode)) {
		char key = keycode;
		if ((key >= 'a' && key <= 'z') || key==' ')
			nameStream << key;
		cout << nameStream.str() << endl;
	}
}
