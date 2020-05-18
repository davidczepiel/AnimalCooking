#include "MapConfig.h"

MapConfig::MapConfig()
{
	fill();
}

void MapConfig::fill(string filename)
{


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

	levelsRecipes.push_back(auxiliar);
	load(filename);

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
void MapConfig::load(string filename)
{
	if (!levelsRecipes.empty())
		levelsRecipes.clear();
	stringstream file(filename);
	file << "../AnimalCooking/resources/" << filename << ".txt";
	fstream partidaGuardada(file.str().c_str(), std::ios::in);
	int i = 0;
	while (!partidaGuardada.eof())

	{
		partidaGuardada >> levelsRecipes.at(i).level;
		partidaGuardada >> levelsRecipes.at(i).stars;
		partidaGuardada >> levelsRecipes.at(i).unlocked;
		i++;
	}
	partidaGuardada.close();

}

void MapConfig::save(string filename)
{
	stringstream file(filename);
	file << "../AnimalCooking/resources/" << filename << ".txt";
	fstream partidaGuardada(file.str().c_str(), ios::out);
	int i = 0;
	for (levelInfo lI : levelsRecipes) {
		partidaGuardada << i << " " << lI.stars << " " << lI.unlocked << endl;
		cout << i << " " << lI.stars << " " << lI.unlocked << endl;
		i++;
	}
	partidaGuardada.close();
}
