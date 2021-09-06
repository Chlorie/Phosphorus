#pragma once

#include <memory>
#include <optional>

#include "export.h"
#include "../utils/chrono.h"

namespace ph
{
    PH_SUPPRESS_EXPORT_WARNING
    class PH_API Application
    {
    public:
        Application();
        virtual ~Application() = default;
        Application(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(const Application&) = delete;
        Application& operator=(Application&&) = delete;

        static Application& instance();
        void run();
        void quit();

        Duration time_since_start() const { return Clock::now() - start_time_; }
        float seconds_since_start() const { return to_seconds(time_since_start()); }
        Duration delta_time() const { return current_update_ - last_update_; }
        float delta_time_sec() const { return to_seconds(delta_time()); }

    protected:
        virtual void update() = 0;

    private:
        inline static Application* instance_ = nullptr;

        TimePoint start_time_;
        TimePoint last_update_;
        TimePoint current_update_;
    };
    PH_RESTORE_EXPORT_WARNING
}
