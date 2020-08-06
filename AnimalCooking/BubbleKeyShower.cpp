#include "BubbleKeyShower.h"
#include "SDLGame.h"
#include "SDL_macros.h"


BubbleKeyShower::BubbleKeyShower(SDLGame* game)
{
	fillMap(game);
}

void BubbleKeyShower::renderFeedBack(const Vector2D& position, const string& msg, const string& key, const bool& gPadKey)
{
	if (gPadKey) { //Hay que usar una imagen
		renderFeedBackImage(position, msg, key);
	}
	else { //Hay que usar texto
		renderFeedBackText(position, msg, key);
	}
}

void BubbleKeyShower::fillMap(SDLGame* game)
{
	//TODO: poner las texturas

	keyToTexture_.insert({ //Map con todos los nombres asociados a cada textura
		{ "a", game->getTextureMngr()->getTexture(Resources::TextureId::HomeIconMapState) }, { "b", game->getTextureMngr()->getTexture(Resources::TextureId::HomeIconMapState) }, 
		{ "x", game->getTextureMngr()->getTexture(Resources::TextureId::HomeIconMapState) }, { "y", game->getTextureMngr()->getTexture(Resources::TextureId::HomeIconMapState) },
		{ "start", game->getTextureMngr()->getTexture(Resources::TextureId::HomeIconMapState) }, { "back", game->getTextureMngr()->getTexture(Resources::TextureId::HomeIconMapState) },
		{ "rightstick", game->getTextureMngr()->getTexture(Resources::TextureId::HomeIconMapState) }, { "leftstick", game->getTextureMngr()->getTexture(Resources::TextureId::HomeIconMapState) },
		{ "leftshoulder", game->getTextureMngr()->getTexture(Resources::TextureId::HomeIconMapState) }, { "rightshoulder", game->getTextureMngr()->getTexture(Resources::TextureId::HomeIconMapState) },
		{ "dpup", game->getTextureMngr()->getTexture(Resources::TextureId::HomeIconMapState) }, { "dpdown", game->getTextureMngr()->getTexture(Resources::TextureId::HomeIconMapState) },
		{ "dpleft", game->getTextureMngr()->getTexture(Resources::TextureId::HomeIconMapState) }, { "dpright", game->getTextureMngr()->getTexture(Resources::TextureId::HomeIconMapState) },
		});

}

void BubbleKeyShower::renderFeedBackText(const Vector2D& position, const string& msg, const string& key)
{
	Texture name = Texture(SDLGame::instance()->getRenderer(), msg + " ",
		SDLGame::instance()->getFontMngr()->getFont(Resources::FontId::QuarkCheese50), { COLOR(0x000000ff) });

	Resources::FontId fuente = Resources::FontId::QuarkCheese50;
	//if (key.length() == 1) fuente = Resources::FontId::ARIAL50;

	Texture keyText = Texture(SDLGame::instance()->getRenderer(), key,
		SDLGame::instance()->getFontMngr()->getFont(fuente), { COLOR(0x000000ff) });

	//Ancho | alto del fondo
	int repeticiones;
	double height = 1;
	if (key.length() > 3) {
		const string& s = (msg.length() < key.length()) ? msg : key;
		repeticiones = s.length() / 3;
		height = 2;
	}
	else repeticiones = (msg.length() + key.length()) / 4;

	Vector2D pos = Vector2D(position.getX() + 50, position.getY() + height * 25);

	//FONDO
	Texture* borde = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BordeTeclaFeedBack);
	Texture* relleno = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::RellenoTeclaFeedBack);
	borde->render(RECT(pos.getX(), pos.getY(), borde->getWidth(), borde->getHeight() * height));
	pos.setX(pos.getX() + borde->getWidth());
	double startingPosRelleno = pos.getX();
	double lengthRelleno = 0;
	for (int i = 0; i < repeticiones; ++i) {
		relleno->render(RECT(pos.getX(), pos.getY(), relleno->getWidth(), relleno->getHeight() * height));
		pos.setX(pos.getX() + relleno->getWidth());
		lengthRelleno = pos.getX() - startingPosRelleno;
	}
	borde->render(RECT(pos.getX(), pos.getY(), borde->getWidth(), borde->getHeight() * height), 0.0,
		RECT(0, 0, borde->getWidth(), borde->getHeight()), SDL_FLIP_HORIZONTAL);

	SDL_Rect nameRect, keyRect;
	if (height == 1) { //En una fila
		nameRect = RECT(startingPosRelleno + lengthRelleno / 2 - (name.getWidth() + keyText.getWidth()) / 2,
			pos.getY() + borde->getHeight() / 2 - name.getHeight() / 2,
			name.getWidth() * name.getHeight() / double(name.getHeight()), name.getHeight());
		keyRect = RECT(startingPosRelleno + lengthRelleno / 2 - (name.getWidth() + keyText.getWidth()) / 2 + name.getWidth(),
			pos.getY() + borde->getHeight() / 2 - name.getHeight() / 2,
			keyText.getWidth() * keyText.getHeight() / double(name.getHeight()), name.getHeight());
	}
	else { //En dos filas
		double textHeight = 0.8 * name.getHeight() + 0.8 * keyText.getHeight();
		nameRect = RECT(startingPosRelleno + lengthRelleno / 2 - (name.getWidth() / 2),
			pos.getY() + borde->getHeight() * height / 2 - textHeight / 2,
			name.getWidth() * 0.8 * name.getHeight() / double(0.8 * name.getHeight()), 0.8 * name.getHeight());
		keyRect = RECT(startingPosRelleno + lengthRelleno / 2 - (keyText.getWidth() / 2),
			pos.getY() + borde->getHeight() * height / 2 - textHeight / 2 + 0.9 * name.getHeight(),
			keyText.getWidth() * 0.8 * keyText.getHeight() / double(0.8 * keyText.getHeight()), 0.8 * keyText.getHeight());
	}
	name.render(nameRect);
	keyText.render(keyRect);
}

