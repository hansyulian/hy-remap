#include "modules.h"
// Define a map to hold the string-to-keycode mappings
map<string, int> keyCodeMap = {
    // Function keys
    {"F1", VK_F1},    // {0x70}     {112}    {F1}
    {"F2", VK_F2},    // {0x71}     {113}    {F2}
    {"F3", VK_F3},    // {0x72}     {114}    {F3}
    {"F4", VK_F4},    // {0x73}     {115}    {F4}
    {"F5", VK_F5},    // {0x74}     {116}    {F5}
    {"F6", VK_F6},    // {0x75}     {117}    {F6}
    {"F7", VK_F7},    // {0x76}     {118}    {F7}
    {"F8", VK_F8},    // {0x77}     {119}    {F8}
    {"F9", VK_F9},    // {0x78}     {120}    {F9}
    {"F10", VK_F10},  // {0x79}     {121}    {F10}
    {"F11", VK_F11},  // {0x7A}     {122}    {F11}
    {"F12", VK_F12},  // {0x7B}     {123}    {F12}
    {"F13", VK_F13},  // {0x7C}     {124}    {F13}
    {"F14", VK_F14},  // {0x7D}     {125}    {F14}
    {"F15", VK_F15},  // {0x7E}     {126}    {F15}
    {"F16", VK_F16},  // {0x7F}     {127}    {F16}
    {"F17", VK_F17},  // {0x80}     {128}    {F17}
    {"F18", VK_F18},  // {0x81}     {129}    {F18}
    {"F19", VK_F19},  // {0x82}     {130}    {F19}
    {"F20", VK_F20},  // {0x83}     {131}    {F20}
    {"F21", VK_F21},  // {0x84}     {132}    {F21}
    {"F22", VK_F22},  // {0x85}     {133}    {F22}
    {"F23", VK_F23},  // {0x86}     {134}    {F23}
    {"F24", VK_F24},  // {0x87}     {135}    {F24}
    
    // Number keys
    {"0", '0'},        // {0x30}    {48}    {0}
    {"1", '1'},        // {0x31}    {49}    {1}
    {"2", '2'},        // {0x32}    {50}    {2}
    {"3", '3'},        // {0x33}    {51}    {3}
    {"4", '4'},        // {0x34}    {52}    {4}
    {"5", '5'},        // {0x35}    {53}    {5}
    {"6", '6'},        // {0x36}    {54}    {6}
    {"7", '7'},        // {0x37}    {55}    {7}
    {"8", '8'},        // {0x38}    {56}    {8}
    {"9", '9'},        // {0x39}    {57}    {9}

    // Numpad keys
    {"NUMPAD_0", VK_NUMPAD0},     // {0x60}     {96}     {NUMPAD 0}
    {"NUMPAD_1", VK_NUMPAD1},     // {0x61}     {97}     {NUMPAD 1}
    {"NUMPAD_2", VK_NUMPAD2},     // {0x62}     {98}     {NUMPAD 2}
    {"NUMPAD_3", VK_NUMPAD3},     // {0x63}     {99}     {NUMPAD 3}
    {"NUMPAD_4", VK_NUMPAD4},     // {0x64}     {100}    {NUMPAD 4}
    {"NUMPAD_5", VK_NUMPAD5},     // {0x65}     {101}    {NUMPAD 5}
    {"NUMPAD_6", VK_NUMPAD6},     // {0x66}     {102}    {NUMPAD 6}
    {"NUMPAD_7", VK_NUMPAD7},     // {0x67}     {103}    {NUMPAD 7}
    {"NUMPAD_8", VK_NUMPAD8},     // {0x68}     {104}    {NUMPAD 8}
    {"NUMPAD_9", VK_NUMPAD9},     // {0x69}     {105}    {NUMPAD 9}
    {"NUMPAD_ADD", VK_ADD},        // {0x6B}    {107}   {NUMPAD +}
    {"NUMPAD_SUBTRACT", VK_SUBTRACT}, // {0x6D}     {109}    {NUMPAD -}
    {"NUMPAD_MULTIPLY", VK_MULTIPLY}, // {0x6A}     {106}    {NUMPAD *}
    {"NUMPAD_DIVIDE", VK_DIVIDE},     // {0x6F}     {111}    {NUMPAD /}
    {"NUMPAD_DECIMAL", VK_DECIMAL},  // {0x6E}  {110}     {NUMPAD .}

    // Arrow keys
    {"UP", VK_UP},     // {0x26}    {38}    {Up}
    {"DOWN", VK_DOWN}, // {0x28}    {40}    {Down}
    {"LEFT", VK_LEFT}, // {0x25}    {37}    {Left}
    {"RIGHT", VK_RIGHT}, // {0x27}  {39}      {Right}

    // Modifier keys
    {"CTRL", VK_CONTROL},        // {0x11}  {17}      {CTRL}
    {"SHIFT", VK_SHIFT},         // {0x10}  {16}      {SHIFT}
    {"ALT", VK_MENU},            // {0x12}  {18}      {ALT}
    {"CAPSLOCK", VK_CAPITAL},    // {0x14}  {20}      {CAPSLOCK}
    {"ESC", VK_ESCAPE},          // {0x1B}  {27}      {ESC}
    {"TAB", VK_TAB},             // {0x09}  {9}       {TAB}
    {"SPACE", VK_SPACE},         // {0x20}  {32}      {SPACE}
    {"ENTER", VK_RETURN},        // {0x0D}  {13}      {ENTER}
    {"BACKSPACE", VK_BACK},      // {0x08}  {8}       {BACKSPACE}

    // Letter keys (A-Z)
    {"A", 'A'},                  // {0x41}  {65}      {A}
    {"B", 'B'},                  // {0x42}  {66}      {B}
    {"C", 'C'},                  // {0x43}  {67}      {C}
    {"D", 'D'},                  // {0x44}  {68}      {D}
    {"E", 'E'},                  // {0x45}  {69}      {E}
    {"F", 'F'},                  // {0x46}  {70}      {F}
    {"G", 'G'},                  // {0x47}  {71}      {G}
    {"H", 'H'},                  // {0x48}  {72}      {H}
    {"I", 'I'},                  // {0x49}  {73}      {I}
    {"J", 'J'},                  // {0x4A}  {74}      {J}
    {"K", 'K'},                  // {0x4B}  {75}      {K}
    {"L", 'L'},                  // {0x4C}  {76}      {L}
    {"M", 'M'},                  // {0x4D}  {77}      {M}
    {"N", 'N'},                  // {0x4E}  {78}      {N}
    {"O", 'O'},                  // {0x4F}  {79}      {O}
    {"P", 'P'},                  // {0x50}  {80}      {P}
    {"Q", 'Q'},                  // {0x51}  {81}      {Q}
    {"R", 'R'},                  // {0x52}  {82}      {R}
    {"S", 'S'},                  // {0x53}  {83}      {S}
    {"T", 'T'},                  // {0x54}  {84}      {T}
    {"U", 'U'},                  // {0x55}  {85}      {U}
    {"V", 'V'},                  // {0x56}  {86}      {V}
    {"W", 'W'},                  // {0x57}  {87}      {W}
    {"X", 'X'},                  // {0x58}  {88}      {X}
    {"Y", 'Y'},                  // {0x59}  {89}      {Y}
    {"Z", 'Z'},                  // {0x5A}  {90}      {Z}

    // Punctuation and other keys
    {"COMMA", VK_OEM_COMMA},       // {0xBC}    {188}   {,}
    {"PERIOD", VK_OEM_PERIOD},     // {0xBE}    {190}   {.}
    {"SLASH", VK_OEM_2},           // {0xBF}    {191}   {/}
    {"SEMICOLON", VK_OEM_1},       // {0xBA}    {186}   {;}
    {"QUOTE", VK_OEM_7},           // {0xDE}    {222}   {'}
    {"LEFTBRACKET", VK_OEM_4},     // {0xDB}    {219}   {[}
    {"RIGHTBRACKET", VK_OEM_6},    // {0xDD}    {221}   {]}
    {"BACKSLASH", VK_OEM_5},       // {0xDC}    {220}   {\}

    // Other common keys
    {"NUMLOCK", VK_NUMLOCK},        // {0x90}   {144}  {NUMLOCK}
    {"SCROLLLOCK", VK_SCROLL},      // {0x91}   {145}  {SCROLLLOCK}
    {"PRINTSCREEN", VK_SNAPSHOT},   // {0x2C}   {44}   {PRINTSCREEN}
    {"PAUSE", VK_PAUSE},            // {0x13}   {19}   {PAUSE}
    {"INSERT", VK_INSERT},          // {0x2D}   {45}   {INSERT}
    {"HOME", VK_HOME},              // {0x24}   {36}   {HOME}
    {"PAGEUP", VK_PRIOR},           // {0x21}   {33}   {PAGEUP}
    {"PAGEDOWN", VK_NEXT},          // {0x22}   {34}   {PAGEDOWN}
    {"DEL", VK_DELETE},             // {0x2E}   {46}   {DEL}
    {"END", VK_END},                // {0x23}   {35}   {END}
    {"LWIN", VK_LWIN},              // {0x5B}   {91}   {LWIN}
    {"RWIN", VK_RWIN},              // {0x5C}   {92}   {RWIN}
    {"LSHIFT", VK_LSHIFT},          // {0xA0}   {160}  {LSHIFT}
    {"RSHIFT", VK_RSHIFT},          // {0xA1}   {161}  {RSHIFT}
    {"LCTRL", VK_LCONTROL},         // {0xA2}   {162}  {LCTRL}
    {"RCTRL", VK_RCONTROL},         // {0xA3}   {163}  {RCTRL}
    {"LALT", VK_LMENU},             // {0xA4}   {164}  {LALT}
    {"RALT", VK_RMENU},             // {0xA5}   {165}  {RALT}

    // Mouse buttons
    {"LEFT_CLICK", VK_LBUTTON},     // {0x01}   {1}    {LEFT_CLICK}
    {"RIGHT_CLICK", VK_RBUTTON},    // {0x02}   {2}    {RIGHT_CLICK}
    {"MIDDLE_CLICK", VK_MBUTTON},   // {0x04}   {4}    {MIDDLE_CLICK}

    // Extra mouse buttons
    {"MFORWARD", VK_XBUTTON1},      // {0x05}   {5}    {MFORWARD}
    {"MBACK", VK_XBUTTON2},         // {0x06}   {6}    {MBACK}
    {"VOLUME_UP", VK_VOLUME_UP},    // {0xAE}   {175}  {VOLUME_UP}
    {"VOLUME_DOWN", VK_VOLUME_DOWN},// {0xAD}   {174}  {VOLUME_DOWN}
    {"PLAY_PAUSE", VK_MEDIA_PLAY_PAUSE}, // {0xB3}  {179}     {PLAY_PAUSE}
    {"STOP", VK_MEDIA_STOP},       // {0xB2}    {178}   {STOP}
    {"MUTE", VK_VOLUME_MUTE},      // {0xAD}    {174}   {MUTE}
    {"NEXT_TRACK", VK_MEDIA_NEXT_TRACK}, // {0xB0}  {176}     {NEXT_TRACK}
    {"PREV_TRACK", VK_MEDIA_PREV_TRACK}, // {0xB1}   {177}  {PREV_TRACK}

    // extra bind namings
    {"WHEEL_UP", HR_WHEEL_UP },  // Custom code for wheel up
    {"WHEEL_DOWN", HR_WHEEL_DOWN},// Custom code for wheel down
    {"TERMINATE_ACTION",HR_TERMINATE_ACTION}
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