cmake_minimum_required (VERSION 3.6.2)

project(AppRace)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_VERBOSE_MAKEFILE FALSE)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

include_directories(../..)

set(SOURCES
        ../../AppRace/main/src/AppRace.cpp
        ../../AppRace/main/src/AppRaceUi.cpp
        ../../AppRace/main/src/CarParameters.cpp
        ../../AppRace/main/src/CarRacingWorker.cpp
        ../../AppRace/main/src/main.cpp
        ../../AppRace/main/src/TrackDataRace.cpp
        ../../CoreApp/main/src/CarMotionHelper.cpp
        ../../Debug/main/src/Debugger.cpp
        ../../Debug/main/src/Logger.cpp
        ../../DemoGui/main/src/ScreenGeneticCar.cpp
        ../../DemoMisc/main/src/Car.cpp
        ../../DemoMisc/main/src/CarSensorLine.cpp
        ../../DemoMisc/main/src/CarSensorPoint.cpp
        ../../DemoMisc/main/src/Track.cpp
        ../../Draw/main/src/Drawer.cpp
        ../../Draw/main/src/Texture.cpp
        ../../Draw/main/src/TextureModifier.cpp
        ../../Genetic/main/src/GeneticCrossParameter.cpp
        ../../Genetic/main/src/GeneticDnaList.cpp
        ../../Genetic/main/src/GeneticDnaListObject.cpp
        ../../Genetic/main/src/GeneticDnaNeuralNetwork.cpp
        ../../Genetic/main/src/GeneticGeneDouble.cpp
        ../../Genetic/main/src/GeneticGeneObject.cpp
        ../../Genetic/main/src/GeneticIndividual.cpp
        ../../Misc/main/src/BezierSpline2D.cpp
        ../../Misc/main/src/Misc.cpp
        ../../Misc/main/src/Vector2D.cpp
        ../../Neural/main/src/NeuralActivation.cpp
        ../../Neural/main/src/NeuralInputValue.cpp
        ../../Neural/main/src/NeuralLayer.cpp
        ../../Neural/main/src/NeuralNetwork.cpp
        ../../Neural/main/src/NeuralNeuron.cpp
        ../../TrackData/main/src/TrackData.cpp)


set(HEADERS
         ../../AppRace/main/inc/AppRace.hpp
         ../../AppRace/main/inc/AppRaceUi.h
         ../../AppRace/main/inc/CarParameters.hpp
         ../../AppRace/main/inc/CarRacingWorker.hpp
         ../../AppRace/main/inc/TrackDataRace.hpp
         ../../CoreApp/main/inc/CarMotionHelper.hpp
         ../../Debug/main/inc/Debugger.hpp
         ../../Debug/main/inc/Logger.hpp
         ../../DemoGui/main/inc/ScreenGeneticCar.hpp
         ../../DemoMisc/main/inc/Car.hpp
         ../../DemoMisc/main/inc/CarSensor.hpp
         ../../DemoMisc/main/inc/CarSensorLine.hpp
         ../../DemoMisc/main/inc/CarSensorPoint.hpp
         ../../DemoMisc/main/inc/Track.hpp
         ../../Draw/main/inc/Drawer.hpp
         ../../Draw/main/inc/Texture.hpp
         ../../Draw/main/inc/TextureModifier.hpp
         ../../Genetic/main/inc/GeneticCrossParameter.hpp
         ../../Genetic/main/inc/GeneticDna.hpp
         ../../Genetic/main/inc/GeneticDnaList.hpp
         ../../Genetic/main/inc/GeneticDnaListObject.hpp
         ../../Genetic/main/inc/GeneticDnaListString.hpp
         ../../Genetic/main/inc/GeneticDnaNeuralNetwork.hpp
         ../../Genetic/main/inc/GeneticGene.hpp
         ../../Genetic/main/inc/GeneticGeneDouble.hpp
         ../../Genetic/main/inc/GeneticGeneObject.hpp
         ../../Misc/main/inc/BezierSpline2D.hpp
         ../../Misc/main/inc/Misc.hpp
         ../../Misc/main/inc/Vector2D.hpp
         ../../Neural/main/inc/NeuralActivation.hpp
         ../../Neural/main/inc/NeuralInputValue.hpp
         ../../Neural/main/inc/NeuralLayer.hpp
         ../../Neural/main/inc/NeuralNetwork.hpp
         ../../Neural/main/inc/NeuralNeuron.hpp
         ../../TrackData/main/inc/TrackData.hpp)

set(UI_SOURCES ./src/AppRace.ui)
qt5_wrap_ui(UI_GENERATED_HEADERS ${UI_SOURCES})

set(RESOURCES ../../Draw/main/resources/images.qrc)

set(CMAKE_AUTOMOC ON)

set(CMAKE AUTOUIC ON)

set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(AppRace WIN32 ${SOURCES} ${HEADERS} ${UI_GENERATED_HEADERS} ${RESOURCES})
target_link_libraries(AppRace Qt5::Widgets)
