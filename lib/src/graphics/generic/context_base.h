#pragma once

#include "phosphorus/graphics/generic/render_backend.h"
#include "phosphorus/math/color.h"
#include "phosphorus/utils/pimpl.h"

namespace ph::gfx
{
    class ContextBase
    {
    public:
        virtual RenderBackend backend() const noexcept = 0;
        virtual Pimpl<class VertexBufferBase> create_vertex_buffer(size_t size) = 0;
        virtual Pimpl<class IndexBufferBase> create_index_buffer(size_t size) = 0;
        virtual void swap_buffers() = 0;
        virtual void clear_color(Color color)  = 0;

    protected:
        ~ContextBase() noexcept = default;
    };
}
