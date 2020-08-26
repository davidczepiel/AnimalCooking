#include "WallAdder.h"
#include "Wall.h"
#include "CollisionsSystem.h"
#include "Manager.h"
#include "Transform.h"
#include "Door.h"
#include "SDLRenderer.h"
#include "ImageViewer.h"
#include "IngredientsPool.h"
#include "WallOpacityManager.h"

#define CASTID(t) static_cast<ecs::GroupID>(t - 1)


WallAdder::WallAdder(EntityManager* mngr,  jute::jValue& nivel, jute::jValue& general, CollisionsSystem* colSys_, 
	std::array<Entity*, 2>& players, const double casillaX, const double casillaY, const double offsetX, const double offsetY, IngredientsPool* pool)
{
	//Paredes
	vector<Data> data; 

	jute::jValue vallas = nivel["Valla"]["entities"];

	for (int i = 0; i < vallas.size(); ++i)
	{
		double posY = nivel["Valla"]["entities"][i]["posY"].as_double();
		double sizeY = nivel["Valla"]["entities"][i]["sizeY"].as_double();

		data.push_back(Data(Vector2D(8 * casillaX, posY * casillaY), //medio 1 ver
			Vector2D(64, sizeY * casillaY),
			Resources::TextureId::Valla));
	}

	data.push_back(Data(Vector2D(8 * casillaX, nivel["VallaFinal"]["posY"].as_double() * casillaY), //fin medio 1
		Vector2D(64, casillaY),
		Resources::TextureId::VallaFinal));
	data.push_back(Data(Vector2D(8 * casillaX, nivel["VallaInicio"]["posY"].as_double() * casillaY), //incio medio 2
		Vector2D(64, casillaY),
		Resources::TextureId::VallaInicio));

	data.push_back(Data(Vector2D(8 * casillaX, 6.75 * casillaY ),	//Medio 2 ver
		Vector2D(44, 0.25*casillaY),
		Resources::TextureId::Collider));
	data.push_back(Data(Vector2D(8 * casillaX + offsetX, 7 * casillaY - offsetY), //Aba hor
		Vector2D(SDLGame::instance()->getWindowWidth() - (6 * casillaX + offsetX), offsetY),
		Resources::TextureId::Collider));

	//Muros de arriba
	Data dataMuro = Data(Vector2D(8 * casillaX + offsetX - 10, 0), //Arr hor
		Vector2D(SDLGame::instance()->getWindowWidth() - (8 * casillaX + offsetX) + 10, offsetY),
		Resources::TextureId::Muro);
	Data dataParedCocina = Data(Vector2D(0, 0), //Arr izq
		Vector2D(SDLGame::instance()->getWindowWidth() - (8 * casillaX + offsetX) + 30, offsetY),
		Resources::TextureId::ParedCocina);


	
	maker(dataMuro, casillaX, casillaY, colSys_, mngr, offsetX, offsetY); //Valla arriba
	maker(dataParedCocina, casillaX, casillaY, colSys_, mngr, offsetX, offsetY, ecs::GroupID::Layer12); //Valla arriba izq 

	for (int i = 0; i < vallas.size(); i++) maker(data[i], casillaX, casillaY, colSys_, mngr, 64, 64);
	//maker(data[0], casillaX, casillaY, colSys_, mngr, 64, 64); //Valla medio 1

	for (int i = vallas.size() - 1; i < data.size(); i++)
	{
		maker(data[i], casillaX, casillaY, colSys_, mngr, 64, 64);
	}

	//maker(data[1], casillaX, casillaY, colSys_, mngr, 64, 64); //Final valla medio 1
	//maker(data[2], casillaX, casillaY, colSys_, mngr, 64, 64); //Inicio valla medio 2
	//maker(data[3], casillaX, casillaY, colSys_, mngr, 64, 64); //Valla medio 2
	//maker(data[4], casillaX, casillaY, colSys_, mngr, 64, 64); //Abajo valla*/

	//Hacer falsa valla
	Entity* valla = mngr->addEntity();
	valla->addComponent<Transform>(Vector2D(8 * casillaX , 7 * casillaY - 100),
								   Vector2D(),	1000, 100);
	valla->addComponent<ImageViewer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::VallaAbajo));
	valla->addComponent<WallOpacityManager>(pool);
	mngr->addToGroup(valla, ecs::Valla);
	
	//Suelos
	Entity* cocina = mngr->addEntity();
	cocina->addComponent<Transform>(Vector2D(0, 0), Vector2D(), 8 * casillaX + offsetX, 9 * casillaY);
	cocina->addComponent<SDLRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Suelo), Vector2D(casillaX, casillaY));
	mngr->addToGroup(cocina, ecs::GroupID::Layer1);

	Entity* campo = mngr->addEntity();
	campo->addComponent<Transform>(Vector2D(8 * casillaX + offsetX, 0), Vector2D(), SDLGame::instance()->getWindowWidth() - (6 * casillaX + offsetX), 7 * casillaY);
	campo->addComponent<SDLRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Hierba), Vector2D(casillaX, casillaY));
	mngr->addToGroup(campo, ecs::GroupID::Layer1);
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
		mngr->addToGroup(corner, CASTID(general["Shelf"]["Layer"].as_int() - 1 ));
		colSys_->addCollider(GETCMP2(corner, Transform), false);
	}

	//hacer repisas decorativas
	for (int i = 0; i < nivel["Shelfs"]["decorativeShefls"].size(); ++i) {
		Entity* shelf = mngr->addEntity();
		int t = Resources::TextureId::EncimeraVConDecoracion;
		
		Transform* tr = shelf->addComponent<Transform>(Vector2D(nivel["Shelfs"]["decorativeShefls"][i]["pos"]["x"].as_double() * casillaX,
			nivel["Shelfs"]["decorativeShefls"][i]["pos"]["y"].as_double() * casillaY), Vector2D(),
			general["Shelf"]["size"]["width"].as_double() * casillaX, general["Shelf"]["size"]["height"].as_double() * casillaY);

		tr->setHitboxSize(tr->getW(), tr->getH());

		shelf->addComponent<SDLRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(t), Vector2D(casillaX, casillaY));
		mngr->addToGroup(shelf, CASTID(general["Shelf"]["Layer"].as_int() - 1));
		//colSys_->addCollider(GETCMP2(shelf, Transform), false);
	}

	//Hacer falsa barra de entregas
	Entity* e;
	int posX = nivel["Clients"]["repisaFalsa"]["pos"]["x"].as_int();
	int posY = nivel["Clients"]["repisaFalsa"]["pos"]["y"].as_int();
	int size = general["Clients"]["repisaFalsa"]["size"]["width"].as_int();
	for (int i = 0; i < size; i++) {
		e = mngr->addEntity();
		e->addComponent<Transform>(Vector2D((posX + i) * casillaX, posY * casillaY), Vector2D(), casillaX, casillaY);
		
		if(i==0)e->addComponent<SDLRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::BarraIzda), Vector2D(casillaX, casillaY));
		else if(i == size-1)e->addComponent<SDLRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::BarraDcha), Vector2D(casillaX, casillaY));
		else e->addComponent<SDLRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::BarraCentro), Vector2D(casillaX, casillaY));
		
		mngr->addToGroup(e, CASTID(general["Shelf"]["Layer"].as_int()));
	}


	//Hacer puerta
	Door* d = new Door(Vector2D(7.55 * casillaX + offsetX / 2, nivel["Puerta"]["posY"].as_double() * casillaY), Vector2D(1 * casillaX, 1.4 * casillaY),
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::Puerta), GETCMP2(players[0], Transform), GETCMP2(players[1], Transform), mngr);
	mngr->addEntity(d);
	mngr->addToGroup(d, ecs::GroupID::Valla);

	//Hacer mantel de fondo del Score
	Entity* ScoreBackground = mngr->addEntity();
	mngr->addToGroup(ScoreBackground, CASTID(general["ScoreBackground"]["Layer"].as_int()));
	ScoreBackground->addComponent<Transform>(Vector2D(general["ScoreBackground"]["pos"]["x"].as_double() * casillaX,
		general["ScoreBackground"]["pos"]["y"].as_double() * casillaY),
		Vector2D(),
		general["ScoreBackground"]["size"]["width"].as_double() * casillaX, general["ScoreBackground"]["size"]["height"].as_double() * casillaY);
	ScoreBackground->addComponent<ImageViewer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::ScoreBackground));
}

void WallAdder::maker(const Data& d, const double casillaX, const double casillaY, CollisionsSystem* colSys_,
	EntityManager* mngr, const double offsetX, const double offsetY, ecs::GroupID id)
{
	Wall* w = new Wall(d.pos, d.size, SDLGame::instance()->getTextureMngr()->getTexture(d.t), casillaX,casillaY,offsetX,mngr);

	mngr->addEntity(w);
	mngr->addToGroup(w, id);
	colSys_->addCollider(GETCMP2(w, Transform), false);
}
