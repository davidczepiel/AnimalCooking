#include "WallAdder.h"
#include "Wall.h"
#include "CollisionsSystem.h"
#include "Manager.h"
#include "Transform.h"

WallAdder::WallAdder(EntityManager* mngr, jute::jValue& nivel, jute::jValue& general, CollisionsSystem* colSys_, const double casilla, const double offset)
{
	vector<Data> data; 
	data.push_back(Data(Vector2D(), //Izq Arr hor
		Vector2D(6 * casilla + offset, offset),		
		Resources::TextureId::Suelo));  

	data.push_back(Data(Vector2D(0, offset), //Izq Arr ver
		Vector2D(offset, 7 * casilla),
		Resources::TextureId::Suelo));

	data.push_back(Data(Vector2D(6 * casilla + offset, 0), //medio 1 ver
		Vector2D(offset, 3.5 * casilla + offset),
		Resources::TextureId::Suelo));

	data.push_back(Data(Vector2D(6 * casilla + offset, 5.5 * casilla + offset),	//Medio 2 ver
		Vector2D(offset, 1.5 * casilla),
		Resources::TextureId::Suelo));

	data.push_back(Data(Vector2D(6 * casilla + offset, 7 * casilla), //Aba hor
		Vector2D(10 * casilla, offset),
		Resources::TextureId::Button));

	data.push_back(Data(Vector2D(6 * casilla + 2 * offset, 0), //Arr hor
		Vector2D(10 * casilla, offset),
		Resources::TextureId::Button));

	data.push_back(Data(Vector2D(SDLGame::instance()->getWindowWidth() - offset, 0), //Der arr ver
		Vector2D(offset, 1 * casilla + offset),
		Resources::TextureId::Button));

	data.push_back(Data(Vector2D(SDLGame::instance()->getWindowWidth() - offset, 2 * casilla + offset), //Der medio 1 ver
		Vector2D(offset, 1 * casilla),
		Resources::TextureId::Button));

	data.push_back(Data(Vector2D(SDLGame::instance()->getWindowWidth() - offset, 4 * casilla + offset), //Der medio 2 ver
		Vector2D(offset, 1 * casilla + offset),
		Resources::TextureId::Button));

	data.push_back(Data(Vector2D(SDLGame::instance()->getWindowWidth() - offset, 6 * casilla + offset), //Der medio 2 ver
		Vector2D(offset, 1 * casilla ),
		Resources::TextureId::Button));

	for (auto& d : data) {
		maker(d, casilla, colSys_, mngr);
	}
}

void WallAdder::maker(const Data& d, const double casilla, CollisionsSystem* colSys_,  EntityManager* mngr)
{
	double rot = 90;
	if (d.size.getY() > d.size.getX()) rot = 0;
	Wall* w = new Wall(d.pos, d.size, rot, SDLGame::instance()->getTextureMngr()->getTexture(d.t), casilla, mngr);

	mngr->addEntity(w);
	mngr->addToGroup(w, ecs::GroupID::FoodLayer);
	colSys_->addCollider(GETCMP2(w, Transform), false);
}
