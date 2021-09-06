#pragma once

#include "event.h"
#include "../math/linear_algebra.h"
#include "../input/mouse_button.h"

namespace ph
{
    class PH_API MouseEvent : public Event
    {
    public:
        MouseEvent(const MouseEvent&) = default;
        MouseEvent(MouseEvent&&) noexcept = default;
        MouseEvent& operator=(const MouseEvent&) = default;
        MouseEvent& operator=(MouseEvent&&) noexcept = default;
        EventFlags flags() const noexcept override { return EventFlagBits::input | EventFlagBits::mouse; }

    protected:
        MouseEvent() = default;
        ~MouseEvent() noexcept = default;
    };

    PH_SUPPRESS_EXPORT_WARNING
    class PH_API MouseMovedEvent final : public MouseEvent
    {
    public:
        explicit MouseMovedEvent(const Float2 pos): pos_(pos) {}
        Float2 position() const noexcept { return pos_; }
        EventType type() const noexcept override { return EventType::mouse_moved; }
        std::string to_string() const override;

    protected:
        Float2 pos_;
    };

    class PH_API MouseScrolledEvent final : public MouseEvent
    {
    public:
        explicit MouseScrolledEvent(const Float2 offset): offset_(offset) {}
        Float2 offset() const noexcept { return offset_; }
        EventType type() const noexcept override { return EventType::mouse_scrolled; }
        std::string to_string() const override;

    protected:
        Float2 offset_;
    };

    class PH_API MouseButtonEvent : public MouseEvent
    {
    public:
        MouseButtonEvent(const MouseButtonEvent&) = default;
        MouseButtonEvent(MouseButtonEvent&&) noexcept = default;
        MouseButtonEvent& operator=(const MouseButtonEvent&) = default;
        MouseButtonEvent& operator=(MouseButtonEvent&&) noexcept = default;

        explicit MouseButtonEvent(const Float2 pos, const MouseButton button): pos_(pos), button_(button) {}
        Float2 position() const noexcept { return pos_; }
        MouseButton button() const noexcept { return button_; }
        std::string to_string() const override;

    protected:
        Float2 pos_;
        MouseButton button_;
        ~MouseButtonEvent() noexcept = default;
    };
    PH_RESTORE_EXPORT_WARNING

    class PH_API MouseButtonPressedEvent final : public MouseButtonEvent
    {
    public:
        using MouseButtonEvent::MouseButtonEvent;
        EventType type() const noexcept override { return EventType::mouse_button_pressed; }
    };

    class PH_API MouseButtonReleasedEvent final : public MouseButtonEvent
    {
    public:
        using MouseButtonEvent::MouseButtonEvent;
        EventType type() const noexcept override { return EventType::mouse_button_released; }
    };
}
