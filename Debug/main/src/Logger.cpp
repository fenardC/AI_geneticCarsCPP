#include "Debug/main/inc/Logger.hpp"

#include <iostream>

Logger::Logger() {
}

void Logger::debug(const std::string message) {
    /* enable automatic flushing */
    std::cout << std::unitbuf;
    std::cout << message << std::endl;
}
