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


