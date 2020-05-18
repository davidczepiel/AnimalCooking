#include "Vector2D.h"
#include <SDL_stdinc.h>
#include "Texture.h"
#include "Entity.h"

enum class MapLevelState { unselected, selected };

class MapLevel{
public:
	MapLevel();
	~MapLevel();
	void draw();
	void setMapLevelState(MapLevelState ms) { mapState_ = ms; }

private:
	MapLevelState mapState_;
};