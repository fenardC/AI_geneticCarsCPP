#!/usr/bin/bash

##set -x

FORCE_DELETE=true

NCPU=$(/usr/bin/nproc 2>/dev/null)
NPROCESS=${NCPU:-1}

if ${FORCE_DELETE}; then
    rm  -f ./Misc/test/Makefile
    rm -rf ./Misc/test/CMakeFiles
    rm  -f ./Misc/test/CMakeCache.txt
    rm  -f ./Misc/test/cmake_install.cmake
    rm  -f ./Misc/test/*.exe
fi
pushd ./Misc/test && cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"
popd
make -j${NPROCESS} -C ./Misc/test -f Makefile clean all

if ${FORCE_DELETE}; then
    rm  -f ./Draw/test/Makefile
    rm -rf ./Draw/test/CMakeFiles
    rm  -f ./Draw/test/CMakeCache.txt
    rm  -f ./Draw/test/cmake_install.cmake
    rm  -f ./Draw/test/ui_AppTestDraw.h
    rm  -f ./Draw/test/moc_*
    rm  -f ./Draw/test/*.exe
fi
pushd ./Draw/test && cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"
popd
make -j${NPROCESS} -C ./Draw/test -f Makefile clean all


