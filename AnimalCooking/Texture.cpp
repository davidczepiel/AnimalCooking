#include "Texture.h"
#include <SDL_image.h>

#include <iostream>

using namespace std;

Texture::Texture() :
		texture_(nullptr), renderer_(nullptr), width_(0), height_(0), nRows_(1), nCols_(1) {
}

Texture::Texture(SDL_Renderer *renderer, const string& fileName, int numRows, int numCols) :
		texture_(nullptr), width_(0), height_(0), nRows_(numRows), nCols_(numCols) {
	loadFromImg(renderer, fileName);
}

Texture::Texture(SDL_Renderer *renderer, const string& text, const Font *font,
		const SDL_Color& color) :
		texture_(nullptr), width_(0), height_(0), nRows_(1), nCols_(1) {
	loadFromText(renderer, text, font, color);
}

Texture::~Texture() {
	close();
}

void Texture::close() {
	if (texture_ != nullptr) {
		SDL_DestroyTexture(texture_); // delete current texture
		texture_ = nullptr;
		width_ = 0;
		height_ = 0;
	}
}

void Texture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(texture_, alpha);
}

bool Texture::loadFromImg(SDL_Renderer *renderer, const string& fileName) {
	SDL_Surface *surface = IMG_Load(fileName.c_str());
	if (surface != nullptr) {
		close(); // destroy current texture
		texture_ = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture_ != nullptr) {
			width_ = surface->w;
			height_ = surface->h;
		}
		SDL_FreeSurface(surface);
	} else {
		throw "Couldn't load image: " + fileName;
	}
	renderer_ = renderer;
	return texture_ != nullptr;
}

bool Texture::loadFromText(SDL_Renderer *renderer, const string& text, const Font *font,
		const SDL_Color& color) {
	SDL_Surface *textSurface = font->renderText(text, color);
	if (textSurface != nullptr) {
		close();
		texture_ = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture_ != nullptr) {
			width_ = textSurface->w;
			height_ = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	} else {
		throw "Couldn't create text: " + text;
	}
	renderer_ = renderer;
	return texture_ != nullptr;
}

void Texture::render(int x, int y) const {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = width_;
	dest.h = height_;
	render(dest);
}

void Texture::render(const SDL_Rect &dest, const SDL_Rect& clip) const {
	if (texture_) {
		SDL_RenderCopy(renderer_, texture_, &clip, &dest);
	}
}

void Texture::render(const SDL_Rect &dest) const {
	SDL_Rect clip = {0, 0, width_, height_ };
	render(dest, clip);
}


void Texture::render(const SDL_Rect &dest, double angle,
		const SDL_Rect &clip) const {
	if (texture_) {
		SDL_RenderCopyEx(renderer_, texture_, &clip, &dest, angle, nullptr,
				SDL_FLIP_NONE);
	}
}

void Texture::render(const SDL_Rect& dest, double angle,
	const SDL_Rect& clip, SDL_RendererFlip flip) const {
	if (texture_) {
		SDL_RenderCopyEx(renderer_, texture_, &clip, &dest, angle, nullptr, flip);
	}
}

void Texture::render(const SDL_Rect &dest, double angle) const {
	SDL_Rect clip = {0, 0, width_, height_ };
	render(dest, angle, clip);
}

//renderiza un frame de la textura
void Texture::renderFrame(const SDL_Rect& destRect, int row, int col, int angle, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;

	int fw = width_ / nCols_;
	int fh = height_ / nRows_;

	srcRect.x = fw * col;
	srcRect.y = fh * row;
	srcRect.w = fw;
	srcRect.h = fh;
	render(destRect, angle, srcRect, flip);
}
void Texture::renderWithTint(const SDL_Rect& dest, Uint8 r, Uint8 g, Uint8 b)
{
	if (texture_) {
		SDL_SetTextureColorMod(texture_, r, g, b);
		render(dest);
		SDL_SetTextureColorMod(texture_, 255, 255, 255);
	}
}

void Texture::renderWithTint(const SDL_Rect& dest, const SDL_Rect& clip, Uint8 r, Uint8 g, Uint8 b)
{
	if (texture_) {
		SDL_SetTextureColorMod(texture_, r, g, b);
		render(dest, clip);
		SDL_SetTextureColorMod(texture_, 255, 255, 255);
	}
}
