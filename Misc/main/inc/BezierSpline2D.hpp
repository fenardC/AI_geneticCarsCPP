#pragma once

#include <vector>

#include "Misc/main/inc/Couple.hpp"
#include "Misc/main/inc/Triple.hpp"
#include "Misc/main/inc/Vector2D.hpp"

class BezierSpline2D {
    public:
        BezierSpline2D();

    public:
        BezierSpline2D(const std::vector<Couple<Vector2D *, Vector2D *>> & pointsAndPerpList);

    public:
        ~BezierSpline2D();

    public:
        std::vector<const Vector2D *> getListResultPerpendicular() const;

    public:
        std::vector<const Vector2D *> getListResultPoint() const;

    public:
        static bool isClose();

    private:
        static const bool CLOSE;

    private:
        std::vector<const Vector2D *> listResultPoint;

    private:
        std::vector<const Vector2D *> listResultPerpendicular;
};
