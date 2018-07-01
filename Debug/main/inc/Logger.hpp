#pragma once

#include <string>

class Logger {
    public:
        static void debug(const std::string message);

    public:
        static void info(const std::string message);

    public:
        static void trace(const std::string message);

    private:
        Logger();

    private:
        static bool enableDebug;

    private:
        static bool enableInfo;

    private:
        static bool enableTrace;
};
