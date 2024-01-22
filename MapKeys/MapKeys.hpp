#pragma once

#include <unordered_map>
#include <Windows.h>

namespace MapKeys {

	/// @brief Map of character keys to their corresponding virtual key codes.
	extern std::unordered_map<char, int> keyMap;

	/// @brief Map of extended keys to their corresponding virtual key codes.
	extern std::unordered_map<int, int> keyMapEX;

	/// @brief Map of extended keys to their corresponding names.
	extern std::unordered_map<int, std::string> keyEXName;
}