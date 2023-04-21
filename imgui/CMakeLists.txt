cmake_minimum_required(VERSION 3.24)
project(imgui)


if (WIN32 OR MSVC)
    set(CMAKE_PREFIX_PATH "C:/dev/vcpkg/installed/x64-windows/share")
endif ()

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

        imgui/blur.cpp

        imgui/examples/example_win32_directx9/icon_font.h
        imgui/examples/example_win32_directx9/MenuBg.h
        imgui/examples/example_win32_directx9/GeneralBg.h
        imgui/examples/example_win32_directx9/abyssinica.h

        imgui/backends/imgui_impl_opengl3.cpp
        imgui/backends/imgui_impl_glfw.cpp
        imgui/backends/imgui_impl_dx9.cpp
        imgui/backends/imgui_impl_win32.cpp
)

target_link_libraries(${PROJECT_NAME} glfw ${OPENGL_LIBRARIES} Microsoft::D3DX9 Microsoft::D3DX10 Microsoft::D3DX11)

target_include_directories(${PROJECT_NAME} PUBLIC imgui)
target_include_directories(${PROJECT_NAME} PUBLIC imgui/backends)
