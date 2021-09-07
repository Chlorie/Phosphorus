#pragma once

#include <clu/c_str_view.h>

#include "generic/render_backend.h"
#include "../core/export.h"
#include "../event/event.h"
#include "../math/color.h"
#include "../math/linear_algebra.h"

namespace ph
{
    PH_SUPPRESS_EXPORT_WARNING
    class PH_API Window final
    {
    public:
        Window(clu::c_str_view title, Int2 size, RenderBackend backend);
        ~Window() noexcept;
        Window(const Window&) = delete;
        Window(Window&& other) noexcept;
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&& other) noexcept;
        void swap(Window& other) noexcept;
        PH_API friend void swap(Window& lhs, Window& rhs) noexcept { lhs.swap(rhs); }

        void close();
        bool should_close() const;
        void poll_events();
        void clear_color(Color color);
        void update();

        Int2 size() const noexcept { return size_; }
        Float2 sizef() const noexcept { return Float2(size_); }

        template <std::invocable<Event&> Fn>
        void set_event_callback(Fn&& callback) { callback_ = static_cast<Fn&&>(callback); }
        void set_vsync(bool enabled);

        void* handle() const noexcept { return window_; }

    private:
        void* window_ = nullptr;
        Int2 size_;
        std::function<void(Event&)> callback_;

        void set_glfw_callbacks() const;
    };
    PH_RESTORE_EXPORT_WARNING
}
