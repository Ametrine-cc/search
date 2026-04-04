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
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <kamakazi>
#include <string>


namespace fs = std::filesystem;

void readConfigFile(const std::string& configPath) {
    std::ifstream file(configPath);
    char buffer[MAX_BUFFER_SIZE]; // Used for logging messages

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            kazi_log(__FUNCTION__, "checking"); // Original logging message

            // Ignore comments (lines starting with --) and empty lines
            if (line.find("--") == 0 || line.empty()) {
                continue;
            }

            // Find the position of the first '=' to separate key and value
            size_t pos = line.find("=");
            if (pos != std::string::npos) {
                // Extract key and value, then trim leading/trailing whitespace
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);

                // Log the original line as per existing behavior
                snprintf(buffer, MAX_BUFFER_SIZE, "configManager | %s", line.c_str());
                kazi_log(__FUNCTION__, buffer);
                // Log parsed key-value pair for debugging
                snprintf(buffer, MAX_BUFFER_SIZE, "Parsed: Key='%s', Value='%s'", key.c_str(), value.c_str());
                kazi_log(__FUNCTION__, buffer);

                if (key == "use_config") {
                    snprintf(buffer, MAX_BUFFER_SIZE, "configManager | checking use_config");
                    kazi_log(__FUNCTION__, buffer);
                    if (value == "true") {
                        Utilities::use_config = true;
                        snprintf(buffer, MAX_BUFFER_SIZE, "%s=%s (set to true)", key.c_str(), value.c_str());
                        kazi_log(__FUNCTION__, buffer);
                    } else if (value == "false") {
                        Utilities::use_config = false;
                        snprintf(buffer, MAX_BUFFER_SIZE, "%s=%s (set to false)", key.c_str(), value.c_str());
                        kazi_log(__FUNCTION__, buffer);
                    } else {
                        // Log an error for unexpected value, default to false
                        Utilities::use_config = false;
                        snprintf(buffer, MAX_BUFFER_SIZE, "Invalid value for 'use_config': '%s'. Expected 'true' or 'false'. Defaulting to false.", value.c_str());
                        kamakazi(buffer, 1);
                    }
                } else if (key == "explore_all") {
                    snprintf(buffer, MAX_BUFFER_SIZE, "configManager | checking explore_all");
                    kazi_log(__FUNCTION__, buffer);
                    if (value == "true") {
                        Utilities::explore_all = true; // Set global configuration variable
                        snprintf(buffer, MAX_BUFFER_SIZE, "%s=%s (set to true)", key.c_str(), value.c_str());
                        kazi_log(__FUNCTION__, buffer);
                    } else if (value == "false") {
                        Utilities::explore_all = false; // Explicitly set to false
                        snprintf(buffer, MAX_BUFFER_SIZE, "%s=%s (set to false)", key.c_str(), value.c_str());
                        kazi_log(__FUNCTION__, buffer);
                    } else {
                        // Log an error for unexpected value, default to false
                        snprintf(buffer, MAX_BUFFER_SIZE, "Invalid value for 'explore_all': '%s'. Expected 'true' or 'false'. Defaulting to false.", value.c_str());
                        kamakazi(buffer, 1);
                        Utilities::explore_all = false; // Default to false on error
                    }
                } else {
                    // Log unknown keys if they are encountered, but ignore for actual config setting
                    snprintf(buffer, MAX_BUFFER_SIZE, "Unknown configuration key encountered: '%s' with value '%s'. Ignoring.", key.c_str(), value.c_str());
                    kazi_log(__FUNCTION__, buffer);
                }
                snprintf(buffer, MAX_BUFFER_SIZE, "configManager | ----------------");
                kazi_log(__FUNCTION__, buffer);
            } else {
                // Log lines that don't conform to key=value format (after comments/empty check)
                snprintf(buffer, MAX_BUFFER_SIZE, "Skipping malformed line (no '=' found): '%s'", line.c_str());
                kazi_log(__FUNCTION__, buffer);
            }
        }
        file.close();
    } else {
        snprintf(buffer, MAX_BUFFER_SIZE, "ERROR: Could not open config file: %s", configPath.c_str());
        kamakazi(buffer, 1);
    }
}

int checkConfig() {
    char buffer[MAX_BUFFER_SIZE];
    char gitignore_buffer[MAX_BUFFER_SIZE];
    char ignore_buffer[MAX_BUFFER_SIZE];

    std::string configPath = CONFIG_FILE_PATH;

    try {
        if (fs::exists(configPath)) {
            snprintf(buffer, MAX_BUFFER_SIZE, "configManager | found");
            kazi_log(__FUNCTION__, buffer);
            readConfigFile(configPath);
        } else {
            throw fs::filesystem_error("Config file not found", configPath, std::error_code());
        }
    } catch (const fs::filesystem_error& e) {
        snprintf(buffer, MAX_BUFFER_SIZE, "%s", e.what());
        kamakazi(buffer, 1);

        return 1;
    }

    return 0;
}
