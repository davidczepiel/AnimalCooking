#include "DishStackViewer.h"
#include"Entity.h"
#include "SDL_macros.h"

DishStackViewer ::DishStackViewer(Interactive* i) : Component(ecs::DishStackViewer),entity(i)
{

}

void DishStackViewer::init()
{
	stack = game_->getTextureMngr()->getTexture(Resources::Platera);
}

void DishStackViewer::draw()
{	
	stack->render(RECT(entity->getPos().getX(), entity->getPos().getY(), entity->getSize().getX(), entity->getSize().getY()));
}