#include "phosphorus/event/mouse_events.h"

namespace ph
{
    std::string MouseMovedEvent::to_string() const
    {
        return fmt::format("[MouseMovedEvent (pos: {})]", pos_);
    }

    std::string MouseScrolledEvent::to_string() const
    {
        return fmt::format("[MouseScrolledEvent (offset: {})]", offset_);
    }

    std::string MouseButtonEvent::to_string() const
    {
        return fmt::format("[{} (pos: {}, button: {})]", 
            name(), pos_, button_);
    }
}
