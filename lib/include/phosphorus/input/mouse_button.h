#pragma once

#include "../core/export.h"
#include "../utils/format.h"

namespace ph
{
    enum class MouseButton : uint8_t { left, right, middle, unknown, max_value };

    PH_API std::string tag_invoke(to_string_t, MouseButton button);
}
