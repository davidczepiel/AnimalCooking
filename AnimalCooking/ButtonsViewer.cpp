#include "ButtonsViewer.h"
#include "SDL_macros.h"
#include "ButtonDirector.h"
#include "ButtonRenderer.h"
#include "Entity.h"

ButtonsViewer::ButtonsViewer() : Component(ecs::ButtonsViewer)
{
	buttonsToRender = nullptr;
}

void ButtonsViewer::init()
{
	buttonsToRender = GETCMP1_(ButtonDirector)->getButtons();
}

void ButtonsViewer::draw()
{
	ButtonRenderer* br;
	for (int i = 0; i < buttonsToRender->size(); i++) {
		br = GETCMP2(buttonsToRender->at(i), ButtonRenderer);
		br->draw();
	}
}
