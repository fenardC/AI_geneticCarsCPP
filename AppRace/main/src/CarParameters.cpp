
#include "AppRace/main/inc/CarParameters.hpp"
#include "Debug/main/inc/Logger.hpp"

#include <vector>


CarParameters::NetworkWeights::NetworkWeights(const std::string name, const double value[])
    : value(value)
    , name(name) {
}

std::string CarParameters::NetworkWeights::getName() const {
    return name;
}

const double * CarParameters::NetworkWeights::getValue() const {
    return value;
}

const double CarParameters::CAR_DNA_77045[] = {
    -3.687971274, 4.208794485, 1.909599646, 3.356289599, -4.517137565,
        4.444885556, 0.8253668461, -1.690869288, -4.668254611, -0.03993178332,
        1.343992044, -0.03011478726, -4.399475612, 0.9016179399, 0.5191588408,
        4.060544202, 3.711753151, 3.583820301, -4.915920998, -0.05427838678
    };

const double CarParameters::CAR_DNA_100388[] = {
    -0.6846811075, -3.704431508, 2.02581483, 1.026103294, -0.5404953227,
        -1.485099734, -0.4924064588, -2.721382221, -4.175540992, -0.4188585799,
        -0.4481293182, -1.587869372, -4.281269721, 1.81823875, -0.08587310015,
        4.566381263, -2.068009282, -1.622265411, -1.364979841, -0.05427838678
    };



CarParameters::CarParameters()
    : parameterList() {
    init();
}

const CarParameters::NetworkWeights * CarParameters::getNext() const {
    return parameterList[0];
}

/* Initialize DNA with previously learned cars. */
void CarParameters::init() {

    parameterList.push_back(new NetworkWeights(std::string("CAR_DNA_100388: OK"),
                            CarParameters::CAR_DNA_100388));

    parameterList.push_back(new NetworkWeights(std::string("CAR_DNA_77045: almost OK"),
                            CarParameters::CAR_DNA_77045));
}

