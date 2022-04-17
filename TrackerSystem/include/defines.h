#pragma once

#ifdef EXPORT_
#define DllExport __declspec(dllexport)
#else 
#define DllExport __declspec(dllimport)
#endif