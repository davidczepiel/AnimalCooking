#include "LoadingBarViewer.h"
#include "Entity.h"
#include "SDL_macros.h"

LoadingBarViewer::LoadingBarViewer(Texture* contorno, Texture* filler): Component(ecs::LoadingBarViewer),
		ownerTransform_(nullptr),
		contorno_(contorno),
		filler_(filler),
		percentage_()
{
}

void LoadingBarViewer::init()
{
	ownerTransform_ = GETCMP1_(Transform);
}

void LoadingBarViewer::draw()
{
	Vector2D pos = ownerTransform_->getPos();

	SDL_Rect dest = RECT(pos.getX(), pos.getY(), ownerTransform_->getW(), ownerTransform_->getH());

	//Renderiza un porcentaje de la barra, si hay
	if (percentage_ > 0) {
		dest.w *= percentage_;
		filler_->render(dest, RECT(0, 0, filler_->getWidth() * percentage_, filler_->getHeight()));
	}

	//Renderiza el contorno de la barra, volviendo el Width a su valor normal
	dest.w = ownerTransform_->getW();
	//contorno_->render(dest);
}

//Extra between 0 and 1, adding % of its total length
void LoadingBarViewer::plusLength(double extra)
{	
	percentage_ += extra;
}
