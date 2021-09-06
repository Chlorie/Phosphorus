#pragma once

#include <memory>
#include <string>

#include "../core/export.h"

namespace ph
{
    class Event;

    namespace detail
    {
        struct LayerVTable final
        {
            void (*destroy)(void*) = nullptr;
            void (*on_attach)(void*) = nullptr;
            void (*on_detach)(void*) = nullptr;
            void (*on_update)(void*) = nullptr;
            void (*on_event)(void*, Event&) = nullptr;
            void (*on_render)(void*) = nullptr;
            void (*on_imgui)(void*) = nullptr;
        };

        // TODO: convert to requires expression once MSVC supports it
        template <typename T> concept has_on_attach = requires(T& layer) { layer.on_attach(); };
        template <typename T> concept has_on_detach = requires(T& layer) { layer.on_detach(); };
        template <typename T> concept has_on_update = requires(T& layer) { layer.on_update(); };
        template <typename T> concept has_on_event = requires(T& layer, Event& ev) { layer.on_event(ev); };
        template <typename T> concept has_on_render = requires(T& layer) { layer.on_render(); };
        template <typename T> concept has_on_imgui = requires(T& layer) { layer.on_imgui(); };

        // I want metaclass
        // `auto ptr` instead of `void* ptr` to circumvent a weird MSVC issue regarding if constexpr
#define PH_GEN_LAYER_VTABLE(func_name)                                      \
        []() -> void(*)(void*)                                              \
        {                                                                   \
            if constexpr (has_##func_name<T>)                               \
                return [](auto ptr) { static_cast<T*>(ptr)->func_name(); }; \
            else                                                            \
                return nullptr;                                             \
        }()

        template <typename T>
        inline constexpr LayerVTable layer_vtable_for =
        {
            [](void* ptr) { delete static_cast<T*>(ptr); },
            PH_GEN_LAYER_VTABLE(on_attach),
            PH_GEN_LAYER_VTABLE(on_detach),
            PH_GEN_LAYER_VTABLE(on_update),
            []() -> void(*)(void*, Event&)
            {
                if constexpr (has_on_event<T>)
                    return [](auto ptr, Event& ev) { static_cast<T*>(ptr)->on_event(ev); };
                else
                    return nullptr;
            }(),
            PH_GEN_LAYER_VTABLE(on_render),
            PH_GEN_LAYER_VTABLE(on_imgui)
        };
#undef PH_GEN_LAYER_VTABLE

        template <typename... Args>
        void call_if_not_null(void (*fptr)(Args ...), std::type_identity_t<Args> ... args)
        {
            if (fptr)
                fptr(static_cast<Args>(args)...);
        }
    }

    PH_SUPPRESS_EXPORT_WARNING
    class PH_API Layer final
    {
    public:
        ~Layer() noexcept { if (ptr_) vtable_->destroy(ptr_); }
        Layer(const Layer&) = delete;
        Layer(Layer&& other) noexcept: vtable_(other.vtable_), ptr_(std::exchange(other.ptr_, nullptr)) {}
        Layer& operator=(const Layer&) = delete;

        Layer& operator=(Layer&& other) noexcept
        {
            if (&other == this) return *this;
            if (ptr_) vtable_->destroy(ptr_);
            vtable_ = other.vtable_;
            ptr_ = std::exchange(other.ptr_, nullptr);
            return *this;
        }

        template <typename T, typename... Ts>
        [[nodiscard]] static Layer create(const std::string_view name, Ts&&... args)
        {
            return Layer(&detail::layer_vtable_for<T>,
                new T(static_cast<Ts&&>(args)...), name);
        }

        void on_attach() { detail::call_if_not_null(vtable_->on_attach, ptr_); }
        void on_detach() { detail::call_if_not_null(vtable_->on_detach, ptr_); }
        void on_update() { detail::call_if_not_null(vtable_->on_update, ptr_); }
        void on_event(Event& ev) { detail::call_if_not_null(vtable_->on_event, ptr_, ev); }
        void on_render() { detail::call_if_not_null(vtable_->on_render, ptr_); }
        void on_imgui() { detail::call_if_not_null(vtable_->on_imgui, ptr_); }

        [[nodiscard]] std::string_view name() const noexcept { return name_; }
        [[nodiscard]] void* data() noexcept { return ptr_; }
        [[nodiscard]] const void* data() const noexcept { return ptr_; }

    private:
        const detail::LayerVTable* vtable_ = nullptr;
        void* ptr_ = nullptr;
        std::string name_;

        Layer(const detail::LayerVTable* vtable, void* ptr, const std::string_view name):
            vtable_(vtable), ptr_(ptr), name_(name) {}
    };
    PH_RESTORE_EXPORT_WARNING
}
