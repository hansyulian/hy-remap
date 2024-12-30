#include "main.h"
// Define a map to hold the string-to-keycode mappings
map<string, int> keyCodeMap = {
    // Function keys
    {"F1", VK_F1},
    {"F2", VK_F2},
    {"F3", VK_F3},
    {"F4", VK_F4},
    {"F5", VK_F5},
    {"F6", VK_F6},
    {"F7", VK_F7},
    {"F8", VK_F8},
    {"F9", VK_F9},
    {"F10", VK_F10},
    {"F11", VK_F11},
    {"F12", VK_F12},
    
    // Number keys
    {"0", '0'},    // N0
    {"1", '1'},    // N1
    {"2", '2'},    // N2
    {"3", '3'},    // N3
    {"4", '4'},    // N4
    {"5", '5'},    // N5
    {"6", '6'},    // N6
    {"7", '7'},    // N7
    {"8", '8'},    // N8
    {"9", '9'},    // N9

    // Numpad keys
    {"NUMPAD_0", VK_NUMPAD0},
    {"NUMPAD_1", VK_NUMPAD1},
    {"NUMPAD_2", VK_NUMPAD2},
    {"NUMPAD_3", VK_NUMPAD3},
    {"NUMPAD_4", VK_NUMPAD4},
    {"NUMPAD_5", VK_NUMPAD5},
    {"NUMPAD_6", VK_NUMPAD6},
    {"NUMPAD_7", VK_NUMPAD7},
    {"NUMPAD_8", VK_NUMPAD8},
    {"NUMPAD_9", VK_NUMPAD9},
    {"NUMPAD_ADD", VK_ADD},
    {"NUMPAD_SUBTRACT", VK_SUBTRACT},
    {"NUMPAD_MULTIPLY", VK_MULTIPLY},
    {"NUMPAD_DIVIDE", VK_DIVIDE},
    {"NUMPAD_DECIMAL", VK_DECIMAL},
    
    // Arrow keys
    {"Up", VK_UP},   // VK_UP
    {"Down", VK_DOWN}, // VK_DOWN
    {"Left", VK_LEFT}, // VK_LEFT
    {"Right", VK_RIGHT},// VK_RIGHT

    // Modifier keys
    {"CTRL", VK_CONTROL},        // 0x11
    {"SHIFT", VK_SHIFT},         // 0x10
    {"ALT", VK_MENU},            // 0x12
    {"CAPSLOCK", VK_CAPITAL},    // 0x14
    {"ESC", VK_ESCAPE},          // 0x1B
    {"TAB", VK_TAB},             // 0x09
    {"SPACE", VK_SPACE},         // 0x20
    {"ENTER", VK_RETURN},        // 0x0D
    {"BACKSPACE", VK_BACK},      // 0x08

    // Letter keys (A-Z)
    {"A", 'A'},
    {"B", 'B'},
    {"C", 'C'},
    {"D", 'D'},
    {"E", 'E'},
    {"F", 'F'},
    {"G", 'G'},
    {"H", 'H'},
    {"I", 'I'},
    {"J", 'J'},
    {"K", 'K'},
    {"L", 'L'},
    {"M", 'M'},
    {"N", 'N'},
    {"O", 'O'},
    {"P", 'P'},
    {"Q", 'Q'},
    {"R", 'R'},
    {"S", 'S'},
    {"T", 'T'},
    {"U", 'U'},
    {"V", 'V'},
    {"W", 'W'},
    {"X", 'X'},
    {"Y", 'Y'},
    {"Z", 'Z'},

    // Punctuation and other keys
    {"COMMA", VK_OEM_COMMA},       // 0xBC
    {"PERIOD", VK_OEM_PERIOD},     // 0xBE
    {"SLASH", VK_OEM_2},           // 0xBF
    {"SEMICOLON", VK_OEM_1},       // 0xBA
    {"QUOTE", VK_OEM_7},           // 0xDE
    {"LEFTBRACKET", VK_OEM_4},     // 0xDB
    {"RIGHTBRACKET", VK_OEM_6},    // 0xDD
    {"BACKSLASH", VK_OEM_5},       // 0xDC

    // Other common keys
    {"NUMLOCK", VK_NUMLOCK},        // 0x90
    {"SCROLLLOCK", VK_SCROLL},      // 0x91
    {"PRINTSCREEN", VK_SNAPSHOT},   // 0x2C
    {"PAUSE", VK_PAUSE},            // 0x13
    {"INSERT", VK_INSERT},          // 0x2D
    {"HOME", VK_HOME},              // 0x24
    {"PAGEUP", VK_PRIOR},           // 0x21
    {"PAGEDOWN", VK_NEXT},          // 0x22
    {"DEL", VK_DELETE},             // 0x2E
    {"END", VK_END},                // 0x23
    {"LWIN",VK_LWIN},
    {"RWIN",VK_RWIN},
    {"LSHIFT", VK_LSHIFT},       // 0xA0
    {"RSHIFT", VK_RSHIFT},      // 0xA1
    {"LCTRL", VK_LCONTROL},      // 0xA2
    {"RCTRL", VK_RCONTROL},     // 0xA3
    {"LALT", VK_LMENU},          // 0xA4
    {"RALT", VK_RMENU},         // 0xA5

    // Mouse buttons
    {"LEFT_CLICK", VK_LBUTTON},     // 0x01
    {"RIGHT_CLICK", VK_RBUTTON},    // 0x02
    {"MIDDLE_CLICK", VK_MBUTTON},   // 0x04
    {"WHEEL_UP", HR_WHEEL_UP },  // Custom code for wheel up
    {"WHEEL_DOWN", HR_WHEEL_DOWN},// Custom code for wheel down

    // Extra mouse buttons
    {"MFORWARD", VK_XBUTTON1},      // 0x05
    {"MBACK", VK_XBUTTON2},          // 0x06
    {"VOLUME_UP",VK_VOLUME_UP},
    {"VOLUME_DOWN",VK_VOLUME_DOWN},
    {"PLAY_PAUSE", VK_MEDIA_PLAY_PAUSE}, // 0xE0
    {"STOP", VK_MEDIA_STOP}, // 0xE0
    {"MUTE", VK_VOLUME_MUTE},
    {"NEXT_TRACK", VK_MEDIA_NEXT_TRACK}, // 0xB0
    {"PREV_TRACK", VK_MEDIA_PREV_TRACK}, // 0xB1
};

// Function to get key code by string
int getKeyCodeFromString(const std::string& key) {
    auto it = keyCodeMap.find(key);
    if (it != keyCodeMap.end()) {
        return it->second;
    } else {
        throw std::invalid_argument("Invalid key name");
    }
}