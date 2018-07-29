#pragma once
#include "CObject/main/inc/CObject.hpp"
#include "Debug/main/inc/Logger.hpp"
#include <sstream>
#include <string>

class CString final : public CObject {

    public:
        CString(const std::string & value)
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
            Logger::trace(std::string("CString::~CString(): ") +
                          std::string("\"") + toString() + std::string("\"") + std::string(" ") + address.str());
        }

    public:
        class Compare final {
            public:
                bool operator()(const CString & a, const CString & b) const {
                    bool result = (0 < a.value.compare(b.value));
                    Logger::trace(std::string("CString::Compare::(): ") + a.value + std::string(" ? ") + b.value +
                                  std::string(" --> ") + (result ? std::string("true") : std::string("false")));
                    return result;
                }
        };

    public:
        CString * clone() /*const*/ final override {
            return new CString(this->value);
        }

    public:
        bool equals(const CObject & other) const final override {
            bool result = false;

            try {
                const CString & myOther = dynamic_cast<const CString &>(other);
                result = (value == myOther.value);
                Logger::trace(std::string("CString::equals(): ") + value + std::string(" ? ") + myOther.value +
                              std::string(" --> ") + (result ? std::string("true") : std::string("false")));
            }
            catch (const std::bad_cast & e) {
                Logger::error(std::string("CString::equals(): ") + std::string(e.what()));
            }

            return result;
        }

    public:
        bool operator==(const CObject & other) {
            return equals(other);
        }

    public:
        std::string toString() const override {
            return value;
        }

    private:
        std::string value;
};
