#pragma once

template <class A, class B, class C>
class Triple {
    public:
        Triple(A first, B second, C third)
            : first(first)
            , second(second)
            , third(third) {
        }

    public:
        A getFirst() const {
            return first;
        }

    public:
        B getSecond() const {
            return second;
        }

    public:
        C getThird() const {
            return third;
        }

    private:
        A first;

    private:
        B second;

    private:
        C third;
};
