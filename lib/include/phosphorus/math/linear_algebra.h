#pragma once

#include <span>
#include <fmt/core.h>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "color.h"

namespace ph
{
    template <typename T, size_t Dim> using Vector = glm::vec<Dim, T>;

    template <typename T> using Vector2 = Vector<T, 2>;
    template <typename T> using Vector3 = Vector<T, 3>;
    template <typename T> using Vector4 = Vector<T, 4>;

    using Int2 = glm::ivec2;
    using Int3 = glm::ivec3;
    using Int4 = glm::ivec4;
    using Float2 = glm::vec2;
    using Float3 = glm::vec3;
    using Float4 = glm::vec4;
    using Float2x2 = glm::mat2;
    using Float3x3 = glm::mat3;
    using Float4x4 = glm::mat4;

    PH_API constexpr Color to_color(const Float4& vector)
    {
        return
        {
            static_cast<uint8_t>(vector.r * 255.0f), static_cast<uint8_t>(vector.g * 255.0f),
            static_cast<uint8_t>(vector.b * 255.0f), static_cast<uint8_t>(vector.a * 255.0f)
        };
    }

    PH_API constexpr Float4 to_vector4(const Color color)
    {
        return
        {
            static_cast<float>(color.r) / 255.0f, static_cast<float>(color.g) / 255.0f,
            static_cast<float>(color.b) / 255.0f, static_cast<float>(color.a) / 255.0f
        };
    }
}

template <typename T, size_t Dim>
struct fmt::formatter<glm::vec<Dim, T>> : formatter<std::string_view>
{
    template <typename FmtCtx>
    auto format(const glm::vec<Dim, T>& vec, FmtCtx& context)
    {
        return formatter<std::string_view>::format(
            fmt::format("({})",
                fmt::join(std::span<const T, Dim>(glm::value_ptr(vec), Dim), ", ")),
            context);
    }
};
