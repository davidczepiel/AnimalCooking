#include "AdversityAdder.h"
#include "MultipleAdversityManager.h"

AdversityAdder::AdversityAdder(jute::jValue& nivel, EntityManager* mngr, std::array<Entity*, 2>& players, 
	Entity* cookersPool, Entity* ingredientsPool, Entity* utensilsPool)
{
	Entity* adversityManager = mngr->addEntity();
	MultipleAdversityManager* mam = adversityManager->addComponent<MultipleAdversityManager>(
		GETCMP2(players[0], Transform), 
		GETCMP2(players[1], Transform), 
		GETCMP2(cookersPool, CookerPool), 
		GETCMP2(ingredientsPool, IngredientsPool),
		GETCMP2(utensilsPool, UtensilsPool));

	for (int i = 0; i < nivel["Adversities"].size(); ++i) {
		
		int tiempo = nivel["Adversities"][i]["Tiempo"].as_int();

		if (nivel["Adversities"][i]["Tipo"].as_string() == "Avion"){
			mam->setTimerTime(ecs::AdversityID::PlaneAdversity, tiempo);
		}
		else if (nivel["Adversities"][i]["Tipo"].as_string() == "Lluvia") {
			mam->setTimerTime(ecs::AdversityID::RainAdversity, tiempo);
		}
		else if (nivel["Adversities"][i]["Tipo"].as_string() == "Gancho") {
			mam->setTimerTime(ecs::AdversityID::HookAdversity, tiempo);
		}
		else if (nivel["Adversities"][i]["Tipo"].as_string() == "Fuego") {
			mam->setTimerTime(ecs::AdversityID::CookersAdversity, tiempo);
		}
	}

	mngr->addToGroup(adversityManager, ecs::GroupID::topLayer);
}
