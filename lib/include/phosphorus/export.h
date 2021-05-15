#pragma once

#if defined(_MSC_VER)
#   define PHOS_API_IMPORT __declspec(dllimport)
#   define PHOS_API_EXPORT __declspec(dllexport)
#   define PHOS_SUPPRESS_EXPORT_WARNING __pragma(warning(push)) __pragma(warning(disable: 4251 4275))
#   define PHOS_RESTORE_EXPORT_WARNING __pragma(warning(pop))
#elif defined(__GNUC__)
#   define PHOS_API_IMPORT
#   define PHOS_API_EXPORT __attribute__((visibility("default")))
#   define PHOS_SUPPRESS_EXPORT_WARNING
#   define PHOS_RESTORE_EXPORT_WARNING
#else
#   define PHOS_API_IMPORT
#   define PHOS_API_EXPORT
#   define PHOS_SUPPRESS_EXPORT_WARNING
#   define PHOS_RESTORE_EXPORT_WARNING
#endif

#if defined(PHOS_BUILD_SHARED)
#   ifdef PHOS_EXPORT_SHARED
#       define PHOS_API PHOS_API_EXPORT
#   else
#       define PHOS_API PHOS_API_IMPORT
#   endif
#else
#   define PHOS_API
#endif
