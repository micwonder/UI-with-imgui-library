rd /s /q "build"
mkdir build
cd build
cmake ../. -DCMAKE_TOOLCHAIN_FILE=C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build .
cd ..
pause