#pragma once

#include "event.h"
#include "../math/linear_algebra.h"

namespace ph
{
    class PH_API WindowEvent : public Event
    {
    public:
        WindowEvent(const WindowEvent&) = default;
        WindowEvent(WindowEvent&&) noexcept = default;
        WindowEvent& operator=(const WindowEvent&) = default;
        WindowEvent& operator=(WindowEvent&&) noexcept = default;
        EventFlags flags() const noexcept override { return EventFlagBits::window; }

    protected:
        WindowEvent() = default;
        ~WindowEvent() noexcept = default;
    };

    class PH_API WindowCloseEvent final : public WindowEvent
    {
    public:
        WindowCloseEvent() = default;
        EventType type() const noexcept override { return EventType::window_close; }
    };

    class PH_API WindowFocusEvent final : public WindowEvent
    {
    public:
        WindowFocusEvent() = default;
        EventType type() const noexcept override { return EventType::window_focus; }
    };

    class PH_API WindowLostFocusEvent final : public WindowEvent
    {
    public:
        WindowLostFocusEvent() = default;
        EventType type() const noexcept override { return EventType::window_lost_focus; }
    };

    PH_SUPPRESS_EXPORT_WARNING
    class PH_API WindowResizedEvent final : public WindowEvent
    {
    public:
        explicit WindowResizedEvent(const Int2 size): size_(size) {}
        Int2 size() const noexcept { return size_; }
        EventType type() const noexcept override { return EventType::window_resized; }
        std::string to_string() const override;

    private:
        Int2 size_;
    };
    PH_RESTORE_EXPORT_WARNING
}
