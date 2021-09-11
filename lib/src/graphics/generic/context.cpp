#include "phosphorus/graphics/generic/context.h"

#include "context_base.h"
#ifdef PHOSPHORUS_OPENGL
#include "../opengl/context.h"
#endif
#include "phosphorus/core/error.h"

namespace ph::gfx
{
    Context::Context(void* handle, const RenderBackend backend)
    {
        using enum RenderBackend;
        switch (backend)
        {
#ifdef PHOSPHORUS_OPENGL
            case opengl:
                impl_.emplace(std::in_place_type<opengl::Context>, handle);
                break;
#endif
            default: fatal_error("Selected render backend is not supported in this build", true);
        }
    }

    void Context::swap_buffers() { impl_->swap_buffers(); }
    void Context::clear_color(const Color color) { impl_->clear_color(color); }
    RenderBackend Context::backend() const noexcept { return impl_->backend(); }
}
