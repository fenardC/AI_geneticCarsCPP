#pragma once

#include <sstream>
#include <string>

#include "Debug/main/inc/Logger.hpp"
#include "CObject/main/inc/CObject.hpp"

class CInteger final : public CObject {

    public:
        CInteger()
            : value(0) {
        }

    public:
        CInteger(int value)
            : value(value) {
        }

    public:
        CInteger(const CInteger & other) = default;

    public:
        virtual ~CInteger() {
            std::ostringstream address;
            address << static_cast<void const *>(this);
            Logger::trace(std::string("~CInteger(): ") + address.str());
        }

    public:
        CInteger * clone() /*const*/ final override {
            return new CInteger(this->value);
        }

    public:
        bool equals(const CObject & other) const final override {
            const CInteger & myOther = reinterpret_cast<const CInteger &>(other);
            return value == myOther.value;

        }

    public:
        int intValue() const {
            return value;
        }

    public:
        std::string toString() const override {
            return std::to_string(value);
        }

    private:
        int value;
};
