#pragma once

#include <fmt/chrono.h>
#include <spdlog/spdlog.h>

#include "export.h"

namespace ph
{
    namespace log
    {
        using Level = spdlog::level::level_enum;

        PH_API spdlog::logger& get_engine_logger();
        PH_API spdlog::logger& get_client_logger();

        template <typename... Ts>
        void engine(const Level level, Ts&&... args)
        {
            get_engine_logger().log(level, std::forward<Ts>(args)...);
        }
        template <typename... Ts>
        void client(const Level level, Ts&&... args)
        {
            get_client_logger().log(level, std::forward<Ts>(args)...);
        }

        PH_API inline void set_engine_level(const Level level) { get_engine_logger().set_level(level); }
        PH_API inline void set_level(const Level level) { get_client_logger().set_level(level); }
    }

    template <typename... Ts>
    void log_trace(Ts&&... args) { log::client(spdlog::level::trace, std::forward<Ts>(args)...); }
    template <typename... Ts>
    void log_debug(Ts&&... args) { log::client(spdlog::level::debug, std::forward<Ts>(args)...); }
    template <typename... Ts>
    void log_info(Ts&&... args) { log::client(spdlog::level::info, std::forward<Ts>(args)...); }
    template <typename... Ts>
    void log_warning(Ts&&... args) { log::client(spdlog::level::warn, std::forward<Ts>(args)...); }
    template <typename... Ts>
    void log_error(Ts&&... args) { log::client(spdlog::level::err, std::forward<Ts>(args)...); }
    template <typename... Ts>
    void log_critical(Ts&&... args) { log::client(spdlog::level::critical, std::forward<Ts>(args)...); }

    template <typename... Ts>
    void log_engine_trace(Ts&&... args) { log::engine(spdlog::level::trace, std::forward<Ts>(args)...); }
    template <typename... Ts>
    void log_engine_debug(Ts&&... args) { log::engine(spdlog::level::debug, std::forward<Ts>(args)...); }
    template <typename... Ts>
    void log_engine_info(Ts&&... args) { log::engine(spdlog::level::info, std::forward<Ts>(args)...); }
    template <typename... Ts>
    void log_engine_warning(Ts&&... args) { log::engine(spdlog::level::warn, std::forward<Ts>(args)...); }
    template <typename... Ts>
    void log_engine_error(Ts&&... args) { log::engine(spdlog::level::err, std::forward<Ts>(args)...); }
    template <typename... Ts>
    void log_engine_critical(Ts&&... args) { log::engine(spdlog::level::critical, std::forward<Ts>(args)...); }
}
