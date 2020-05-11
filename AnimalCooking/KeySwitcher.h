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
	KeySwitcher(const Vector2D& pos, const Vector2D& size) :
		playerIsChoosing_(false),
		pos_(pos), size_(size), backGround_(nullptr) {}

	bool playerIsChoosing_;

	Vector2D pos_, size_;
	Texture* backGround_;
};

