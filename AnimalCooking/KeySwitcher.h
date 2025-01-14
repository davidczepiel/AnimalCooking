#pragma once
#include "Vector2D.h"
#include "SDL.h"
#include "Texture.h"
#include "SDLGame.h"

class KeySwitcher
{
public:
	inline void setPos(const Vector2D& Pos) { pos_ = Pos; }
	inline void setSize(const Vector2D& Size) { size_ = Size; }
	inline void setBackGroundTexture(Texture* t) { backGround_ = t; }

	const bool& getPlayerIsChoosing() const { return playerIsChoosing_; }

	virtual void update() = 0;
	virtual void draw() = 0;
protected:
	KeySwitcher(const Vector2D& pos, const Vector2D& size, const Resources::TextureId& name) :
		playerIsChoosing_(false), name_(SDLGame::instance()->getTextureMngr()->getTexture(name)),
		pos_(pos), size_(size), backGround_(nullptr), timeClicked_(), timeClickedCD_(70), col(1) {}
	bool playerIsChoosing_;

	Texture* name_;
	Vector2D pos_, size_;
	Texture* backGround_;
	Uint32 timeClicked_, timeClickedCD_;
	size_t col;
};

