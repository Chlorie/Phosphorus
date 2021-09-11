#pragma once

namespace ph
{
    class VirtualBase
    {
    public:
        virtual ~VirtualBase() noexcept = default;
        VirtualBase() noexcept = default;
        VirtualBase(const VirtualBase&) noexcept = default;
        VirtualBase(VirtualBase&&) noexcept = default;
        VirtualBase& operator=(const VirtualBase&) noexcept = default;
        VirtualBase& operator=(VirtualBase&&) noexcept = default;
    };
}
