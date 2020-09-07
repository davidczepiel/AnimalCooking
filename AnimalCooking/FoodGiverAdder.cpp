#include "FoodGiverAdder.h"
#define ADD(T) fg = makeFoodGiver<T>(type,n)
#define CASTID(t) static_cast<ecs::GroupID>(t - 1)

FoodGiverAdder::FoodGiverAdder(EntityManager* mngr, jute::jValue nivel, jute::jValue general, std::array<Entity*, 2>& player, Entity* gameManager, const double casillaX, const double casillaY)
	:mngr(mngr), nivel(nivel), general(general), casillaX(casillaX), casillaY(casillaY), players(player), gameManager(gameManager)
{
	jute::jValue ents = nivel["FoodGivers"];
	for (size_t i = 0; i < ents.size(); i++)
	{
		for (size_t n = 0; n < ents[i][1].size(); n++)
		{
			FoodGiver* fg = SwitchFG(ents[i][0].as_string(), i, n);
			for (int c = 0; c < ents[i][1]["components"].size(); ++c) {
				initializeComponent(ents[i][1]["components"][c].as_string(), fg);
			}
		}
	}
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}
FoodGiver* FoodGiverAdder::SwitchFG(const string& fgName, int type, int n) {
	FoodGiver* fg = nullptr;
	switch (str2int(fgName.c_str()))
	{
	case str2int("BreadBurger"):
		ADD(BreadBurgerGiver);
		break;
	case str2int("BreadHotDog"):
		ADD(BreadHotDogGiver);
		break;
	case str2int("Dough"):
		ADD(DoughGiver);
		break;
	case str2int("Dressing"):
		ADD(DressingGiver);
		break;
	case str2int("Rice"):
		ADD(RiceGiver);
		break;
	case str2int("Nori"):
		ADD(NoriGiver);
		break;
	default:
		break;
	}
	return fg;
}
template <typename T>
FoodGiver* FoodGiverAdder::makeFoodGiver(int type, int n)
{
	Texture* t = nullptr;

	if (nivel["FoodGivers"][type][1][n]["texture"].as_string() == "alinoIzq")t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::AceiteBordeIzq);
	else if (nivel["FoodGivers"][type][1][n]["texture"].as_string() == "alinoDer")t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::AceiteBordeDer);
	else if (nivel["FoodGivers"][type][1][n]["texture"].as_string() == "alino")t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Aceite);
	else if (nivel["FoodGivers"][type][1][n]["texture"].as_string() == "alinoVertical")t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::AceiteVertical);
	else if (nivel["FoodGivers"][type][1][n]["texture"].as_string() == "alinoVerSinIzq")t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::AceiteVerSinIzq);
	else if (nivel["FoodGivers"][type][1][n]["texture"].as_string() == "alinoVerSinDer")t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::AceiteVerSinDer);
	else if (nivel["FoodGivers"][type][1][n]["texture"].as_string() == "alinoSin")t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::AceiteSin);
	else if (nivel["FoodGivers"][type][1][n]["texture"].as_string() == "aceiteVerticalBordeSup")t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::AceiteVerticalBordeSup);
	else if(nivel["FoodGivers"][type][1][n]["texture"].as_string() == "arroz" ) t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Arroz);
	else if (nivel["FoodGivers"][type][1][n]["texture"].as_string() == "arrozBordeSup") t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::ArrozBordeSup);
	else if (nivel["FoodGivers"][type][1][n]["texture"].as_string() == "arrozSinBordeDer") t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::ArrozSinBordeDer);
	else if (nivel["FoodGivers"][type][1][n]["texture"].as_string() == "ArrozHor") t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::ArrozHor);
	else if (nivel["FoodGivers"][type][1][n]["texture"].as_string() == "ArroceraAislada") t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::ArroceraAislada);
	else if (nivel["FoodGivers"][type][1][n]["texture"].as_string() == "panera" ) t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Panera);
	else if (nivel["FoodGivers"][type][1][n]["texture"].as_string() == "paneraVerSinDer") t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::PaneraVerSinDer);
	else if (nivel["FoodGivers"][type][1][n]["texture"].as_string() == "paneraVer") t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::PaneraVer);
	else if (nivel["FoodGivers"][type][1][n]["texture"].as_string() == "paneraBordeDer") t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::PaneraBordeDer);
	else if (nivel["FoodGivers"][type][1][n]["texture"].as_string() == "encimeraMasa") t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::EncimeraMasa);
	else if (nivel["FoodGivers"][type][1][n]["texture"].as_string() == "algas") t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::NoriFoodGiver);
	else if(nivel["FoodGivers"][type][1][n]["texture"].as_string() == "algasVDcha") t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::algasVDcha);

	FoodGiver* fg = new T(Vector2D(nivel["FoodGivers"][type][1][n]["pos"]["x"].as_double() * casillaX, nivel["FoodGivers"][type][1][n]["pos"]["y"].as_double() * casillaY),
		Vector2D(general["Givers"]["size"]["width"].as_double() * casillaX, general["Givers"]["size"]["height"].as_double() * casillaY),
		GETCMP2(players[0], Transport), GETCMP2(players[1], Transport), GETCMP2(gameManager, GameControl),t);

	fg->setHitboxSize(Vector2D(fg->getSize().getX(), fg->getSize().getY()));

	fg->addComponent<FoodGiverViewer>(fg);
	fg->addComponent<SelectorPopUpEntity>(GETCMP2(players[0], InteractionRect), GETCMP2(players[1], InteractionRect),
		GETCMP2(players[0], Selector), GETCMP2(players[1], Selector), fg);

	mngr->addEntity(fg);
	mngr->addToGroup(fg, CASTID(general["Givers"]["Layer"].as_int()));
	interactives_.push_back(fg);
	return fg;
}
//La cadena (component) no puede superar 10 caracteres
void FoodGiverAdder::initializeComponent(const string& component, Entity* entity)
{
	switch (str2int(component.c_str()))
	{
	case str2int("AdvEffect"):
		break;
	default:
		break;
	}
}