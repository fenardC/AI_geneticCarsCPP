#include <vector>
#include <sstream>

#include "Debug/main/inc/Logger.hpp"
#include "Draw/main/inc/Drawer.hpp"
#include "Misc/main/inc/Couple.hpp"
#include "Misc/main/inc/Vector2D.hpp"
#include "TrackData/main/inc/TrackData.hpp"


TrackData::TrackData(std::string name)
    : points()
    , pointsAndPerpList()
    , name(name) {
}

TrackData::~TrackData() {
    {
        auto deleteVector = [](const Vector2D * p) {
            std::ostringstream address;
            address << static_cast<void const *>(p);
            Logger::debug("~TrackData(): points: " + address.str());

            delete p;
        };
        std::for_each(points.begin(), points.end(), deleteVector);
        points.clear();
    }
    {
        auto deleteCouple = [](const Couple<Vector2D *, Vector2D *> c) {
            std::ostringstream address;
            address << static_cast<void const *>(c.getFirst());
            address << std::string(" ");
            address << static_cast<void const *>(c.getSecond());
            Logger::debug("~TrackData(): points: " + address.str());

            delete c.getFirst();
            delete c.getSecond();
        };
        std::for_each(pointsAndPerpList.begin(), pointsAndPerpList.end(),
                      deleteCouple);
        pointsAndPerpList.clear();
    }

}

void TrackData::debug() {
    if (TrackData::DEBUG_ENABLED) {
        for (Couple<Vector2D *, Vector2D *>  c : pointsAndPerpList) {
            Logger::debug(c.getFirst()->toString() + std::string(" | ") + c.getSecond()->toString());
        }
    }
}

std::vector<Couple<Vector2D *, Vector2D *>> TrackData::getPointsAndPerpList() const {
    return pointsAndPerpList;
}

std::string TrackData::getName() const {
    return name;
}

void TrackData::translate(const int deltaX, const int deltaY) {
    const Vector2D translator(deltaX, deltaY);

    for (Vector2D * p : points) {
        p->add(translator);
    }
}

void TrackData::computePointsAndPerpList() {
    const int pointsSize = points.size();
    /* Before current point. */
    Vector2D * previous;
    /* After current point. */
    Vector2D * next;

    for (int i = 0; i < pointsSize; i++) {
        if (i == 0) {
            /* Is first */
            previous = points[pointsSize - 1];
            next = points[1];

        }
        else if (i == (pointsSize - 1)) {
            /* last */
            previous = points[pointsSize - 2];
            next = points[0];

        }
        else {
            /* others */
            previous = points[i - 1];
            next = points[i + 1];
        }

        pointsAndPerpList.push_back(Couple<Vector2D *, Vector2D *>(points[i], computePerp(*previous, *next, true)));
    }
}

Vector2D * TrackData::computePerp(const Vector2D & previous, const Vector2D & next, const bool onRight) {
    Vector2D * tangent = Vector2D::substract(next, previous);

    Vector2D * res = Vector2D::normalize(Vector2D((onRight ? -1 : 1) * tangent->getY(),
                                         (onRight ? 1 : -1) * tangent->getX()));
    delete tangent;
    return res;
}

const bool TrackData::DEBUG_ENABLED = false;
