#include "MapKeys.hpp"

// Map of character keys to their corresponding virtual key codes.
std::unordered_map<char, int> MapKeys::keyMap = {
    {'a', 0x41},
    {'b', 0x42},
    {'c', 0x43},
    {'d', 0x44},
    {'e', 0x45},
    {'f', 0x46},
    {'g', 0x47},
    {'h', 0x48},
    {'i', 0x49},
    {'j', 0x4A},
    {'k', 0x4B},
    {'l', 0x4C},
    {'m', 0x4D},
    {'n', 0x4E},
    {'o', 0x4F},
    {'p', 0x50},
    {'q', 0x51},
    {'r', 0x52},
    {'s', 0x53},
    {'t', 0x54},
    {'u', 0x55},
    {'v', 0x56},
    {'w', 0x57},
    {'x', 0x58},
    {'y', 0x59},
    {'z', 0x5A},
    {'0', 0x30},
    {'1', 0x31},
    {'2', 0x32},
    {'3', 0x33},
    {'4', 0x34},
    {'5', 0x35},
    {'6', 0x36},
    {'7', 0x37},
    {'8', 0x38},
    {'9', 0x39},
};

// Map of extended keys to their corresponding virtual key codes.
std::unordered_map<int, int> MapKeys::keyMapEX = {
    {9, VK_TAB},
    {8, VK_BACK},
    {32, VK_SPACE},
};

// Map of extended keys to their corresponding names.
std::unordered_map<int, std::string> MapKeys::keyEXName = {
    {9, "TAB"},
    {8, "BACK"},
    {32, "SPACE"},
};
