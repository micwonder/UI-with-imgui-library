cmake_minimum_required(VERSION 3.24)
project(gui)

if (WIN32 OR MSVC)
    set(CMAKE_PREFIX_PATH "C:/dev/vcpkg/installed/x64-windows/share")
endif ()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TARGET ${PROJECT_NAME})
set(TEST_TARGET gui_test)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLEW REQUIRED)
find_package(dxsdk-d3dx CONFIG REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

find_package(glfw3 CONFIG REQUIRED)

add_subdirectory(imgui)
add_executable(${TEST_TARGET} "main.cpp")
add_library(${TARGET} STATIC "gui.cpp" "gui.hpp" "checkbox.cpp" "event.hpp" "button.cpp" "inputtexts.cpp" "selector.cpp" "tiles.cpp"  "clean_gui.cpp" "clean_gui.hpp" "design/MenuBg.h" "design/GeneralBg.h" "design/icon_font.h" "design/abyssinica.h" "design/blur.cpp" "design/blur_x.h" "design/blur_y.h" "button.cpp" "checkbox.cpp" "graph.cpp") #"design/abyssinica.h" "design/blur.cpp" "design/blur.hpp" "design/blur_x.h" "design/blur_y.h" "design/GeneralBg.h" "design/icon_font.h" "design/MenuBg.h")
target_include_directories(${TARGET} PUBLIC .)

target_link_libraries(${TARGET} imgui glfw ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} Microsoft::D3DX9 Microsoft::D3DX10 Microsoft::D3DX11)

target_link_libraries(${TEST_TARGET} ${TARGET} imgui glfw ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} Microsoft::D3DX9 Microsoft::D3DX10 Microsoft::D3DX11)