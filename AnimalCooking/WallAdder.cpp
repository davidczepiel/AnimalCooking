#include "WallAdder.h"
#include "Wall.h"
#include "CollisionsSystem.h"
#include "Manager.h"
#include "Transform.h"
#include "Door.h"
#include "SDLRenderer.h"

#define CASTID(t) static_cast<ecs::GroupID>(t - 1)


WallAdder::WallAdder(EntityManager* mngr,  jute::jValue& nivel, jute::jValue& general, CollisionsSystem* colSys_, 
	std::array<Entity*, 2>& players, const double casillaX, const double casillaY, const double offsetX, const double offsetY)
{
	//Paredes
	vector<Data> data; 
	data.push_back(Data(Vector2D(7 * casillaX, 0), //medio 1 ver
		Vector2D(offsetX, 4.25 * casillaY),
		Resources::TextureId::Suelo));
	data.push_back(Data(Vector2D(7 * casillaX, 5.75 * casillaY),	//Medio 2 ver
		Vector2D(offsetX, 1.25 * casillaY),
		Resources::TextureId::Suelo));
	data.push_back(Data(Vector2D(7 * casillaX + offsetX, 7 * casillaY - offsetY), //Aba hor
		Vector2D(SDLGame::instance()->getWindowWidth() - (6 * casillaX + offsetX), offsetY),
		Resources::TextureId::Button));
	data.push_back(Data(Vector2D(7 * casillaX + offsetX, 0), //Arr hor
		Vector2D(SDLGame::instance()->getWindowWidth() - (6 * casillaX + offsetX), offsetY),
		Resources::TextureId::Button));
	for (auto& d : data) {
		maker(d, casillaX,casillaY, colSys_, mngr, offsetX,offsetY);
	}

	//Hacer esquinas
	for (int i = 0; i < nivel["Shelfs"]["corners"].size(); ++i) {
		Entity* corner = mngr->addEntity();
		int t = Resources::TextureId::EsquinaSupDchaCopas + (2 * SDLGame::instance()->getRandGen()->nextInt(0, 3));
		if (nivel["Shelfs"]["corners"][i]["sitio"].as_string() == "izq") ++t;

		Transform* tr = corner->addComponent<Transform>(Vector2D(nivel["Shelfs"]["corners"][i]["pos"]["x"].as_double() * casillaX,
			nivel["Shelfs"]["corners"][i]["pos"]["y"].as_double() * casillaY), Vector2D(),
			general["Shelf"]["size"]["width"].as_double() * casillaX, general["Shelf"]["size"]["height"].as_double() * casillaY);

		tr->setHitboxSize(tr->getW(), tr->getH());

		corner->addComponent<SDLRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(t), Vector2D(casillaX, casillaY));
		mngr->addToGroup(corner, CASTID(general["Shelf"]["Layer"].as_int()));
		colSys_->addCollider(GETCMP2(corner, Transform), false);
	}

	//Hacer falsa barra de entregas
	Entity* e;
	int posX = nivel["Clients"]["repisaFalsa"]["pos"]["x"].as_int();
	int posY = nivel["Clients"]["repisaFalsa"]["pos"]["y"].as_int();
	int size = general["Clients"]["repisa"]["size"]["width"].as_int();
	for (int i = 0; i < size; i++) {
		e = mngr->addEntity();
		e->addComponent<Transform>(Vector2D((posX + i) * casillaX, posY * casillaY), Vector2D(), casillaX, casillaY);
		
		if(i==0)e->addComponent<SDLRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::BarraIzda), Vector2D(casillaX, casillaY));
		else if(i == size-1)e->addComponent<SDLRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::BarraDcha), Vector2D(casillaX, casillaY));
		else e->addComponent<SDLRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::BarraCentro), Vector2D(casillaX, casillaY));
		
		mngr->addToGroup(e, CASTID(general["Shelf"]["Layer"].as_int()));
	}

	//Suelos
	Entity* cocina = mngr->addEntity();
	cocina->addComponent<Transform>(Vector2D(0, 0), Vector2D(), 7 * casillaX + offsetX, 7 * casillaY);
	cocina->addComponent<SDLRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Suelo), Vector2D(casillaX, casillaY));
	mngr->addToGroup(cocina, ecs::GroupID::Layer1);

	Entity* campo = mngr->addEntity();
	campo->addComponent<Transform>(Vector2D(7 * casillaX + offsetX, 0), Vector2D(), SDLGame::instance()->getWindowWidth() - (6 * casillaX + offsetX), 7 * casillaY);
	campo->addComponent<SDLRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Hierba), Vector2D(casillaX, casillaY));
	mngr->addToGroup(campo, ecs::GroupID::Layer1);

	//Hacer puerta
	Door* d = new Door(Vector2D(6.5 * casillaX + offsetX / 2, 4.25 * casillaY), Vector2D(1 * casillaX, 1.5 * casillaY), 
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Panel), GETCMP2(players[0], Transform), GETCMP2(players[1], Transform), mngr);
	mngr->addEntity(d);
	mngr->addToGroup(d, ecs::GroupID::FoodLayer);
}

void WallAdder::maker(const Data& d, const double casillaX, const double casillaY, CollisionsSystem* colSys_, EntityManager* mngr, const double offsetX, const double offsetY)
{
	Wall* w = new Wall(d.pos, d.size, SDLGame::instance()->getTextureMngr()->getTexture(d.t), casillaX,casillaY,offsetX,mngr);

	mngr->addEntity(w);
	mngr->addToGroup(w, ecs::GroupID::FoodLayer);
	colSys_->addCollider(GETCMP2(w, Transform), false);
}
