#pragma once
#include <string>
#include "defines.h"
class TrackerEvent;

class DllExport ISerializer
{
public:

	virtual std::string serialize(TrackerEvent* e) = 0;
};

