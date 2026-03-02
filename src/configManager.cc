#include "include/utilities.h"
#include <iostream>
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

                    printf("%s | %s\n", USE_CONFIG.c_str(), value.c_str());

                } else if (key.find(SHOW_COLORS) == 0) {
                    std::string value = key.substr(SHOW_COLORS.size());
                    size_t pos_space = 0;

                    while ((pos_space = value.find(" ", pos_space)) != std::string::npos) {
                        value.replace(pos_space, 1, "");
                    }

                    size_t pos_equals = 0;

                    while ((pos_equals = value.find("=", pos_equals)) != std::string::npos) {
                        value.replace(pos_equals, 1, "");
                    }

                    printf("%s | %s\n", SHOW_COLORS.c_str(), value.c_str());
                }
            }

            // printf("%s\n", line.c_str());
        }

    } catch (std::exception& e) {
        printf("Error reading config file: %s\n", filename.c_str());
        printf("Please check the file path and permissions or generate a new config file.\n");
        return -1;
    }

    return 0;

}
