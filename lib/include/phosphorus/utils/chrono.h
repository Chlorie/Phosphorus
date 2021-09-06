#pragma once

#include <chrono>

#include "../core/export.h"

namespace ph
{
    using Clock = std::chrono::steady_clock;
    using TimePoint = Clock::time_point;
    using Duration = Clock::duration;

    PH_API constexpr float to_seconds(const Duration dur)
    {
        return std::chrono::duration_cast<std::chrono::duration<float>>(dur).count();
    }
}
