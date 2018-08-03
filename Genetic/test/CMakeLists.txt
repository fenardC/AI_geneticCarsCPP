cmake_minimum_required (VERSION 3.6.2)

project(AppTestGenetic CXX)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_VERBOSE_MAKEFILE FALSE)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

include_directories(../..)


set(SOURCES
        ../../Debug/main/src/Debugger.cpp
        ../../Debug/main/src/Logger.cpp
        ../../Genetic/main/src/GeneticCrossParameter.cpp
        ../../Genetic/main/src/GeneticDnaList.cpp
        ../../Genetic/main/src/GeneticDnaListObject.cpp
        ../../Genetic/main/src/GeneticDnaListString.cpp
        ../../Genetic/main/src/GeneticDnaNeuralNetwork.cpp
        ../../Genetic/main/src/GeneticDnaTree.cpp
        ../../Genetic/main/src/GeneticDnaTreeFormula.cpp
        ../../Genetic/main/src/GeneticGeneDouble.cpp
        ../../Genetic/main/src/GeneticGeneFormulaOperand.cpp
        ../../Genetic/main/src/GeneticGeneObject.cpp
        ../../Genetic/main/src/GeneticGeneString.cpp
        ../../Genetic/main/src/GeneticGeneTreeBranch.cpp 
        ../../Genetic/main/src/GeneticIndividual.cpp
        ../../Genetic/main/src/GeneticPopulation.cpp
        ../../Misc/main/src/Misc.cpp
        ../../Genetic/test/src/AppTest.cpp)


set(HEADERS
         ../../Debug/main/inc/Debugger.hpp
         ../../Debug/main/inc/Logger.hpp
         ../../Genetic/main/inc/GeneticCrossParameter.hpp
         ../../Genetic/main/inc/GeneticDna.hpp
         ../../Genetic/main/inc/GeneticDnaList.hpp
         ../../Genetic/main/inc/GeneticDnaListObject.hpp
         ../../Genetic/main/inc/GeneticDnaListString.hpp
         ../../Genetic/main/inc/GeneticDnaNeuralNetwork.hpp
         ../../Genetic/main/inc/GeneticDnaTree.hpp
         ../../Genetic/main/inc/GeneticDnaTreeFormula.hpp
         ../../Genetic/main/inc/GeneticGene.hpp
         ../../Genetic/main/inc/GeneticGeneDouble.hpp
         ../../Genetic/main/inc/GeneticGeneFormulaOperand.hpp
         ../../Genetic/main/inc/GeneticGeneObject.hpp
         ../../Genetic/main/inc/GeneticGeneString.hpp
         ../../Genetic/main/inc/GeneticGeneTreeBranch.hpp
         ../../Genetic/main/inc/GeneticIndividual.hpp
         ../../Genetic/main/inc/GeneticPopulation.hpp
         ../../Misc/main/inc/Misc.hpp)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(AppTestGenetic ${SOURCES} ${HEADERS})
target_link_libraries(AppTestGenetic Qt5::Widgets)

