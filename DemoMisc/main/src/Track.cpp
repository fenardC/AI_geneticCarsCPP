#include "DemoMisc/main/inc/Track.hpp"

const bool Track::DEBUG_ENABLED = false;

Track::Track(const std::string & name, BezierSpline2D * spline, double splineWidth, double maxLapMillis)
    : name(name)
    , spline(spline)
    , splineWidth(splineWidth)
    , maxLapMillis(maxLapMillis)
    , listTriangle() {
    init();
}

Track::~Track() {
    delete spline;
#warning to be finished
    //listTriangle
}

std::vector<Triple<const Vector2D *, const Vector2D *, const Vector2D *>>
Track::getListTriangle() const {
    return listTriangle;
}

double Track::getMaxLapMillis() const {
    return maxLapMillis;
}

std::string Track::getName() const {
    return name;
}

BezierSpline2D * Track::getSpline() const {
    return spline;
}

double Track::getSplineWidth() const {
    return splineWidth;
}

int Track::isPointInTrack(const Vector2D & pos) const {
    for (size_t i = 0; i < listTriangle.size(); i++) {
        const Triple<const Vector2D *, const Vector2D *, const Vector2D *> & tri = listTriangle[i];

        if (pointInTriangle(pos, *tri.getFirst(), *tri.getSecond(), *tri.getThird())) {
            return i;
        }
    }

    return -1;
}

void Track::renderCenterLine(Drawer & d) const {
    const std::vector<const Vector2D *> listPoint = spline->getListResultPoint();
    const int listPointSize = listPoint.size();
    /* Current point. */
    const Vector2D * current;
    /* After current point. */
    const Vector2D * next;

    d.setColor(QColor(Qt::white));

    for (int i = 0; i < listPointSize; i++) {
        if (i == 0) {
            /* Is first */
            current = listPoint[i];
            next = listPoint[1];

        }
        else if (i == (listPointSize - 1)) {
            /* last */
            current = listPoint[i];
            next = listPoint[0];

        }
        else {
            /* others */
            current = listPoint[i];
            next = listPoint[i + 1];
        }

        d.drawDashedLine(current->getX(), current->getY(), next->getX(), next->getY());
    }
}

void Track::renderDebug(Drawer & drawer) const {
    for (const Triple<const Vector2D *, const Vector2D *, const Vector2D *> t : listTriangle) {
        const double firstX = t.getFirst()->getX();
        const double firstY = t.getFirst()->getY();
        const double secondX = t.getSecond()->getX();
        const double secondY = t.getSecond()->getY();
        const double thirdX = t.getThird()->getX();
        const double thirdY = t.getThird()->getY();

        if (Track::DEBUG_ENABLED) {
            drawer.setColor(QColor(Qt::green));
            drawer.drawLine(firstX, firstY, secondX, secondY);
            drawer.drawLine(secondX, secondY, thirdX, thirdY);
            drawer.drawLine(firstX, firstY, thirdX, thirdY);
        }
        else {
            drawer.setColor(QColor(Qt::lightGray));
            int pointsX[] = {(int) firstX, (int) secondX, (int) thirdX};
            int pointsY[] = {(int) firstY, (int) secondY, (int) thirdY};
            const int pointCount = sizeof(pointsX) / sizeof pointsX[0];
            drawer.fillPolygon(pointsX, pointsY, pointCount);
        }
    }
}

void Track::renderSplineDebug(Drawer & drawer) const {
    if (Track::DEBUG_ENABLED) {
        int index = 0;

        for (const Vector2D * point : spline->getListResultPoint()) {
            drawer.setColor(QColor(Qt::green));
            drawer.drawRect(point->getX(), point->getY(), 5, 5);
            drawer.setColor(QColor(Qt::blue));
            drawer.drawRect(point->getX() + 5 * spline->getListResultPerpendicular()[index]->getX(),
                            point->getY() + 5 * spline->getListResultPerpendicular()[index]->getY(), 5, 9);
            index++;
        }
    }
}

void Track::renderStart(Drawer & d) const {
    const Vector2D & perpFirst(*spline->getListResultPerpendicular()[0]);
    const Vector2D & pointFirst(*spline->getListResultPoint()[0]);
    const Vector2D & perp1 = *perpFirst.multiply(splineWidth);
    Vector2D * v11 = Vector2D::add(pointFirst, perp1);
    Vector2D * v12 = Vector2D::substract(pointFirst, perp1);
    d.setColor(QColor(Qt::red));
    d.drawLine(v11->getX(), v11->getY(), v12->getX(), v12->getY());
}

void Track::init() {
    listTriangle.clear();
    std::vector<const Vector2D *> listPoint = spline->getListResultPoint();
    std::vector<const Vector2D *> listPerp = spline->getListResultPerpendicular();

    const int listPointSize = listPoint.size();
    const Vector2D * pointFirst;
    const Vector2D * pointSecond;
    const Vector2D * perpFirst;
    const Vector2D * perpSecond;
    Vector2D * perp1;
    Vector2D * perp2;
    Vector2D * v11;
    Vector2D * v12;
    Vector2D * v21;
    Vector2D * v22;

    for (int i = 0; i < listPointSize; i++) {
        if (i < (listPointSize - 1) || BezierSpline2D::isClose()) {

            if (i == listPointSize - 1 && BezierSpline2D::isClose()) {
                perpFirst = listPerp[i];
                perpSecond = listPerp[0];
                pointFirst = listPoint[i];
                pointSecond = listPoint[0];
            }
            else {
                perpFirst = listPerp[i];
                perpSecond = listPerp[i + 1];
                pointFirst = listPoint[i];
                pointSecond = listPoint[i + 1];
            }

            perp1 = perpFirst->multiply(splineWidth / 2);
            perp2 = perpSecond->multiply(splineWidth / 2);

            v11 = Vector2D::add(*pointFirst, *perp1);
            v12 = Vector2D::substract(*pointFirst, *perp1);
            v21 = Vector2D::add(*pointSecond, *perp2);
            v22 = Vector2D::substract(*pointSecond, *perp2);

            listTriangle.push_back(Triple<const Vector2D *, const Vector2D *, const Vector2D *>(v11, v12, v21));
            listTriangle.push_back(Triple<const Vector2D *, const Vector2D *, const Vector2D *>(v22, v12, v21));
        }
    }
}

bool Track::pointInTriangle(const Vector2D & p,
                            const Vector2D & p1, const Vector2D & p2, const Vector2D & p3) {
    bool result;
    bool b1 = sign(p, p1, p2) < 0;
    bool b2 = sign(p, p2, p3) < 0;
    bool b3 = sign(p, p3, p1) < 0;
    result = (b1 == b2) && (b2 == b3);
    return result;
}

double Track::sign(const Vector2D & p1, const Vector2D & p2, const Vector2D & p3) {
    return (p1.getX() - p3.getX()) * (p2.getY() - p3.getY()) -
           (p2.getX() - p3.getX()) * (p1.getY() - p3.getY());
}
