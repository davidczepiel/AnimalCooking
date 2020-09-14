#include "TutorialManager.h"
#include "Entity.h"
#include "Transform.h"
#include "SDL_macros.h"

void TutorialManager::init()
{
	Transform* tr_ = GETCMP1_(Transform);

	rect_ = RECT(tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), tr_->getH());

	background_ = game_->getTextureMngr()->getTexture(Resources::TextureId::TutorialImageBackground);

	images_ = { game_->getTextureMngr()->getTexture(Resources::TextureId::TutorialImage0),
				game_->getTextureMngr()->getTexture(Resources::TextureId::TutorialImage1),
				game_->getTextureMngr()->getTexture(Resources::TextureId::TutorialImage2),
				game_->getTextureMngr()->getTexture(Resources::TextureId::TutorialImage3),
				game_->getTextureMngr()->getTexture(Resources::TextureId::TutorialImage4),
				game_->getTextureMngr()->getTexture(Resources::TextureId::TutorialImage5)};
}

void TutorialManager::draw()
{
	images_[index_]->render(rect_);
	background_->render(rect_);
}
