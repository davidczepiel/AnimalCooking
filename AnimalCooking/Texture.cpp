#include "Texture.h"
#include <iostream>
#include "checkML.h"
#include "Font.h"

using namespace std;

//Destruye la textura
void Texture::clean() {
	SDL_DestroyTexture(texture);
	texture = nullptr;
	w = h = 0;
}

//Carga la textura en la tarjeta grafica
void Texture::load(string filename, uint nRows, uint nCols) {
	SDL_Surface* tempSurface = IMG_Load(filename.c_str());
	if (tempSurface == nullptr) // throw new SDLError(IMG_GetError());
	clean();
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (texture == nullptr) // throw new SDLError(IMG_GetError());
	numRows = nRows;
	numCols = nCols;
	w = tempSurface->w;
	h = tempSurface->h;
	fw = w / numCols;
	fh = h / numRows;
	SDL_FreeSurface(tempSurface);
}

//renderiza toda la textura
void Texture::render(const SDL_Rect &destRect, double angle, const SDL_Point* p, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = 0; srcRect.y = 0;
	srcRect.w = w; srcRect.h = h;

	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, p, flip);
}

//renderiza un frame de la textura
void Texture::renderFrame(const SDL_Rect& destRect, int row, int col, int angle, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = fw * col;
	srcRect.y = fh * row;
	srcRect.w = fw;
	srcRect.h = fh;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, 0, flip);
}

void Texture::loadFromText(string text, const Font& font, SDL_Color color) {
	SDL_Surface* textSurface = font.generateSurface(text, color);
	if (textSurface == nullptr);
		//throw SDLError(TTF_GetError());
	else {
		clean();
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture == nullptr) {
			//throw SDLError(SDL_GetError());
			w = h = 0;
		}
		else {
			w = textSurface->w;
			h = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
}