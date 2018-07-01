#include <algorithm>
#include <sstream>

#include "Debug/main/inc/Logger.hpp"
#include "Misc/main/inc/BezierSpline2D.hpp"

BezierSpline2D::BezierSpline2D()
    : listResultPoint()
    , listResultPerpendicular() {
}

BezierSpline2D::BezierSpline2D(const std::vector<Couple<Vector2D *, Vector2D *>> & pointsAndPerpList)
    : BezierSpline2D() {
    for (Couple<Vector2D *, Vector2D *> c : pointsAndPerpList) {
        const Vector2D * point = new Vector2D(c.getFirst()->getX(), c.getFirst()->getY());
        const Vector2D * normal = new Vector2D(c.getSecond()->getX(), c.getSecond()->getY());
        listResultPoint.push_back(point);
        listResultPerpendicular.push_back(normal);
    }
}

BezierSpline2D::~BezierSpline2D() {
    {
        auto deleteVector = [](const Vector2D * p) {
            std::ostringstream address;
            address << static_cast<void const *>(p);
            Logger::debug("~BezierSpline2D(): list points: " + address.str());

            delete p;
        };
        std::for_each(listResultPoint.begin(), listResultPoint.end(), deleteVector);
        listResultPoint.clear();
    }
    {
        auto deleteVector = [](const Vector2D * p) {
            std::ostringstream address;
            address << static_cast<void const *>(p);
            Logger::debug("~BezierSpline2D(): list perpendicular points: " + address.str());

            delete p;
        };
        std::for_each(listResultPerpendicular.begin(), listResultPerpendicular.end(), deleteVector);
        listResultPerpendicular.clear();
    }
}

std::vector<const Vector2D *> BezierSpline2D::getListResultPerpendicular() const {
    return listResultPerpendicular;
}

std::vector<const Vector2D *> BezierSpline2D::getListResultPoint() const {
    return listResultPoint;
}

bool BezierSpline2D::isClose() {
    return BezierSpline2D::CLOSE;
}

const bool BezierSpline2D::CLOSE = true;
