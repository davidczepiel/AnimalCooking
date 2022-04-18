#pragma once
#include "GameEvent.h"

class DllExport LevelStartEvent : public GameEvent {
public:
	LevelStartEvent();
	~LevelStartEvent();

	/// <summary>
	/// Dvuelve la clase en Json.
	/// debe devolver como utlimo caracter ","
	/// </summary>
	virtual std::string toJson() override;
};

