#ifndef UTILITIES_H
#define UTILITIES_H

// Colors for logging
struct Colors {
    public:
    inline static const char *red = "\033[31m";
    inline static const char *green = "\033[32m";
    inline static const char *blue = "\033[34m";
    inline static const char *yellow = "\033[33m";
    inline static const char *magenta = "\033[35m";
    inline static const char *cyan = "\033[36m";
    inline static const char *white = "\033[37m";
    inline static const char *RESET = "\033[0m";
};

// Logging function
void logs(const char *function, const char *message);

#endif
