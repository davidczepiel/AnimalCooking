#pragma once
#include "TrackerEvent.h"

class DllExport SessionStartEvent : public TrackerEvent {
public:
	SessionStartEvent();
	~SessionStartEvent();

	/// <summary>
	/// Dvuelve la clase en Json.
	/// debe devolver como utlimo caracter ","
	/// </summary>
	virtual std::string toJson() override;
};