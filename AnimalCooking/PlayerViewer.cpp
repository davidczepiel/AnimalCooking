#pragma once
#include "PlayerViewer.h"
#include "GameConfig.h"

void PlayerViewer::init()
{	
	tr_ = GETCMP1_(Transform);
	animator = GETCMP1_(Animator);
}

void PlayerViewer::draw()
{
	SDL_Rect dest = {tr_->getPos().getX(),tr_->getPos().getY(),tr_->getW(),tr_->getH()};

	// int(((game_->getTime() / animator->getAnimSpeed()) % 6)) --> usarlo como parametro 

	
	switch (animator->getCurrentState())
	{
	case Animator::States::Idle:
        idleSpritesheet_->renderFrame(dest,0, int(((game_->getTime() / config::ANIM_SPEED) % idleSpritesheet_->getNumCols())),0);
		break;
	case Animator::States::IdleWithKnife:
		idleSpritesheet_->renderFrame(dest, 2, int(((game_->getTime() / config::ANIM_SPEED) % idleSpritesheet_->getNumCols())), 0);
		break;
	case Animator::States::IdleWithMace:
		idleSpritesheet_->renderFrame(dest, 4, int(((game_->getTime() / config::ANIM_SPEED) % idleSpritesheet_->getNumCols())), 0);
		break;
	case Animator::States::IdleWithNet:
		idleSpritesheet_->renderFrame(dest, 8, int(((game_->getTime() / config::ANIM_SPEED) % idleSpritesheet_->getNumCols())), 0);
		break;
	case Animator::States::IdleWithGrater:
		idleSpritesheet_->renderFrame(dest, 2, int(((game_->getTime() / config::ANIM_SPEED) % idleSpritesheet_->getNumCols())), 0);
		break;
	case Animator::States::IdleWithDish:
		idleSpritesheet_->renderFrame(dest, 6, int(((game_->getTime() / config::ANIM_SPEED) % idleSpritesheet_->getNumCols())), 0);
		break;

	case Animator::States::Walk:
		walkSpritesheet_->renderFrame(dest, 0, int(((game_->getTime() / config::ANIM_SPEED) % walkSpritesheet_->getNumCols())), 0);
		break;
	case Animator::States::WalkWithKnife:
		walkSpritesheet_->renderFrame(dest, 2, int(((game_->getTime() / config::ANIM_SPEED) % walkSpritesheet_->getNumCols())), 0);
		break;
	case Animator::States::WalkWithMace:
		walkSpritesheet_->renderFrame(dest, 4, int(((game_->getTime() / config::ANIM_SPEED) % walkSpritesheet_->getNumCols())), 0);
		break;
	case Animator::States::WalkWithNet:
		walkSpritesheet_->renderFrame(dest, 8, int(((game_->getTime() / config::ANIM_SPEED) % walkSpritesheet_->getNumCols())), 0);
		break;
	case Animator::States::WalkWithGrater:
		walkSpritesheet_->renderFrame(dest, 0, int(((game_->getTime() / config::ANIM_SPEED) % walkSpritesheet_->getNumCols())), 0);
		break;
	case Animator::States::WalkWithDish:
		walkSpritesheet_->renderFrame(dest, 6, int(((game_->getTime() / config::ANIM_SPEED) % walkSpritesheet_->getNumCols())), 0);
		break;


	default:
		break;
	}

	
}