void BubbleKeyShower::renderFeedBackImage(const Vector2D& position, const string& msg, const string& key)
{
	auto itFind = keyToTexture_.find(key);

	if (itFind == keyToTexture_.end() || itFind->second == nullptr) { //Si no hay una imagen que corresponda, renderizo su nombre
		renderFeedBackText(position, msg, key);
		return;
	}

	Texture* keyText = itFind->second;

	Texture name = Texture(SDLGame::instance()->getRenderer(), msg + "  ",
		SDLGame::instance()->getFontMngr()->getFont(Resources::FontId::QuarkCheese50), { COLOR(0x000000ff) });

	Resources::FontId fuente = Resources::FontId::QuarkCheese50;
	//if (key.length() == 1) fuente = Resources::FontId::ARIAL50;

	//Ancho | alto del fondo
	int repeticiones = 2;
	double height = 1;

	Vector2D pos = Vector2D(position.getX() + 50, position.getY() + height * 25);

	//FONDO
	Texture* borde = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BordeTeclaFeedBack);
	Texture* relleno = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::RellenoTeclaFeedBack);
	borde->render(RECT(pos.getX(), pos.getY(), borde->getWidth(), borde->getHeight() * height));
	pos.setX(pos.getX() + borde->getWidth());
	double startingPosRelleno = pos.getX();
	double lengthRelleno = 0;
	for (int i = 0; i < repeticiones; ++i) {
		relleno->render(RECT(pos.getX(), pos.getY(), relleno->getWidth(), relleno->getHeight() * height));
		pos.setX(pos.getX() + relleno->getWidth());
		lengthRelleno = pos.getX() - startingPosRelleno;
	}
	borde->render(RECT(pos.getX(), pos.getY(), borde->getWidth(), borde->getHeight() * height), 0.0,
		RECT(0, 0, borde->getWidth(), borde->getHeight()), SDL_FLIP_HORIZONTAL);

	SDL_Rect nameRect, keyRect;

	nameRect = RECT(startingPosRelleno + lengthRelleno / 2 - (name.getWidth() + 32) / 2,
		pos.getY() + borde->getHeight() / 2 - name.getHeight() / 2,
		name.getWidth() * name.getHeight() / double(name.getHeight()), name.getHeight());
	keyRect = RECT(startingPosRelleno + lengthRelleno / 2 - (name.getWidth() + 32) / 2 + name.getWidth(),
		pos.getY() + borde->getHeight() / 2 - 16,
		32, 32);


	name.render(nameRect);
	keyText->render(keyRect);
}

