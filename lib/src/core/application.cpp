#include "phosphorus/core/application.h"

#include "phosphorus/core/error.h"
#include "phosphorus/core/log.h"
#include "phosphorus/event/window_events.h"

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
        PH_ENGINE_ASSERT(window_, "The window should be initialized before running the app");
        window_->set_event_callback(std::bind_front(&Application::propagate_event, this));
        last_update_ = Clock::now() - first_delta_time;
        while (!window_->should_close())
        {
            current_update_ = Clock::now();
            window_->poll_events();
            update();
            for (Layer& layer : layer_stack_) layer.on_update();
            window_->update();
            last_update_ = current_update_;
        }
    }

    void Application::quit() { window_->close(); }

    void Application::initialize_window(const clu::c_str_view title, const Int2 size, const RenderBackend backend)
    {
        window_.emplace(title, size, backend);
        log_engine_info("Created window {} with size {}", title, size);
    }

    void Application::propagate_event(Event& ev)
    {
        ev.dispatch([this](WindowCloseEvent&) { window_->close(); });
        // ev.dispatch<WindowResizedEvent>([this](auto&) { recreate_swapchain(); });
        for (Layer& layer : layer_stack_ | std::views::reverse)
        {
            layer.on_event(ev);
            if (ev.blocked()) break;
        }
    }
}
