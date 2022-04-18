#pragma once
#include "ISerializer.h"

class DllExport JsonSerializer: public ISerializer
{
	/// <summary>
	/// Convierte el evento a formato json
	/// </summary>
	/// <param name="e">Evento a serializar</param>
	/// <returns></returns>
	virtual std::string serialize(TrackerEvent* e);

	/// <summary>
	/// Se inicia la estructura del objeto json
	/// </summary>
	/// <returns> Texto necesario para iniciar</returns>
	virtual std::string startSyntax() override;

	/// <summary>
	/// Se cierra la estructura del objeto json
	/// </summary>
	/// <returns> Texto necesario para cerrar</returns>
	virtual std::string endSyntax() override;
};

