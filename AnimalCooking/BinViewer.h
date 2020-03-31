#pragma once
#include "Component.h"
#include "Texture.h"
#include "Interactive.h"

class BinViewer : public Component
{
public:
	BinViewer(Interactive* e) : Component(ecs::BinViewer), tex_(nullptr), binEnt_(e){}
	~BinViewer() {}

	void init() override;
	void draw() override;
private:
	Texture* tex_;
	Interactive* binEnt_;
};

