#include "include/utilities.h"
#include <iostream>
#include <filesystem>
#include <string>
#include <cstring>

namespace fs = std::filesystem;

// Set if logs should return an output or not
bool Utilities::should_log = false;

// Scan folder function
void scanFolder(const std::string& path, const std::string& fileName) {
    // Check if the path exists and is a directory
    try {
        if (fs::exists(path) && fs::is_directory(path)) {
            // Iterate through the directory entries
            for (const auto& entry : fs::directory_iterator(path)) {
                // Print file name and type
                if (entry.is_directory()) {
                    // If its a directory [DIR] is added to the end of the output
                    char buffer[256];
                    snprintf(buffer, sizeof(buffer), "%s [DIR]", entry.path().filename().string().c_str());
                    logs("finding_folder", buffer);
                } else {
                    // If its a file nothing is added and output stays the same
                    char buffer[256];
                    snprintf(buffer, sizeof(buffer), "%s", entry.path().filename().string().c_str());
                    logs("finding_file", buffer);
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
        std::cerr << "Usage: " << argv[0] << " <file name>" << std::endl;
        return 1;
    }

    // Check for debug flag
    for (int i = 1; i < argc; i++) {
        // if debug flag is found enable logging
        if (strcmp(argv[i], "--debug") == 0) {
            Utilities::should_log = true;
        }
    }

    scanFolder("./", argv[1]); // Scans the current directory

    // Return 0 to indicate successful execution
    return 0;
}
