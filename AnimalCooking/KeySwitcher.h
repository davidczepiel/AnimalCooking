#pragma once
#include "Vector2D.h"
#include "SDL.h"

class KeySwitcher
{
public:
	virtual void update() = 0;

	inline void setPos(const Vector2D& Pos) { pos_ = Pos; }
	inline void setSize(const Vector2D& Size) { size_ = Size; }
	const bool& getPlayerIsChoosing() const { return playerIsChoosing_; }
protected:
	KeySwitcher(const Vector2D& pos, const Vector2D& size) :
		playerIsChoosing_(false),
		pos_(pos), size_(size) {}

	bool playerIsChoosing_;

	Vector2D pos_, size_;
};

