#pragma once
#include "Component.h"
class ScoreViewer : public Component
{
public:
	ScoreViewer();
	void init() override;
	void draw() override;
};

