#pragma once

#include "Component.h"
#include "Texture.h"
class PlayerViewer : public Component {
public:
	PlayerViewer() : Component(ecs::PlayerViewer) {};
	void update() override;
private:
	Texture* tr_ = nullptr;
};

