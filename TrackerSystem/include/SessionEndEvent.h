#pragma once
#include "TrackerEvent.h"

class DllExport SessionEndEvent : public TrackerEvent {
public:
	SessionEndEvent();
	~SessionEndEvent();

	/// <summary>
	/// Dvuelve la clase en Json.
	/// debe devolver como utlimo caracter ","
	/// </summary>
	virtual std::string toJson() override;
};