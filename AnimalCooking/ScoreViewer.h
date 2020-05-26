#pragma once
#include "Component.h"
#include "ScoreManager.h"
class ScoreViewer : public Component
{
public:
	ScoreViewer() : Component(ecs::ScoreViewer), scoreManager_(nullptr) {}
	void init() override;
	void draw() override;

	void setPos(Vector2D pos) { pos_ = pos; }

private:
	ScoreManager* scoreManager_;
	Vector2D pos_;
};

