#include "EnviromentAdder.h"
#include "Transform.h"

EnviromentAdder::EnviromentAdder(jute::jValue& nivel, EntityManager* mngr, std::array<Entity*, 2>& players ,const double casillaX, const double casillaY)
{
	Entity* enviromentManager = mngr->addEntity();
	EnviromentPool* envP =enviromentManager->addComponent<EnviromentPool>(GETCMP2(players.at(0),Transform), GETCMP2(players.at(1), Transform), GETCMP2(players.at(0), PlayerController), GETCMP2(players.at(1), PlayerController));
	enviromentManager->addComponent<EnviromentViewer>(envP);
	//vector<tuple<ecs::AdversityID, int>> adversitiesList;

	for (int i = 0; i < nivel["Enviroment"].size(); ++i) {

		Vector2D pos =Vector2D( nivel["Enviroment"][i]["pos"]["x"].as_int()*casillaX, nivel["Enviroment"][i]["pos"]["y"].as_int() * casillaY);

		if (nivel["Enviroment"][i]["Tipo"].as_string() == "Slow") {
			envP->addEnvUnit(pos,100,100,"Slow");
		}

		if (nivel["Enviroment"][i]["Tipo"].as_string() == "Resbalar") {
			envP->addEnvUnit(pos, 100, 100, "Resbalar");
		}

	}

		mngr->addToGroup(enviromentManager, ecs::GroupID::Layer12);
}
