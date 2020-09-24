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
	auxiliar.lore[0] = "Attention everyone! Kevin Bacon and Cluck Norris,";
	auxiliar.lore[1] = "from Villa del Pun, have started a new business.";
	auxiliar.lore[2] = "Food trucks are very trendy!";
	auxiliar.buttonPosition = Vector2D(350, 800);
	auxiliar.buttonsSize = Vector2D(80, 100);

	levelsRecipes_.push_back(auxiliar);

	/////////////////////////////////////
   ///////		 LEVEL 2		//////
  /////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore[0] = "Czepielan’s restaurant needs a pair of";
	auxiliar.lore[1] = "chefs for a special event. Are our chefs";	
	auxiliar.lore[2] = "ready for such an opportunity?";
	auxiliar.buttonPosition = Vector2D(594, 570);
	auxiliar.buttonsSize = Vector2D(40, 50);
	levelsRecipes_.push_back(auxiliar);

	/////////////////////////////////////
   ///////		 LEVEL 3		//////
  /////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore[0] = "Rumours spread throughout the country ";
	auxiliar.lore[1] = "about a cooking contest. People";
	auxiliar.lore[2] = "are very excited about it!";
	auxiliar.buttonPosition = Vector2D(1000, 780);
	auxiliar.buttonsSize = Vector2D(80, 100);

	levelsRecipes_.push_back(auxiliar);

	/////////////////////////////////////
   ///////		 LEVEL 4		//////
  /////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore[0] = "Kevin and Cluck have told us that traditional cooking";
	auxiliar.lore[1] = "isn’t their strength so this contest might give";		
	auxiliar.lore[2] = "tthem a new opportunity to get better at it.";
	auxiliar.buttonPosition = Vector2D(1380, 530);
	auxiliar.buttonsSize = Vector2D(40, 50);

	levelsRecipes_.push_back(auxiliar);

	/////////////////////////////////////
   ///////		 LEVEL 5		//////
  /////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore[0] = "A lot of chefs have auditioned for the contest.";
	auxiliar.lore[1] = "We can’t wait to see the future participants.";
	auxiliar.lore[2] = " ";
	auxiliar.buttonPosition = Vector2D(1693, 690);
	auxiliar.buttonsSize = Vector2D(70, 88);

	levelsRecipes_.push_back(auxiliar);


	/////////////////////////////////////
   ///////		 EXTRA 1   		  //////
  /////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore[0] = "“We are naturals.";
	auxiliar.lore[1] = "We’ll beat everyone if we get into the contest”";
	auxiliar.lore[2] = " ";
	auxiliar.buttonPosition = Vector2D(950, 470);
	auxiliar.buttonsSize = Vector2D(46, 58);

	levelsRecipes_.push_back(auxiliar);

	//6
	auxiliar.name = "";
	auxiliar.lore[0] = "Kevin and Cluck have arrived to the casting!";
	auxiliar.lore[1] = "Will their dishes  be good enough?";
	auxiliar.lore[2] = " ";
	auxiliar.buttonPosition = Vector2D(490, 930);
	auxiliar.buttonsSize = Vector2D(80, 100);

	levelsRecipes_.push_back(auxiliar);
	//7
	auxiliar.name = "";
	auxiliar.lore[0] = "Wow! For the first time two citizens from";
	auxiliar.lore[1] = "Villa del Pun have entered the cooking contest.";
	auxiliar.lore[2] = "Will they win?";
	auxiliar.buttonPosition = Vector2D(1020, 980);
	auxiliar.buttonsSize = Vector2D(70, 88);

	levelsRecipes_.push_back(auxiliar);
	//8
	auxiliar.name = "";
	auxiliar.lore[0] = "The contest has begun, ";
	auxiliar.lore[1] = "and Kevin Bacon and Cluck Norris";
	auxiliar.lore[2] = "face well known dishes";
	auxiliar.buttonPosition = Vector2D(810,680);
	auxiliar.buttonsSize = Vector2D(50, 63);

	levelsRecipes_.push_back(auxiliar);
	//9
	auxiliar.name = "";
	auxiliar.lore[0] = "Villa del Pun people are starting to believe";
	auxiliar.lore[1] = "this it’s their opportunity to shine.";
	auxiliar.lore[2] = " ";
	auxiliar.buttonPosition = Vector2D(1520, 760);
	auxiliar.buttonsSize = Vector2D(70, 88);

	levelsRecipes_.push_back(auxiliar);
	//10
	auxiliar.name = "";
	auxiliar.lore[0] = "Everyone knows that almost half of the participants";
	auxiliar.lore[1] = "can’t overcome the meteorological challenge.";
	auxiliar.lore[2] = "Why could that be?";
	auxiliar.buttonPosition = Vector2D(1693, 700);
	auxiliar.buttonsSize = Vector2D(70, 88);

	levelsRecipes_.push_back(auxiliar);


	/////////////////////////////////////
   ///////		 EXTRA 2   		  //////
  /////////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore[0] = "“The real storm was all the dishes";
	auxiliar.lore[1] = "that we had to do in this challenge.”";
	auxiliar.lore[2] = " ";
	auxiliar.buttonPosition = Vector2D(912, 250);
	auxiliar.buttonsSize = Vector2D(46, 58);

	levelsRecipes_.push_back(auxiliar);
	//11
	
	auxiliar.name = "";
	auxiliar.lore[0] = "The contest will now take place in the mountains.";
	auxiliar.lore[1] = "Other participants will have an advantage here...";
	auxiliar.lore[2] = "like Yetis!";
	auxiliar.buttonPosition = Vector2D(420, 620);
	auxiliar.buttonsSize = Vector2D(60, 75);

	levelsRecipes_.push_back(auxiliar);
	//12
	auxiliar.name = "";
	auxiliar.lore[0] = "The contest is definitely harder for them now.";
	auxiliar.lore[1] = " ";
	auxiliar.lore[2] = "And yeah, ice is slippery";
	auxiliar.buttonPosition = Vector2D(725, 970);
	auxiliar.buttonsSize = Vector2D(80, 100);

	levelsRecipes_.push_back(auxiliar);
	//13
	auxiliar.name = "";
	auxiliar.lore[0] = " ";
	auxiliar.lore[1] = "“C-Cold, It’s t-too cold”";
	auxiliar.lore[2] = " ";
	auxiliar.buttonPosition = Vector2D(1140, 745);
	auxiliar.buttonsSize = Vector2D(60, 75);

	levelsRecipes_.push_back(auxiliar);
	//14
	auxiliar.name = "";
	auxiliar.lore[0] = "Our participants have been told that ";
	auxiliar.lore[1] = "whatever they cook here will be their lunch until";
	auxiliar.lore[2] = "next round. How will they preserve it?";
	auxiliar.buttonPosition = Vector2D(1510, 785);
	auxiliar.buttonsSize = Vector2D(55, 69);

	levelsRecipes_.push_back(auxiliar);
	//15
	auxiliar.name = "";
	auxiliar.lore[0] = "A blizzard is expected to hit the area, but";
	auxiliar.lore[1] = "the contest will continue! How will our";
	auxiliar.lore[2] = "participants perform in these conditions?";
	auxiliar.buttonPosition = Vector2D(1600, 475);
	auxiliar.buttonsSize = Vector2D(50, 63);

	levelsRecipes_.push_back(auxiliar);
	/////////////////////////////////////
	///////		 EXTRA 3  		  //////
	///////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore[0] = "News come from the mountains: second round has";
	auxiliar.lore[1] = "finished. If Kevin and Cluck are still in";
	auxiliar.lore[2] = "the competition, nothing will stop them.";
	auxiliar.buttonPosition = Vector2D(917, 445);
	auxiliar.buttonsSize = Vector2D(46, 58);

	levelsRecipes_.push_back(auxiliar);

	//16

	auxiliar.name = "";
	auxiliar.lore[0] = "Some people doubt Kevin and Bacon.";
	auxiliar.lore[1] = "They think they won't be able to prepare the";
	auxiliar.lore[2] = "delicate sushi with their hooves and wings.";
	auxiliar.buttonPosition = Vector2D(200, 580);
	auxiliar.buttonsSize = Vector2D(70, 88);

	levelsRecipes_.push_back(auxiliar);
	//17
	auxiliar.name = "";
	auxiliar.lore[0] = " ";
	auxiliar.lore[1] = "It’s time for Villa del Pun traditional dishes!";
	auxiliar.lore[2] = " ";
	auxiliar.buttonPosition = Vector2D(720, 660);
	auxiliar.buttonsSize = Vector2D(80, 100);

	levelsRecipes_.push_back(auxiliar);
	//18
	auxiliar.name = "";
	auxiliar.lore[0] = "Kevin and Cluck had a lot of success with the sushi!";
	auxiliar.lore[1] = "It seems that everyone is requesting new recipes.";
	auxiliar.lore[2] = "“Itadakimasu”";
	auxiliar.buttonPosition = Vector2D(590, 970);
	auxiliar.buttonsSize = Vector2D(80, 100);

	levelsRecipes_.push_back(auxiliar);
	//19
	auxiliar.name = "";
	auxiliar.lore[0] = "Less and less participants remain";
	auxiliar.lore[1] = "for the grand finale.";
	auxiliar.lore[2] = "Things are getting pretty heated.";
	auxiliar.buttonPosition = Vector2D(1370, 810);
	auxiliar.buttonsSize = Vector2D(60, 75);

	levelsRecipes_.push_back(auxiliar);
	//20
	auxiliar.name = "";
	auxiliar.lore[0] = "Controversy over the appearance of";
	auxiliar.lore[1] = "some strangeseeds in the orchard.";
	auxiliar.lore[2] = "Who could have planted those?";
	auxiliar.buttonPosition = Vector2D(1610, 580);
	auxiliar.buttonsSize = Vector2D(60, 75);

	levelsRecipes_.push_back(auxiliar);
	/////////////////////////////////////
	///////		 EXTRA 4  		  //////
	///////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore[0] = " ";
	auxiliar.lore[1] = "“Since when plants invade your kitchen?!”";
	auxiliar.lore[2] = " ";
	auxiliar.buttonPosition = Vector2D(1135, 450);
	auxiliar.buttonsSize = Vector2D(46, 58);

	levelsRecipes_.push_back(auxiliar);

	//21

	auxiliar.name = "";
	auxiliar.lore[0] = "The participants prepare for the new type of dishes.";
	auxiliar.lore[1] = "They don’t seem as healthy though.";
	auxiliar.lore[2] = "Perhaps they gain some weight.";
	auxiliar.buttonPosition = Vector2D(700, 650);
	auxiliar.buttonsSize = Vector2D(60, 75);

	levelsRecipes_.push_back(auxiliar);
	//22
	auxiliar.name = "";
	auxiliar.lore[0] = " ";
	auxiliar.lore[1] = "“We miss salads”";
	auxiliar.lore[2] = " ";
	auxiliar.buttonPosition = Vector2D(200, 940);
	auxiliar.buttonsSize = Vector2D(80, 100);

	levelsRecipes_.push_back(auxiliar);
	//23
	auxiliar.name = "";
	auxiliar.lore[0] = "-Hello, hello, hello! We have hotdogs,";
	auxiliar.lore[1] = "with whatever you’d like'em with!";
	auxiliar.lore[2] = " ";
	auxiliar.buttonPosition = Vector2D(850, 900);
	auxiliar.buttonsSize = Vector2D(80, 100);

	levelsRecipes_.push_back(auxiliar);
	//24
	auxiliar.name = "";
	auxiliar.lore[0] = "The grand finale is getting closer";
	auxiliar.lore[1] = "and with it the fear of losing.";
	auxiliar.lore[2] = " ";
	auxiliar.buttonPosition = Vector2D(1210, 900);
	auxiliar.buttonsSize = Vector2D(80, 100);

	levelsRecipes_.push_back(auxiliar);
	//25
	auxiliar.name = "";
	auxiliar.lore[0] = "The grand finale will be at";
	auxiliar.lore[1] = "Cluck O’Ten island.";
	auxiliar.lore[2] = "We are so excited!";
	auxiliar.buttonPosition = Vector2D(1200, 500);
	auxiliar.buttonsSize = Vector2D(46, 58);

	levelsRecipes_.push_back(auxiliar);
	/////////////////////////////////////
	///////		 EXTRA 5  		  //////
	///////////////////////////////////

	auxiliar.name = "";
	auxiliar.lore[0] = " ";
	auxiliar.lore[1] = "“We need to calm down!!!!”";
	auxiliar.lore[2] = " ";
	auxiliar.buttonPosition = Vector2D(1580, 330);
	auxiliar.buttonsSize = Vector2D(60, 75);

	levelsRecipes_.push_back(auxiliar);

	/////////////////////////////////////
	///////		 Nivel final  	  //////
	///////////////////////////////////
	auxiliar.name = "";
	auxiliar.lore[0] = "The grand finale! The winning price is getting";
	auxiliar.lore[1] = "your own restaurant at this awesome building. ";
	auxiliar.lore[2] = "Ready, set… Go!";
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