#pragma once

#include <SDL.h>
#include "Font.h"
#include <string>

using namespace std;

class Texture {
public:
	Texture();
	Texture(SDL_Renderer *renderer, const string& fileName, int numRows = 1, int numCols = 1);
	Texture(SDL_Renderer *renderer, const string& text, const Font *font,
			const SDL_Color& color);
	virtual ~Texture();

	inline int getWidth() {
		return width_;
	}

	inline int getHeight() {
		return height_;
	}

	inline bool isReady() {
		return texture_ != nullptr;
	}

	inline int getNumCols() {
		return nCols_;
	}

	inline int getNumRows() {
		return nRows_;
	}

	// load from image or text, in both cases we should provide a rendered
	bool loadFromImg(SDL_Renderer *renderer, const string& fileName);
	bool loadFromText(SDL_Renderer *renderer, const string& text, const Font *font,
			const SDL_Color& color = { 0, 0, 0, 255 });

	// render the complete texture at position (x,y).
	void render(int x, int y) const;

	// render part of the texture (clip) to a destination rectangle, if no
	// clip provided it renders all texture (scaled to dest).
	void render(const SDL_Rect &dest) const;
	void render(const SDL_Rect &dest, const SDL_Rect& clip) const;

	// render part of the texture (clip) to a destination rectangle with a rotation,
	// if no clip provided it renders all texture (scaled to dest).
	void render(const SDL_Rect &dest, double angle,	const SDL_Rect &clip) const;
	void render(const SDL_Rect &dest, double angle) const;
	void render(const SDL_Rect& dest, double angle, const SDL_Rect& clip, SDL_RendererFlip flip) const;

	void renderFrame(const SDL_Rect& destRect, int row, int col, int angle, SDL_RendererFlip flip = SDL_FLIP_NONE) const;

	void renderWithTint(const SDL_Rect& dest, Uint8 r, Uint8 g, Uint8 b);
	void renderWithTint(const SDL_Rect& dest, const SDL_Rect& clip, Uint8 r, Uint8 g, Uint8 b);

	void close();

private:
	SDL_Texture *texture_;
	SDL_Renderer *renderer_;
	int width_;
	int height_;
	int nRows_;
	int nCols_;
};
