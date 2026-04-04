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
#include <kamakazi>

namespace fs = std::filesystem;


void Startsearch(const std::string& query, char type, std::string path) {
    char buffer[MAX_BUFFER_SIZE];
    snprintf(buffer, MAX_BUFFER_SIZE, "%s", path.c_str());

    kazi_log("search", "searching");
    snprintf(buffer, MAX_BUFFER_SIZE, "query: %s type: %c", query.c_str(), type);

    try {
        if (fs::exists(path) && fs::is_directory(path)) {
            kazi_log("search", buffer);

            for (const auto& entry : fs::directory_iterator(path)) {
                char buffer[MAX_BUFFER_SIZE];

                if (entry.is_directory()) {

                    if (!Utilities::ignore_gitignore && entry.path().filename().string().find_first_of('.') == 0 && entry.path().filename().string() == ".git") {
                        continue;
                    }

                    snprintf(buffer, MAX_BUFFER_SIZE, "%s/", entry.path().relative_path().c_str());

                    if (strstr(buffer, query.c_str()) != nullptr) {
                        printf("search | %s\n", buffer);
                    }

                    if (Utilities::explore_all) {
                        search(query, type, entry.path().c_str());
                    }
                } else if (entry.is_regular_file()) {
                    snprintf(buffer, MAX_BUFFER_SIZE, "%s", entry.path().relative_path().c_str());
                    if (strstr(buffer, query.c_str()) != nullptr) {
                        printf("search | %s\n", buffer);
                    }
                }
            }
        }
    } catch (const std::exception& e) {
        snprintf(buffer, MAX_BUFFER_SIZE, "search | %s", e.what());
        kamakazi(buffer, 1);
    }
}

void search(const std::string& query, char type, std::string path) {

    if (Utilities::use_config) {
        if (checkConfig() != 0) {
            exit(0);
        } else {
            Startsearch(query, type, path);
        }
    } else {
        Startsearch(query, type, path);
    }
}
