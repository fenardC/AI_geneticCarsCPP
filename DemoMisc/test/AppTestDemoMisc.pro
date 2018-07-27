#-------------------------------------------------
#
# Project created by QtCreator 2018-03-06T11:56:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AppTestDemoMisc
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
        ../../Debug/main/src/Debugger.cpp \
        ../../Debug/main/src/Logger.cpp \
        ../../DemoGui/main/src/ScreenGeneticCar.cpp \
        ../../DemoMisc/main/src/Car.cpp \
        ../../DemoMisc/main/src/CarSensorLine.cpp \
        ../../DemoMisc/main/src/CarSensorPoint.cpp \
        ../../DemoMisc/main/src/Track.cpp \
        ../../DemoMisc/test/src/AppTestDemoMisc.cpp \
        ../../DemoMisc/test/src/DemoCar.cpp \
        ../../DemoMisc/test/src/main.cpp \
        ../../Draw/main/src/Drawer.cpp \
        ../../Draw/main/src/Texture.cpp \
        ../../Draw/main/src/TextureModifier.cpp \
        ../../Misc/main/src/Vector2D.cpp \
        ../../Misc/main/src/BezierSpline2D.cpp \
        ../../Misc/main/src/Misc.cpp

INCLUDEPATH += ../..

HEADERS += \
         ../../Debug/main/inc/Debugger.hpp \
         ../../Debug/main/inc/Logger.hpp \
         ../../DemoGui/main/inc/ScreenGeneticCar.hpp \
         ../../DemoMisc/main/inc/Car.hpp \
         ../../DemoMisc/main/inc/CarSensor.hpp \
         ../../DemoMisc/main/inc/CarSensorLine.hpp \
         ../../DemoMisc/main/inc/CarSensorPoint.hpp \
         ../../DemoMisc/main/inc/Track.hpp \
         ../../DemoMisc/test/inc/AppTestDemoMisc.h \
         ../../Draw/main/inc/Drawer.hpp \
         ../../Draw/main/inc/Texture.hpp \
         ../../Draw/main/inc/TextureModifier.hpp \
         ../../Misc/main/inc/Vector2D.hpp \
         ../../Misc/main/inc/BezierSpline2D.hpp \
         ../../Misc/main/inc/Misc.hpp

FORMS += \
       ./src/AppTestDemoMisc.ui

RESOURCES += \
    ../../Draw/main/resources/images.qrc
