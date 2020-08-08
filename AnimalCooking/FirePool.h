#pragma once
#include "Component.h"
#include "Transform.h"
#include "CollisionsSystem.h"
#include "SDL_macros.h"

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
	}

	SDL_Rect rect;
	Transform* tr;
	int frame;
	bool active;
	Uint32 lastAnimTick;
	int id;
};

class FirePool : public Component
{
public:
	FirePool(CollisionsSystem* collSys) :
		Component(ecs::FirePool),
		cs_(collSys),
		fireTexture(SDLGame::instance()->getTextureMngr()->getTexture(Resources::FireOverHeated)),
		animationFrameRate_(100),
		poolFires_(20),
		idCount(0)
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

	Fire* activateSingleFire(SDL_Rect rect_, int id_, bool hitbox = false) {
		int i = 0;
		while (i < fires_.size() && fires_[i]->active) i++;

		if (i >= fires_.size()) return nullptr;

		fires_[i]->rect = rect_;
		fires_[i]->tr->setPos(Vector2D(rect_.x, rect_.y));
		fires_[i]->tr->setWH(rect_.w, rect_.h);
		fires_[i]->tr->setHitboxSize(Vector2D(rect_.w - 10, rect_.h - 10));
		fires_[i]->active = true;
		fires_[i]->id = id_;
		if(hitbox) cs_->addCollider(fires_[i]->tr, false);

		return fires_[i];
	}

	void desactivateFire(int id_) {
		for (Fire* f : fires_) {
			if (f->id == id_) {
				f->active = false;
				cs_->removeCollider(f->tr);
			}
		}
	}

	void update() override {
		for (Fire* f : fires_) {
			if (f->active && (SDL_GetTicks() - f->lastAnimTick >= animationFrameRate_)) {
				f->lastAnimTick = SDL_GetTicks();
				f->frame++;
				if(f->frame >= 3) f->frame = 0;
			}
		}
	}

	void draw() override {
		for (Fire* f : fires_) {
			if (f->active) 
				fireTexture->renderFrame(f->rect, 0, f->frame, 0);
		}
	}
private:
	CollisionsSystem* cs_;

	Texture* fireTexture;
	std::vector<Fire*> fires_;
	int animationFrameRate_;
	int poolFires_;

	int idCount;
};

