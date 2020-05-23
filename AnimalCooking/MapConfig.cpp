#include "MapConfig.h"
#include "MapState.h"

MapConfig::MapConfig(string fileN) : fileName_(fileN), levelsRecipes_(), newGame_(false)
{
}

MapConfig::MapConfig(string fileN, bool newGame) : 
	fileName_(fileN), levelsRecipes_(), newGame_(newGame)
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
	if (!newGame_) load();
	else {
		int numberOfLevel = 0;

		for (int i = 0; i < levelsRecipes_.size(); i++)
		{
			levelsRecipes_[i].level = numberOfLevel;
			levelsRecipes_[i].stars = 0;
			levelsRecipes_[i].unlocked = false;
			numberOfLevel++;

		}
		levelsRecipes_.at(0).unlocked = true; //If new game = unlock lvl 1
	}

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


		if (partidaGuardada.is_open())
			while (!partidaGuardada.eof())
			{
				partidaGuardada >> levelsRecipes_.at(i).level;
				partidaGuardada >> levelsRecipes_.at(i).stars;
				partidaGuardada >> levelsRecipes_.at(i).unlocked;
				i++;
			}


		partidaGuardada.close();
	}
}

void MapConfig::removeProfile()
{
	remove(string("../AnimalCooking/resources/" + fileName_ + ".txt").c_str());

	stringstream file("");

	ifstream profiles("../AnimalCooking/resources/profiles.txt");
	if (profiles.is_open()) {
		while (!profiles.eof()) {
			string cadena;
			std::getline(profiles, cadena);
			if (!profiles.fail() && cadena != fileName_) {
				file << cadena << endl;
			}		
		}
	}
	profiles.close();
	remove(string("../AnimalCooking/resources/profiles.txt").c_str());
	ofstream p("../AnimalCooking/resources/profiles.txt", ios::beg);
	p << file.str();
	p.close();
}

void MapConfig::save()
{
	fileName_ = SDLGame::instance()->getName();
	int unlocked_levels = SDLGame::instance()->getCurrenUnlockLevel();
	map<int, int>stars = SDLGame::instance()->getUnlockedStars();
	load();
	for (auto it : stars) {
		levelsRecipes_.at(it.first).stars = it.second;

	}
	for (int i = 0; i < unlocked_levels; i++)
	{
		levelsRecipes_.at(i).unlocked = true;
	}
	stringstream file(fileName_);
	file << "../AnimalCooking/resources/" << fileName_ << ".txt";
	fstream partidaGuardada(file.str().c_str(), ios::out);
	int i = 0;
	for (levelInfo lI : levelsRecipes_) {
		partidaGuardada << i << " " << lI.stars << " " << lI.unlocked << endl;
		i++;
	}
	partidaGuardada.close();


}

vector<string> MapConfig::getProfiles()
{
	vector<string> p;
	ifstream profiles("../AnimalCooking/resources/profiles.txt");
	if (profiles.is_open()) {
		while (!profiles.eof()) {
			string cadena;
			std::getline(profiles, cadena);
			if (!profiles.fail())
				p.push_back(cadena);
		}
	}
	return p;
}