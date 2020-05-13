#pragma once
#include "PlayerViewer.h"
#include "GameConfig.h"

void PlayerViewer::init()
{	
	tr_ = GETCMP1_(Transform);
	animator = GETCMP1_(Animator);		
}

void PlayerViewer::update()
{	
	if (player != nullptr && em != nullptr)
	{
		if (animator->getDir().getY() > 0)
		{
			if (em->getGroups()[ecs::GroupID::PlayerLayer].size() > 0)
			{
				em->getGroups()[ecs::GroupID::PlayerLayer].remove(player);
				em->getGroups()[ecs::GroupID::PlayerLayerAux].push_back(player);
			}
		}
		else if (animator->getDir().getY() < 0)
		{
			if (em->getGroups()[ecs::GroupID::PlayerLayerAux].size() > 0)
			{
				em->getGroups()[ecs::GroupID::PlayerLayerAux].remove(player);
				em->getGroups()[ecs::GroupID::PlayerLayer].push_back(player);
			}
		}
		else
		{
			if (em->getGroups()[ecs::GroupID::PlayerLayer].size() > 0)
			{
				em->getGroups()[ecs::GroupID::PlayerLayer].remove(player);
				em->getGroups()[ecs::GroupID::PlayerLayerAux].push_back(player);
			}
		}
	}
}

void PlayerViewer::setIdle(SDL_Rect dest,int fil1,int fil2)
{	
	if ((animator->getDir().getX() > 0 && animator->getDir().getY() == 0) || (animator->getDir().getY() > 0 && animator->getDir().getX() > 0) || ((animator->getDir().getY() > 0 && animator->getDir().getX() == 0)) || (animator->getDir().getX() == 0 && animator->getDir().getY() == 0)) idleSpritesheet_->renderFrame(dest, fil1, int(((game_->getTime() / config::ANIM_SPEED) % idleSpritesheet_->getNumCols())), 0);
	else if ((animator->getDir().getX() < 0 && animator->getDir().getY() == 0) || (animator->getDir().getY() > 0 && animator->getDir().getX() < 0))  idleSpritesheet_->renderFrame(dest, fil1, int(((game_->getTime() / config::ANIM_SPEED) % idleSpritesheet_->getNumCols())), 0, SDL_FLIP_HORIZONTAL);
	else if ((animator->getDir().getY() < 0 && animator->getDir().getX() == 0) || (animator->getDir().getY() < 0 && animator->getDir().getX() > 0)) idleSpritesheet_->renderFrame(dest, fil2, int(((game_->getTime() / config::ANIM_SPEED) % idleSpritesheet_->getNumCols())), 0);
	else if (animator->getDir().getY() < 0 && animator->getDir().getX() < 0)   idleSpritesheet_->renderFrame(dest, fil2, int(((game_->getTime() / config::ANIM_SPEED) % idleSpritesheet_->getNumCols())), 0, SDL_FLIP_HORIZONTAL);
}

void PlayerViewer::setWalkOrAttack(SDL_Rect dest, Texture* spriteSheet,int fil1, int fil2)
{
	if ((animator->getDir().getX() > 0 && animator->getDir().getY() == 0) || (animator->getDir().getY() > 0 && animator->getDir().getX() == 0) || (animator->getDir().getY() > 0 && animator->getDir().getX() > 0)) spriteSheet->renderFrame(dest, fil1, int(((game_->getTime() / config::ANIM_SPEED) % spriteSheet->getNumCols())), 0); 
	else if ((animator->getDir().getX() < 0 && animator->getDir().getY() == 0) || animator->getDir().getY() > 0 && animator->getDir().getX() < 0) spriteSheet->renderFrame(dest, fil1, int(((game_->getTime() / config::ANIM_SPEED) % spriteSheet->getNumCols())), 0, SDL_FLIP_HORIZONTAL);
	else if ((animator->getDir().getY() < 0 && animator->getDir().getX() == 0) || (animator->getDir().getY() < 0 && animator->getDir().getX() > 0)) spriteSheet->renderFrame(dest, fil2, int(((game_->getTime() / config::ANIM_SPEED) % spriteSheet->getNumCols())), 0);
	else if (animator->getDir().getY() < 0 && animator->getDir().getX() < 0) spriteSheet->renderFrame(dest, fil2, int(((game_->getTime() / config::ANIM_SPEED) % spriteSheet->getNumCols())), 0, SDL_FLIP_HORIZONTAL);
}

void PlayerViewer::draw()
{
	SDL_Rect dest = {tr_->getPos().getX(),tr_->getPos().getY(),tr_->getW(),tr_->getH()};

		
	switch (animator->getCurrentState())
	{
	case Animator::States::Idle:
		setIdle(dest, 0, 1);
		break;
	case Animator::States::IdleWithKnife:
		setIdle(dest, 2, 3);
		break;
	case Animator::States::IdleWithMace:
		setIdle(dest, 4, 5);
		break;
	case Animator::States::IdleWithNet:
		setIdle(dest,8,9);
		break;
	case Animator::States::IdleWithGrater:
		setIdle(dest, 11, 12);
		break;
	case Animator::States::IdleWithDishFood:
		setIdle(dest, 6, 7);
		break;
	case Animator::States::IdleWithDirtyKnife:
		setIdle(dest, 14, 15);
		break;
	case Animator::States::IdleWithDirtyMace:
		setIdle(dest, 16, 17);
		break;
	case Animator::States::IdleWithDirtyNet:
		setIdle(dest, 18, 19);
		break;
	case Animator::States::IdleWithDirtyGrater:
		setIdle(dest, 12, 13);
		break;

	case Animator::States::Walk:
		setWalkOrAttack(dest, walkSpritesheet_,0, 1);		
		break;
	case Animator::States::WalkWithKnife:
		setWalkOrAttack(dest, walkSpritesheet_,2,3);
		break;
	case Animator::States::WalkWithMace:
		setWalkOrAttack(dest, walkSpritesheet_, 4, 5);
		break;
	case Animator::States::WalkWithNet:
		setWalkOrAttack(dest, walkSpritesheet_, 8, 9);
		break;
	case Animator::States::WalkWithGrater:
		setWalkOrAttack(dest, walkSpritesheet_,11,12);
		break;
	case Animator::States::WalkWithDishFood:
		setWalkOrAttack(dest, walkSpritesheet_, 6, 7);
		break;
	case Animator::States::WalkWithDirtyKnife:
		setWalkOrAttack(dest, walkSpritesheet_, 14, 15);
		break;
	case Animator::States::WalkWithDirtyMace:
		setWalkOrAttack(dest, walkSpritesheet_, 16, 17);
		break;
	case Animator::States::WalkWithDirtyNet:
		setWalkOrAttack(dest, walkSpritesheet_, 18, 19);
		break;
	case Animator::States::WalkWithDirtyGrater:
		setWalkOrAttack(dest, walkSpritesheet_, 12, 13);
		break;

	case Animator::States::AttackWithKnife:
		setWalkOrAttack(dest,attackSpritesheet_ ,0, 1);
		break;
	case Animator::States::AttackWithMace:
		setWalkOrAttack(dest, attackSpritesheet_, 2, 3);
		break;
	case Animator::States::AttackWithNet:
		setWalkOrAttack(dest, attackSpritesheet_, 4, 5);
		break;
	case Animator::States::AttackWithGrater:
		setWalkOrAttack(dest, attackSpritesheet_, 7, 8);
		break;

	default:
		break;
	}	
}
