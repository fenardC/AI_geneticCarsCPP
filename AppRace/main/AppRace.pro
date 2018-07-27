#-------------------------------------------------
#
# Project created by QtCreator 2018-03-06T11:56:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AppRace
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        ../../AppRace/main/src/AppRace.cpp \
        ../../AppRace/main/src/AppRaceUi.cpp \
        ../../AppRace/main/src/CarParameters.cpp \
        ../../AppRace/main/src/CarRacingWorker.cpp \
        ../../AppRace/main/src/main.cpp \
        ../../AppRace/main/src/TrackDataRace.cpp \
        ../../CoreApp/main/src/CarMotionHelper.cpp \
        ../../Debug/main/src/Debugger.cpp \
        ../../Debug/main/src/Logger.cpp \
        ../../DemoGui/main/src/ScreenGeneticCar.cpp \
        ../../DemoMisc/main/src/Car.cpp \
        ../../DemoMisc/main/src/CarSensorLine.cpp \
        ../../DemoMisc/main/src/CarSensorPoint.cpp \
        ../../DemoMisc/main/src/Track.cpp \
        ../../Draw/main/src/Drawer.cpp \
        ../../Draw/main/src/Texture.cpp \
        ../../Draw/main/src/TextureModifier.cpp \
        ../../Genetic/main/src/GeneticCrossParameter.cpp \
        ../../Genetic/main/src/GeneticDnaList.cpp \
        ../../Genetic/main/src/GeneticDnaListObject.cpp \
        ../../Genetic/main/src/GeneticDnaNeuralNetwork.cpp \
        ../../Genetic/main/src/GeneticGeneDouble.cpp \
        ../../Genetic/main/src/GeneticGeneObject.cpp \
        ../../Genetic/main/src/GeneticIndividual.cpp \
        ../../Misc/main/src/BezierSpline2D.cpp \
        ../../Misc/main/src/Misc.cpp \
        ../../Misc/main/src/Vector2D.cpp \
        ../../Neural/main/src/NeuralActivation.cpp \
        ../../Neural/main/src/NeuralInputValue.cpp \
        ../../Neural/main/src/NeuralLayer.cpp \
        ../../Neural/main/src/NeuralNetwork.cpp \
        ../../Neural/main/src/NeuralNeuron.cpp \
        ../../TrackData/main/src/TrackData.cpp

INCLUDEPATH += ../..

HEADERS += \
         ../../AppRace/main/inc/AppRace.hpp \
         ../../AppRace/main/inc/AppRaceUi.h \
         ../../AppRace/main/inc/CarParameters.hpp \
         ../../AppRace/main/inc/CarRacingWorker.hpp \
         ../../AppRace/main/inc/TrackDataRace.hpp \
         ../../CoreApp/main/inc/CarMotionHelper.hpp \
         ../../Debug/main/inc/Debugger.hpp \
         ../../Debug/main/inc/Logger.hpp \
         ../../DemoGui/main/inc/ScreenGeneticCar.hpp \
         ../../DemoMisc/main/inc/Car.hpp \
         ../../DemoMisc/main/inc/CarSensor.hpp \
         ../../DemoMisc/main/inc/CarSensorLine.hpp \
         ../../DemoMisc/main/inc/CarSensorPoint.hpp \
         ../../DemoMisc/main/inc/Track.hpp \
         ../../Draw/main/inc/Drawer.hpp \
         ../../Draw/main/inc/Texture.hpp \
         ../../Draw/main/inc/TextureModifier.hpp \
         ../../Genetic/main/inc/GeneticCrossParameter.hpp \
         ../../Genetic/main/inc/GeneticDna.hpp \
         ../../Genetic/main/inc/GeneticDnaList.hpp \
         ../../Genetic/main/inc/GeneticDnaListObject.hpp \
         ../../Genetic/main/inc/GeneticDnaListString.hpp \
         ../../Genetic/main/inc/GeneticDnaNeuralNetwork.hpp \
         ../../Genetic/main/inc/GeneticGene.hpp \
         ../../Genetic/main/inc/GeneticGeneDouble.hpp \
         ../../Genetic/main/inc/GeneticGeneObject.hpp \
         ../../Misc/main/inc/BezierSpline2D.hpp \
         ../../Misc/main/inc/Misc.hpp \
         ../../Misc/main/inc/Vector2D.hpp \
         ../../Neural/main/inc/NeuralActivation.hpp \
         ../../Neural/main/inc/NeuralInputValue.hpp \
         ../../Neural/main/inc/NeuralLayer.hpp \
         ../../Neural/main/inc/NeuralNetwork.hpp \
         ../../Neural/main/inc/NeuralNeuron.hpp \
         ../../TrackData/main/inc/TrackData.hpp


FORMS += \
       ./src/AppRace.ui

RESOURCES += \
    ../../Draw/main/resources/images.qrc
