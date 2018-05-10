#include "Debug/main/inc/Debugger.hpp"

const std::string Debugger::SENSOR = "sensor";

Debugger::Debugger() {
}

bool Debugger::isDebugEnabled(const std::string & string) {
    bool result = false;

    if (0 == SENSOR.compare(string)) {
        result = true;
    }

    return result;
}

