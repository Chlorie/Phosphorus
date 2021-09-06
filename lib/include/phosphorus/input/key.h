#pragma once

#include "../core/export.h"
#include "../utils/format.h"

namespace ph
{
    // Currently copying GLFW's key codes
    enum class Key : uint16_t
    {
        none,
        space = 32, apostrophe = 39,
        comma = 44, minus, period, slash,
        num_0, num_1, num_2, num_3, num_4, num_5, num_6, num_7, num_8, num_9,
        semicolon = 59, equal = 61,
        a = 65, b, c, d, e, f, g, h, i, j, k, l, m,
        n, o, p, q, r, s, t, u, v, w, x, y, z,
        left_bracket, backslash, right_bracket,
        grave = 96, world_1 = 161, world_2,
        escape = 256, enter, tab, backspace, insert, delete_,
        right, left, down, up, page_up, page_down, home, end,
        caps_lock = 280, scroll_lock, num_lock, print_screen, pause,
        f1 = 290, f2, f3, f4, f5, f6, f7, f8, f9, f10,
        f11, f12, f13, f14, f15, f16, f17, f18, f19, f20,
        f21, f22, f23, f24, f25,
        numpad_0 = 320, numpad_1, numpad_2, numpad_3, numpad_4,
        numpad_5, numpad_6, numpad_7, numpad_8, numpad_9,
        numpad_decimal, numpad_divide, numpad_multiply, numpad_subtract, numpad_add,
        numpad_enter, numpad_equal,
        left_shift = 340, left_control, left_alt, left_super,
        right_shift, right_control, right_alt, right_super,
        menu, unknown,
        max_size
    };

    PH_API std::string tag_invoke(to_string_t, Key key);
}
