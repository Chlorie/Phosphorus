#include "context.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "buffer.h"
#include "phosphorus/core/error.h"
#include "phosphorus/core/log.h"
#include "phosphorus/math/linear_algebra.h"

namespace ph::gfx::opengl
{
    namespace
    {
        GLFWwindow* cast_window(void* ptr) { return static_cast<GLFWwindow*>(ptr); }

        std::string_view gl_source_name(const GLenum source)
        {
            switch (source)
            {
                case GL_DEBUG_SOURCE_API: return "OpenGL API";
                case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "window-system API";
                case GL_DEBUG_SOURCE_SHADER_COMPILER: return "shading language compiler";
                case GL_DEBUG_SOURCE_THIRD_PARTY: return "3rd-party app associated with OpenGL";
                case GL_DEBUG_SOURCE_APPLICATION: return "application";
                default: return "unknown source";
            }
        }

        std::string_view gl_msg_type(const GLenum type)
        {
            switch (type)
            {
                case GL_DEBUG_TYPE_ERROR: return "Error";
                case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "Deprecated";
                case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "Undefined";
                case GL_DEBUG_TYPE_PORTABILITY: return "Portability";
                case GL_DEBUG_TYPE_PERFORMANCE: return "Performance";
                case GL_DEBUG_TYPE_MARKER: return "Marker";
                case GL_DEBUG_TYPE_PUSH_GROUP: return "Pushing";
                case GL_DEBUG_TYPE_POP_GROUP: return "Popping";
                default: return "Unknown";
            }
        }

        log::Level gl_severity_to_log_level(const GLenum severity)
        {
            switch (severity)
            {
                case GL_DEBUG_SEVERITY_HIGH: return log::Level::err;
                case GL_DEBUG_SEVERITY_MEDIUM: return log::Level::warn;
                case GL_DEBUG_SEVERITY_LOW: return log::Level::info;
                case GL_DEBUG_SEVERITY_NOTIFICATION:
                default: return log::Level::debug;
            }
        }
    }

    Context::Context(void* handle): window_(handle)
    {
        set_as_current();
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
            fatal_error("Failed to load OpenGL functions", true);
        const auto* version = glGetString(GL_VERSION);
        const auto* vendor = glGetString(GL_VENDOR);
        const auto* renderer = glGetString(GL_RENDERER);
        log_engine_info("Initialized OpenGL context");
        log_engine_info("OpenGL version: {}", version);
        log_engine_info("Vendor: {}, Renderer: {}", vendor, renderer);

        if constexpr (is_debug)
        {
            glDebugMessageCallback(
                [](const GLenum source, const GLenum type, const uint32_t id,
                const GLenum severity, const GLsizei length, const char* msg, const void*)
                {
                    log::engine(gl_severity_to_log_level(severity),
                        "[OpenGL Message #{}] [{}] {} (from {})",
                        id, gl_msg_type(type), std::string_view(msg, length), gl_source_name(source));
                }, nullptr);
        }
    }

    Pimpl<VertexBufferBase> Context::create_vertex_buffer(const size_t size)
    {
        set_as_current();
        uint32_t id;
        glGenBuffers(1, &id);
        return Pimpl<VertexBufferBase>(std::in_place_type<VertexBuffer>, id);
    }

    Pimpl<IndexBufferBase> Context::create_index_buffer(size_t size)
    {
        set_as_current();
        uint32_t id;
        glGenBuffers(1, &id);
        return Pimpl<IndexBufferBase>(std::in_place_type<IndexBuffer>, id);
    }

    void Context::swap_buffers() { glfwSwapBuffers(cast_window(window_)); }

    void Context::clear_color(const Color color)
    {
        set_as_current();
        const auto vec = to_vector4(color);
        glClearColor(vec.r, vec.g, vec.b, vec.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Context::set_as_current()
    {
        thread_local Context* current = nullptr;
        if (current != this)
        {
            glfwMakeContextCurrent(cast_window(window_));
            current = this;
        }
    }
}
