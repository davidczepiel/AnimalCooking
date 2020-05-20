#include "MapConfig.h"

MapConfig::MapConfig(string fileN): fileName_(fileN), levelsRecipes_()
{
	fill();
}

void MapConfig::fill()
{
	levelInfo auxiliar;

	  /////////////////////////////////////
	 ///////		 LEVEL 1		//////
	/////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore = "";
	auxiliar.housePosition = Vector2D(15, 15);

	levelsRecipes_.push_back(auxiliar);

	  /////////////////////////////////////
	 ///////		 LEVEL 2		//////
	/////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore = "";
	auxiliar.housePosition = Vector2D(15, 15);

	levelsRecipes_.push_back(auxiliar);

	  /////////////////////////////////////
	 ///////		 LEVEL 3		//////
	/////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore = "";
	auxiliar.housePosition = Vector2D(15, 15);

	levelsRecipes_.push_back(auxiliar);

	  /////////////////////////////////////
	 ///////		 LEVEL 4		//////
	/////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore = "";
	auxiliar.housePosition = Vector2D(15, 15);

	levelsRecipes_.push_back(auxiliar);

	  /////////////////////////////////////
	 ///////		 LEVEL 5		//////
	/////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore = "";
	auxiliar.housePosition = Vector2D(15, 15);

	levelsRecipes_.push_back(auxiliar);

	//Cargar resto de datos
	load();

	  /////////////////////////////////////
	 ///////		 LEVEL N		//////
	/////////////////////////////////////

	/*auxiliar.name = "";
	auxiliar.lore = "";
	auxiliar.housePosition = Vector2D(15, 15);
	auxiliar.stars = 0;
	auxiliar.unlocked = false;

	levelsRecipes.push_back(auxiliar);*/
}

void MapConfig::load()
{
	if (!levelsRecipes_.empty()) {
		stringstream file(fileName_);
		file << "../AnimalCooking/resources/" << fileName_ << ".txt";
		fstream partidaGuardada(file.str().c_str(), std::ios::in);
		int i = 0;

		if (partidaGuardada.is_open()) {
			while (!partidaGuardada.eof())
			{
				partidaGuardada >> levelsRecipes_.at(i).level;
				partidaGuardada >> levelsRecipes_.at(i).stars;
				partidaGuardada >> levelsRecipes_.at(i).unlocked;
				i++;
			}			
		}	
		partidaGuardada.close();
	}
}

void MapConfig::save()
{
	stringstream file(fileName_);
	file << "../AnimalCooking/resources/" << fileName_ << ".txt";
	fstream partidaGuardada(file.str().c_str(), ios::out);
	int i = 0;
	for (levelInfo lI : levelsRecipes_) {
		partidaGuardada << i << " " << lI.stars << " " << lI.unlocked << endl;
		cout << i << " " << lI.stars << " " << lI.unlocked << endl;
		i++;
	}
	partidaGuardada.close();
}
