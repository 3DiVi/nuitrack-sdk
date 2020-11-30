#ifndef NUITRACK_EXPORT_H
#define NUITRACK_EXPORT_H

#ifdef _WIN32

#ifdef NUITRACK_EXPORT
#define NUITRACK_API __declspec(dllexport)
#else
#define NUITRACK_API __declspec(dllimport)
#endif

#ifdef MIDDLEWARE_EXPORT
#define MIDDLEWARE_API __declspec(dllexport)
#else
#define MIDDLEWARE_API __declspec(dllimport)
#endif

#define NUITRACK_LOCAL
#define NUITRACK_DEPRECATED __declspec(deprecated)

#else
#define MIDDLEWARE_API __attribute__ ((visibility ("default")))
#define NUITRACK_API __attribute__ ((visibility ("default")))
#define NUITRACK_LOCAL __attribute__ ((visibility ("hidden")))
#define NUITRACK_DEPRECATED __attribute__ ((deprecated))
#endif

#endif /* NUITRACK_EXPORT_H */
