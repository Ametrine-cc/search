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

#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

// Colors for logging
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

// Default configuration file path
const std::string CONFIG_FILE_PATH = "/home/Yurien/Projects/search/src/config.lua";

// Configuration options
const std::string USE_CONFIG = "use_config";
const std::string SHOW_COLORS = "show_colors";
const std::string EXPLORE_ALL = "explore_all";

struct Utilities {
    static bool should_log;
    static bool full_scan;
    static std::string root_dir;
};

#define MAX_BUFFER_SIZE 1000

// Logging function
void logs(const char *function, const char *message);

// Read configuration file
int readConfigFile();

#endif
