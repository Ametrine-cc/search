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

#ifndef UTILITIES_HH
#define UTILITIES_HH

#include <string>

// Colorme
struct Colors {
    public:
    inline static const char *red = "\033[31m";
    inline static const char *green = "\033[32m";
    inline static const char *blue = "\033[34m";
    inline static const char *yellow = "\033[33m";
    inline static const char *magenta = "\033[35m";
    inline static const char *cyan = "\033[36m";
    inline static const char *white = "\033[37m";
    inline static const char *RESET = "\033[0m";
};

const char *color_me(const char *color);

// Main utilities for search functionality
struct Utilities {
    static bool should_log;
    static bool explore_all;
    static bool ignore_gitignore;
    static bool ignore_hidden;

    static std::string path;

};

// Default configuration file path
const std::string CONFIG_FILE_PATH = []() {
    const char* user_env = std::getenv("USER");
    std::string user_str;

    if (user_env != nullptr) {
        user_str = user_env;
    } else {
        user_str = "$USER";
    }

    return "/home/" + user_str + "/.config/search/config.conf";
}();

// Define the maximum buffer size
#define MAX_BUFFER_SIZE 1024

// Logging function
void logs(const char *function, const char *message);
void elogs(const char *message);

// Search functions
int checkConfig();
void search(const std::string& query, char type, std::string path);

#endif
