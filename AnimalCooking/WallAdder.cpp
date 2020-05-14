#include "WallAdder.h"
#include "Wall.h"
#include "CollisionsSystem.h"
#include "Manager.h"
#include "Transform.h"
#include "Door.h"
#include "SDLRenderer.h"
#include "ImageViewer.h"

#define CASTID(t) static_cast<ecs::GroupID>(t - 1)


WallAdder::WallAdder(EntityManager* mngr,  jute::jValue& nivel, jute::jValue& general, CollisionsSystem* colSys_, 
	std::array<Entity*, 2>& players, const double casilla, const double offset)
{
	//Paredes

	vector<Data> data; 
	data.push_back(Data(Vector2D(8 * casilla, 0), //medio 1 ver
		Vector2D(64, 3.75 * casilla),
		Resources::TextureId::Valla));
	data.push_back(Data(Vector2D(8 * casilla, 3.75*casilla), //fin medio 1
		Vector2D(64, casilla),
		Resources::TextureId::VallaFinal));
	data.push_back(Data(Vector2D(8 * casilla, 5.75 * casilla), //incio medio 2
		Vector2D(64, casilla),
		Resources::TextureId::VallaInicio));
	data.push_back(Data(Vector2D(8 * casilla, 6.75 * casilla ),	//Medio 2 ver
		Vector2D(44, 0.25*casilla),
		Resources::TextureId::Collider));
	data.push_back(Data(Vector2D(8 * casilla + offset, 7 * casilla - offset), //Aba hor
		Vector2D(SDLGame::instance()->getWindowWidth() - (6 * casilla + offset), offset),
		Resources::TextureId::Collider));
	data.push_back(Data(Vector2D(8 * casilla + offset -10 ,0), //Arr hor
		Vector2D(SDLGame::instance()->getWindowWidth() - (8 * casilla + offset) + 10, offset),
		Resources::TextureId::Muro));

	
	maker(data[5], casilla, colSys_, mngr, offset); //Valla arriba
	maker(data[0], casilla, colSys_, mngr, 64); //Valla medio 1
	maker(data[1], casilla, colSys_, mngr, 64); //Final valla medio 1
	maker(data[2], casilla, colSys_, mngr, 64); //Inicio valla medio 2
	maker(data[3], casilla, colSys_, mngr, 64); //Valla medio 2
	maker(data[4], casilla, colSys_, mngr, 64); //Abajo valla*/

	//Hacer falsa valla
	Entity* valla = mngr->addEntity();
	valla->addComponent<Transform>(Vector2D(8 * casilla , 7 * casilla - 100),
								   Vector2D(),	1000, 100);
	valla->addComponent<ImageViewer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::VallaAbajo));
	mngr->addToGroup(valla, ecs::Valla);

	//Hacer esquinas
	for (int i = 0; i < nivel["Shelfs"]["corners"].size(); ++i) {
		Entity* corner = mngr->addEntity();
		int t = Resources::TextureId::EsquinaSupDchaCopas + (2 * SDLGame::instance()->getRandGen()->nextInt(0, 3));
		if (nivel["Shelfs"]["corners"][i]["sitio"].as_string() == "izq") ++t;

		Transform* tr = corner->addComponent<Transform>(Vector2D(nivel["Shelfs"]["corners"][i]["pos"]["x"].as_double() * casilla,
			nivel["Shelfs"]["corners"][i]["pos"]["y"].as_double() * casilla), Vector2D(),
			general["Shelf"]["size"]["width"].as_double() * casilla, general["Shelf"]["size"]["height"].as_double() * casilla);

		tr->setHitboxSize(tr->getW(), tr->getH());

		corner->addComponent<SDLRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(t), Vector2D(casilla, casilla));
		mngr->addToGroup(corner, CASTID(general["Shelf"]["Layer"].as_int()));
		colSys_->addCollider(GETCMP2(corner, Transform), false);
	}

	//Hacer falsa barra de entregas
	Entity* e;
	int posX = nivel["Clients"]["repisaFalsa"]["pos"]["x"].as_int();
	int posY = nivel["Clients"]["repisaFalsa"]["pos"]["y"].as_int();
	int size = general["Clients"]["repisaFalsa"]["size"]["width"].as_int();
	for (int i = 0; i < size; i++) {
		e = mngr->addEntity();
		e->addComponent<Transform>(Vector2D((posX + i) * casilla, posY * casilla), Vector2D(), casilla, casilla);
		
		if(i==0)e->addComponent<SDLRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::BarraIzda), Vector2D(casilla, casilla));
		else if(i == size-1)e->addComponent<SDLRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::BarraDcha), Vector2D(casilla, casilla));
		else e->addComponent<SDLRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::BarraCentro), Vector2D(casilla, casilla));
		
		mngr->addToGroup(e, CASTID(general["Shelf"]["Layer"].as_int()));
	}

	//Suelos
	Entity* cocina = mngr->addEntity();
	cocina->addComponent<Transform>(Vector2D(0, 0), Vector2D(), 8 * casilla + offset, 7 * casilla);
	cocina->addComponent<SDLRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Suelo), Vector2D(casilla, casilla));
	mngr->addToGroup(cocina, ecs::GroupID::Layer1);

	Entity* campo = mngr->addEntity();
	campo->addComponent<Transform>(Vector2D(8 * casilla + offset, 0), Vector2D(), SDLGame::instance()->getWindowWidth() - (6 * casilla + offset), 7 * casilla);
	campo->addComponent<SDLRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Hierba), Vector2D(casilla, casilla));
	mngr->addToGroup(campo, ecs::GroupID::Layer1);

	//Hacer puerta
	Door* d = new Door(Vector2D(7.55 * casilla + offset / 2, 4.37 * casilla), Vector2D(1 * casilla, 1.4 * casilla), 
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::Puerta), GETCMP2(players[0], Transform), GETCMP2(players[1], Transform), mngr);
	mngr->addEntity(d);
	mngr->addToGroup(d, ecs::GroupID::FeedBackLayer);

	//Hacer mantel de fondo del Score
	Entity* ScoreBackground = mngr->addEntity();
	mngr->addToGroup(ScoreBackground, CASTID(general["ScoreBackground"]["Layer"].as_int()));
	ScoreBackground->addComponent<Transform>(Vector2D(general["ScoreBackground"]["pos"]["x"].as_double() * casilla,
		general["ScoreBackground"]["pos"]["y"].as_double() * casilla),
		Vector2D(),
		general["ScoreBackground"]["size"]["width"].as_double() * casilla, general["ScoreBackground"]["size"]["height"].as_double() * casilla);
	ScoreBackground->addComponent<ImageViewer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::ScoreBackground));
}

void WallAdder::maker(const Data& d, const double casilla, CollisionsSystem* colSys_, EntityManager* mngr, const double offset)
{
	Wall* w = new Wall(d.pos, d.size, SDLGame::instance()->getTextureMngr()->getTexture(d.t), casilla, offset, mngr);

	mngr->addEntity(w);
	mngr->addToGroup(w, ecs::GroupID::Layer2);
	colSys_->addCollider(GETCMP2(w, Transform), false);
}
