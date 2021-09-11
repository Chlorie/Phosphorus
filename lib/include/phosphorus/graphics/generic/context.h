#pragma once

#include "render_backend.h"
#include "../../core/export.h"
#include "../../math/color.h"
#include "../../utils/pimpl.h"

namespace ph::gfx
{
    class PH_API Context final : public PimplBase<class ContextBase>
    {
    public:
        Context(void* handle, RenderBackend backend);
        void swap_buffers();
        void clear_color(Color color);
        [[nodiscard]] RenderBackend backend() const noexcept;
    };
}
