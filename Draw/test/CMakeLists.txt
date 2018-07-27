cmake_minimum_required (VERSION 3.6.2)

project(AppTestDraw)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_VERBOSE_MAKEFILE FALSE)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

include_directories(../..)

set(SOURCES
        ../../Debug/main/src/Logger.cpp
        ../../Draw/main/src/Drawer.cpp
        ../../Draw/main/src/Texture.cpp
        ../../Draw/main/src/TextureModifier.cpp
        ../../Draw/test/src/AppTestDraw.cpp
        ../../Draw/test/src/main.cpp
        ../../Draw/test/src/TestDraw.cpp
        ../../Misc/main/src/Misc.cpp
        ../../Misc/main/src/Vector2D.cpp)

set(HEADERS
         ../../Debug/main/inc/Logger.hpp
         ../../Draw/test/inc/AppTestDraw.h
         ../../Draw/main/inc/Drawer.hpp
         ../../Draw/main/inc/DrawParameterNeuralNetwork.hpp
         ../../Draw/test/inc/TestDraw.hpp
         ../../Draw/main/inc/Texture.hpp
         ../../Draw/main/inc/TextureModifier.hpp
         ../../Misc/main/inc/Misc.hpp
         ../../Misc/main/inc/Vector2D.hpp)

set(UI_SOURCES ./src/AppTestDraw.ui)
qt5_wrap_ui(UI_GENERATED_HEADERS ${UI_SOURCES})

set(RESOURCES ../../Draw/main/resources/images.qrc)

set(CMAKE_AUTOMOC ON)

set(CMAKE AUTOUIC ON)

set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

add_executable(AppTestDraw WIN32 ${SOURCES} ${HEADERS} ${UI_GENERATED_HEADERS} ${RESOURCES})
target_link_libraries(AppTestDraw Qt5::Widgets)

