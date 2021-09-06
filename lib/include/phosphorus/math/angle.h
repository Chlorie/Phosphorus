#pragma once

#include <numbers>

#include "../core/export.h"

namespace ph
{
    inline constexpr float pi = std::numbers::pi_v<float>;

    PH_API constexpr float to_radians(const float deg)
    {
        constexpr float ratio = pi / 180.0f;
        return deg * ratio;
    }

    PH_API constexpr float to_degrees(const float rad)
    {
        constexpr float ratio = 180.0f * std::numbers::inv_pi_v<float>;
        return rad * ratio;
    }

    namespace literals
    {
        PH_API constexpr float operator""_deg(const long double deg) { return to_radians(static_cast<float>(deg)); }
        PH_API constexpr float operator""_deg(const uint64_t deg) { return to_radians(static_cast<float>(deg)); }
        PH_API constexpr float operator""_rad(const long double rad) { return to_degrees(static_cast<float>(rad)); }
        PH_API constexpr float operator""_rad(const uint64_t rad) { return to_degrees(static_cast<float>(rad)); }
    }
}
