#pragma once

#include <clu/tag_invoke.h>
#include <fmt/core.h>
#include <fmt/ranges.h>

namespace ph
{
    inline constexpr struct to_string_t final
    {
        template <typename T> requires
            clu::tag_invocable<to_string_t, T&&> &&
            std::convertible_to<clu::tag_invoke_result_t<to_string_t, T&&>, std::string>
        constexpr std::string operator()(T&& value) const noexcept(
            clu::nothrow_tag_invocable<to_string_t, T&&> &&
            std::is_nothrow_convertible_v<clu::tag_invoke_result_t<to_string_t, T&&>, std::string>)
        {
            return clu::tag_invoke(*this, static_cast<T&&>(value));
        }
    } to_string{};
}

template <typename T>
    requires requires(const T& value) { ph::to_string(value); }
struct fmt::formatter<T> : formatter<std::string_view>
{
    template <typename FmtCtx>
    auto format(const T& value, FmtCtx& context)
    {
        return formatter<std::string_view>::format(
            ph::to_string(value), context);
    }
};
