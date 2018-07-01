#pragma once

#include <string>

class CObject {
    public:
        virtual ~CObject() {
        }

    public:
        virtual CObject * clone() /*const*/ = 0;

    public:
        virtual bool equals(const CObject & other) const = 0;

    public:
        virtual std::string toString() const = 0;
};
