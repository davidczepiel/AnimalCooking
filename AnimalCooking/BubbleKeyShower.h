#pragma once
#include <string>
#include <map>
#include <array>
#include "Vector2D.h"
#include "Texture.h"

class SDLGame;
class BubbleKeyShower
{
public:
	BubbleKeyShower():keyToTexture_() {}
	BubbleKeyShower(SDLGame* game);
	void renderFeedBack(const Vector2D& pos, const string& msg, const string& key, const int player, const bool& gPadKey);

	Texture* getTexture(const string& s, const int player) const;
private:
	void fillMap(SDLGame* game);
	void renderFeedBackImage(const Vector2D& pos, const string& msg, const string& key, const int player);
	void renderFeedBackText(const Vector2D& pos, const string& msg, const string& key);
	std::array<map<string, Texture*>, 2> keyToTexture_; //Usado para feedback
};

