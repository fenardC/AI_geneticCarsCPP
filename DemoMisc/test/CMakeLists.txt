cmake_minimum_required (VERSION 3.6.2)

project(AppTestDemoMisc)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_VERBOSE_MAKEFILE FALSE)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

include_directories(../..)

set(SOURCES
 ../../Debug/main/src/Debugger.cpp
 ../../Debug/main/src/Logger.cpp
 ../../DemoGui/main/src/ScreenGeneticCar.cpp
 ../../DemoMisc/main/src/Car.cpp
 ../../DemoMisc/main/src/CarSensorLine.cpp
 ../../DemoMisc/main/src/CarSensorPoint.cpp
 ../../DemoMisc/main/src/Track.cpp
 ../../DemoMisc/test/src/AppTestDemoMisc.cpp
 ../../DemoMisc/test/src/DemoCar.cpp
 ../../DemoMisc/test/src/main.cpp
 ../../Draw/main/src/Drawer.cpp
 ../../Draw/main/src/Texture.cpp
 ../../Draw/main/src/TextureModifier.cpp
 ../../Misc/main/src/Vector2D.cpp
 ../../Misc/main/src/BezierSpline2D.cpp
 ../../Misc/main/src/Misc.cpp)


set(HEADERS
 ../../Debug/main/inc/Debugger.hpp
 ../../Debug/main/inc/Logger.hpp
 ../../DemoGui/main/inc/ScreenGeneticCar.hpp
 ../../DemoMisc/main/inc/Car.hpp
 ../../DemoMisc/main/inc/CarSensor.hpp
 ../../DemoMisc/main/inc/CarSensorLine.hpp
 ../../DemoMisc/main/inc/CarSensorPoint.hpp
 ../../DemoMisc/main/inc/Track.hpp
 ../../DemoMisc/test/inc/AppTestDemoMisc.h
 ../../DemoMisc/test/inc/DemoCar.hpp
 ../../Draw/main/inc/Drawer.hpp
 ../../Draw/main/inc/Texture.hpp
 ../../Draw/main/inc/TextureModifier.hpp
 ../../Misc/main/inc/Vector2D.hpp
 ../../Misc/main/inc/BezierSpline2D.hpp
 ../../Misc/main/inc/Misc.hpp)

set(UI_SOURCES ./src/AppTestDemoMisc.ui)
qt5_wrap_ui(UI_GENERATED_HEADERS ${UI_SOURCES})

set(RESOURCES ../../Draw/main/resources/images.qrc)

set(CMAKE_AUTOMOC ON)

set(CMAKE AUTOUIC ON)

set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(AppTestDemoMisc WIN32 ${SOURCES} ${HEADERS} ${UI_GENERATED_HEADERS} ${RESOURCES})
target_link_libraries(AppTestDemoMisc Qt5::Widgets)

