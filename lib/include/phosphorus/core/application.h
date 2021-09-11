#pragma once

#include <optional>
#include <clu/c_str_view.h>

#include "export.h"
#include "../math/linear_algebra.h"
#include "../layer/layer_stack.h"
#include "../graphics/window.h"
#include "../graphics/generic/render_backend.h"
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

        [[nodiscard]] static Application& instance();
        void run();
        void quit();

        [[nodiscard]] Duration time_since_start() const { return Clock::now() - start_time_; }
        [[nodiscard]] float seconds_since_start() const { return to_seconds(time_since_start()); }
        [[nodiscard]] Duration delta_time() const { return current_update_ - last_update_; }
        [[nodiscard]] float delta_time_sec() const { return to_seconds(delta_time()); }

        [[nodiscard]] Window& window() { return *window_; }
        [[nodiscard]] const Window& window() const { return *window_; }
        [[nodiscard]] LayerStack& layer_stack() { return layer_stack_; }
        [[nodiscard]] const LayerStack& layer_stack() const { return layer_stack_; }

    protected:
        virtual void update() {}
        void initialize_window(clu::c_str_view title, Int2 size, RenderBackend backend);

    private:
        inline static Application* instance_ = nullptr;

        TimePoint start_time_;
        TimePoint last_update_;
        TimePoint current_update_;

        std::optional<Window> window_;
        LayerStack layer_stack_;

        void propagate_event(Event& ev);
    };
    PH_RESTORE_EXPORT_WARNING
}
