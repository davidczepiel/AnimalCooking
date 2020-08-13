#pragma once
#include "Component.h"
#include "MapConfig.h"
#include "SDL_macros.h"
#include "Transform.h"
class MapInfoBoxViewer :public Component{
public:
	MapInfoBoxViewer(Transform* buttonT);
	~MapInfoBoxViewer();
	void init() override;
	void draw() override;

	inline void setCurrentInfoLevel(levelInfo* info) { info_ = info; }
	inline void setActive(bool b) { active = b; }

private:
	levelInfo* info_;
	Texture* boxText_;
	Texture* gotStar_;
	Texture* notGotStar_;

	Transform* buttonT;

	double casillaX_;
	double casillaY_;
	bool active;
};

