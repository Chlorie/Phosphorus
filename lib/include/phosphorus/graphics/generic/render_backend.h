#pragma once

#include <cstdint>

namespace ph
{
    enum class RenderBackend : uint8_t
    {
        opengl, d3d11, vulkan
    };
}
