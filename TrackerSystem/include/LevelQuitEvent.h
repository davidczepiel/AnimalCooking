#pragma once
#include "GameEvent.h"

class DllExport LevelQuitEvent : public GameEvent {
public:
	LevelQuitEvent();
	~LevelQuitEvent();

	/// <summary>
	/// Dvuelve la clase en Json.
	/// debe devolver como utlimo caracter ","
	/// </summary>
	virtual std::string toJson() override;
};

