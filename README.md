# AI_geneticCarsCPP
Artificial intelligence project for car animation.

# Abstract
This project aims at integrating demonstration about neural network.  
This is the C++ port of the parent project written in JAVA.  


Cars are taught to travel several circuits. Then a well chosen car is put 
on an unknown circuit to demonstrate how the neural network works.

The architecture of the neural network is built around two neurons that calculate 
commands for steering wheel and engine of the car. Each neuron is given input 
values from sensors (the distances from the outside of the circuit and the current car position).

The learning strategy is to experience population of cars with initial random
 values for the weights and threshold for the neurons. 
Depending on completion achieved on the circuit, cars are scored. Until at least one car succeeded
 in completing circuits, the experience is redone with modification of the weights and the thresholds
  thanks to a genetic algorithm that takes into account the score of the cars.

_It is interesting to see this, I think._
_Cyril FENARD._

# Key words

## Topics

**Perceptron** **Weights** **Threshold** **Genetic mutation** **Learning** **Neural network**

## Software

**C++** **QT** **CMake** **Eclipse**
**Windows** **Cygwin** **Linux**


# Check development environment

	$ uname -smov
	CYGWIN_NT-10.0 2018-11-08 14:34 x86_64 Cygwin

	$ cat /cygdrive/c/eclipse/.eclipseproduct | grep version
	version=4.9.0

# Some technical reminders

  * building the application

        $ export FORCE_DELETE=true && ./buildAll.sh

  * running the applications

        $ ./AppLearning/main/AppLearning
        $ ./AppRace/main/AppRace
        $ ./DemoMisc/test/AppTestDemoMisc
        $ ./Draw/test/AppTestDraw
        $ ./Genetic/test/AppTestGenetic
        $ ./Misc/test/AppTestMisc
        $ ./Neural/test/AppTestNeural
