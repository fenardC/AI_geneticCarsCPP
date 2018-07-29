#pragma once
#include "CObject/main/inc/CObject.hpp"
#include "Debug/main/inc/Logger.hpp"
#include <sstream>
#include <string>

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
            Logger::trace(std::string("CInteger::~CInteger(): ") + address.str());
        }

    public:
        static void assertEquals(const std::string & s, const CInteger val, const CInteger expected) {
            const double delta = 1E-15;

            if ((std::abs(val.value - expected.value)) > delta) {
                Logger::error(s + std::string(" ") + std::to_string(val.value)  +
                              std::string(" does not match ") + std::to_string(expected.value));
            }
        }

    public:
        CInteger * clone() /*const*/ final override {
            return new CInteger(this->value);
        }

    public:
        bool equals(const CObject & other) const final override {
            bool result = false;

            try {
                const CInteger & myOther = dynamic_cast<const CInteger &>(other);
                result = (value == myOther.value);
            }
            catch (const std::bad_cast & e) {
                Logger::error(std::string("CInteger::equals(): ") + std::string(e.what()));
            }

            return result;
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
