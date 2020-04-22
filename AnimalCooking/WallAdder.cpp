#include "WallAdder.h"
#include "Wall.h"
#include "CollisionsSystem.h"
#include "Manager.h"
#include "Transform.h"

WallAdder::WallAdder(EntityManager* mngr, jute::jValue& nivel, jute::jValue& general, CollisionsSystem* colSys_, const double casilla, const double offset)
{
	int i = 0;
	while (i < nivel["Walls"].size()) {
		Vector2D size;
		if (nivel["Walls"][i]["size"]["width"].as_double() > 0) {
			size = Vector2D(nivel["Walls"][i]["size"]["width"].as_double() * casilla, offset);
		}
		else {
			size = Vector2D(offset, nivel["Walls"][i]["size"]["height"].as_double() * casilla);
		}	

		double rot = 0;
		if (size.getY() > size.getX()) rot = 90;

		Resources::TextureId t;
		if (nivel["Walls"][i]["texture"].as_string() == "outside") t = Resources::TextureId::Button;
		else t = Resources::TextureId::Suelo;	

		Vector2D pos;
		if (nivel["Walls"][i]["needsOffset"].as_bool()) {
			pos = Vector2D(nivel["Walls"][i]["pos"]["x"].as_double() * casilla + offset, nivel["Walls"][i]["pos"]["y"].as_double() * casilla + offset);
		}
		else {
			Vector2D(nivel["Walls"][i]["pos"]["x"].as_double() * casilla, nivel["Walls"][i]["pos"]["y"].as_double() * casilla);
		}

		Wall* w = new Wall(Vector2D(nivel["Walls"][i]["pos"]["x"].as_double() * casilla, nivel["Walls"][i]["pos"]["y"].as_double() * casilla),
			size, rot, SDLGame::instance()->getTextureMngr()->getTexture(t), casilla, mngr);

		mngr->addEntity(w);
		mngr->addToGroup(w, ecs::GroupID::FoodLayer);
		colSys_->addCollider(GETCMP2(w, Transform), false);
		++i;
	}
}
