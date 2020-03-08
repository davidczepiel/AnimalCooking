#pragma once
#include "Component.h"
#include "Entity.h"
#include "Cooker.h"

class CookerPool: public Component {
public:
	CookerPool(size_t sizeIni = 5);
	~CookerPool();
	void update() override;
	void draw() override;

	template<typename C, typename ...Targs>
	C* addCooker(Targs&& ...mArgs) {
		assert(cookers.size() < cookers.capacity());
		C* c(new C(std::forward<Targs>(mArgs)...));
		cookers.emplace_back(c);
	}
	Cooker* addCooker(Cooker* c) {
		assert(cookers.size() < cookers.capacity());
		cookers.emplace_back(c);
	}

private:
	vector<Cooker*> cookers;
};