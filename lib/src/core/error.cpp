#include "phosphorus/core/error.h"

#include "phosphorus/core/log.h"

namespace ph
{
    namespace
    {
        void log_error_msg(const std::string_view msg, const bool from_engine)
        {
            if (from_engine)
                log_engine_error(msg);
            else
                log_error(msg);
        }
    }

    void assertion_failure(const std::string_view expr, const std::string_view msg,
        const bool from_engine, const std::source_location loc)
    {
        log_error_msg(
            fmt::format("Assertion {} failed in {} ({} {}:{}), description: {}",
                expr, loc.function_name(), loc.file_name(), loc.line(), loc.column(), msg), from_engine);
        std::terminate();
    }

    void throw_exception(const std::string_view msg,
        const bool from_engine, const std::source_location loc) noexcept(false)
    {
        log_error_msg(
            fmt::format("Exception in {} ({} {}:{}), description: {}",
                loc.function_name(), loc.file_name(), loc.line(), loc.column(), msg), from_engine);
        throw RuntimeError(std::string(msg));
    }

    void fatal_error(const std::string_view msg,
        const bool from_engine, const std::source_location loc) noexcept
    {
        try
        {
            (from_engine ? log::get_engine_logger() : log::get_client_logger())
               .critical(fmt::format("Fatal error in {} ({} {}:{}), description: {}",
                    loc.function_name(), loc.file_name(), loc.line(), loc.column(), msg), from_engine);
        }
        catch (...) {}
        std::abort();
    }
}
