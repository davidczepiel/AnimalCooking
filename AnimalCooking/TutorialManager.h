#pragma once
#include "Component.h"
#include <list>

class TutorialManager : public Component
{
public:
	TutorialManager() : Component(ecs::TutorialManager), rect_(), background_(nullptr), images_(), index_() {}

	void init() override;
	void draw() override;

	inline void goRight() { 
		++index_; 
		if (index_ == images_.end()) index_ = images_.begin();
	}
	inline void goLeft() { 
		if (index_ == images_.begin()) index_ = --images_.end();
		--index_; 
	}

private:
	SDL_Rect rect_;
	Texture* background_;
	list<Texture*> images_;
	list<Texture*>::iterator index_;
};

