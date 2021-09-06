#pragma once

#include <glm/glm.hpp>

#include "../core/export.h"

namespace ph
{
    using Color = glm::u8vec4;

    PH_API constexpr Color to_color(const uint32_t value)
    {
        return
        {
            static_cast<uint8_t>(value >> 24), static_cast<uint8_t>(value >> 16),
            static_cast<uint8_t>(value >> 8), static_cast<uint8_t>(value)
        };
    }

    namespace literals
    {
        PH_API constexpr Color operator""_rgba(const uint64_t value) { return to_color(static_cast<uint32_t>(value)); }
        PH_API constexpr Color operator""_rgb(const uint64_t value) { return to_color((static_cast<uint32_t>(value) << 8) + 0xffu); }
    }
}
