#pragma once
#include "Vector2D.h"
#include <SDL_stdinc.h>
#include "Texture.h"
#include "Timer.h"

enum class CookerStates { empty, cooking, cooked, burned };
class Food;
class Cooker {
public:
	virtual ~Cooker();
	virtual void draw();

	void setPos(Vector2D& pos) { pos_.set(pos); }
	void setSize(Vector2D& size) { size_.set(size); }
	void setRot(double rot) { rot_ = rot; }
	void setTexture(Texture* text) { texture_ = text; }
	void setCookerState(CookerStates s) { state_ = s; };

	inline const Vector2D& getPos() const { return pos_; }
	inline int getWidth() const { return size_.getX(); }
	inline int getHeight() const { return size_.getY(); }
	inline Vector2D& getSize() { return size_; }
	inline CookerStates getCookerState() { return state_; };
	Texture* getEmptyTexture() { return nullptr; };
	Texture* getFullTexture() { return nullptr; };
	Texture* getCookingTexture() { return nullptr; };
	Texture* getCookedTexture() { return nullptr; };
	Timer* getCookerTimer() { return timer_; };
	Uint32 getCookingTime() { return cookingTime_; }
	vector<Food*>& getFoods() { return foods_; }

	inline int getCookerType() { return (int) cookerType_; };

protected:
	Cooker(Vector2D& pos, Vector2D& size, double rot, Texture* text);

	Vector2D pos_;
	Vector2D size_;
	double rot_;

	Texture* texture_;

	CookerStates state_;

	Timer* timer_;
	Uint32 cookingTime_;

	vector<Food*> foods_;
    Resources::Cookers cookerType_;
};

class Oven : public Cooker {
public:
	Oven(Vector2D& pos, Vector2D& size, double rot, Texture* text);
};

class Skillet : public Cooker {
public:
	Skillet(Vector2D& pos, Vector2D& size, double rot, Texture* text);
};