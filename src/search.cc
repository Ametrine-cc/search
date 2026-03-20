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
#include <cstdlib>
#include <cstring>
#include <filesystem>

namespace fs = std::filesystem;

void search(const std::string& query, char type, std::string path) {
    char buffer[MAX_BUFFER_SIZE];
    snprintf(buffer, MAX_BUFFER_SIZE, "%s", path.c_str());

    if (checkConfig() != 0) {
        exit(0);
    } else {
        logs("search", "searching");
        snprintf(buffer, MAX_BUFFER_SIZE, "query: %s type: %c", query.c_str(), type);

        try {
            if (fs::exists(path) && fs::is_directory(path)) {
                logs("search", buffer);

                for (const auto& entry : fs::directory_iterator(path)) {
                    char buffer[MAX_BUFFER_SIZE];

                    if (entry.is_directory()) {
                        snprintf(buffer, MAX_BUFFER_SIZE, "%s/", entry.path().relative_path().c_str());

                        if (strstr(buffer, query.c_str()) != nullptr) {
                            printf("search | %s\n", buffer);
                        }

                        search(query, type, entry.path().c_str());
                    } else if (entry.is_regular_file()) {
                        snprintf(buffer, MAX_BUFFER_SIZE, "%s", entry.path().relative_path().c_str());
                        if (strstr(buffer, query.c_str()) != nullptr) {
                            printf("search | %s\n", buffer);
                        }
                    }
                }
            }
        } catch (const std::exception& e) {
            logs("search", e.what());
        }
    }
}
