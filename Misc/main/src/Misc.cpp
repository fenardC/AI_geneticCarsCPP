/* Force initialization of cout before static object construction. */
#include <iostream>

#include "Debug/main/inc/Logger.hpp"
#include "Misc/main/inc/Misc.hpp"
#include <iterator>
#include <map>

double Misc::bound(const double val, const int low, const int high) { /*const*/
    double result = val;

    if (val > high) {
        result = high;
    }
    else if (val < low) {
        result = low;
    }

    return result;
}

int Misc::mix(const double min, const double max, const double value) {
    return static_cast<int>(value * (max - min) + min);
}

QColor Misc::mix(const int fromRgbMin, const int toRgbMax, const double ratio) {
    const QColor color1 = QColor::fromRgb(QRgb(fromRgbMin));
    const QColor color2 = QColor::fromRgb(QRgb(toRgbMax));
    const double ratioComplement = 1 - ratio;

    const int red = (int)(color2.red() * ratio  + color1.red() * ratioComplement);
    const int green = (int)(color2.green() * ratio + color1.green() * ratioComplement);
    const int blue = (int)(color2.blue() * ratio + color1.blue() * ratioComplement);
    return QColor(red, green, blue);
}

bool Misc::random(const double chanceInPercent) {
    std::uniform_real_distribution<double> dist(0.0, 100.0);
    const double randomInPercent = dist(randomGenerator);
    return chanceInPercent > randomInPercent ? true : false;
}

double Misc::random(const double min, const double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(randomGenerator);
}

/* max value is excluded (as JAVA case).*/
int Misc::random(const int min, const int max) {
    int result = 0;

    if (0 < max) {
        std::uniform_int_distribution<int> dist(min, max - 1);
        result = dist(randomGenerator);
    }

    return result;
}

const std::shared_ptr<GeneticIndividual> &
Misc::randomInWeightedMap(const std::map<std::shared_ptr<GeneticIndividual>, double> & map) {
    auto item = map.begin();
    std::advance(item, Misc::random(0, map.size()));
    return item->first;
}

Misc::Misc() {
}

std::mt19937 Misc::initRandomGenerator(bool withSeeding) {
    std::mt19937 generator(0);
    Logger::trace(std::string("Misc::initRandomGenerator>()"));

    if (withSeeding) {
        /* Will be used to obtain a seed for the random number engine. */
        std::random_device rd;
        generator = std::mt19937(rd());
        Logger::info(std::string("Misc::initRandomGenerator(): seeding done."));
    }

    Logger::trace(std::string("Misc::initRandomGenerator<()"));
    return generator;
}


/* One single random generator for all random numbers. */
/* Standard mersenne_twister_engine seeded with rd() */
std::mt19937 Misc::randomGenerator = Misc::initRandomGenerator(true);
