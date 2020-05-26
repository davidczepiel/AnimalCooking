#pragma once
#include "Component.h"
#include"Texture.h"
#include <vector>
#include"SDLGame.h"
#include"SDL_macros.h"
#include"GameConfig.h"
using namespace std;
class CreditsViewer :
	public Component
{
public:
	CreditsViewer() :Component(ecs::CreditsViewer), tenByTenLogo(), names(vector<VisualNames>(10)), game_(SDLGame::instance()) {}
	virtual void init()override;
	virtual void update()override;
	virtual void draw()override;
	void initializeNames();
private:
	struct VisualNames
	{
		Texture* name;
		Vector2D pos;
	};
	vector<VisualNames> names;
	Texture* tenByTenLogo;
	Vector2D logoPos;
	SDLGame* game_;
};

