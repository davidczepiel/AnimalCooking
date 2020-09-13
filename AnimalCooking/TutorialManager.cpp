#include "TutorialManager.h"
#include "Entity.h"
#include "Transform.h"
#include "SDL_macros.h"

void TutorialManager::init()
{
	Transform* tr_ = GETCMP1_(Transform);

	rect_ = RECT(tr_->getPos().getX(), tr_->getPos().getX(), tr_->getW(), tr_->getH());

	background_ = game_->getTextureMngr()->getTexture(/*Resources::TextureId::TutorialImageBackground*/ 0);

	images_ = { game_->getTextureMngr()->getTexture(/*Resources::TextureId::TutorialImage0*/ 0),
				game_->getTextureMngr()->getTexture(/*Resources::TextureId::TutorialImage1*/ 1),
				game_->getTextureMngr()->getTexture(/*Resources::TextureId::TutorialImage2*/ 2),
				game_->getTextureMngr()->getTexture(/*Resources::TextureId::TutorialImage3*/ 3),
				game_->getTextureMngr()->getTexture(/*Resources::TextureId::TutorialImage4*/ 4),
				game_->getTextureMngr()->getTexture(/*Resources::TextureId::TutorialImage5*/ 5),
				game_->getTextureMngr()->getTexture(/*Resources::TextureId::TutorialImage6*/ 6)};
}

void TutorialManager::draw()
{
	(*index_)->render(rect_);
	background_->render(rect_);
}
