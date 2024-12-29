#include "key_remapper.h"
// Define a map to hold the string-to-keycode mappings
map<string, int> keyCodeMap = {
    // Function keys
    {"F1", 0x70},  // VK_F1
    {"F2", 0x71},  // VK_F2
    {"F3", 0x72},  // VK_F3
    {"F4", 0x73},  // VK_F4
    {"F5", 0x74},  // VK_F5
    {"F6", 0x75},  // VK_F6
    {"F7", 0x76},  // VK_F7
    {"F8", 0x77},  // VK_F8
    {"F9", 0x78},  // VK_F9
    {"F10", 0x79}, // VK_F10
    {"F11", 0x7A}, // VK_F11
    {"F12", 0x7B}, // VK_F12
    {"F13", 0x7C}, // VK_F13
    {"F14", 0x7D}, // VK_F14
    {"F15", 0x7E}, // VK_F15
    {"F16", 0x7F}, // VK_F16
    {"F17", 0x80}, // VK_F17
    {"F18", 0x81}, // VK_F18
    {"F19", 0x82}, // VK_F19
    {"F20", 0x83}, // VK_F20
    {"F21", 0x84}, // VK_F21
    {"F22", 0x85}, // VK_F22
    {"F23", 0x86}, // VK_F23
    {"F24", 0x87}, // VK_F24
    
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
    {"Numpad0", 0x60}, // VK_NUMPAD0
    {"Numpad1", 0x61}, // VK_NUMPAD1
    {"Numpad2", 0x62}, // VK_NUMPAD2
    {"Numpad3", 0x63}, // VK_NUMPAD3
    {"Numpad4", 0x64}, // VK_NUMPAD4
    {"Numpad5", 0x65}, // VK_NUMPAD5
    {"Numpad6", 0x66}, // VK_NUMPAD6
    {"Numpad7", 0x67}, // VK_NUMPAD7
    {"Numpad8", 0x68}, // VK_NUMPAD8
    {"Numpad9", 0x69}, // VK_NUMPAD9
    {"NumpadAdd", 0x6B}, // VK_ADD
    {"NumpadSubtract", 0x6D}, // VK_SUBTRACT
    {"NumpadMultiply", 0x6A}, // VK_MULTIPLY
    {"NumpadDivide", 0x6F}, // VK_DIVIDE
    {"NumpadDecimal", 0x6E}, // VK_DECIMAL
    
    // Arrow keys
    {"Up", 0x26},   // VK_UP
    {"Down", 0x28}, // VK_DOWN
    {"Left", 0x25}, // VK_LEFT
    {"Right", 0x27},// VK_RIGHT

    // Modifier keys
    {"CTRL", 0x11},  // VK_CONTROL
    {"SHIFT", 0x10}, // VK_SHIFT
    {"ALT", 0x12},   // VK_MENU
    {"CAPSLOCK", 0x14},  // VK_CAPITAL
    {"ESC", 0x1B},   // VK_ESCAPE
    {"TAB", 0x09},   // VK_TAB
    {"SPACE", 0x20}, // VK_SPACE
    {"ENTER", 0x0D}, // VK_RETURN
    {"BACKSPACE", 0x08}, // VK_BACK

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
    {"COMMA", 0xBC},    // VK_OEM_COMMA
    {"PERIOD", 0xBE},   // VK_OEM_PERIOD
    {"SLASH", 0xBF},    // VK_OEM_2
    {"SEMICOLON", 0xBA},// VK_OEM_1
    {"QUOTE", 0xDE},    // VK_OEM_7
    {"LEFTBRACKET", 0xDB}, // VK_OEM_4
    {"RIGHTBRACKET", 0xDD}, // VK_OEM_6
    {"BACKSLASH", 0xDC},   // VK_OEM_5

    // Other common keys
    {"NUMLOCK", 0x90},   // VK_NUMLOCK
    {"SCROLLLOCK", 0x91},// VK_SCROLL
    {"PRINTSCREEN", 0x2C}, // VK_SNAPSHOT
    {"PAUSE", 0x13},     // VK_PAUSE
    {"INSERT", 0x2D},    // VK_INSERT
    {"HOME", 0x24},      // VK_HOME
    {"PAGEUP", 0x21},    // VK_PRIOR
    {"PAGEDOWN", 0x22},  // VK_NEXT
    {"DEL", 0x2E},       // VK_DELETE
    {"END", 0x23},       // VK_END
    {"SHIFTLEFT", 0xA0}, // VK_LSHIFT
    {"SHIFTRIGHT", 0xA1},// VK_RSHIFT
    {"CTRLLEFT", 0xA2},  // VK_LCONTROL
    {"CTRLRIGHT", 0xA3}, // VK_RCONTROL
    {"ALTLEFT", 0xA4},   // VK_LMENU
    {"ALTRIGHT", 0xA5},  // VK_RMENU

    // Mouse buttons
    {"LEFT_CLICK", 0x01},  // VK_LBUTTON
    {"RIGHT_CLICK", 0x02}, // VK_RBUTTON
    {"MIDDLE_CLICK", 0x04}, // VK_MBUTTON

    // Extra mouse buttons
    {"MFORWARD", 0x05},   // VK_XBUTTON1
    {"MBACK", 0x06},      // VK_XBUTTON2
    {"WHEEL_UP", HR_WHEEL_UP },  // Custom code for wheel up
    {"WHEEL_DOWN", HR_WHEEL_DOWN},// Custom code for wheel down
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