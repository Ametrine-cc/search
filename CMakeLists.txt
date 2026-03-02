cmake_minimum_required(VERSION 3.10)
project(Search VERSION 1.0 LANGUAGES CXX)

# --- Standards & Configuration ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Disable examples for dependencies if applicable
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# --- Executable Definition ---
add_executable(search
    src/main.cc
    src/logs.cc
    src/configManager.cc
)

# --- Installation ---

# Install the binary to the standard 'bin' directory
install(TARGETS search DESTINATION bin)

# Locate the user's home directory safely
set(USER_CONFIG_DIR "$ENV{HOME}/.config/search")

# Install the config file
install(FILES src/config.lua DESTINATION ${USER_CONFIG_DIR})
