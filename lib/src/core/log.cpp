#include "phosphorus/core/log.h"

#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace ph::log
{
    namespace
    {
        struct Loggers
        {
            std::shared_ptr<spdlog::logger> engine_logger;
            std::shared_ptr<spdlog::logger> client_logger;
        };

        const Loggers& get_loggers()
        {
            static Loggers loggers = []
            {
                spdlog::set_pattern("%^[%T] %n: %v%$");
                Loggers res;
                res.engine_logger = spdlog::stdout_color_mt("PCore");
                res.engine_logger->set_level(spdlog::level::trace);
                res.client_logger = spdlog::stdout_color_mt("App");
                res.client_logger->set_level(spdlog::level::trace);
                return res;
            }();
            return loggers;
        }
    }

    spdlog::logger& get_engine_logger() { return *get_loggers().engine_logger; }
    spdlog::logger& get_client_logger() { return *get_loggers().client_logger; }
}
