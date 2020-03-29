#pragma once
#include "Component.h"
#include "ScoreManager.h"
class ScoreViewer : public Component
{
public:
	ScoreViewer(): Component(ecs::ScoreViewer), scoreManager_(nullptr){}
	void init() override;
	void draw() override;
private:
	ScoreManager* scoreManager_;
};

