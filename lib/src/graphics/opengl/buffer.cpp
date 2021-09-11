#include "buffer.h"

#include <glad/glad.h>

namespace ph::gfx::opengl
{
    VertexBuffer::~VertexBuffer() noexcept
    {
        glDeleteBuffers(1, &id_);
    }

    void VertexBuffer::set_data(const clu::const_buffer data)
    {
        bind();
        glBufferData(GL_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(data.size()), data.data(), GL_STATIC_DRAW);
    }

    void VertexBuffer::bind()
    {
        thread_local uint32_t id = 0;
        if (id_ != id)
        {
            glBindBuffer(GL_ARRAY_BUFFER, id_);
            id_ = id;
        }
    }

    IndexBuffer::~IndexBuffer() noexcept
    {
        glDeleteBuffers(1, &id_);
    }

    void IndexBuffer::set_data(const clu::const_buffer data)
    {
        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(data.size()), data.data(), GL_STATIC_DRAW);
    }

    void IndexBuffer::bind()
    {
        thread_local uint32_t id = 0;
        if (id_ != id)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
            id_ = id;
        }
    }
}
