#pragma once

#include "Component.h"
#include "Utensil.h"
#include "UtensilsPool.h"
#include "IngredientsPool.h"
#include "GameControl.h"
#include "CollisionsSystem.h"
#include "TimerViewer.h"
#include "FirePool.h"

class GameLogic : public Component
{
public:
	GameLogic(TimerViewer* Tv);
	~GameLogic() {}
	void init() override;
	virtual void update() override { levelTimer_->update(); }

	void setIngredientPool(IngredientsPool* p) { ingPool = p; }
	void setUtensilsPool(UtensilsPool* u) { utensilPool = u; utensilPool->SetGameLogic(this); }
	void setLevelTimer(Uint32 time, Vector2D pos, Vector2D size);
	void setFirePool(FirePool* fp) { firePool_ = fp; }

	void hitIngredient(SDL_Rect rect, Resources::UtensilType type);
	void hitFire(SDL_Rect rect);

	int getLevelTime() { return levelTimer_->getTime(); }

private:
	void playHit(Resources::UtensilType type);

	CollisionsSystem* colSys_;
	IngredientsPool* ingPool;
	FoodPool* foodPool;
	UtensilsPool* utensilPool;
	TimerViewer* tv;
	LevelTimer* levelTimer_;
	FirePool* firePool_;
};
