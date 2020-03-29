#pragma once
#include "Vector2D.h"
#include <SDL_stdinc.h>
#include "Texture.h"
#include "Timer.h"
#include"Interactive.h"
#include "Entity.h"

enum class CookerStates { empty, cooking, cooked, burned };
class Food;
class InsertExpel;
class Cooker:public Interactive {
public:
	virtual ~Cooker();
	virtual void draw();

	
	void setTexture(Texture* text) { texture_ = text; }
	void setCookerState(CookerStates s) { state_ = s; };


	inline CookerStates getCookerState() { return state_; };
	Texture* getEmptyTexture() { return texture_; };
	Texture* getFullTexture() { return nullptr; };
	Texture* getCookingTexture() { return nullptr; };
	Texture* getCookedTexture() { return nullptr; };
	Timer* getCookerTimer() { return timer_; };
	Uint32 getCookingTime() { return cookingTime_; }
	vector<Food*>& getFoods() { return foods_; }

	inline int getCookerType() { return (int) cookerType_; };
	void action1(int player)override;

protected:
	Cooker(Vector2D& pos, Vector2D& size, double rot, Texture* text,Transport* t1,Transport* t2,Entity* e);

	

	Texture* texture_;
	Entity* entity_;
	CookerStates state_;

	Timer* timer_;
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