#pragma once

#include <iomanip>
#include <sstream>
#include <string>

#include "Debug/main/inc/Logger.hpp"
#include "CObject/main/inc/CObject.hpp"

class CDouble final : public CObject {

    public:
        CDouble(double value)
            : value(value) {
        }

    public:
        CDouble(const CDouble & other) = default;

    public:
        virtual ~CDouble() {
            std::ostringstream address;
            address << static_cast<void const *>(this);
            Logger::trace(std::string("~CDouble(): ") + address.str());
        }

    public:
        CDouble * clone() /*const*/ final override {
            return new CDouble(this->value);
        }

    public:
        bool equals(const CObject & other) const final override {
            const CDouble & myOther = reinterpret_cast<const CDouble &>(other);
            return value == myOther.value;
        }

    public:
        double doubleValue() const {
            return value;
        }

    public:
        std::string toString() const final override {
            std::ostringstream out;
            out << std::setprecision(10) << value;
            return out.str();
        }

    private:
        double value;
};
