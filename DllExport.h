
#ifndef DLL_EXPORT_H_
#define DLL_EXPORT_H_

#ifndef PE_EXPORT
#define PEAPI __declspec(dllimport)
#else
#define PEAPI __declspec(dllexport)
#endif

#endif
