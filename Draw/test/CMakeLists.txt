# 

cmake_minimum_required (VERSION 3.6.2)

##set(CMAKE_ECLIPSE_VERSION 4.6)

project(AppTestDraw)
enable_language(CXX)

set(CMAKE_VERBOSE_MAKEFILE TRUE)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

include_directories(../..)

set(SOURCES
        ../../Debug/main/src/Logger.cpp
        ../../Draw/test/src/main.cpp
        ../../Draw/test/src/AppTestDraw.cpp
        ../../Draw/test/src/TestDraw.cpp
        ../../Draw/main/src/Drawer.cpp
        ../../Misc/main/src/Misc.cpp)

set(HEADERS
         ../../Debug/main/inc/Logger.hpp
         ../../Draw/test/inc/AppTestDraw.h
         ../../Draw/test/inc/TestDraw.hpp
         ../../Draw/main/inc/Drawer.hpp
         ../../Draw/main/inc/Texture.hpp
         ../../Draw/main/inc/TextureModifier.hpp
         ../../Draw/main/inc/DrawParameterNeuralNetwork.hpp
         ../../Misc/main/inc/Misc.hpp)

set(UI_SOURCES ./src/AppTestDraw.ui)
qt5_wrap_ui(UI_GENERATED_HEADERS ${UI_SOURCES})

set(CMAKE_AUTOMOC ON)

set(CMAKE AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g -O0")
message(${CMAKE_CXX_FLAGS})

add_executable(AppTestDraw WIN32 ${SOURCES} ${HEADERS} ${UI_GENERATED_HEADERS})
target_link_libraries(AppTestDraw Qt5::Widgets)

