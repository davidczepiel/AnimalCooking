#pragma once
#include "Component.h"
#include "Texture.h"
#include "Transform.h"
#include "Entity.h"
#include "Animator.h"
#include "Transport.h"

class PlayerViewer : public Component {
public:
	PlayerViewer(Texture* idle, Texture* walk, Texture* attack, EntityManager* em_, Entity* p_) : Component(ecs::PlayerViewer), idleSpritesheet_(idle), walkSpritesheet_(walk), attackSpritesheet_(attack), em(em_), player(p_) { tp = player->getComponent<Transport>(ecs::Transport); }
	PlayerViewer(Texture* idle, Texture* walk, Texture* attack) : Component(ecs::PlayerViewer), idleSpritesheet_(idle), walkSpritesheet_(walk), attackSpritesheet_(attack) {};
	~PlayerViewer() {}

	void init() override;
	void update()override;
	void draw() override;
private:
	void setWalkOrAttack(SDL_Rect dest,Texture* spriteSheet,int fil1,int fil2);
	void setIdle(SDL_Rect dest,int fil1,int fil2);
	void swapLayer(ecs::GroupID id1, ecs::GroupID id2);

	Texture* idleSpritesheet_ = nullptr;
	Texture* walkSpritesheet_ = nullptr;
	Texture* attackSpritesheet_ = nullptr;
	Transform* tr_ = nullptr;
	Animator* animator = nullptr;
	EntityManager* em = nullptr;
	Entity* player = nullptr;
	Transport* tp = nullptr;
};

