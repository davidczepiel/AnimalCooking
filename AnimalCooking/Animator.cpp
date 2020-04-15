#include "Animator.h"

Animator::Animator() : Component(ecs::Animator)
{
}

SDL_Rect& Animator::animate(Texture* t, int fx, int fy, int numRows, int numCols)
{
	int fw = t->getWidth() / numCols;
	int fh = t->getHeight() / numRows;
	
	clip.x = fw * fx;
	clip.y = fh * fy;
	clip.w = fw;
	clip.h = fh;

	return clip;
}
