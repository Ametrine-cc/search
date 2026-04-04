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
    src/search.cc
    src/colorMe.cc
    src/configManager.cc
    src/include/utilities.hh
)

# --- Dependencies ---
find_library(KAMAKAZI_PATH NAMES KamakaziLib)

# --- Check if it was actually found ---
if(NOT KAMAKAZI_PATH)
  message(FATAL_ERROR "KamakaziLib not found! Did you run 'sudo cmake --install'?")
endif()

target_link_libraries(search PRIVATE ${KAMAKAZI_PATH})

# --- Install the binary to the standard 'bin' directory ---
install(TARGETS search DESTINATION bin)

# --- Locate the user's home directory safely ---
set(USER_CONFIG_DIR "$ENV{HOME}/.config/search")

# --- Install the config file ---
install(FILES src/config.conf DESTINATION ${USER_CONFIG_DIR})
