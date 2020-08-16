#include "MapConfig.h"
#include "MapState.h"

MapConfig::MapConfig(): levelsRecipes_(), newGame_(nullptr)
{
}

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
	auxiliar.lore[0] = "Get the kitchens ready, the cooking conmpetition starts in Villa del Pun!";
	auxiliar.lore[1] = "Your first opponents are your pastrycook neighbours...";
	auxiliar.lore[2] = "can you beat them?";
	auxiliar.buttonPosition = Vector2D(415, 807);
	auxiliar.buttonsSize = Vector2D(80, 40);

	levelsRecipes_.push_back(auxiliar);

	/////////////////////////////////////
   ///////		 LEVEL 2		//////
  /////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore[0] = "The villagers find out about the cooking competition and that the best restaurant";
	auxiliar.lore[1] = "in the village wants to challenge you to be the representative of the village in this one";	
	auxiliar.lore[2] = "Show them what a gourmet dish is!";
	auxiliar.buttonPosition = Vector2D(594, 590);
	auxiliar.buttonsSize = Vector2D(40, 20);
	levelsRecipes_.push_back(auxiliar);

	/////////////////////////////////////
   ///////		 LEVEL 3		//////
  /////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore[0] = "You've moved on to the next phase, however, you still have a long way to go.";
	auxiliar.lore[1] = "It's your turn to join the other villages at Serendipity.";
	auxiliar.lore[2] = "Look out! There are a lot of planes passing by.";
	auxiliar.buttonPosition = Vector2D(1008, 820);
	auxiliar.buttonsSize = Vector2D(80, 40);

	levelsRecipes_.push_back(auxiliar);

	/////////////////////////////////////
   ///////		 LEVEL 4		//////
  /////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore[0] = "Wow! You start to gain fame after the challenges and you even";
	auxiliar.lore[1] = "have your first fans,although these are friends and acquaintances.";		
	auxiliar.lore[2] = "It's time to show that you're better at cooking than anything else.";
	auxiliar.buttonPosition = Vector2D(1380, 560);
	auxiliar.buttonsSize = Vector2D(40, 20);

	levelsRecipes_.push_back(auxiliar);

	/////////////////////////////////////
   ///////		 LEVEL 5		//////
  /////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore[0] = "Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE GRAND FINAL!";
	auxiliar.buttonPosition = Vector2D(1693, 720);
	auxiliar.buttonsSize = Vector2D(70, 35);

	levelsRecipes_.push_back(auxiliar);
	//6
	auxiliar.name = "";
	auxiliar.lore[0] = "Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE GRAND FINAL!";
	auxiliar.buttonPosition = Vector2D(1693, 720);
	auxiliar.buttonsSize = Vector2D(70, 35);

	levelsRecipes_.push_back(auxiliar);
	//7
	auxiliar.name = "";
	auxiliar.lore[0] = "Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE GRAND FINAL!";
	auxiliar.buttonPosition = Vector2D(1593, 720);
	auxiliar.buttonsSize = Vector2D(70, 35);

	levelsRecipes_.push_back(auxiliar);
	//8
	auxiliar.name = "";
	auxiliar.lore[0] = "Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE GRAND FINAL!";
	auxiliar.buttonPosition = Vector2D(1493, 720);
	auxiliar.buttonsSize = Vector2D(70, 35);

	levelsRecipes_.push_back(auxiliar);
	//9
	auxiliar.name = "";
	auxiliar.lore[0] = "Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE GRAND FINAL!";
	auxiliar.buttonPosition = Vector2D(1393, 720);
	auxiliar.buttonsSize = Vector2D(70, 35);

	levelsRecipes_.push_back(auxiliar);
	//10
	auxiliar.name = "";
	auxiliar.lore[0] = "Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE GRAND FINAL!";
	auxiliar.buttonPosition = Vector2D(1293, 720);
	auxiliar.buttonsSize = Vector2D(70, 35);

	levelsRecipes_.push_back(auxiliar);

	//Cargar resto de datos
	if (!newGame_) load();
	else {
		int numberOfLevel = 0;

		stringstream file(fileName_);
		file << "../AnimalCooking/resources/saves/" << fileName_ << ".txt";
		fstream partidaGuardada(file.str().c_str(), ios::out);

		levelsRecipes_[0].level = numberOfLevel;
		levelsRecipes_[0].stars = 0;
		levelsRecipes_.at(0).unlocked = true;
		partidaGuardada << numberOfLevel << " " << levelsRecipes_[0].stars << " " << levelsRecipes_[0].unlocked << endl;
		numberOfLevel++;
		for (int i = 1; i < levelsRecipes_.size(); i++)
		{
			levelsRecipes_[i].level = numberOfLevel;
			levelsRecipes_[i].stars = 0;
			levelsRecipes_[i].unlocked = false;
			partidaGuardada << numberOfLevel << " " << levelsRecipes_[i].stars << " " << levelsRecipes_[i].unlocked << endl;
			numberOfLevel++;
		}
		 //If new game = unlock lvl 1
		partidaGuardada.close();
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
		file << "../AnimalCooking/resources/saves/" << fileName_ << ".txt";
		fstream partidaGuardada(file.str().c_str(), std::ios::in);
		int i = 0;

		if (partidaGuardada.is_open())
			while (!partidaGuardada.eof())
			{
				partidaGuardada >> levelsRecipes_.at(i).level;
				partidaGuardada >> levelsRecipes_.at(i).stars;
				partidaGuardada >> levelsRecipes_.at(i).unlocked;			
				i++;
				if (i == levelsRecipes_.size())
					break;
			}
		partidaGuardada.close();
	}
}

void MapConfig::removeProfile()
{
	remove(string("../AnimalCooking/resources/saves/" + fileName_ + ".txt").c_str());

	stringstream file("");

	ifstream profiles("../AnimalCooking/resources/saves/profiles.txt");
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
	remove(string("../AnimalCooking/resources/saves/profiles.txt").c_str());
	ofstream p("../AnimalCooking/resources/saves/profiles.txt", ios::beg);
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
	for (int i = 0; i <= unlocked_levels; i++)
	{
		levelsRecipes_.at(i).unlocked = true;
	}
	stringstream file(fileName_);
	file << "../AnimalCooking/resources/saves/" << fileName_ << ".txt";
	fstream partidaGuardada(file.str().c_str(), ios::out);
	int i = 0;
	for (levelInfo lI : levelsRecipes_) {
		partidaGuardada << i << " " << lI.stars << " " << lI.unlocked << endl;
		i++;
	}
	partidaGuardada.close();
}

void MapConfig::saveNewProfile(const string& newProfile)
{
	if (newProfile.empty())
		return;

	const vector<string>& perfiles = getProfiles();
	auto it = std::find(perfiles.begin(), perfiles.end(), newProfile);
	if (it != perfiles.end())
		return;

	ofstream profiles("../AnimalCooking/resources/saves/profiles.txt", ios::app);
	if (profiles.is_open()) profiles << newProfile << endl;
	profiles.close();
}

vector<string> MapConfig::getProfiles()
{
	vector<string> p;
	ifstream profiles("../AnimalCooking/resources/saves/profiles.txt");
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