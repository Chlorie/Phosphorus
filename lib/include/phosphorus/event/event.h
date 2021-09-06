#pragma once

#include <array>
#include <clu/concepts.h>
#include <clu/flags.h>
#include <clu/meta_list.h>
#include <clu/meta_algorithm.h>

#include "events_fwd.h"
#include "../core/export.h"
#include "../utils/format.h"

namespace ph
{
    enum class EventType : uint8_t
    {
        window_close, window_resized, window_focus, window_lost_focus,
        key_pressed, key_released, key_typed,
        mouse_button_pressed, mouse_button_released, mouse_moved, mouse_scrolled,
        max_value
    };

    using EventTypeList = clu::type_list<
        WindowCloseEvent, WindowResizedEvent, WindowFocusEvent, WindowLostFocusEvent,
        KeyPressedEvent, KeyReleasedEvent, KeyTypedEvent,
        MouseButtonPressedEvent, MouseButtonReleasedEvent, MouseMovedEvent, MouseScrolledEvent>;

    static_assert(EventTypeList::size == static_cast<size_t>(EventType::max_value));
    template <typename Ev> requires (EventTypeList::contains_v<Ev>)
    inline constexpr EventType event_type_of = static_cast<EventType>(clu::meta::find_v<EventTypeList, Ev>);

    // I want reflection!!!
    inline constexpr std::array<std::string_view, EventTypeList::size> event_type_names
    {
        "WindowCloseEvent", "WindowResizedEvent", "WindowFocusEvent", "WindowLostFocusEvent",
        "KeyPressedEvent", "KeyReleasedEvent", "KeyTypedEvent",
        "MouseButtonPressedEvent", "MouseButtonReleasedEvent", "MouseMovedEvent", "MouseScrolledEvent"
    };

    enum class EventFlagBits : uint8_t { window, input, keyboard, mouse, flags_bit_size };
    using namespace clu::flag_enum_operators;
    using EventFlags = clu::flags<EventFlagBits>;

    namespace detail
    {
        template <typename Fn, typename Ev>
        concept EventDispatchable =
        (EventTypeList::contains_v<Ev>) &&
        std::invocable<Fn, Ev&> &&
        clu::same_as_any_of<std::invoke_result_t<Fn, Ev&>, void, bool>;

#ifdef __RESHARPER__ // TODO: Resharper doesn't short circuit concept evaluation (2021.2), remove this after it is fixed
        template <typename Fn, typename Ev>
        constexpr bool invocable_implies_valid_result_impl()
        {
            if constexpr (std::invocable<Fn, Ev&>)
                return clu::same_as_any_of<std::invoke_result_t<Fn, Ev&>, void, bool>;
            else
                return true;
        }
        template <typename Fn, typename Ev>
        concept InvocableImpliesValidResult = invocable_implies_valid_result_impl<Fn, Ev>();
#else
        template <typename Fn, typename Ev>
        concept InvocableImpliesValidResult =
        (!std::invocable<Fn, Ev&>) || clu::same_as_any_of<std::invoke_result_t<Fn, Ev&>, void, bool>;
#endif

        template <typename Fn, typename... Evs>
        constexpr bool void_dispatcher_impl(clu::type_list<Evs...>) noexcept
        {
            return (InvocableImpliesValidResult<Fn, Evs> && ...);
        }

        template <typename Fn, typename Ev>
        concept VoidDispatchable = std::same_as<Ev, void> && void_dispatcher_impl<Fn>(EventTypeList{});
    }

    template <typename Fn, typename Ev>
    concept Dispatchable = detail::VoidDispatchable<Fn, Ev> || detail::EventDispatchable<Fn, Ev>;

    class PH_API Event
    {
    public:
        Event(const Event&) = default;
        Event(Event&&) = default;
        Event& operator=(const Event&) = default;
        Event& operator=(Event&&) = default;

        virtual EventType type() const noexcept = 0;
        std::string_view name() const noexcept { return event_type_names[static_cast<size_t>(type())]; }
        virtual EventFlags flags() const noexcept = 0;
        bool blocked() const noexcept { return blocked_; }
        virtual std::string to_string() const { return fmt::format("[{}]", name()); }

        template <typename Ev = void, Dispatchable<Ev> Fn = void>
        bool dispatch(Fn&& invocable)
        {
            if constexpr (std::is_same_v<Ev, void>)
                return dispatch_void_impl(static_cast<Fn&&>(invocable), EventTypeList{});
            else
            {
                if (event_type_of<Ev> != type()) return false;
                dispatch_to<Ev>(static_cast<Fn&&>(invocable), *this);
                return true;
            }
        }

    protected:
        Event() noexcept = default;
        ~Event() noexcept = default;

    private:
        bool blocked_ = false;

        PH_API friend std::string tag_invoke(to_string_t, const Event& ev) { return ev.to_string(); }

        template <typename Ev, typename Fn>
        static void dispatch_to(Fn&& invocable, Event& ev)
        {
            if constexpr (std::is_void_v<std::invoke_result_t<Fn, Ev&>>)
                std::invoke(std::forward<Fn>(invocable), *static_cast<Ev*>(&ev));
            else
                ev.blocked_ = std::invoke(std::forward<Fn>(invocable), *static_cast<Ev*>(&ev));
        }

        template <typename Fn, typename... Evs>
        bool dispatch_void_impl(Fn&& invocable, clu::type_list<Evs...>)
        {
            using Fptr = void(*)(Fn&&, Event&);
            static constexpr std::array<Fptr, EventTypeList::size> table
            {
                []
                {
                    if constexpr (std::is_invocable_v<Fn, Evs&>)
                        return &Event::dispatch_to<Evs, Fn>;
                    else
                        return nullptr;
                }()...
            };
            const Fptr fptr = table[static_cast<size_t>(type())];
            if (!fptr) return false;
            fptr(std::forward<Fn>(invocable), *this);
            return true;
        }
    };
}
