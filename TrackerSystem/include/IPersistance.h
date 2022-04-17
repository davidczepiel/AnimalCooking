#pragma once

#include "defines.h"

class TrackerEvent;
class ISerializer;

class DllExport IPersistance
{
public:
	IPersistance(ISerializer* s);
	virtual ~IPersistance() { delete _serializer; }

	virtual void send(TrackerEvent* e) = 0;
	virtual void flush() = 0;
	virtual void setPath(char* path) = 0;

	void setSerializer(ISerializer* serializer);

protected:
	ISerializer* _serializer;
};

