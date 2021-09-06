#pragma once

#include "event.h"
#include "../input/key.h"

namespace ph
{
    class PH_API KeyEvent : public Event
    {
    public:
        KeyEvent(const KeyEvent&) = default;
        KeyEvent(KeyEvent&&) noexcept = default;
        KeyEvent& operator=(const KeyEvent&) = default;
        KeyEvent& operator=(KeyEvent&&) noexcept = default;
        EventFlags flags() const noexcept override { return EventFlagBits::input | EventFlagBits::keyboard; }
        Key key() const noexcept { return key_code_; }

    protected:
        Key key_code_;
        explicit KeyEvent(const Key key): key_code_(key) {}
        ~KeyEvent() noexcept = default;
    };

    class PH_API KeyPressedEvent final : public KeyEvent
    {
    public:
        explicit KeyPressedEvent(const Key key, const bool repeat = false): KeyEvent(key), repeat_(repeat) {}
        bool repeat() const noexcept { return repeat_; }
        EventType type() const noexcept override { return EventType::key_pressed; }
        std::string to_string() const override;

    private:
        bool repeat_ = false;
    };

    class PH_API KeyReleasedEvent final : public KeyEvent
    {
    public:
        explicit KeyReleasedEvent(const Key key): KeyEvent(key) {}
        EventType type() const noexcept override { return EventType::key_released; }
        std::string to_string() const override;
    };

    class PH_API KeyTypedEvent final : public Event
    {
    public:
        explicit KeyTypedEvent(const char32_t code_point): code_point_(code_point) {}
        char32_t code_point() const noexcept { return code_point_; }
        EventFlags flags() const noexcept override { return EventFlagBits::input | EventFlagBits::keyboard; }
        EventType type() const noexcept override { return EventType::key_typed; }
        std::string to_string() const override;

    private:
        char32_t code_point_ = 0;
    };
}
