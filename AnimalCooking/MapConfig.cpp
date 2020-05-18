#include "MapConfig.h"

MapConfig::MapConfig()
{
	fill();
}
/*string name = "";
	string lore = "";	
	SDL_Rect houseBox = SDL_Rect();
	Vector2D housePosition = Vector2D();
	Vector2D buttonPosition = Vector2D();
	unsigned int stars = 0;
	bool unlocked = false;
	*/
void MapConfig::fill()
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
	auxiliar.stars = 0;
	auxiliar.unlocked = false;


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

	  /////////////////////////////////////
	 ///////		 LEVEL N		//////
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
}
