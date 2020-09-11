#include "AdversityAdder.h"
#include "MultipleAdversityManager.h"

AdversityAdder::AdversityAdder(jute::jValue& nivel, EntityManager* mngr, std::array<Entity*, 2>& players, 
	Entity* cookersPool, Entity* ingredientsPool, Entity* utensilsPool, Entity* firesPool, GhostPool* ghostPool, GameLogic* gl)
{
	Entity* adversityManager = mngr->addEntity();
	MultipleAdversityManager* mam = adversityManager->addComponent<MultipleAdversityManager>(
		GETCMP2(players[0], Transform), 
		GETCMP2(players[1], Transform), 
		GETCMP2(cookersPool, CookerPool), 
		GETCMP2(ingredientsPool, IngredientsPool),
		GETCMP2(utensilsPool, UtensilsPool),
		GETCMP2(firesPool, FirePool), 
		ghostPool,gl);

	vector<tuple<ecs::AdversityID, int>> adversitiesList;	

	for (int i = 0; i < nivel["Adversities"].size(); ++i) {
		
		int tiempo = nivel["Adversities"][i]["Tiempo"].as_int();

		if (nivel["Adversities"][i]["Tipo"].as_string() == "Avion"){
			adversitiesList.emplace_back(tuple<ecs::AdversityID, int>(ecs::AdversityID::PlaneAdversity, tiempo));	
		}
		else if (nivel["Adversities"][i]["Tipo"].as_string() == "Lluvia") {
			adversitiesList.emplace_back(tuple<ecs::AdversityID, int>(ecs::AdversityID::RainAdversity, tiempo));	
		}
		else if (nivel["Adversities"][i]["Tipo"].as_string() == "Gancho") {
			adversitiesList.emplace_back(tuple<ecs::AdversityID, int>(ecs::AdversityID::HookAdversity, tiempo));	
		}
		else if (nivel["Adversities"][i]["Tipo"].as_string() == "Fuego") {
			adversitiesList.emplace_back(tuple<ecs::AdversityID, int>(ecs::AdversityID::CookersAdversity, tiempo));
		}
		else if (nivel["Adversities"][i]["Tipo"].as_string() == "Paloma") {
			adversitiesList.emplace_back(tuple<ecs::AdversityID, int>(ecs::AdversityID::PidgeonAdversity, tiempo));
		}
		else if (nivel["Adversities"][i]["Tipo"].as_string() == "Ventisca") {
			adversitiesList.emplace_back(tuple<ecs::AdversityID, int>(ecs::AdversityID::BlizzardAdversity, tiempo));
		}
		else if (nivel["Adversities"][i]["Tipo"].as_string() == "MuerteIngredientes") {
			adversitiesList.emplace_back(tuple<ecs::AdversityID, int>(ecs::AdversityID::IngredientsdeathAdversity, tiempo));
		}
	}

	if (!adversitiesList.empty()) {
		int min = std::get<1>(adversitiesList.at(0));
		int minPos = 0;

		for (int i = 0; i < adversitiesList.size(); ++i) {
			for (int e = 0; e < adversitiesList.size(); ++e) {
				if (std::get<1>(adversitiesList.at(e)) < min) {
					min = std::get<1>(adversitiesList.at(e));
					minPos = e;
				}
			}
			mam->addAdversityToQueue(std::get<0>(adversitiesList.at(minPos)), std::get<1>(adversitiesList.at(minPos)));
			std::get<1>(adversitiesList.at(minPos)) = 9999999;
			min = 9999999;
		}

		mngr->addToGroup(adversityManager, ecs::GroupID::topLayer);
	}
}
