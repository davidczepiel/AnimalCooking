#pragma once
#include "Component.h"
#include <vector>
class ButtonDirector : public Component
{
private:
	vector<Entity*> buttons_;
public:
	ButtonDirector();

	void update() override;

	void addButton(Entity* button);
	void clearButons();
	vector<Entity*>* getButtons() { return &buttons_; }
};

