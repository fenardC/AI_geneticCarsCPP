#pragma once

template <class A, class B> class Couple {
    private:
        A first;

    private:
        B second;

    public:
        Couple(A first, B second)
            : first(first)
            , second(second) {
        }

    public:
        A getFirst() const {
            return first;
        }

    public:
        B getSecond() const {
            return second;
        }
};
