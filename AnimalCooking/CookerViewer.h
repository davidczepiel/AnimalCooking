#pragma once
#include "Component.h"
#include "CookerPool.h"
#include "Cooker.h"

class CookerViewer : public Component {
public:
	CookerViewer();
	virtual ~CookerViewer();
	void init() override;
	void draw() override;

private:
	vector<Cooker*> pool_;
};