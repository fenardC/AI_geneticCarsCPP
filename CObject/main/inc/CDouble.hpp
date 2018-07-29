#pragma once
#include "CObject/main/inc/CObject.hpp"
#include "Debug/main/inc/Logger.hpp"
#include <iomanip>
#include <sstream>
#include <string>

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
            Logger::trace(std::string("CDouble::~CDouble(): ") + address.str());
        }

    public:
        static void assertEquals(const std::string & s, const CDouble val, const CDouble expected) {
            const double delta = 1E-15;

            if ((std::abs(val.value - expected.value)) > delta) {
                Logger::error(s + std::string(" ") + std::to_string(val.value)  +
                              std::string(" does not match ") + std::to_string(expected.value));
            }
        }

    public:
        CDouble * clone() /*const*/ final override {
            return new CDouble(this->value);
        }

    public:
        double doubleValue() const {
            return value;
        }

    public:
        bool equals(const CObject & other) const final override {
            bool result = false;

            try {
                const CDouble & myOther = dynamic_cast<const CDouble &>(other);
                result = (value == myOther.value);
            }
            catch (const std::bad_cast & e) {
                Logger::error(std::string("CDouble::equals(): ") + std::string(e.what()));
            }

            return result;
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
