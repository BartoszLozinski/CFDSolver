#!/bin/bash

# select configuration (Debug/Release) from first argument, default Debug
CONFIG=${1:-Debug}
if [[ "$CONFIG" != "Debug" && "$CONFIG" != "Release" ]]; then
    echo "Usage: $0 [Debug|Release]"
    exit 1
fi

if [ ! -d build ]; then
    mkdir build
fi

if [ ! -d "build/$CONFIG" ]; then
    mkdir "build/$CONFIG"
fi

cd "build/$CONFIG" || exit 1
cmake ../.. -G Ninja -DCMAKE_BUILD_TYPE=$CONFIG
ninja
cd ../..
