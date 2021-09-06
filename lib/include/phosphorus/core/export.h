#pragma once

#if defined(_MSC_VER)
#   define PH_API_IMPORT __declspec(dllimport)
#   define PH_API_EXPORT __declspec(dllexport)
#   define PH_SUPPRESS_EXPORT_WARNING __pragma(warning(push)) __pragma(warning(disable: 4251 4275))
#   define PH_RESTORE_EXPORT_WARNING __pragma(warning(pop))
#elif defined(__GNUC__)
#   define PH_API_IMPORT
#   define PH_API_EXPORT __attribute__((visibility("default")))
#   define PH_SUPPRESS_EXPORT_WARNING
#   define PH_RESTORE_EXPORT_WARNING
#else
#   define PH_API_IMPORT
#   define PH_API_EXPORT
#   define PH_SUPPRESS_EXPORT_WARNING
#   define PH_RESTORE_EXPORT_WARNING
#endif

#if defined(PH_BUILD_SHARED)
#   ifdef PH_EXPORT_SHARED
#       define PH_API PH_API_EXPORT
#   else
#       define PH_API PH_API_IMPORT
#   endif
#else
#   define PH_API
#endif
