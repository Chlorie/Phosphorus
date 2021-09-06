#include "phosphorus/event/key_events.h"

namespace ph
{
    std::string KeyPressedEvent::to_string() const
    {
        return fmt::format("[KeyPressedEvent (key: {}, repeat: {})]",
            key_code_, repeat_);
    }

    std::string KeyReleasedEvent::to_string() const
    {
        return fmt::format("[KeyReleasedEvent (key: {})]", key_code_);
    }

    std::string KeyTypedEvent::to_string() const
    {
        return fmt::format("[KeyTypedEvent (code point: {})]",
            static_cast<uint32_t>(code_point_));
    }
}
