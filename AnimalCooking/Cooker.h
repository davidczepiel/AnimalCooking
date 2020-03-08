#pragma once
//#include "Food.h"
#include "Vector2D.h"
#include <SDL_stdinc.h>
#include "Texture.h"

enum class CookerStates { empty, full, burning, cooking, cooked, burned };

class Food;
class Cooker {
public:
	virtual ~Cooker() {}
	virtual void update();
	virtual void draw();
	virtual void startCooking(Food* food);

	void setPos(Vector2D& pos) { pos_.set(pos); }
	void setSize(Vector2D& size) { size_.set(size); }
	void setRot(double rot) { rot_ = rot; }
	void setTexture(Texture* text) { texture_ = text; }
	void setCookerState(CookerStates s) { state_ = s; };

	Food* getCooking();
	inline const Vector2D& getPos() const { return pos_; }
	inline int getWidth() const { return size_.getX(); }
	inline int getHeight() const { return size_.getY(); }
	inline Vector2D& getSize() { return size_; }
	CookerStates getCookerState() { return state_; };

protected:
	Cooker(Vector2D& pos, Vector2D& size, double rot, Texture* text);
	void stopCooking();

	Vector2D pos_;
	Vector2D size_;
	double rot_;

	Texture* texture_;

	Food* imCooking;
	Food* imBurning;
	Uint32 startTime;
	Uint32 cookingTime;
	Uint32 burningTime;
	bool isBurned;

	CookerStates state_;
};

class Sarten : public Cooker {
public:
	Sarten(Vector2D& pos, Vector2D& size, double rot, Texture* text);
};