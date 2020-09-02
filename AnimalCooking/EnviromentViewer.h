#pragma once
#include "Component.h"
#include "EnviromentPool.h"
#include "EnviromentUnit.h"

class EnviromentViewer :
	public Component
{
public:

	EnviromentViewer(EnviromentPool* envPool);
	virtual ~EnviromentViewer() { }

	void init() override;
	void draw() override;
private:
	vector<EnviromentUnit*>* pool_;
};

