#pragma once
#include "IPersistance.h"
#include <queue>
#include <thread>
#include <atomic>

class DllExport ServerPersistance : public IPersistance {
public:
	ServerPersistance(ISerializer* s, char* serverRoute);
	~ServerPersistance();

	void send(TrackerEvent* e);
	void flush();

	void setPath(char* path) override {}

private:

	std::atomic<bool> _flushRequested;
	std::atomic<bool> _threadActive;

	std::queue<TrackerEvent*>* _activeQueue;
	std::queue<TrackerEvent*> _eventQueue1;
	std::queue<TrackerEvent*> _eventQueue2;

	std::thread* _thread;

	void flushQueue();
	void writeQueue(std::queue<TrackerEvent*>& queue);
};

