#include "Texture.h"

enum class MapLevelState { unselected, selected };

class MapLevel{
public:
	MapLevel();
	~MapLevel();
	void setMapLevelState(MapLevelState ms) { mapState_ = ms; }

private:
	MapLevelState mapState_;
	Texture* unselectedText_;
	Texture* selectedText_;

};