#include "Resources.h"
#include "SDL_macros.h"

vector<Resources::FontInfo> Resources::fonts_ {
//
	{ ARIAL24, "../AnimalCooking/resources/fonts/arial.ttf", 24 }
};

vector<Resources::ImageInfo> Resources::images_ {
//
	{ Button, "../AnimalCooking/resources/images/button.png" }
};

vector<Resources::TextMsgInfo> Resources::messages_ {
//
	{ HelloWorld, "Hello World", { COLOR(0xaaffffff) }, ARIAL24 }
};

vector<Resources::MusicInfo> Resources::musics_ {
//

};

vector<Resources::SoundInfo> Resources::sounds_ {
//

};

