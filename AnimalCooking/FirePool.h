#pragma once
#include "Component.h"
#include "Transform.h"
#include "CollisionsSystem.h"
#include "SDL_macros.h"

class GameLogic;

using namespace std;

struct Fire {
	Fire(int frame_, bool active_, Uint32 lastAnimTick_) : tr(new Transform()) {
		frame = frame_;
		active = active_;
		lastAnimTick = lastAnimTick_;
		rect = SDL_Rect();
		tr->setPos(Vector2D(rect.x, rect.y));
		tr->setWH(rect.w, rect.h);
		id = -1;
		extinguish = false;
	}

	SDL_Rect rect;
	Transform* tr;
	int frame;
	bool active;
	Uint32 lastAnimTick;
	int id;
	bool extinguish;
};

class FirePool : public Component
{
public:
	FirePool(CollisionsSystem* collSys, GameLogic* gameLgc) :
		Component(ecs::FirePool),
		cs_(collSys),
		gl_(gameLgc),
		fireTexture(SDLGame::instance()->getTextureMngr()->getTexture(Resources::FireOverHeated)),
		smokeTexture(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)), //poner animacion de humo aqui
		animationFrameRate_(100),
		animationFrameRateExt_(100),
		poolFires_(20),
		idCount(0),
		activeFires(0)
		{
			for (int i = 0; i < poolFires_; ++i) {
				fires_.push_back(new Fire(SDLGame::instance()->getRandGen()->nextInt(0, 3), false, 0));
			}
		}
	~FirePool() {
		for (int i = 0; i < fires_.size(); ++i) {
			delete fires_[i];
		}
	}

	inline const std::vector<Fire*>& getPool() { return fires_; }

	void spawnFlare(SDL_Rect rect_) {
		activateSingleFire(RECT(rect_.x, rect_.y + rect_.h - 64, 64 * 2, 64 * 2), idCount, true);
		activateSingleFire(RECT(rect_.x, rect_.y + rect_.h, 64, 64), idCount);
		activateSingleFire(RECT(rect_.x + 64, rect_.y + rect_.h, 64, 64), idCount);
		idCount = (idCount + 1) % poolFires_;
	}

	Fire* activateSingleFire(SDL_Rect rect_, int id_, bool hitbox = false);

	void desactivateFire(int id_) {
		for (Fire* f : fires_) {
			if (f->id == id_ && f->active && !f->extinguish) {
				f->extinguish = true;
				f->frame = 0;
				f->lastAnimTick = SDL_GetTicks();

				if(activeFires == 1) SDLGame::instance()->getAudioMngr()->haltChannel(4);
				activeFires--;
				cout << activeFires << endl;
				cs_->removeCollider(f->tr);
			}
		}
	}

	void update() override {
		for (Fire* f : fires_) {
			if (f->active) {
				if (!f->extinguish && (SDL_GetTicks() - f->lastAnimTick >= animationFrameRate_)) {
					f->lastAnimTick = SDL_GetTicks();
					f->frame++;
					if (f->frame >= fireTexture->getNumCols()) f->frame = 0;
				}
				else if (f->extinguish && (SDL_GetTicks() - f->lastAnimTick >= animationFrameRateExt_)) {
					f->lastAnimTick = SDL_GetTicks();
					f->frame++;
					if (f->frame >= smokeTexture->getNumCols()) f->active = false;
				}
			}
		}
	}

	void draw() override {
		for (Fire* f : fires_) {
			if (f->active) {
				fireTexture->renderFrame(f->rect, 0, f->frame, 0);
				if (f->extinguish) smokeTexture->renderFrame(f->rect, 0, f->frame, 0);
			}
		}
	}
private:
	CollisionsSystem* cs_;
	GameLogic* gl_;

	Texture* fireTexture;
	Texture* smokeTexture;
	std::vector<Fire*> fires_;
	int animationFrameRate_;
	int animationFrameRateExt_;
	int poolFires_, activeFires;

	int idCount;
};

