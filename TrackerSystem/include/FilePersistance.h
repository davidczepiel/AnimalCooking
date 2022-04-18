#pragma once
#include "IPersistance.h"
#include <queue>
#include <thread> 
#include <atomic>

class DllExport FilePersistance : public IPersistance
{
public:

	FilePersistance(ISerializer* s, char* filePath);
	virtual ~FilePersistance();

	/// <summary>
	/// Añade un evento para que sea serializado
	/// a la cola que no se este serializando
	/// </summary>
	/// <param name="e">Evento a añadir</param>
	virtual void send(TrackerEvent* e);

	/// <summary>
	/// Cambio de cola para que se empiece a serializar
	/// </summary>
	virtual void flush();

	virtual void setPath(char* path) override;

private:

	char* _filePath;
	std::atomic<bool> _flushRequested;
	std::atomic<bool> _threadActive;

	std::queue<TrackerEvent*>* _activeQueue;
	std::queue<TrackerEvent*> _eventQueue1;
	std::queue<TrackerEvent*> _eventQueue2;

	std::thread* _thread;
	 
	/// <summary>
	/// Bucle del hilo
	/// Llama a la serializacion de la cola
	/// </summary>
	void flushQueue();

	/// <summary>
	/// Usado por el hilo
	/// Serializa los eventos en la cola hasta vaciarla
	/// </summary>
	/// <param name="queue"></param>
	void writeQueue(std::queue<TrackerEvent*>& queue);
};

