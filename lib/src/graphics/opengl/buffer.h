#pragma once

#include "../generic/buffer_base.h"
#include "context.h"

namespace ph::gfx::opengl
{
    class VertexBuffer final : public VertexBufferBase
    {
    public:
        explicit VertexBuffer(const uint32_t id): id_(id) {}
        ~VertexBuffer() noexcept;
        void set_data(clu::const_buffer data) override;
    private:
        uint32_t id_;
        void bind();
    };

    class IndexBuffer final : public IndexBufferBase
    {
    public:
        explicit IndexBuffer(const uint32_t id): id_(id) {}
        ~IndexBuffer() noexcept;
        void set_data(clu::const_buffer data) override;
    private:
        uint32_t id_;
        void bind();
    };
}
