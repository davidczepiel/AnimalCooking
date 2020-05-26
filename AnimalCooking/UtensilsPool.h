#pragma once
#include "Component.h"
#include "ObjectPool.h"
#include "Utensil.h"
class UtensilsPool: public Component
{
public:
	UtensilsPool(size_t size=4);
	~UtensilsPool();

	vector<Utensil*>& getPool() { return pool_; }

	Utensil* addUtensil(Utensil* u) {
		assert(pool_.size() < pool_.capacity());
		pool_.emplace_back(u);
		return u;
	}
	template<typename T, typename ...Targs>
	T* addUtensil(Targs&& ...mArgs) {
		assert(pool_.size() < pool_.capacity());
		T* t(new T(std::forward<Targs>(mArgs)...));
		pool_.emplace_back(t);
		return t;
	}
	void SetGameLogic(GameLogic* gl);
private:
	vector<Utensil*> pool_;
};

