#include "phosphorus/event/window_events.h"

namespace ph
{
    std::string WindowResizedEvent::to_string() const
    {
        return fmt::format("[WindowResizedEvent (size: {})]", size_);
    }
}
