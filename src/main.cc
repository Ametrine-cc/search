#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

void scanFolder(const std::string& path) {
    try {
        if (fs::exists(path) && fs::is_directory(path)) {
            for (const auto& entry : fs::directory_iterator(path)) {
                std::cout << entry.path().filename() << (entry.is_directory() ? " [DIR]" : "") << std::endl;
            }
        } else {
            std::cerr << "Path does not exist or is not a directory." << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main(int argc, char * argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <directory>" << std::endl;
        return 1;
    }

    scanFolder(argv[1]); // Scans the current directory

    return 0;
}
