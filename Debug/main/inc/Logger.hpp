#pragma once

#include <string>

class Logger {
    public:
        static void debug(const std::string message);

    private:
        Logger();
};
