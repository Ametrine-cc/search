// Search | Search for files and directories easier
// Copyright (C) 2026  Ametrine Foundation
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "include/utilities.hh"
#include <cstring>
#include <cstdio>

bool Utilities::should_log = false;
bool Utilities::explore_all = false;
bool Utilities::ignore_gitignore = false;
bool Utilities::ignore_hidden = false;
std::string Utilities::path = "";

int main(int argc, char *argv[]) {
    char buffer[MAX_BUFFER_SIZE];
    char search_type[1];

    logs(__FUNCTION__, "Search for files and directories easier");

    // if debug flags are found enable logging
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--debug") == 0) {
            Utilities::should_log = true;
            logs(__FUNCTION__, "Debug mode enabled");
            continue;
        }

        if (strcmp(argv[i], "--full") == 0) {
            if (Utilities::explore_all) {
                logs(__FUNCTION__, "--full flag ignored, explore_all is already true");
            } else {
                logs(__FUNCTION__, "Full exploration enabled");
                Utilities::explore_all = true;
            }
            continue;
        }

        if (strcmp(argv[i], "--ignore-gitignore") == 0) {
            if (Utilities::ignore_gitignore) {
                logs(__FUNCTION__, "--ignore-gitignore flag ignored, already set");
            } else {
                logs(__FUNCTION__, "Ignore .gitignore enabled");
                Utilities::ignore_gitignore = true;
            }

            logs(__FUNCTION__, "Ignoring .gitignore can cause some issues for maintainers of projects, search takes no responsibility for any issues that may arise from ignoring .gitignore");
            continue;
        }
    }

    if (argc < 2) {
        elogs("Usage: <file name or directory path>");
        return 1;
    }

    std::string path = argv[1];
    Utilities::path = path;

    if (path.length() <= 1) {
        elogs("path must be a valid directory or file path to search");
        return 1;
    }

    if (path.find_last_of("/") != std::string::npos && path.find_last_of(".") == std::string::npos) {
        snprintf(buffer, sizeof(buffer), "Root directory: %s", argv[0]);
        logs(__FUNCTION__, buffer);

        search_type[0] = 'd';
    } else if (path.find_last_of(".") != std::string::npos) {
        snprintf(buffer, sizeof(buffer), "File: %s", path.c_str());
        logs(__FUNCTION__, buffer);

        search_type[0] = 'f';
    }

    search(path, search_type[0]);

    return 0;
}
