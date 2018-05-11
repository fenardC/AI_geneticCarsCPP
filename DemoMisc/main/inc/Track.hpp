#pragma once

#include <string>
#include <vector>

#include "Misc/main/inc/BezierSpline2D.hpp"
#include "Draw/main/inc/Drawer.hpp"
#include "Misc/main/inc/Triple.hpp"
#include "Misc/main/inc/Vector2D.hpp"

class Track {

    public:
        Track(const std::string & name, BezierSpline2D * spline, double splineWidth, double maxLapMillis);

    public:
        std::vector<Triple<const Vector2D *, const Vector2D *, const Vector2D *>> getListTriangle() const;

    public:
        double getMaxLapMillis() const;

    public:
        std::string getName() const;

    public:
        BezierSpline2D * getSpline() const;

    public:
        double getSplineWidth() const;

    public:
        int isPointInTrack(const Vector2D & pos) const;

    public:
        void renderCenterLine(Drawer & d) const;

    public:
        void renderDebug(Drawer & drawer) const;

    public:
        void renderSplineDebug(Drawer & drawer) const;

    public:
        void renderStart(Drawer & d) const;

    private:
        void init();

    private:
        static bool pointInTriangle(const Vector2D & p,
                                    const Vector2D & p1, const Vector2D & p2, const Vector2D & p3);

    private:
        static double sign(const Vector2D & p1, const Vector2D & p2, const Vector2D & p3);

    private:
        static const bool DEBUG_ENABLED;

    private:
        std::string name;

    private:
        BezierSpline2D * spline;

    private:
        double splineWidth;

    private:
        double maxLapMillis;

    private:
        std::vector<Triple<const Vector2D *, const Vector2D *, const Vector2D *>> listTriangle;
};
