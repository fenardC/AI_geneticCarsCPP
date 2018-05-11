#pragma once

#include <map>
#include <vector>

#include "DemoGui/main/inc/ScreenGeneticCar.hpp"
#include "DemoMisc/main/inc/CarSensor.hpp"
#include "DemoMisc/main/inc/CarSensorLine.hpp"
#include "DemoMisc/main/inc/CarSensorPoint.hpp"
#include "DemoMisc/main/inc/Track.hpp"
#include "Draw/main/inc/Drawer.hpp"
#include "Draw/main/inc/Texture.hpp"
#include "Draw/main/inc/TextureModifier.hpp"
#include "Misc/main/inc/Misc.hpp"

class GeneticIndividual;

class Car final {
    public:
        Car(std::string name, int typeSensor, double ratio);

    public:
        ~Car();

    public:
        void addRoadCollision(const Vector2D & offset) ;

    public:
        double getAngle() const;

    public:
        QColor getColor() const ;

    public:
        int getEngine() const;

    public:
        int getEngineCommand() const;

    public:
        GeneticIndividual * getIndiv() const;

    public:
        int getLap() const;

    public:
        std::string getName() const;

    public:
        Vector2D * getPosition() const;

    public:
        double getRatio() const;

    public:
        double getSensorValue(const std::string & name) const;

    public:
        double getTimeLap() const;

    public:
        Track * getTrack() const;

    public:
        double getTrackPercentCompletion() const;

    public:
        int getWheelCommand() const;

    public:
        bool isOnTrack() const;

    public:
        void putOnTrack(Track * const track) ;

    public:
        void render(Drawer & d) const ;

    private:
        void renderCarOnly(Drawer & d) const;

    public:
        void setAngle(double angle);

    public:
        void setBestIndexSpline(int bestIndexSpline) ;

    public:
        void setColor(QColor color) ;

    public:
        void setEngineCommand(int engineCommand) ;

    public:
        void setIndiv(GeneticIndividual * indiv) ;

    public:
        void setLap(int lap) ;

    public:
        void setPosition(Vector2D * position) ;

    public:
        void setRatio(double ratio) ;

    public:
        void setTimeLap(double timeLap) ;

    public:
        void setTrack(Track * track) ;

    public:
        void setWheelCommand(int wheelCommand) ;

    public:
        void testRender(Drawer & d) const;

    public:
        void testTick(double millis) ;

    public:
        void tick(double millis) ;

    private:
        void tickCarOnly(double millis) ;

    private:
        std::string name;

    private:
        int maxIndexTriangleDiff;

    private:
        Track * track;

    private:
        GeneticIndividual * indiv;

    private:
        std::map<std::string, CarSensor *> mapRoadSensor;

    private:
        std::vector<CarSensorPoint *> listRoadCollision;

    private:
        int wheelCommand;

    private:
        int engineCommand;

    private:
        int engine;

    private:
        double acceleration;

    private:
        Vector2D * position;

    private:
        double angle;

    private:
        double ratio;

    private:
        TextureModifier * textureModifier;

    private:
        int bestIndexSpline;

    private:
        int lap;

    private:
        double timeLap;

    private:
        QColor color;
};
