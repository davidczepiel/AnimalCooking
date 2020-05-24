#include "NameAsker.h"

NameAsker::NameAsker() : Component(ecs::NameAsker), active(true), bg(nullptr), casillaX(0), casillaY(0), nameStream(" "), nameWidth_() {
	ih = SDLGame::instance()->getInputHandler();
}

void NameAsker::draw()
{
	if (active) {
		bg->render(RECT(0, 0, game_->getWindowWidth(), game_->getWindowHeight()));
		/////////////////////////////////////////////////////////////////////////////////////////////
		///   Si queremos cambiar el tamaño de la fuente hay que hacerlo también en gameConfig    ///
		/////////////////////////////////////////////////////////////////////////////////////////////
		Texture t(game_->getRenderer(), nameStream.str(),
			game_->getFontMngr()->getFont(Resources::FontId::QuarkCheese100), hex2sdlcolor(
				"#000000FF"));
		t.render(RECT(
			8 * casillaX - t.getWidth()/2,
			4.4 * casillaY,
			t.getWidth(),
			t.getHeight()), 0);
		nameWidth_ = t.getWidth();
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
			if (((key >= 'a' && key <= 'z') || key == ' ') && 3 * casillaX > nameWidth_)
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
