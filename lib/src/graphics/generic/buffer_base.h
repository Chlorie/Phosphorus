#pragma once

#include <clu/buffer.h>

namespace ph::gfx
{
    class VertexBufferBase
    {
    public:
        virtual void set_data(clu::const_buffer data) = 0;

    protected:
        ~VertexBufferBase() noexcept = default;
    };

    class IndexBufferBase
    {
    public:
        virtual void set_data(clu::const_buffer data) = 0;

    protected:
        ~IndexBufferBase() noexcept = default;
    };
}
