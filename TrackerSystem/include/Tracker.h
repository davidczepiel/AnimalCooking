#pragma once
#include <iostream>
#include <cassert>
#include <string>
#include "defines.h"
#include "IPersistance.h"

//class IPersistance;
class TrackerEvent;

class DllExport Tracker
{
private:
	static Tracker* instance;
public:
	enum PersistanceType { FilePersistance_, ServerPersistance_ };
	enum SerializerType { JSON_ };

public:
	~Tracker(); 

	/// <summary>
	/// Inicializa el tracker, necesario llamarlo
	/// 
	/// </summary>
	/// <param name="storageDir">Ruta a la carpeta en la que se guardaran los ficheros de las sesiones</param>
	/// <param name="persistanceType">Tipo de persistencia a usar</param>
	/// <param name="serializerType">Tipo de serializacion a usar</param>
	/// <returns></returns>
	static bool Init(const std::string& storageDir = "./", PersistanceType persistanceType = PersistanceType::FilePersistance_, SerializerType serializerType = SerializerType::JSON_);

	/// <summary>
	/// Devuelve la instancia estatica del tracker
	/// Es necesario haber llamado a Init
	/// </summary>
	/// <returns></returns>
	inline static Tracker* Instance() {
		assert(instance != nullptr);
		return instance;
	}

	void setGameID(const int gameID) { this->gameID = gameID; }
	void setStoragePath(const std::string& path);

	/// <summary>
	/// Inicio de la sesion de juego
	/// </summary>
	void Start();

	/// <summary>
	/// Fin de la sesion
	/// </summary>
	void End();

	/// <summary>
	/// Envía una peticion de flush a persistance
	/// </summary>
	void flush();

	/// <summary>
	/// Establece al evento la informacion del tracker y
	/// Lo envia a Persistance para que se serialice
	/// </summary>
	/// <param name="e"></param>
	void trackEvent(TrackerEvent* e);

private:

	Tracker(); 

	void setUserID();
	
	/// <summary>
	/// Devuelve la time stamp para el evento
	/// </summary>
	/// <returns>time stamp</returns>
	time_t getTimestamp();

	uint64_t userID;
	
	int gameID;
	int sessionID;

	IPersistance* persistance;

};

