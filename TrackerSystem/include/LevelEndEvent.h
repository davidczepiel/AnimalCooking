#pragma once
#include "GameEvent.h"

class DllExport LevelEndEvent : public GameEvent {
public:
	LevelEndEvent();
	~LevelEndEvent();
	virtual std::string toJson() override;

	bool getLevelWin() const;

	void setLevelWin(bool lW);
private:
	bool _levelWin;
};

