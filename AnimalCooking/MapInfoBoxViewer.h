#pragma once
#include "Component.h"
#include "MapConfig.h"
class MapInfoBoxViewer :public Component{
public:
	MapInfoBoxViewer(double cX, double cY);
	~MapInfoBoxViewer();
	void init() override;
	void draw() override;

	inline void setCurrentInfoLevel(levelInfo info) { info_ = info; }

private:
	levelInfo info_;
	Texture* boxText_;
	Texture* gotStar_;
	Texture* notGotStar_;

	double casillaX_;
	double casillaY_;
};

