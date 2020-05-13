#pragma once
#include "Component.h"
#include "Texture.h"
#include "Transform.h"
#include "Entity.h"
#include "Animator.h"

class PlayerViewer : public Component {
public:
	PlayerViewer(Texture* idle, Texture* walk, Texture* attack, EntityManager* em_, Entity* p_) : Component(ecs::PlayerViewer), idleSpritesheet_(idle), walkSpritesheet_(walk), attackSpritesheet_(attack), em(em_), player(p_) {};
	PlayerViewer(Texture* idle, Texture* walk, Texture* attack) : Component(ecs::PlayerViewer), idleSpritesheet_(idle), walkSpritesheet_(walk), attackSpritesheet_(attack) {};
	void init() override;
	void update()override;
	void draw() override;
private:
	Texture* idleSpritesheet_ = nullptr;
	Texture* walkSpritesheet_ = nullptr;
	Texture* attackSpritesheet_ = nullptr;
	Transform* tr_ = nullptr;
	Animator* animator = nullptr;
	EntityManager* em = nullptr;
	Entity* player = nullptr;

	void setWalkOrAttack(SDL_Rect dest,Texture* spriteSheet,int fil1,int fil2);
	void setIdle(SDL_Rect dest,int fil1,int fil2);
};

