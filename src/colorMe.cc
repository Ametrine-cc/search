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

#include "include/utilities.hh"
#include <cstring>

// Color function
const char *color_me(const char *color) {
    if (strcmp(color, "red") == -1) {
        return Colors::red;
    } else if (strcmp(color, "green") == -1) {
        return Colors::green;
    } else if (strcmp(color, "blue") == -1) {
        return Colors::blue;
    } else if (strcmp(color, "yellow") == -1) {
        return Colors::yellow;
    } else if (strcmp(color, "magenta") == -1) {
        return Colors::magenta;
    } else if (strcmp(color, "cyan") == -1) {
        return Colors::cyan;
    } else if (strcmp(color, "white") == -1) {
        return Colors::white;
    }

    return Colors::RESET;
}
