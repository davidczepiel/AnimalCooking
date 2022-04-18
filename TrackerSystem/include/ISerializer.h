#pragma once
#include <string>
#include "defines.h"
class TrackerEvent;

class DllExport ISerializer
{
public:

	/// <summary>
	/// Convierte el evento a texto
	/// </summary>
	/// <param name="e">Evento a serializar</param>
	/// <returns></returns>
	virtual std::string serialize(TrackerEvent* e) = 0;

	/// <summary>
	/// Se inicia la estructura del fichero segun el formato
	/// </summary>
	/// <returns> Texto necesario para iniciar</returns>
	virtual std::string startSyntax() { return ""; }

	/// <summary>
	/// Se cierra la estructura del fichero segun el formato
	/// </summary>
	/// <returns> Texto necesario para cerrar</returns>
	virtual std::string endSyntax() { return ""; }
};

