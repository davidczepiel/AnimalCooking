#pragma once
#include <string>
#include <map>
#include "Vector2D.h"
#include "Texture.h"

class SDLGame;
class BubbleKeyShower
{
public:
	BubbleKeyShower() {}
	BubbleKeyShower(SDLGame* game);
	void renderFeedBack(const Vector2D& pos, const string& msg, const string& key, const bool& gPadKey);

	Texture* getTexture(const string& s) const {
		auto itFind = keyToTexture_.find(s);
		return (itFind == keyToTexture_.end()) ? nullptr : //Devuelvo nulo si no ha sido posible encontrarla
			itFind->second; //Devuelvo la textura si existe
	}

private:
	void fillMap(SDLGame* game);
	void renderFeedBackImage(const Vector2D& pos, const string& msg, const string& key);
	void renderFeedBackText(const Vector2D& pos, const string& msg, const string& key);
	map<string, Texture*> keyToTexture_; //Usado para feedback
};

