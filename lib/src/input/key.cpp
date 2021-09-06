#include "phosphorus/input/key.h"

#include <array>

namespace ph
{
    namespace
    {
        // @formatter:off
        constexpr auto get_key_names()
        {
            std::array<std::string_view, static_cast<size_t>(Key::max_size)> result{};
            for (auto& name : result) name = "Undefined";
            result[0] = "None";
            result[32] = "Space"; result[39] = "'";
            const char* comma_to_nine = ",-./0123456789";
            for (size_t i = 44; i <= 57; i++) result[i] = std::string_view{ &comma_to_nine[i - 44], 1 };
            result[59] = ";"; result[61] = "=";
            const char* a_to_right_bracket = "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]";
            for (size_t i = 65; i <= 93; i++) result[i] = std::string_view{ &a_to_right_bracket[i - 65], 1 };
            result[96] = "`";
            result[161] = "World 1";     result[162] = "World 2";
            result[256] = "Escape";      result[257] = "Enter";      result[258] = "Tab";
            result[259] = "Backspace";   result[260] = "Insert";     result[261] = "Delete";
            result[262] = "Right";       result[263] = "Left";       result[264] = "Down";
            result[265] = "Up";          result[266] = "PageUp";     result[267] = "PageDown";
            result[268] = "Home";        result[269] = "End";
            result[280] = "CapsLock";    result[281] = "ScrollLock"; result[282] = "NumLock";
            result[283] = "PrintScreen"; result[284] = "Pause";
            result[290] = "F1";  result[291] = "F2";  result[292] = "F3";  result[293] = "F4";
            result[294] = "F5";  result[295] = "F6";  result[296] = "F7";  result[297] = "F8";
            result[298] = "F9";  result[299] = "F10"; result[300] = "F11"; result[301] = "F12";
            result[302] = "F13"; result[303] = "F14"; result[304] = "F15"; result[305] = "F16";
            result[306] = "F17"; result[307] = "F18"; result[308] = "F19"; result[309] = "F20";
            result[310] = "F21"; result[311] = "F22"; result[312] = "F23"; result[313] = "F24";
            result[314] = "F25";
            result[320] = "Numpad0";     result[321] = "Numpad1"; result[322] = "Numpad2";
            result[323] = "Numpad3";     result[324] = "Numpad4"; result[325] = "Numpad5";
            result[326] = "Numpad6";     result[327] = "Numpad7"; result[328] = "Numpad8";
            result[329] = "Numpad9";     result[330] = "Numpad."; result[331] = "Numpad/";
            result[332] = "Numpad*";     result[333] = "Numpad-"; result[334] = "Numpad+";
            result[335] = "NumpadEnter"; result[336] = "Numpad=";
            result[340] = "LShift"; result[341] = "LCtrl";
            result[342] = "LAlt";   result[343] = "LSuper";
            result[344] = "RShift"; result[345] = "RCtrl";
            result[346] = "RAlt";   result[347] = "RSuper";
            result[348] = "Menu";   result[349] = "Unknown";
            return result;
        }
        // @formatter:on

        inline constexpr auto key_names = get_key_names();
    }

    std::string tag_invoke(to_string_t, const Key key)
    {
        return std::string(key_names[static_cast<size_t>(key)]);
    }
}
