#pragma once
#include "Component.h"
#include "Entity.h"
#include "Cooker.h"

class CookerPool: public Component {
public:
	CookerPool(size_t sizeIni = 5);
	~CookerPool();
	void update() override;

	vector <Cooker*> getPool() { return pool_; };
	//void draw() override;

	template<typename C, typename ...Targs>
	C* addCooker(Targs&& ...mArgs) {
		assert(pool_.size() < pool_.capacity());
		C* c(new C(std::forward<Targs>(mArgs)...));
		pool_.emplace_back(c);
	}
	Cooker* addCooker(Cooker* c) {
		assert(pool_.size() < pool_.capacity());
		pool_.emplace_back(c);
	}

private:
	vector<Cooker*> pool_;
};