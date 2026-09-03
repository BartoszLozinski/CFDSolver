 #!/bin/bash
 
 CONFIG=${1:-Debug}
 if [[ "$CONFIG" != "Debug" && "$CONFIG" != "Release" ]]; then
     echo "Usage: $0 [Debug|Release]"
     exit 1
 fi
 
cd  ./cpp

 if [ ! -d "build/$CONFIG" ]; then
     mkdir -p "build/$CONFIG"
 fi
 
 cd "build/$CONFIG"
 cmake ../.. -G Ninja -DCMAKE_BUILD_TYPE=$CONFIG
 ninja
 
 cd ../../../
