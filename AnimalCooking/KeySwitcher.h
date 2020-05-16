#pragma once
#include "Vector2D.h"
#include "SDL.h"
#include "Texture.h"

class KeySwitcher
{
public:
	virtual void update() = 0;
	virtual void draw() = 0;

	inline void setPos(const Vector2D& Pos) { pos_ = Pos; }
	inline void setSize(const Vector2D& Size) { size_ = Size; }
	const bool& getPlayerIsChoosing() const { return playerIsChoosing_; }

	inline void setBackGroundTexture(Texture* t) { backGround_ = t; }
protected:
	KeySwitcher(const Vector2D& pos, const Vector2D& size, const string& name) :
		playerIsChoosing_(false), name_(name),
		pos_(pos), size_(size), backGround_(nullptr), timeClicked_(), timeClickedCD_(70), col(1) {}
	bool playerIsChoosing_;

	string name_;
	Vector2D pos_, size_;
	Texture* backGround_;
	Uint32 timeClicked_, timeClickedCD_;
	size_t col;
};

