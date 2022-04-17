#pragma once
#include "ISerializer.h"

class DllExport JsonSerializer: public ISerializer
{
	virtual std::string serialize(TrackerEvent* e);
};

