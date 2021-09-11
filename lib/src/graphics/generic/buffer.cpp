#include "phosphorus/graphics/generic/buffer.h"

#include "buffer_base.h"
#include "phosphorus/graphics/generic/context.h"
#include "context_base.h"

namespace ph::gfx
{
    VertexBuffer::VertexBuffer(Context& context, const size_t size) { impl_ = context.impl()->create_vertex_buffer(size); }
    VertexBuffer::VertexBuffer(Context& context, const clu::const_buffer data):
        VertexBuffer(context, data.size()) { impl_->set_data(data); }
    void VertexBuffer::set_data(const clu::const_buffer data) { impl_->set_data(data); }

    IndexBuffer::IndexBuffer(Context& context, const size_t size) { impl_ = context.impl()->create_index_buffer(size); }
    IndexBuffer::IndexBuffer(Context& context, const clu::const_buffer data):
        IndexBuffer(context, data.size()) { impl_->set_data(data); }
    void IndexBuffer::set_data(const clu::const_buffer data) { impl_->set_data(data); }
}
