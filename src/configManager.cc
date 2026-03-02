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
#include <fstream>
#include <string>

int readConfigFile() {

    std::string filename = CONFIG_FILE_PATH;

    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open config file");
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.find("--") == 0) {
                continue;
            }

            if (line.find("local") == 0) {
                std::string key = line.substr(6);

                char buffer[MAX_BUFFER_SIZE];

                if (key.find(USE_CONFIG) == 0) {
                    std::string value = key.substr(USE_CONFIG.size());
                    size_t pos_space = 0;

                    while ((pos_space = value.find(" ", pos_space)) != std::string::npos) {
                        value.replace(pos_space, 1, "");
                    }

                    size_t pos_equals = 0;

                    while ((pos_equals = value.find("=", pos_equals)) != std::string::npos) {
                        value.replace(pos_equals, 1, "");
                    }

                    snprintf(buffer, sizeof(buffer), "%s | %s", USE_CONFIG.c_str(), value.c_str());
                    logs("ConfigManager", buffer);

                    Utilities::use_config = true;

                } else if (key.find(EXPLORE_ALL) == 0) {
                    std::string value = key.substr(EXPLORE_ALL.size());
                    size_t pos_space = 0;

                    while ((pos_space = value.find(" ", pos_space)) != std::string::npos) {
                        value.replace(pos_space, 1, "");
                    }

                    size_t pos_equals = 0;

                    while ((pos_equals = value.find("=", pos_equals)) != std::string::npos) {
                        value.replace(pos_equals, 1, "");
                    }

                    snprintf(buffer, sizeof(buffer), "%s | %s\n", EXPLORE_ALL.c_str(), value.c_str());
                    logs("ConfigManager", buffer);

                    Utilities::explore_all = true;

                }
            }
        }
    } catch (std::exception& e) {
        char buffer[MAX_BUFFER_SIZE];

        snprintf(buffer, sizeof(buffer), "Error reading config file: %s\n", filename.c_str());
        logs("ConfigManager", buffer);
    }

    return 0;

}
