cmake_minimum_required (VERSION 3.6.2)

project(AppTestNeural)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_VERBOSE_MAKEFILE FALSE)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

include_directories(../..)


set(SOURCES
        ./src/AppTest.cpp
        ../../Debug/main/src/Debugger.cpp
        ../../Debug/main/src/Logger.cpp
        ../../Draw/main/src/Drawer.cpp
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
        ../../Neural/main/src/NeuralActivation.cpp
        ../../Neural/main/src/NeuralInputValue.cpp
        ../../Neural/main/src/NeuralLayer.cpp
        ../../Neural/main/src/NeuralNetwork.cpp
        ../../Neural/main/src/NeuralNeuron.cpp)


set(HEADERS
         ../../Debug/main/inc/Debugger.hpp
         ../../Debug/main/inc/Logger.hpp
         ../../Draw/main/inc/Drawer.hpp
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
         ../../Misc/main/inc/Misc.hpp
         ../../Neural/main/inc/NeuralActivation.hpp
         ../../Neural/main/inc/NeuralInputValue.hpp
         ../../Neural/main/inc/NeuralLayer.hpp
         ../../Neural/main/inc/NeuralNetwork.hpp
         ../../Neural/main/inc/NeuralNeuron.hpp)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(AppTestNeural ${SOURCES} ${HEADERS})
target_link_libraries(AppTestNeural Qt5::Widgets)

