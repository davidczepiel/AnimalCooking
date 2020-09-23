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
	auxiliar.lore[0] = "Get the kitchens ready, the cooking competition starts in Villa";
	auxiliar.lore[1] = "del Pun!Your first opponents are your pastrycook neighbours...";
	auxiliar.lore[2] = "pastrycook neighbours...Can you beat them?";
	auxiliar.buttonPosition = Vector2D(350, 800);
	auxiliar.buttonsSize = Vector2D(80, 100);

	levelsRecipes_.push_back(auxiliar);

	/////////////////////////////////////
   ///////		 LEVEL 2		//////
  /////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore[0] = "The villagers have found out about the cooking competition! But the";
	auxiliar.lore[1] = "best restaurant in the village wants to challenge you to be the ";	
	auxiliar.lore[2] = "village representative. Show them what a gourmet dish is!";
	auxiliar.buttonPosition = Vector2D(594, 570);
	auxiliar.buttonsSize = Vector2D(40, 50);
	levelsRecipes_.push_back(auxiliar);

	/////////////////////////////////////
   ///////		 LEVEL 3		//////
  /////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore[0] = "You've moved on to the next phase, however, you still have a long";
	auxiliar.lore[1] = "way to go. It's your turn to join the other villages at Serendipity.";
	auxiliar.lore[2] = "Look out! There are a lot of planes passing by.";
	auxiliar.buttonPosition = Vector2D(1000, 780);
	auxiliar.buttonsSize = Vector2D(80, 100);

	levelsRecipes_.push_back(auxiliar);

	/////////////////////////////////////
   ///////		 LEVEL 4		//////
  /////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore[0] = "Wow! You start to gain fame after the challenges, and you even";
	auxiliar.lore[1] = "have your first fans! Although these are friends and acquaintances.";		
	auxiliar.lore[2] = "It's time to show that you're better at cooking than anything else.";
	auxiliar.buttonPosition = Vector2D(1380, 530);
	auxiliar.buttonsSize = Vector2D(40, 50);

	levelsRecipes_.push_back(auxiliar);

	/////////////////////////////////////
   ///////		 LEVEL 5		//////
  /////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore[0] = "Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "The Grand Final!";
	auxiliar.buttonPosition = Vector2D(1693, 690);
	auxiliar.buttonsSize = Vector2D(70, 88);

	levelsRecipes_.push_back(auxiliar);


	/////////////////////////////////////
   ///////		 EXTRA 1   		  //////
  /////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore[0] = "Extra 1. Extra 1. Extra 1. Extra 1.";
	auxiliar.lore[1] = "Extra 1. Extra 1. Extra 1. Extra 1.";
	auxiliar.lore[2] = "Extra 1. Extra 1. Extra 1. Extra 1.";
	auxiliar.buttonPosition = Vector2D(950, 470);
	auxiliar.buttonsSize = Vector2D(46, 58);

	levelsRecipes_.push_back(auxiliar);

	//6
	auxiliar.name = "";
	auxiliar.lore[0] = "6 Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE GRAND FINAL!";
	auxiliar.buttonPosition = Vector2D(490, 930);
	auxiliar.buttonsSize = Vector2D(80, 100);

	levelsRecipes_.push_back(auxiliar);
	//7
	auxiliar.name = "";
	auxiliar.lore[0] = "7 Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE GRAND FINAL!";
	auxiliar.buttonPosition = Vector2D(1020, 980);
	auxiliar.buttonsSize = Vector2D(70, 88);

	levelsRecipes_.push_back(auxiliar);
	//8
	auxiliar.name = "";
	auxiliar.lore[0] = "8 Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE  GRAND  FINAL!";
	auxiliar.buttonPosition = Vector2D(810,680);
	auxiliar.buttonsSize = Vector2D(50, 63);

	levelsRecipes_.push_back(auxiliar);
	//9
	auxiliar.name = "";
	auxiliar.lore[0] = "9 Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE GRAND FINAL!";
	auxiliar.buttonPosition = Vector2D(1520, 760);
	auxiliar.buttonsSize = Vector2D(70, 88);

	levelsRecipes_.push_back(auxiliar);
	//10
	auxiliar.name = "";
	auxiliar.lore[0] = "10 Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE GRAND FINAL!";
	auxiliar.buttonPosition = Vector2D(1693, 700);
	auxiliar.buttonsSize = Vector2D(70, 88);

	levelsRecipes_.push_back(auxiliar);


	/////////////////////////////////////
   ///////		 EXTRA 2   		  //////
  /////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore[0] = "Extra 2. Extra 2. Extra 2. Extra 2.";
	auxiliar.lore[1] = "Extra 2. Extra 2. Extra 2. Extra 2.";
	auxiliar.lore[2] = "Extra 2. Extra 2. Extra 2. Extra 2.";
	auxiliar.buttonPosition = Vector2D(912, 250);
	auxiliar.buttonsSize = Vector2D(46, 58);

	levelsRecipes_.push_back(auxiliar);
	//11
	
	auxiliar.name = "";
	auxiliar.lore[0] = "11 Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE GRAND FINAL!";
	auxiliar.buttonPosition = Vector2D(420, 620);
	auxiliar.buttonsSize = Vector2D(60, 75);

	levelsRecipes_.push_back(auxiliar);
	//12
	auxiliar.name = "";
	auxiliar.lore[0] = "12 Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE GRAND FINAL!";
	auxiliar.buttonPosition = Vector2D(725, 970);
	auxiliar.buttonsSize = Vector2D(80, 100);

	levelsRecipes_.push_back(auxiliar);
	//13
	auxiliar.name = "";
	auxiliar.lore[0] = "13 Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE GRAND FINAL!";
	auxiliar.buttonPosition = Vector2D(1140, 745);
	auxiliar.buttonsSize = Vector2D(60, 75);

	levelsRecipes_.push_back(auxiliar);
	//14
	auxiliar.name = "";
	auxiliar.lore[0] = "14 Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE GRAND FINAL!";
	auxiliar.buttonPosition = Vector2D(1510, 785);
	auxiliar.buttonsSize = Vector2D(55, 69);

	levelsRecipes_.push_back(auxiliar);
	//15
	auxiliar.name = "";
	auxiliar.lore[0] = "15 Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE GRAND FINAL!";
	auxiliar.buttonPosition = Vector2D(1600, 475);
	auxiliar.buttonsSize = Vector2D(50, 63);

	levelsRecipes_.push_back(auxiliar);
	/////////////////////////////////////
	///////		 EXTRA 3  		  //////
	///////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore[0] = "Extra 2. Extra 2. Extra 2. Extra 2.";
	auxiliar.lore[1] = "Extra 2. Extra 2. Extra 2. Extra 2.";
	auxiliar.lore[2] = "Extra 2. Extra 2. Extra 2. Extra 2.";
	auxiliar.buttonPosition = Vector2D(917, 445);
	auxiliar.buttonsSize = Vector2D(46, 58);

	levelsRecipes_.push_back(auxiliar);

	//16

	auxiliar.name = "";
	auxiliar.lore[0] = "16 Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE GRAND FINAL!";
	auxiliar.buttonPosition = Vector2D(200, 580);
	auxiliar.buttonsSize = Vector2D(70, 88);

	levelsRecipes_.push_back(auxiliar);
	//17
	auxiliar.name = "";
	auxiliar.lore[0] = "17 Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE GRAND FINAL!";
	auxiliar.buttonPosition = Vector2D(720, 660);
	auxiliar.buttonsSize = Vector2D(80, 100);

	levelsRecipes_.push_back(auxiliar);
	//18
	auxiliar.name = "";
	auxiliar.lore[0] = "18 Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE GRAND FINAL!";
	auxiliar.buttonPosition = Vector2D(590, 970);
	auxiliar.buttonsSize = Vector2D(80, 100);

	levelsRecipes_.push_back(auxiliar);
	//19
	auxiliar.name = "";
	auxiliar.lore[0] = "19 Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE GRAND FINAL!";
	auxiliar.buttonPosition = Vector2D(1370, 810);
	auxiliar.buttonsSize = Vector2D(60, 75);

	levelsRecipes_.push_back(auxiliar);
	//20
	auxiliar.name = "";
	auxiliar.lore[0] = "20 Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE GRAND FINAL!";
	auxiliar.buttonPosition = Vector2D(1610, 580);
	auxiliar.buttonsSize = Vector2D(60, 75);

	levelsRecipes_.push_back(auxiliar);
	/////////////////////////////////////
	///////		 EXTRA 4  		  //////
	///////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore[0] = "Extra 4. Extra 4. Extra 4. Extra 4.";
	auxiliar.lore[1] = "Extra 4. Extra 4. Extra 4. Extra 4.";
	auxiliar.lore[2] = "Extra 4. Extra 4. Extra 4. Extra 4.";
	auxiliar.buttonPosition = Vector2D(1135, 450);
	auxiliar.buttonsSize = Vector2D(46, 58);

	levelsRecipes_.push_back(auxiliar);

	//21

	auxiliar.name = "";
	auxiliar.lore[0] = "21 Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE GRAND FINAL!";
	auxiliar.buttonPosition = Vector2D(700, 650);
	auxiliar.buttonsSize = Vector2D(60, 75);

	levelsRecipes_.push_back(auxiliar);
	//22
	auxiliar.name = "";
	auxiliar.lore[0] = "22 Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE GRAND FINAL!";
	auxiliar.buttonPosition = Vector2D(200, 940);
	auxiliar.buttonsSize = Vector2D(80, 100);

	levelsRecipes_.push_back(auxiliar);
	//23
	auxiliar.name = "";
	auxiliar.lore[0] = "23 Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE GRAND FINAL!";
	auxiliar.buttonPosition = Vector2D(850, 900);
	auxiliar.buttonsSize = Vector2D(80, 100);

	levelsRecipes_.push_back(auxiliar);
	//24
	auxiliar.name = "";
	auxiliar.lore[0] = "24 Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE GRAND FINAL!";
	auxiliar.buttonPosition = Vector2D(1210, 900);
	auxiliar.buttonsSize = Vector2D(80, 100);

	levelsRecipes_.push_back(auxiliar);
	//25
	auxiliar.name = "";
	auxiliar.lore[0] = "25 Ingredients...ready. Utensils... ready.";
	auxiliar.lore[1] = "Get prepared, because you have reached";
	auxiliar.lore[2] = "THE GRAND FINAL!";
	auxiliar.buttonPosition = Vector2D(1580, 330);
	auxiliar.buttonsSize = Vector2D(60, 75);

	levelsRecipes_.push_back(auxiliar);
	/////////////////////////////////////
	///////		 EXTRA 5  		  //////
	///////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore[0] = "Extra 5. Extra 5. Extra 5. Extra 5.";
	auxiliar.lore[1] = "Extra 5. Extra 5. Extra 5. Extra 5.";
	auxiliar.lore[2] = "Extra 5. Extra 5. Extra 5. Extra 5.";
	auxiliar.buttonPosition = Vector2D(1200, 500);
	auxiliar.buttonsSize = Vector2D(46, 58);

	levelsRecipes_.push_back(auxiliar);

	/////////////////////////////////////
	///////		 Nivel final  	  //////
	///////////////////////////////////
	auxiliar.name = "";
	auxiliar.lore[0] = "Nivel final.Nivel final. Nivel final. Nivel final.";
	auxiliar.lore[1] = "Nivel final";
	auxiliar.lore[2] = "Nivel final";
	auxiliar.buttonPosition = Vector2D(930, 570);
	auxiliar.buttonsSize = Vector2D(46, 58);

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