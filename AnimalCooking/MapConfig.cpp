#include "MapConfig.h"

MapConfig::MapConfig()
{
	fill();
}

void MapConfig::fill()
{

	//Inicializar el fichero de partida


	levelInfo auxiliar;

	  /////////////////////////////////////
	 ///////		 LEVEL 1		//////
	/////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore = "";
	auxiliar.houseBox.x = 10;
	auxiliar.houseBox.y = 10;
	auxiliar.houseBox.w = 10;
	auxiliar.houseBox.h = 10;
	auxiliar.housePosition = Vector2D(15, 15);
	auxiliar.stars = 0;
	auxiliar.unlocked = false;

	levelsRecipes.push_back(auxiliar);

	  /////////////////////////////////////
	 ///////		 LEVEL 2		//////
	/////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore = "";
	auxiliar.houseBox.x = 10;
	auxiliar.houseBox.y = 10;
	auxiliar.houseBox.w = 10;
	auxiliar.houseBox.h = 10;
	auxiliar.housePosition = Vector2D(15, 15);
	auxiliar.stars = 0;
	auxiliar.unlocked = false;

	levelsRecipes.push_back(auxiliar);

	  /////////////////////////////////////
	 ///////		 LEVEL 3		//////
	/////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore = "";
	auxiliar.houseBox.x = 10;
	auxiliar.houseBox.y = 10;
	auxiliar.houseBox.w = 10;
	auxiliar.houseBox.h = 10;
	auxiliar.housePosition = Vector2D(15, 15);
	auxiliar.stars = 0;
	auxiliar.unlocked = false;

	levelsRecipes.push_back(auxiliar);

	  /////////////////////////////////////
	 ///////		 LEVEL 4		//////
	/////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore = "";
	auxiliar.houseBox.x = 10;
	auxiliar.houseBox.y = 10;
	auxiliar.houseBox.w = 10;
	auxiliar.houseBox.h = 10;
	auxiliar.housePosition = Vector2D(15, 15);
	auxiliar.stars = 0;
	auxiliar.unlocked = false;

	levelsRecipes.push_back(auxiliar);

	  /////////////////////////////////////
	 ///////		 LEVEL 5		//////
	/////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore = "";
	auxiliar.houseBox.x = 10;
	auxiliar.houseBox.y = 10;
	auxiliar.houseBox.w = 10;
	auxiliar.houseBox.h = 10;
	auxiliar.housePosition = Vector2D(15, 15);
	auxiliar.stars = 0;
	auxiliar.unlocked = false;

	levelsRecipes.push_back(auxiliar);

	  /////////////////////////////////////
	 ///////		 LEVEL N		//////
	/////////////////////////////////////

	/*auxiliar.name = "";
	auxiliar.lore = "";
	auxiliar.houseBox.x = 10;
	auxiliar.houseBox.y = 10;
	auxiliar.houseBox.w = 10;
	auxiliar.houseBox.h = 10;
	auxiliar.housePosition = Vector2D(15, 15);
	auxiliar.stars = 0;
	auxiliar.unlocked = false;

	levelsRecipes.push_back(auxiliar);*/
}
