#include "Debug/main/inc/Logger.hpp"

#include <iostream>

Logger::Logger() {
}

void Logger::debug(const std::string message) {
    if (enableDebug) {
        /* enable automatic flushing */
        std::cout << std::unitbuf;
        std::cout << message << std::endl;
    }
}

void Logger::info(const std::string message) {
    if (enableInfo) {
        /* enable automatic flushing */
        std::cout << std::unitbuf;
        std::cout << message << std::endl;
    }
}

void Logger::trace(const std::string message) {
    if (enableTrace) {
        /* enable automatic flushing */
        std::cout << std::unitbuf;
        std::cout << message << std::endl;
    }
}

bool Logger::enableDebug = true;
bool Logger::enableInfo = true;
bool Logger::enableTrace = true;
