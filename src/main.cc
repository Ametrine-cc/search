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
#include <kamakazi>
#include <cstdio>

bool Kamakazi_Utils::should_log = false;
bool Kamakazi_Utils::ignore_dangerLevel = false;
bool Kamakazi_Utils::show_dangerLevel = false;

bool Utilities::use_config = true;
bool Utilities::explore_all = false;
bool Utilities::ignore_gitignore = false;
std::string Utilities::path = "";

int main(int argc, char *argv[]) {
    char buffer[MAX_BUFFER_SIZE];
    char search_type[1];

    kazi_log(__FUNCTION__, "Search for files and directories easier");

    // if debug flags are found enable logging
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--debug") == 0) {
            Kamakazi_Utils::should_log = true;
            kazi_log(__FUNCTION__, "Debug mode enabled");
            continue;
        }

        if (strcmp(argv[i], "--full") == 0) {
            if (Utilities::explore_all) {
                kazi_log(__FUNCTION__, "--full flag ignored, explore_all is already true");
            } else {
                kazi_log(__FUNCTION__, "Full exploration enabled");
                Utilities::explore_all = true;
            }
            continue;
        }

        if (strcmp(argv[i], "--ignore-gitignore") == 0) {
            if (Utilities::ignore_gitignore) {
                kazi_log(__FUNCTION__, "--ignore-gitignore flag ignored, already set");
            } else {
                kazi_log(__FUNCTION__, "Ignore .gitignore enabled");
                Utilities::ignore_gitignore = true;
            }

            kazi_log(__FUNCTION__, "Ignoring .gitignore can cause some issues for maintainers of projects, search takes no responsibility for any issues that may arise from ignoring .gitignore");
            continue;
        }

        if (strcmp(argv[i], "--ignore-config") == 0) {
            if (!Utilities::use_config) {
                kazi_log(__FUNCTION__, "--ignore-config flag ignored, already set");
            } else {
                kazi_log(__FUNCTION__, "Use config enabled");
                Utilities::use_config = false;
            }
            continue;
        }
    }

    if (argc < 2) {
        kamakazi("Usage: <file name or directory path>", 0);
    }

    std::string path = argv[1];
    Utilities::path = path;

    if (path.length() <= 1) {
        kamakazi("path must be a valid directory or file path to search", 0);
    }

    if (path.find_last_of("/") != std::string::npos && path.find_last_of(".") == std::string::npos) {
        snprintf(buffer, sizeof(buffer), "Root directory: %s", argv[0]);
        kazi_log(__FUNCTION__, buffer);

        search_type[0] = 'd';
    } else if (path.find_last_of(".") != std::string::npos) {
        snprintf(buffer, sizeof(buffer), "File: %s", path.c_str());
        kazi_log(__FUNCTION__, buffer);

        search_type[0] = 'f';
    }

    search(path, search_type[0], "./");

    return 0;
}
