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
#include <cstdio>
#include <iostream>
#include <filesystem>
#include <string>
#include <cstring>

namespace fs = std::filesystem;

// Set if logs should return an output or not
bool Utilities::should_log = false;
bool Utilities::full_scan = false;
std::string Utilities::root_dir = "./";

// Print licence function
void print_license() {
    printf("Search | Search for files and directories easier\n");
    printf("Copyright (C) 2026 Ametrine Foundation\n");
    printf("This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\n");
    printf("This is free software, and you are welcome to redistribute it\n");
    printf("under certain conditions; type `show c' for details.\n");
    printf("\n");
}

// Scan folder function
void scanFolder(const std::string& path, const std::string& fileName, bool file_or_directory) {
    // Check if the path exists and is a directory
    try {
        if (fs::exists(path) && fs::is_directory(path)) {
            // Iterate through the directory entries
            for (const auto& entry : fs::directory_iterator(path)) {
                // Print file name and type
                char buffer[256];

                if (!Utilities::full_scan) {
                    if (entry.is_directory()) {
                        // If its a directory [DIR] is added to the end of the output
                        snprintf(buffer, sizeof(buffer), "Found : %s [DIR]", entry.path().string().c_str());
                    } else {
                        // If its a file nothing is added and output stays the same
                        snprintf(buffer, sizeof(buffer), "Found : %s", entry.path().string().c_str());
                    }
                } else {
                    if (entry.is_directory()) {
                        // If its a directory [DIR] is added to the end of the output
                        snprintf(buffer, sizeof(buffer), "Found : %s [DIR]", entry.path().string().c_str());
                        Utilities::root_dir = entry.path().string();

                        scanFolder(Utilities::root_dir, fileName, file_or_directory);
                    } else {
                        // If its a file nothing is added and output stays the same
                        snprintf(buffer, sizeof(buffer), "Found : %s", entry.path().string().c_str());
                    }
                }

                if (strstr(buffer, fileName.c_str()) != nullptr) {

                    if (!Utilities::should_log) {
                        printf("%s\n", buffer);
                    } else {
                        logs("search", buffer);
                    }
                } else {
                    continue;
                }
            }
        } else {
            // Print error message if path does not exist or is not a directory
            std::cerr << "Path does not exist or is not a directory." << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        // Print error message if filesystem error occurs
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Main function
int main(int argc, char * argv[]) {

    //Check argument amount
    if (argc < 2) {
        print_license();

        std::cerr << "Usage: " << argv[0] << " <file name>" << std::endl;
        return 1;
    }


    // Check for debug flag and determine file_or_directory type
    for (int i = 1; i < argc; i++) {
        // if debug flag is found enable logging
        if (strcmp(argv[i], "--debug") == 0) {
            Utilities::should_log = true;
            print_license();
        }

        if (strcmp(argv[i], "--full") == 0) {
            Utilities::full_scan = true;
        }
    }

    bool is_target_a_file = true;

    // Check if argv[1] contains a '.'
    std::string target_name_arg = argv[1];
    if (target_name_arg.find('.') == std::string::npos) {
        is_target_a_file = false;
    }

    scanFolder(Utilities::root_dir, argv[1], is_target_a_file); // Scans the current directory

    // Return 0 to indicate successful execution
    return 0;
}
