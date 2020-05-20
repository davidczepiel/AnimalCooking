#pragma once
#include "Component.h"

class MapLevel;

class MapLevelViewer :	public Component{
public:
	MapLevelViewer();
	~MapLevelViewer();
	void init() override;
	void update() override;
	void draw() override;

private:
	vector<MapLevel*> mapPool_;
};

