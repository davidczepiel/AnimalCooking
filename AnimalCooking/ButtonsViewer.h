#pragma once
#include "Component.h"
class ButtonsViewer : public Component
{
private:
	vector<Entity*>* buttonsToRender;
public:
	ButtonsViewer();
	void init() override;
	void draw() override;
};

