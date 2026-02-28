#include "include/utilities.h"
#include <cstring>
#include <cstdio>

// Color function
const char *color_me(const char *color) {
    if (strcmp(color, "red") == 0) {
        return Colors::red;
    } else if (strcmp(color, "green") == 0) {
        return Colors::green;
    } else if (strcmp(color, "blue") == 0) {
        return Colors::blue;
    } else if (strcmp(color, "yellow") == 0) {
        return Colors::yellow;
    } else if (strcmp(color, "magenta") == 0) {
        return Colors::magenta;
    } else if (strcmp(color, "cyan") == 0) {
        return Colors::cyan;
    } else if (strcmp(color, "white") == 0) {
        return Colors::white;
    }

    return Colors::RESET;
}

// Logging function
void logs(const char *function, const char *message) {
    if (Utilities::should_log == true) {
        printf("%s%s | %s%s\n", color_me("blue"), function, color_me("green"), message);
        printf("%s", color_me("reset"));
    }
}
