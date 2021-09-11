#pragma once

#include <clu/buffer.h>

#include "../../core/export.h"
#include "../../utils/pimpl.h"

namespace ph::gfx
{
    class Context;

    class PH_API VertexBuffer final : public PimplBase<class VertexBufferBase>
    {
    public:
        VertexBuffer(Context& context, size_t size);
        VertexBuffer(Context& context, clu::const_buffer data);
        void set_data(clu::const_buffer data);
    };

    class PH_API IndexBuffer final : public PimplBase<class IndexBufferBase>
    {
    public:
        IndexBuffer(Context& context, size_t size);
        IndexBuffer(Context& context, clu::const_buffer data);
        void set_data(clu::const_buffer data);
    };
}
