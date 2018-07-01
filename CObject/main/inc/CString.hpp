#pragma once

#include <string>
#include <sstream>

#include "CObject/main/inc/CObject.hpp"
#include "Debug/main/inc/Logger.hpp"

class CString final : public CObject {

    public:
        CString(std::string value)
            : value(value) {
        }

    public:
        CString(const CString & other)
            : value(other.value) {
        }

    public:
        virtual ~CString() {
            std::ostringstream address;
            address << static_cast<void const *>(this);
            Logger::trace(std::string("~CString(): ") + address.str());
        }

    public:
        bool equals(const CObject & other) const override {
            (void)(other);
            return false;
        }

    public:
        std::string toString() const override {
            return value;
        }

    private:
        std::string value;
};
