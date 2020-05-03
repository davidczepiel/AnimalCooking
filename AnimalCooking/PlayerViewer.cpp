#pragma once
#include "PlayerViewer.h"
#include "GameConfig.h"

void PlayerViewer::init()
{	
	tr_ = GETCMP1_(Transform);
	animator = GETCMP1_(Animator);
}


void PlayerViewer::setIdle(SDL_Rect dest,int fil1,int fil2)
{
	if (animator->getDir().getX() == 0 && animator->getDir().getY() == 0) idleSpritesheet_->renderFrame(dest, fil1, int(((game_->getTime() / config::ANIM_SPEED) % idleSpritesheet_->getNumCols())), 0);
	if ((animator->getDir().getX() > 0 && animator->getDir().getY() == 0) || (animator->getDir().getY() > 0 && animator->getDir().getX() > 0) || ((animator->getDir().getY() > 0 && animator->getDir().getX() == 0))) idleSpritesheet_->renderFrame(dest, fil1, int(((game_->getTime() / config::ANIM_SPEED) % idleSpritesheet_->getNumCols())), 0);
	else if ((animator->getDir().getX() < 0 && animator->getDir().getY() == 0) || (animator->getDir().getY() > 0 && animator->getDir().getX() < 0))  idleSpritesheet_->renderFrame(dest, fil1, int(((game_->getTime() / config::ANIM_SPEED) % idleSpritesheet_->getNumCols())), 0, SDL_FLIP_HORIZONTAL);
	else if ((animator->getDir().getY() < 0 && animator->getDir().getX() == 0) || (animator->getDir().getY() < 0 && animator->getDir().getX() > 0)) idleSpritesheet_->renderFrame(dest, fil2, int(((game_->getTime() / config::ANIM_SPEED) % idleSpritesheet_->getNumCols())), 0);
	else if (animator->getDir().getY() < 0 && animator->getDir().getX() < 0)   idleSpritesheet_->renderFrame(dest, fil2, int(((game_->getTime() / config::ANIM_SPEED) % idleSpritesheet_->getNumCols())), 0, SDL_FLIP_HORIZONTAL);
}

void PlayerViewer::setWalk(SDL_Rect dest, int fil1, int fil2)
{
	if ((animator->getDir().getX() > 0 && animator->getDir().getY() == 0) || (animator->getDir().getY() > 0 && animator->getDir().getX() == 0) || (animator->getDir().getY() > 0 && animator->getDir().getX() > 0)) walkSpritesheet_->renderFrame(dest, fil1, int(((game_->getTime() / config::ANIM_SPEED) % walkSpritesheet_->getNumCols())), 0); //
	else if ((animator->getDir().getX() < 0 && animator->getDir().getY() == 0) || animator->getDir().getY() > 0 && animator->getDir().getX() < 0) walkSpritesheet_->renderFrame(dest, fil1, int(((game_->getTime() / config::ANIM_SPEED) % walkSpritesheet_->getNumCols())), 0, SDL_FLIP_HORIZONTAL);
	else if ((animator->getDir().getY() < 0 && animator->getDir().getX() == 0) || (animator->getDir().getY() < 0 && animator->getDir().getX() > 0)) walkSpritesheet_->renderFrame(dest, fil2, int(((game_->getTime() / config::ANIM_SPEED) % walkSpritesheet_->getNumCols())), 0);
	else if (animator->getDir().getY() < 0 && animator->getDir().getX() < 0) walkSpritesheet_->renderFrame(dest, fil2, int(((game_->getTime() / config::ANIM_SPEED) % walkSpritesheet_->getNumCols())), 0, SDL_FLIP_HORIZONTAL);
}

void PlayerViewer::draw()
{
	SDL_Rect dest = {tr_->getPos().getX(),tr_->getPos().getY(),tr_->getW(),tr_->getH()};

	// int(((game_->getTime() / animator->getAnimSpeed()) % Nº columnas)) --> usarlo como parametro 

	
	switch (animator->getCurrentState())
	{
	case Animator::States::Idle:
		setIdle(dest, 0, 1);
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
		setWalk(dest, 0, 1);		
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

	case Animator::States::AttackWithKnife:
		attackSpritesheet_->renderFrame(dest,0, int(((game_->getTime() / config::ANIM_SPEED) % attackSpritesheet_->getNumCols())), 0);
		break;
	case Animator::States::AttackWithMace:
		attackSpritesheet_->renderFrame(dest, 2, int(((game_->getTime() / config::ANIM_SPEED) % attackSpritesheet_->getNumCols())), 0);
		break;
	case Animator::States::AttackWithNet:
		attackSpritesheet_->renderFrame(dest, 4, int(((game_->getTime() / config::ANIM_SPEED) % attackSpritesheet_->getNumCols())), 0);
		break;
	case Animator::States::AttackWithGrater:
		attackSpritesheet_->renderFrame(dest, 0, int(((game_->getTime() / config::ANIM_SPEED) % attackSpritesheet_->getNumCols())), 0);
		break;

	default:
		break;
	}

	
}
