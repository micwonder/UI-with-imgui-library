cmake_minimum_required(VERSION 3.24)
project(imgui)

find_package(glfw3 CONFIG REQUIRED)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

add_library(
        ${PROJECT_NAME}
        STATIC
        imgui/imgui.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_demo.cpp

        imgui/backends/imgui_impl_opengl3.cpp
        imgui/backends/imgui_impl_glfw.cpp
)

target_link_libraries(${PROJECT_NAME} glfw ${OPENGL_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC imgui)
