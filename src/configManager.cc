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
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void readConfigFile(const std::string& configPath) {
    std::ifstream file(configPath);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            printf("%s\n", line.c_str());
        }
        file.close();
    }
}

int checkConfig() {
    char buffer[MAX_BUFFER_SIZE];
    char gitignore_buffer[MAX_BUFFER_SIZE];
    char ignore_buffer[MAX_BUFFER_SIZE];

    std::string configPath = CONFIG_FILE_PATH;

    try {
        if (fs::exists(configPath)) {
            logs(__FUNCTION__, "found");
            readConfigFile(configPath);

            return 0;
        } else {
            throw fs::filesystem_error("Config file not found", configPath, std::error_code());
        }
    } catch (const fs::filesystem_error& e) {
        snprintf(buffer, MAX_BUFFER_SIZE, "%s", e.what());
        elogs(buffer);

        return 1;
    }
}
