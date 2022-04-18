#pragma once
#include "GameEvent.h"

class DllExport LevelEndEvent : public GameEvent {
public:
	LevelEndEvent();
	~LevelEndEvent();

	/// <summary>
	/// Dvuelve la clase en Json.
	/// debe devolver como utlimo caracter ","
	/// </summary>
	virtual std::string toJson() override;

	bool getLevelWin() const;

	void setLevelWin(bool lW);
private:
	bool _levelWin;
};

