#include "NameAsker.h"

NameAsker::NameAsker() : Component(ecs::NameAsker), active(true), bg(nullptr), casillaX(0), casillaY(0), nameStream(" ") {
	ih = SDLGame::instance()->getInputHandler();
}

void NameAsker::draw()
{
	if (active) {
		bg->render(RECT(casillaX, casillaY, 14 * casillaX, 7 * casillaY));
		/////////////////////////////////////////////////////////////////////////////////////////////
		///   Si queremos cambiar el tamaño de la fuente hay que hacerlo también en gameConfig    ///
		/////////////////////////////////////////////////////////////////////////////////////////////
		Texture t(SDLGame::instance()->getRenderer(), nameStream.str(),
			SDLGame::instance()->getFontMngr()->getFont(Resources::FontId::QuarkCheese70), hex2sdlcolor(
				"#000000FF"));
		t.render(RECT(
			8 * casillaX - t.getWidth()/2,
			4.4 * casillaY,
			t.getWidth(),
			t.getHeight()), 0);
	}
}

void NameAsker::init()
{
	bg = SDLGame::instance()->getTextureMngr()->getTexture(Resources::NameAsker);
	casillaX = SDLGame::instance()->getCasillaX();
	casillaY = SDLGame::instance()->getCasillaY();
}

void NameAsker::update()
{
	if (active) {
		SDL_Keycode keycode = ih->getLastKeyPressed();
		if (ih->isKeyDown(keycode)) {
			char key = keycode;
			if (((key >= 'a' && key <= 'z') || key == ' ') && nameStream.str().size() < game_->getWindowWidth() / (config::FONT_SIZE / 2))
				nameStream << key;
			else if (keycode == SDLK_BACKSPACE) {
				if (nameStream.str().size() > 1) {
					string aux = nameStream.str();
					aux.pop_back();
					nameStream.str(aux);
					nameStream.seekp(0, nameStream.end);
				}
				else nameStream.str(" ");
			}
			else if (keycode == SDLK_RETURN && nameStream.str().size() > 1)
			{
				MapState* mapState = static_cast<MapState*>(game_->getFSM()->currentState());
				active = false;
				mapState->setName(nameStream.str());
				mapState->setState();
			}
		}
	}
}

void NameAsker::setActive(bool a)
{
	active = a;
	if (active) {
		nameStream.clear();
		nameStream.str(" ");
	}
}
