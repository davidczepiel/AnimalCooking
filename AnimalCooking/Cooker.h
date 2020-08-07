#pragma once
#include "Vector2D.h"
#include <SDL_stdinc.h>
#include "Texture.h"
#include "Timer.h"
#include "Interactive.h"
#include "Entity.h"

enum class CookerStates { empty, cooking, cooked, burned, overheated };
class Food;
class InsertExpel;
class Cooker :public Interactive {
public:
	virtual ~Cooker();
	virtual void draw();
	void action1(int player)override;
	void feedback(int player) override;
	void sound();

	void setCookerState(CookerStates s);
	inline CookerStates getCookerState() { return state_; };

	virtual void setEmptyTexture() = 0;
	virtual void setBurnedTexture() = 0;
	virtual void setCookingTexture() = 0;
	virtual void setOverHeatedTexture() = 0;

	Timer* getCookerTimer() { return timer_; };
	Uint32 getCookingTime() { return cookingTime_; }
	vector<Food*>& getFoods() { return foods_; }

	inline int getCookerType() { return (int)cookerType_; };

protected:
	Cooker(Vector2D& pos, Vector2D& size, double rot, Texture* text, Transport* t1, Transport* t2, Entity* e,string textureState);
	void initTimer();

	Texture* texture_;
	Texture* smokeTexture_;
	Texture* fireTexture_;
	Entity* entity_;
	CookerTimer* timer_;
	vector<Food*> foods_;
	CookerStates state_;
	Uint32 cookingTime_;
	Uint32 lastTimeSound_;
	Resources::Cookers cookerType_;
	string textureState;
};

class Oven : public Cooker {
public:
	Oven(Vector2D& pos, Vector2D& size, double rot, Texture* text, Transport* t1, Transport* t2, Entity* e, string textureState_);

	virtual void setEmptyTexture() override { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OvenOFF); };
	virtual void setBurnedTexture() override { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OvenON); };
	virtual void setCookingTexture() override { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OvenON); };
	virtual void setOverHeatedTexture() override { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OvenOFF); };
};

class Skillet : public Cooker {
public:
	Skillet(Vector2D& pos, Vector2D& size, double rot, Texture* text, Transport* t1, Transport* t2, Entity* e, string textureState_);

	virtual void setEmptyTexture() override 
	{ 
		if(textureState=="corner")texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletOFFEsquina);
		else texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletOFF);
	};

	virtual void setBurnedTexture() override 
	{ 
		if (textureState == "corner")texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletONEsquina);
		else texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletON); 
	};

	virtual void setCookingTexture() override 
	{ 
		if (textureState == "corner")texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletONEsquina);
		else texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletON); 
	};

	virtual void setOverHeatedTexture() override { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OvenOFF); };
};