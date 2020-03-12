#pragma once
#include "Component.h"
#include "CookerPool.h"

class InsertExpel: public Component {
public:
	InsertExpel();
	~InsertExpel();
	void init() override;
	void update() override;

private:
	
};