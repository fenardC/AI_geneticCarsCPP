#pragma once

#include <string>

class Debugger {

    private:
        static const std::string SENSOR;

    private:
        Debugger();

    public:
        static bool isDebugEnabled(const std::string & string);
};
