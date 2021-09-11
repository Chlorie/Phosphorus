#pragma once

#include "../generic/context_base.h"

namespace ph::gfx::opengl
{
    class Context final : public ContextBase
    {
    public:
        explicit Context(void* handle);
        RenderBackend backend() const noexcept override { return RenderBackend::opengl; }
        Pimpl<VertexBufferBase> create_vertex_buffer(size_t size) override;
        Pimpl<IndexBufferBase> create_index_buffer(size_t size) override;
        void swap_buffers() override;
        void clear_color(Color color) override;

    private:
        void* window_ = nullptr;
        void set_as_current();
    };
}
