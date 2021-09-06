#include "phosphorus/graphics/window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "phosphorus/core/error.h"
#include "phosphorus/core/log.h"
#include "phosphorus/event/key_events.h"
#include "phosphorus/event/mouse_events.h"
#include "phosphorus/event/window_events.h"

namespace ph
{
    namespace
    {
        GLFWwindow* cast_window(void* ptr) { return static_cast<GLFWwindow*>(ptr); }
        Window& user_ref(GLFWwindow* ptr) { return *static_cast<Window*>(glfwGetWindowUserPointer(ptr)); }

        struct GlfwLifetime
        {
            GlfwLifetime()
            {
                if (!glfwInit())
                    fatal_error("Failed to initialize GLFW", true);
            }

            ~GlfwLifetime() noexcept { glfwTerminate(); }
        };
    }

    Window::Window(const clu::c_str_view title, const Int2 size, const RenderBackend backend): size_(size)
    {
        using enum RenderBackend;
        static GlfwLifetime glfw;
        switch (backend)
        {
            case opengl: break;
            default: throw_exception("Selected render backend is not supported yet", true);
        }
        glfwWindowHint(GLFW_RESIZABLE, true);
        window_ = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(cast_window(window_), this);
    }

    Window::~Window() noexcept
    {
        if (window_)
            glfwDestroyWindow(cast_window(window_));
    }

    Window::Window(Window&& other) noexcept:
        window_(std::exchange(other.window_, nullptr)),
        size_(other.size_),
        callback_(std::move(other.callback_)) {}

    Window& Window::operator=(Window&& other) noexcept
    {
        if (this == &other) return *this;
        if (window_)
            glfwDestroyWindow(cast_window(window_));
        window_ = std::exchange(other.window_, nullptr);
        size_ = other.size_;
        glfwSetWindowUserPointer(cast_window(window_), this);
        return *this;
    }

    void Window::swap(Window& other) noexcept
    {
        std::swap(window_, other.window_);
        glfwSetWindowUserPointer(cast_window(window_), this);
        glfwSetWindowUserPointer(cast_window(other.window_), &other);
        std::swap(size_, other.size_);
        std::swap(callback_, other.callback_);
    }

    void Window::close() { glfwSetWindowShouldClose(cast_window(window_), true); }
    bool Window::should_close() const { return glfwWindowShouldClose(cast_window(window_)); }
    void Window::poll_events() { glfwPollEvents(); }

    void Window::clear_color(Color) {} // TODO: implement
    void Window::update() {} // TODO: implement
    void Window::set_vsync(const bool enabled) { glfwSwapInterval(enabled ? 1 : 0); }

    void Window::set_glfw_callbacks() const
    {
        glfwSetWindowSizeCallback(cast_window(window_),
            [](GLFWwindow* glfw_window, const int width, const int height)
            {
                Window& window = user_ref(glfw_window);
                window.size_ = { width, height };
                WindowResizedEvent ev({ width, height });
                window.callback_(ev);
            });

        glfwSetWindowCloseCallback(cast_window(window_),
            [](GLFWwindow* glfw_window)
            {
                Window& window = user_ref(glfw_window);
                WindowCloseEvent ev;
                window.callback_(ev);
            });

        glfwSetWindowFocusCallback(cast_window(window_),
            [](GLFWwindow* glfw_window, const int focus)
            {
                Window& window = user_ref(glfw_window);
                if (focus)
                {
                    WindowFocusEvent ev;
                    window.callback_(ev);
                }
                else
                {
                    WindowLostFocusEvent ev;
                    window.callback_(ev);
                }
            });

        glfwSetKeyCallback(cast_window(window_),
            [](GLFWwindow* glfw_window, const int key, const int scancode, const int action, const int mods)
            {
                (void)scancode, (void)mods; // TODO: Deal with these params
                Window& window = user_ref(glfw_window);
                const Key key_code = (key < static_cast<int>(Key::unknown) && key >= 0)
                                         ? static_cast<Key>(key) : Key::unknown;
                if (key_code == Key::unknown) log_engine_warning("Received ev from unknown key");
                switch (action)
                {
                    case GLFW_PRESS:
                    {
                        KeyPressedEvent ev(key_code, false);
                        window.callback_(ev);
                        return;
                    }
                    case GLFW_REPEAT:
                    {
                        KeyPressedEvent ev(key_code, true);
                        window.callback_(ev);
                        return;
                    }
                    case GLFW_RELEASE:
                    {
                        KeyReleasedEvent ev{ key_code };
                        window.callback_(ev);
                        return;
                    }
                    default: throw_exception("Unknown key action", true);
                }
            });

        glfwSetCharCallback(cast_window(window_),
            [](GLFWwindow* glfw_window, const uint32_t code_point)
            {
                Window& window = user_ref(glfw_window);
                KeyTypedEvent ev(static_cast<char32_t>(code_point));
                window.callback_(ev);
            });

        glfwSetMouseButtonCallback(cast_window(window_),
            [](GLFWwindow* glfw_window, const int button, const int action, const int mods)
            {
                (void)mods; // TODO: Deal with these params
                Window& window = user_ref(glfw_window);
                MouseButton mouse_button;
                switch (button)
                {
                    case GLFW_MOUSE_BUTTON_LEFT: mouse_button = MouseButton::left;
                        break;
                    case GLFW_MOUSE_BUTTON_RIGHT: mouse_button = MouseButton::right;
                        break;
                    case GLFW_MOUSE_BUTTON_MIDDLE: mouse_button = MouseButton::middle;
                        break;
                    default:
                    {
                        mouse_button = MouseButton::unknown;
                        log_engine_warning("Received ev from unknown mouse button");
                        break;
                    }
                }
                double x, y;
                glfwGetCursorPos(glfw_window, &x, &y);
                switch (action)
                {
                    case GLFW_PRESS:
                    {
                        MouseButtonPressedEvent ev({ static_cast<float>(x), static_cast<float>(y) }, mouse_button);
                        window.callback_(ev);
                        return;
                    }
                    case GLFW_RELEASE:
                    {
                        MouseButtonReleasedEvent ev({ static_cast<float>(x), static_cast<float>(y) }, mouse_button);
                        window.callback_(ev);
                        return;
                    }
                    default: throw_exception("Unknown mouse button action", true);
                }
            });

        glfwSetScrollCallback(cast_window(window_),
            [](GLFWwindow* glfw_window, const double x_off, const double y_off)
            {
                Window& window = user_ref(glfw_window);
                MouseScrolledEvent ev({ static_cast<float>(x_off), static_cast<float>(y_off) });
                window.callback_(ev);
            });

        glfwSetCursorPosCallback(cast_window(window_),
            [](GLFWwindow* glfw_window, const double x, const double y)
            {
                Window& window = user_ref(glfw_window);
                MouseMovedEvent ev({ static_cast<float>(x), static_cast<float>(y) });
                window.callback_(ev);
            });

        glfwSetErrorCallback([](const int error_code, const char* description)
        {
            log_engine_error("GLFW error ({}): {}", error_code, description);
        });
    }
}
