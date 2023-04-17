cmake_minimum_required(VERSION 3.24)
project(gui)

if (WIN32 OR MSVC)
    set(CMAKE_PREFIX_PATH "C:/dev/vcpkg/installed/x64-windows/share")
endif ()

set(TARGET ${PROJECT_NAME})
set(TEST_TARGET gui_test)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

find_package(glfw3 CONFIG REQUIRED)

add_executable(${TEST_TARGET} "main.cpp")
add_library(${TARGET} STATIC "gui.cpp" "gui.hpp" "clean_gui.cpp" "clean_gui.hpp" "stb_image.h" "design/abyssinica.h" "design/blur.cpp" "design/blur.hpp" "design/blur_x.h" "design/blur_y.h" "design/GeneralBg.h" "design/icon_font.h" "design/MenuBg.h")
target_include_directories(${TARGET} PUBLIC .)

target_link_libraries(${TARGET} imgui glfw ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

target_link_libraries(${TEST_TARGET} ${TARGET} imgui glfw ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

