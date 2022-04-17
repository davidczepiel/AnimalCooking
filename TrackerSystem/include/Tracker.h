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

	/**
	 * Inits system
	 * @return true when all good
	 * @return false when something bad happened
	 */
	static bool Init(const std::string& storagePath = "./data.json", PersistanceType persistanceType = PersistanceType::FilePersistance_, SerializerType serializerType = SerializerType::JSON_);

	inline static Tracker* Instance() {
		assert(instance != nullptr);
		return instance;
	}

	/**
	 * 
	 * @param userNameID 
	 */
	void setUserID(const uint16_t userNameID);

	/**
	 * Game ID 
	 * @param gameID int
	 */
	void setGameID(const int gameID) { this->gameID = gameID; }

	/**
	 * Where to store data
	 * @param path 
	 */
	void setStoragePath(const std::string& path);

	/**
	 * Start of session
	 * @return true 
	 * @return false 
	 */
	bool Start();

	/**
	 * End of session
	 * @return true 
	 * @return false 
	 */
	bool End();

	void flush();

	void trackEvent(TrackerEvent* e);

	/*template<typename T = TrackerEvent, typename ...Targs>
	void trackEvent(Targs&&... args) {
		TrackerEvent* te = new T(std::forward<Targs>(args)...);
		if (te != nullptr) {
		    te->setTimeStamp(getTimestamp());
		    te->setGameId(gameID);
		    te->setSessionId(sessionID);W
		
		    //TODO: string OR unsigned long int
		    te->setUserId(userID);
		}
		
		persistance->send(te);
	}*/

private:

	Tracker(); 

	
	/**
	* time_t == long long
	*/
	time_t getTimestamp();

	uint64_t userID;
	
	int gameID;
	int sessionID;

	IPersistance* persistance;
};

