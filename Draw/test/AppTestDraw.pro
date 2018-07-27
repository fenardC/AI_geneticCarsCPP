#-------------------------------------------------
#
# Project created by QtCreator 2018-03-06T11:56:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AppTestDraw
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
         ../../Debug/main/src/Logger.cpp \
         ../../Draw/main/src/Drawer.cpp \
         ../../Draw/main/src/Texture.cpp \
         ../../Draw/main/src/TextureModifier.cpp \
         ../../Draw/test/src/AppTestDraw.cpp \
         ../../Draw/test/src/main.cpp \
         ../../Draw/test/src/TestDraw.cpp \
         ../../Misc/main/src/Misc.cpp \
         ../../Misc/main/src/Vector2D.cpp

INCLUDEPATH += ../..

HEADERS += \
        ../../Debug/main/inc/Logger.hpp \
        ../../Draw/main/inc/Drawer.hpp \
        ../../Draw/main/inc/DrawParameterNeuralNetwork.hpp \
        ../../Draw/main/inc/Texture.hpp \
        ../../Draw/main/inc/TextureModifier.hpp \
        ../../Draw/test/inc/AppTestDraw.h \
        ../../Draw/test/inc/TestDraw.hpp \
        ../../Misc/main/inc/Misc.hpp

FORMS += \
       ./src/AppTestDraw.ui

RESOURCES += \
    ../main/resources/images.qrc
