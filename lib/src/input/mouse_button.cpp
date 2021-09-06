#include "phosphorus/input/mouse_button.h"

#include <array>

namespace ph
{
    namespace
    {
        // I want reflection, C++-chan please give me reflection
        inline constexpr std::array<std::string_view, static_cast<size_t>(MouseButton::max_value)> names
        {
            "Left", "Right", "Middle", "Unknown"
        };
    }

    std::string tag_invoke(to_string_t, const MouseButton button)
    {
        return std::string(names[static_cast<size_t>(button)]);
    }
}
