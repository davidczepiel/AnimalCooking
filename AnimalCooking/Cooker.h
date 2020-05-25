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
class Cooker:public Interactive {
public:
	virtual ~Cooker();
	virtual void draw();

	void setCookerState(CookerStates s);
	inline CookerStates getCookerState() { return state_; };

	virtual void setEmptyTexture() = 0;
	virtual void setBurnedTexture() = 0;
	virtual void setCookingTexture() = 0;
	virtual void setOverHeatedTexture() = 0;

	Timer* getCookerTimer() { return timer_; };
	Uint32 getCookingTime() { return cookingTime_; }
	vector<Food*>& getFoods() { return foods_; }

	inline int getCookerType() { return (int) cookerType_; };
	void action1(int player)override;
	void feedback(int player) override;
	void sound();

protected:
	Cooker(Vector2D& pos, Vector2D& size, double rot, Texture* text,Transport* t1,Transport* t2,Entity* e);

	void initTimer();

	Texture* texture_;
	Texture* smokeTexture_;
	Texture* fireTexture_;
	Entity* entity_;
	CookerStates state_;

	CookerTimer* timer_;
	Uint32 cookingTime_;
	Uint32 lastTimeSound_;

	vector<Food*> foods_;
	Resources::Cookers cookerType_;
};

class Oven : public Cooker {
public:
	Oven(Vector2D& pos, Vector2D& size, double rot, Texture* text, Transport* t1, Transport* t2, Entity* e);

	virtual void setEmptyTexture() override { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OvenOFF); };
	virtual void setBurnedTexture() override { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OvenON); };
	virtual void setCookingTexture() override { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OvenON); };
	virtual void setOverHeatedTexture() override { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OvenOFF); };
};

class Skillet : public Cooker {
public:
	Skillet(Vector2D& pos, Vector2D& size, double rot, Texture* text, Transport* t1, Transport* t2, Entity* e);

	virtual void setEmptyTexture() override { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletOFF); };
	virtual void setBurnedTexture() override { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletON); };
	virtual void setCookingTexture() override { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletON); };
	virtual void setOverHeatedTexture() override { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OvenOFF); };
};