#pragma once
#include "Vector2D.h"
#include <SDL_stdinc.h>
#include "Texture.h"
#include "Timer.h"
#include "Interactive.h"
#include "Entity.h"

enum class CookerStates { empty, cooking, cooked, burned };
class Food;
class InsertExpel;
class Cooker:public Interactive {
public:
	virtual ~Cooker();
	virtual void draw();

	void setCookerState(CookerStates s);

	inline CookerStates getCookerState() { return state_; };
	inline void setEmptyTexture() { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cooker); };
	inline void setBurnedTexture() { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CookerBurned); };
	inline void setCookingTexture() { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CookerCooking); };
	inline void setCookedTexture() { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CookerCooked); };
	Timer* getCookerTimer() { return timer_; };
	Uint32 getCookingTime() { return cookingTime_; }
	vector<Food*>& getFoods() { return foods_; }

	inline int getCookerType() { return (int) cookerType_; };
	void action1(int player)override;
	void feedback(int player) override;

protected:
	Cooker(Vector2D& pos, Vector2D& size, double rot, Texture* text,Transport* t1,Transport* t2,Entity* e);

	void initTimer();

	Texture* texture_;
	Entity* entity_;
	CookerStates state_;

	CookerTimer* timer_;
	Uint32 cookingTime_;

	vector<Food*> foods_;
	Resources::Cookers cookerType_;
};

class Oven : public Cooker {
public:
	Oven(Vector2D& pos, Vector2D& size, double rot, Texture* text, Transport* t1, Transport* t2, Entity* e);
};

class Skillet : public Cooker {
public:
	Skillet(Vector2D& pos, Vector2D& size, double rot, Texture* text, Transport* t1, Transport* t2, Entity* e);
};