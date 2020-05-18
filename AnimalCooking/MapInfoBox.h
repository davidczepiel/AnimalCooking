#pragma once
#include "Component.h"
#include "SDL_macros.h"
#include "MapConfig.h"

class MapInfoBox :public Component {
public:
	MapInfoBox(double cX, double cY);
	virtual void init()override;
	virtual void draw()override;

	inline void setCurrentInfoLevel(levelInfo info) {info_ = info;}

private:
	levelInfo info_;
	Texture* boxText_;
	Texture* gotStar_;
	Texture* notGotStar_;

	double casillaX_;
	double casillaY_;
};
