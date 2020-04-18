#include "GameControl.h" 
#include "Ingredient.h"  

GameControl::GameControl(Transport* p1, Transport* p2, UtensilsPool* u, FoodPool* fp, IngredientsPool* ip, Resources::Level level) : Component(ecs::GameControl),utensilsPool(u),foodPool(fp),tP1(p1),tP2(p2),ingPool_(ip)
{
	const string rutaNivel = "../AnimalCooking/resources/cfg/nivel" + std::to_string(level - 1) + ".cfg";
	jsonLevel = jute::parser::parse_file(rutaNivel);

	const string rutaGeneral = "../AnimalCooking/resources/cfg/general.cfg";
	jsonGeneral = jute::parser::parse_file(rutaGeneral);

	timer.setTime(1000);
	timer.timerStart();
}

void GameControl::init()
{
	
}

void GameControl::update()
{
	//Cuando empieza el nivel,al pasar x tiempo aparecen los ingredientes
	if (timer.isTimerEnd())
	{
		for (int i = 0; i < 4; i++)
		{
			newIngredient();
		}
		timer.timerReset();
	}
	else timer.update();
}

void GameControl::newIngredient() 

{   // Se crea un ingrediente nuevo aleatorio
	jute::jValue ingsType = jsonLevel["IngredientsPool"]["entities"];
	int n = SDLGame::instance()->getRandGen()->nextInt(0, ingsType.size());
	string s = jsonLevel["IngredientsPool"]["entities"][n][0].as_string();	
	Ingredient* ing = newIngType(s);  

	double casilla = SDLGame::instance()->getWindowHeight() / 9;    
	ing->setSize(jsonGeneral["Ingredientes"]["size"]["width"].as_double() * casilla,jsonGeneral["Ingredientes"]["size"]["height"].as_double() * casilla);
		
    //double y = (game_->getWindowHeight() / 4) * game_->getRandGen()->nextInt(1, 4);
	double y = game_->getRandGen()->nextInt(ing->getHeight(), game_->getWindowHeight()-25);
    ing->setVel(Vector2D(0,0));
    ing->setPos(Vector2D(game_->getWindowWidth() - 25, y));

	ingPool_->addIngredient(ing);
	ing = nullptr;
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

Ingredient* GameControl::newIngType(const string& s) {

	Ingredient* i =nullptr;
	
	switch (str2int(s.c_str()))
	{
	case str2int("Tomato"):
		i = new Tomato();
		cout << "Tomato" << endl;
		break;
	case str2int("Carrot"):
		i = new Carrot();
		cout << "Carrot" << endl;
		break;
	case str2int("Lettuce"):
		i = new Lettuce();
		cout << "Lettuce" << endl;
		break;
	case str2int("Mushroom"):
		i = new Mushroom();
		cout << "Mushroom" << endl;
		break;
	case str2int("Sausage"):
		i = new Sausage();
		cout << "Sausage" << endl;
		break;
	case str2int("Chicken"):
		i = new Chicken();
		cout << "Chicken" << endl;
		break;
	case str2int("Meat"):
		i = new Meat();
		cout << "Meat" << endl;
		break;
	case str2int("Potato"):
		i = new Potato();
		cout << "Potato" << endl;
		break;
	case str2int("Onion"):
		i = new Onion();
		cout << "Onion" << endl;
		break;
	case str2int("Clam"):
		i = new Clam();
		cout << "Clam" << endl;
		break;
	case str2int("Cheese"):
		i = new Cheese();
		cout << "Cheese" << endl;
		break;
	case str2int("Fish"):
		i = new Fish();
		cout << "Fish" << endl;
		break;
	default:
		break;
	}
	return i;
}

void GameControl::newFood(Food* f, Vector2D pos) {
	foodPool->AddFood(f);
	f->onDrop(true);
	f->setPos(pos);
	f->setTransports(tP1, tP2);
	newIngredient(); //al matar un ingrediente aparece otro
}

Food* GameControl::newFood(Resources::FoodType type, Vector2D pos) {     //llamar al metodo foodpool para crear uno nuevo de tipo type y pos 
	Food* f;
	switch (type) {

		///////////KNIFE
	case(Resources::FoodType::SlicedTomato):
		f = new SlicedTomato(pos,tP1,tP2);
		break;
	case(Resources::FoodType::SlicedCheese):
		f = new SlicedCheese(pos, tP1, tP2);
		break;
	case(Resources::FoodType::SlicedCarrot):
		f = new SlicedCarrot(pos, tP1, tP2);
		break;
	case(Resources::FoodType::SlicedMeat):
		f = new SlicedMeat(pos, tP1, tP2);
		break;
	case(Resources::FoodType::SlicedLettuce):
		f = new SlicedLettuce(pos, tP1, tP2);
		break;
	case(Resources::FoodType::SlicedSausage):
		f = new SlicedSausage(pos, tP1, tP2);
		break;
	case(Resources::FoodType::SlicedMushroom):
		f = new SlicedMushroom(pos, tP1, tP2);
		break;
	case(Resources::FoodType::SlicedPotato):
		f = new SlicedPotato(pos, tP1, tP2);
		break;
	case(Resources::FoodType::SlicedOnion):
		f = new SlicedOnion(pos, tP1, tP2);
		break;
	case(Resources::FoodType::SlicedChicken):
		f = new SlicedTomato(pos, tP1, tP2);
		break;


		//////////////MACE
	case(Resources::FoodType::MashedTomato):
		f = new SlicedTomato(pos, tP1, tP2); ///Esto est� puesto para que no queje de que no se inicializa
		//f = new MashedTomato(pos);
		break;
	case(Resources::FoodType::MashedMeat):
		f = new MashedMeat(pos, tP1, tP2);
		break;
	case(Resources::FoodType::MashedMushroom):
		f = new MashedMushroom(pos, tP1, tP2);
		break;
	
		///////////////GRATER
	case(Resources::FoodType::GratedCheese):
		f = new GratedCheese(pos, tP1, tP2);
		break;

		///////////////NET
	case(Resources::FoodType::CaughtClam):
		f = new CaughtClam(pos, tP1, tP2);
		break;
	case(Resources::FoodType::CaughtFish):
		f = new CaughtFish(pos, tP1, tP2);
		break;
	case(Resources::FoodType::CaughtSausage):
		f = new CaughtSausage(pos, tP1, tP2);
		break;
	
		//////////////EMPTY
	default:
		f = new SlicedTomato(pos, tP1, tP2); // Para que no queje
		break;
	}
	foodPool->AddFood(f);
	f->onDrop(true);
	return f;
}

