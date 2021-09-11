#pragma once

#include <clu/c_str_view.h>

#include "generic/render_backend.h"
#include "generic/context.h"
#include "../core/export.h"
#include "../event/event.h"
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

        [[nodiscard]] Int2 size() const noexcept { return size_; }
        [[nodiscard]] Float2 sizef() const noexcept { return Float2(size_); }

        template <std::invocable<Event&> Fn>
        void set_event_callback(Fn&& callback) { callback_ = static_cast<Fn&&>(callback); }
        void set_vsync(bool enabled);

        [[nodiscard]] void* handle() const noexcept { return window_; }
        [[nodiscard]] gfx::Context& graphics_context() noexcept { return context_; }
        [[nodiscard]] const gfx::Context& graphics_context() const noexcept { return context_; }

    private:
        void* window_ = nullptr;
        Int2 size_;
        std::function<void(Event&)> callback_;
        gfx::Context context_;

        void set_glfw_callbacks() const;
    };
    PH_RESTORE_EXPORT_WARNING
}
