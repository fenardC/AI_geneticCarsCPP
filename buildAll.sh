#!/usr/bin/bash

set -e
## set -x

: ${FORCE_DELETE:=false}

NCPU=$(/usr/bin/nproc 2>/dev/null)
NPROCESS=${NCPU:-1}

## cmake -DCMAKE_C_COMPILER=/usr/libexec/ccc-analyzer

CMAKE_PROJECT_OPTION='-Wall -Wextra -ansi -pedantic'
## CMAKE_PROJECT_OPTION+=' -Weffc++'

: ${CMAKE_BUILD_TYPE_OPTION:=Debug}

echo "Build is of type: ${CMAKE_BUILD_TYPE_OPTION}"

if ${FORCE_DELETE}; then
    rm  -f ./Misc/test/Makefile
    rm -rf ./Misc/test/CMakeFiles
    rm  -f ./Misc/test/CMakeCache.txt
    rm  -f ./Misc/test/cmake_install.cmake
    rm  -f ./Misc/test/*.o
    rm  -f ./Misc/test/*.exe
fi
pushd ./Misc/test && cmake -DCMAKE_CXX_FLAGS="${CMAKE_PROJECT_OPTION}" -DCMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE_OPTION}" -G "Unix Makefiles"
popd
make -j${NPROCESS} -C ./Misc/test -f Makefile all

if ${FORCE_DELETE}; then
    rm  -f ./Draw/test/Makefile
    rm -rf ./Draw/test/CMakeFiles
    rm  -f ./Draw/test/CMakeCache.txt
    rm  -f ./Draw/test/cmake_install.cmake
    rm  -f ./Draw/test/ui_AppTestDraw.h
    rm  -f ./Draw/test/moc_*
    rm  -f ./Draw/test/*.o
    rm  -f ./Draw/test/*.exe
fi
pushd ./Draw/test && cmake -DCMAKE_CXX_FLAGS="${CMAKE_PROJECT_OPTION}" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE_OPTION} -G "Unix Makefiles"
popd
make -j${NPROCESS} -C ./Draw/test -f Makefile all

if ${FORCE_DELETE}; then
    rm  -f ./DemoMisc/test/Makefile
    rm -rf ./DemoMisc/test/CMakeFiles
    rm  -f ./DemoMisc/test/CMakeCache.txt
    rm  -f ./DemoMisc/test/cmake_install.cmake
    rm  -f ./DemoMisc/test/ui_AppTestDemoMisc.h
    rm  -f ./DemoMisc/test/moc_*
    rm  -f ./DemoMisc/test/*.o
    rm  -f ./DemoMisc/test/*.exe
fi
pushd ./DemoMisc/test && cmake -DCMAKE_CXX_FLAGS="${CMAKE_PROJECT_OPTION}" -DCMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE_OPTION}" -G "Unix Makefiles"
popd
make -j${NPROCESS} -C ./DemoMisc/test -f Makefile all

if ${FORCE_DELETE}; then
    rm  -f ./Genetic/test/Makefile
    rm -rf ./Genetic/test/CMakeFiles
    rm  -f ./Genetic/test/CMakeCache.txt
    rm  -f ./Genetic/test/cmake_install.cmake
    rm  -f ./Genetic/test/*.o
    rm  -f ./Genetic/test/*.exe
fi
pushd ./Genetic/test && cmake -DCMAKE_CXX_FLAGS="${CMAKE_PROJECT_OPTION}" -DCMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE_OPTION}" -G "Unix Makefiles"
popd
make -j${NPROCESS} -C ./Genetic/test -f Makefile all


if ${FORCE_DELETE}; then
    rm  -f ./Neural/test/Makefile
    rm -rf ./Neural/test/CMakeFiles
    rm  -f ./Neural/test/CMakeCache.txt
    rm  -f ./Neural/test/cmake_install.cmake
    rm  -f ./Neural/test/*.o
    rm  -f ./Neural/test/*.exe
fi
pushd ./Neural/test && cmake -DCMAKE_CXX_FLAGS="${CMAKE_PROJECT_OPTION}" -DCMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE_OPTION}" -G "Unix Makefiles"
popd
make -j${NPROCESS} -C ./Neural/test -f Makefile all


if ${FORCE_DELETE}; then
    rm  -f ./AppLearning/main/Makefile
    rm -rf ./AppLearning/main/CMakeFiles
    rm  -f ./AppLearning/main/CMakeCache.txt
    rm  -f ./AppLearning/main/cmake_install.cmake
    rm  -f ./AppLearning/main/ui_AppLearning.h
    rm  -f ./AppLearning/main/moc_*
    rm  -f ./AppLearning/main/*.o
    rm  -f ./AppLearning/main/*.exe
fi
pushd ./AppLearning/main && cmake -DCMAKE_CXX_FLAGS="${CMAKE_PROJECT_OPTION}" -DCMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE_OPTION}" -G "Unix Makefiles"
popd
make -j${NPROCESS} -C ./AppLearning/main -f Makefile all

if ${FORCE_DELETE}; then
    rm  -f ./AppRace/main/Makefile
    rm -rf ./AppRace/main/CMakeFiles
    rm  -f ./AppRace/main/CMakeCache.txt
    rm  -f ./AppRace/main/cmake_install.cmake
    rm  -f ./AppRace/main/ui_AppRace.h
    rm  -f ./AppRace/main/moc_*
    rm  -f ./AppRace/main/*.o
    rm  -f ./AppRace/main/*.exe
fi
pushd ./AppRace/main && cmake -DCMAKE_CXX_FLAGS="${CMAKE_PROJECT_OPTION}" -DCMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE_OPTION}" -G "Unix Makefiles"
popd
make -j${NPROCESS} -C ./AppRace/main -f Makefile all

