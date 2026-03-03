// Search | Search for files and directories easier
// Copyright (C) 2026  Ametrine Foundation

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "include/utilities.h"
#include <cstring>
#include <cstdio>

// Color function
const char *color_me(const char *color) {
    if (strcmp(color, "red") == 0) {
        return Colors::red;
    } else if (strcmp(color, "green") == 0) {
        return Colors::green;
    } else if (strcmp(color, "blue") == 0) {
        return Colors::blue;
    } else if (strcmp(color, "yellow") == 0) {
        return Colors::yellow;
    } else if (strcmp(color, "magenta") == 0) {
        return Colors::magenta;
    } else if (strcmp(color, "cyan") == 0) {
        return Colors::cyan;
    } else if (strcmp(color, "white") == 0) {
        return Colors::white;
    }

    return Colors::RESET;
}

// Error logging function
void elogs(const char *message) {
    printf("%sERROR %s| %s%s\n", color_me("red"), color_me("reset"), color_me("magenta"), message);
    printf("%s", color_me("reset"));
}

// Logging function
void logs(const char *function, const char *message) {
    if (Utilities::should_log == true) {
        printf("%s%s | %s%s\n", color_me("blue"), function, color_me("green"), message);
        printf("%s", color_me("reset"));
    }
}
