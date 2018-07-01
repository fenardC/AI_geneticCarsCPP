#pragma once

#include <vector>

#include "Misc/main/inc/Couple.hpp"
#include "Misc/main/inc/Vector2D.hpp"


class TrackData {

    public:
        TrackData(std::string);

    public:
        ~TrackData();

    public:
        void debug();

    public:
        std::string getName() const;

    public:
        std::vector<Couple<Vector2D *, Vector2D *>> getPointsAndPerpList() const;

    protected:
        void translate(const int deltaX, const int deltaY);

    protected:
        void computePointsAndPerpList();

    private:
        static Vector2D * computePerp(const Vector2D & previous, const Vector2D & next, const bool onRight) ;

    private:
        static const bool DEBUG_ENABLED;

    protected:
        std::vector<Vector2D *> points;

    protected:
        std::vector<Couple<Vector2D *, Vector2D *>> pointsAndPerpList;

    private:
        std::string name;
};
