#pragma once

#include <stdexcept>
#include <string_view>
#include <source_location>

#include "export.h"

namespace ph
{
    PH_SUPPRESS_EXPORT_WARNING
    class PH_API RuntimeError final : public std::runtime_error
    {
        using std::runtime_error::runtime_error;
    };
    PH_RESTORE_EXPORT_WARNING

    [[noreturn]] PH_API void assertion_failure(std::string_view expr, std::string_view msg,
        bool from_engine = false, std::source_location loc = std::source_location::current());
    [[noreturn]] PH_API void throw_exception(std::string_view msg,
        bool from_engine = false, std::source_location loc = std::source_location::current()) noexcept(false);
    [[noreturn]] PH_API void fatal_error(std::string_view msg,
        bool from_engine = false, std::source_location loc = std::source_location::current()) noexcept;

#define PH_CATCH_FATAL \
    catch (const std::exception& e) { ::ph::fatal_error(e.what()); } \
    catch (...) { ::ph::fatal_error("unknown error"); } (void)0
#define PH_ENGINE_CATCH_FATAL \
    catch (const std::exception& e) { ::ph::fatal_error(e.what(), true); } \
    catch (...) { ::ph::fatal_error("unknown error", true); } (void)0

#ifndef NDEBUG
    constexpr bool is_debug = true;
#   define PH_ASSERT(expr, msg) while (!(expr)) ::ph::assertion_failure(#expr, msg, false)
#   define PH_ENGINE_ASSERT(expr, msg) while (!(expr)) ::ph::assertion_failure(#expr, msg, true)
#else
    constexpr bool is_debug = false;
#   define PH_ASSERT(expr, msg) (void)0
#   define PH_ENGINE_ASSERT(expr, msg) (void)0
#endif
}
