cmake_minimum_required (VERSION 3.6.2)

project(AppTestMisc)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_VERBOSE_MAKEFILE FALSE)

find_package(Qt5Widgets REQUIRED)

include_directories(../..)

set(SOURCES
        ./src/AppTest.cpp
        ../../Debug/main/src/Logger.cpp
        ../../Misc/main/src/BezierSpline2D.cpp
        ../../Misc/main/src/Misc.cpp
        ../../Misc/main/src/Vector2D.cpp)

set(HEADERS
         ../../Debug/main/inc/Logger.hpp
         ../../Misc/main/inc/BezierSpline2D.hpp
         ../../Misc/main/inc/Couple.hpp
         ../../Misc/main/inc/Misc.hpp
         ../../Misc/main/inc/Triple.hpp
         ../../Misc/main/inc/Vector2D.hpp)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(AppTestMisc ${SOURCES} ${HEADERS})
target_link_libraries(AppTestMisc Qt5::Widgets)

