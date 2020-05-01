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
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PigIdle);
        texture_->renderFrame(dest,0, int(((game_->getTime() / config::ANIM_SPEED) % texture_->getNumCols())),0);
		break;

	case Animator::States::IdleWithKnife:
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PigIdle);
		texture_->renderFrame(dest, 2, int(((game_->getTime() / config::ANIM_SPEED) % texture_->getNumCols())), 0);
		break;
	case Animator::States::IdleWithMace:
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PigIdle);
		texture_->renderFrame(dest, 4, int(((game_->getTime() / config::ANIM_SPEED) % texture_->getNumCols())), 0);
		break;

	case Animator::States::IdleWithNet:
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PigIdle);
		texture_->renderFrame(dest, 2, int(((game_->getTime() / config::ANIM_SPEED) % texture_->getNumCols())), 0);
		break;
	case Animator::States::IdleWithGrater:
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PigIdle);
		texture_->renderFrame(dest, 2, int(((game_->getTime() / config::ANIM_SPEED) % texture_->getNumCols())), 0);
		break;
	case Animator::States::IdleWithDish:
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PigIdle);
		texture_->renderFrame(dest, 2, int(((game_->getTime() / config::ANIM_SPEED) % texture_->getNumCols())), 0);
		break;
	case Animator::States::Walk:
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PigWalk);
		texture_->renderFrame(dest, 0, int(((game_->getTime() / config::ANIM_SPEED) % texture_->getNumCols())), 0);
		break;


	default:
		break;
	}

	
}
