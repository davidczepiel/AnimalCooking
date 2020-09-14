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
		index_ = (index_ + 1) % images_.size();
	}
	inline void goLeft() { 
		index_ = (index_ + images_.size() - 1) % images_.size(); 
	}
	inline void go(size_t n) { index_ = n % images_.size(); }

private:
	SDL_Rect rect_;
	Texture* background_;
	vector<Texture*> images_;
	size_t index_;
};

