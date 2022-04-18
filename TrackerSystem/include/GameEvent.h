#pragma once
#include "TrackerEvent.h"
#include "defines.h"

class DllExport GameEvent: public TrackerEvent{
public:
	GameEvent();
	~GameEvent();

	/// <summary>
	/// Dvuelve la clase en Json.Todos los eventos que hereden de esta clase
	/// deben de devolver como utlimo caracter ","
	/// </summary>
	virtual std::string toJson();

	uint16_t getLevelId() const;

	void setLevelId(uint16_t lI);
private:
	uint16_t _levelId;
};

