#include "phosphorus/core/application.h"

#include "phosphorus/core/error.h"
#include "phosphorus/core/log.h"

namespace ph
{
    Application::Application()
    {
        PH_ENGINE_ASSERT(!instance_, "Multiple application instances cannot co-exist");
        start_time_ = Clock::now();
        constexpr log::Level log_level = is_debug ? log::Level::debug : log::Level::warn;
        log::set_engine_level(log_level);
        log::set_level(log_level);
        instance_ = this;
    }

    Application& Application::instance()
    {
        PH_ENGINE_ASSERT(instance_,
            "Application state is not initialized, the instance pointer is still null");
        return *instance_;
    }

    void Application::run()
    {
        using namespace std::literals;
        static constexpr auto first_delta_time = 17ms;
        last_update_ = Clock::now() - first_delta_time;
        while (true)
        {
            current_update_ = Clock::now();
            update();
            last_update_ = current_update_;
        }
    }

    void Application::quit() {}
}
