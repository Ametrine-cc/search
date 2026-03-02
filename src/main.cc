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
#include <fstream>
#include <cstring>

namespace fs = std::filesystem;

// Set if logs should return an output or not
bool Utilities::should_log = false;
bool Utilities::full_scan = false;
bool Utilities::use_config = false;
bool Utilities::explore_all = false;

std::string Utilities::root_dir = "./";

// Print licence functions
void print_license_short() {
    printf("Search | Search for files and directories easier\n");
    printf("Copyright (C) 2026 Ametrine Foundation\n");
    printf("This program comes with ABSOLUTELY NO WARRANTY; for details type `--show w'.\n");
    printf("This is free software, and you are welcome to redistribute it\n");
    printf("under certain conditions; type `--show c' for details.\n");
    printf("\n");
}

void print_license() {
    std::ifstream file(LICENSE_FILE_PATH);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << '\n';
        }
        // The ifstream 'file' is automatically closed when it goes out of scope (RAII).
    } else {
        // Output an error message to stderr if the file cannot be opened.
        std::cerr << "Error: Could not open license file at " << LICENSE_FILE_PATH << std::endl;
    }
    // Retain the original trailing newline output.
    std::cout << '\n';
}

void print_warranty() {
    printf("15. Disclaimer of Warranty.\n\n");
    printf("    THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY\n");
    printf("    APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT\n");
    printf("    HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM \"AS IS\" WITHOUT\n");
    printf("    WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT\n");
    printf("    NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND\n");
    printf("    FITNESS FOR A PARTICULAR PURPOSE. THE ENTIRE RISK AS TO THE QUALITY\n");
    printf("    AND PERFORMANCE OF THE PROGRAM IS WITH YOU. SHOULD THE PROGRAM\n");
    printf("    PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING,\n");
    printf("    REPAIR OR CORRECTION.\n\n");
    printf("16. Limitation of Liability.\n\n");
    printf("    IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN\n");
    printf("    WRITING WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES\n");
    printf("    AND/OR CONVEYS THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR\n");
    printf("    DAMAGES, INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL\n");
    printf("    DAMAGES ARISING OUT OF THE USE OR INABILITY TO USE THE PROGRAM\n");
    printf("    (INCLUDING BUT NOT LIMITED TO LOSS OF DATA OR DATA BEING RENDERED\n");
    printf("    INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD PARTIES OR A FAILURE\n");
    printf("    OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS), EVEN IF SUCH\n");
    printf("    HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH\n");
    printf("    DAMAGES.\n\n");
    printf("17. Interpretation of Sections 15 and 16.\n\n");
    printf("    If the disclaimer of warranty and limitation of liability provided\n");
    printf("    above cannot be given local legal effect according to their terms,\n");
    printf("    reviewing courts shall apply local law that most closely approximates\n");
    printf("    an absolute waiver of all civil liability in connection with the\n");
    printf("    Program, unless a warranty or assumption of liability accompanies a\n");
    printf("    copy of the Program in return for a fee.\n");

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

                // Determine if a full (recursive) scan is enabled using Utilities::explore_all
                if (!Utilities::explore_all) { // If not a full scan (i.e., shallow scan)
                    if (entry.is_directory()) {
                        // If it's a directory [DIR] is added to the end of the output
                        snprintf(buffer, sizeof(buffer), "Found : %s [DIR]", entry.path().string().c_str());
                    } else {
                        // If it's a file nothing is added and output stays the same
                        snprintf(buffer, sizeof(buffer), "Found : %s", entry.path().string().c_str());
                    }
                } else { // If it is a full (recursive) scan
                    if (entry.is_directory()) {
                        // If it's a directory [DIR] is added to the end of the output
                        snprintf(buffer, sizeof(buffer), "Found : %s [DIR]", entry.path().string().c_str());
                        // For recursive calls, pass the current entry's path directly.
                        // Modifying the global Utilities::root_dir here would cause incorrect behavior in recursion.
                        scanFolder(entry.path().string(), fileName, file_or_directory);
                    } else {
                        // If it's a file nothing is added and output stays the same
                        snprintf(buffer, sizeof(buffer), "Found : %s", entry.path().string().c_str());
                    }
                }

                if (!Utilities::explore_all && !file_or_directory && !entry.is_directory()) {
                    continue;
                }

                // Check if the file/directory name contains the search term
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

    // Check for debug flag and determine file_or_directory type
    for (int i = 1; i < argc; i++) {
        // if debug flag is found enable logging
        if (strcmp(argv[i], "--debug") == 0) {
            Utilities::should_log = true;
            print_license_short();
        }
    }

    // Read config file
    if (readConfigFile() != 0) {
        printf("You can use the following command to generate a new config file:\n");
        printf("search --config generate\n");
        return 1;
    }

    if (Utilities::use_config) {
        logs("main", "use_config is true, using config");

        if (Utilities::explore_all) {
            logs("main", "explore_all is enabled");
        } else {
            logs("main", "no default flags found, scanning root directory");
        }
    } else {
        logs("main", "use_config is false, skipping config usage");
    }

    // Check for full scan flag
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--full") == 0) {
            if (Utilities::explore_all) {
                logs("main", "--full flag ignored, explore_all is already true");
                continue;
            } else {
                Utilities::explore_all = true;
            }
        }

        if (strcmp(argv[i], "--show") == 0) {
            if (strcmp(argv[i + 1], "c") == 0) {
                print_license();
            } else if (strcmp(argv[i + 1], "w") == 0) {
                print_warranty();
            } else {
                std::cerr << "Error: --show flag requires a file name argument." << std::endl;
                return 1;
            }

            return 0;
        }
    }

    // Check argument amount
    if (argc < 2) {
        print_license_short();

        std::cerr << "Usage: " << argv[0] << " <file name>" << std::endl;
        return 1;
    }

    bool is_target_a_file = true;

    std::string target_name_arg;

    for (int i = 1; i < argc; ++i) {
        // Check if argv[i] does NOT start with "--"
        if (strncmp(argv[i], "--", 2) != 0) {
            target_name_arg = argv[i];
            break; // Found the first non-flag argument, so stop searching
        }
    }

    // Check if target_name_arg contains a '.'
    // If not, it's considered a search for a directory or a file without a specific extension.
    if (target_name_arg.find('.') == std::string::npos) {
        logs("main", "target name does not contain a '.', scanning for directories and files without specific extensions");
        is_target_a_file = false;
    }

    char buffer[MAX_BUFFER_SIZE];
    snprintf(buffer, MAX_BUFFER_SIZE, "root dir: %s\n", Utilities::root_dir.c_str());

    logs("main", buffer);

    scanFolder(Utilities::root_dir, target_name_arg, is_target_a_file); // Scans the current directory

    return 0;
}
