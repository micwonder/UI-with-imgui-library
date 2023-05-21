#pragma once
#define GLEW_STATIC
#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#endif
#ifdef __linux__
#define GLFW_EXPOSE_NATIVE_X11
#endif
#ifdef __APPLE__
#define GLFW_EXPOSE_NATIVE_COCOA
#endif

#include <vector>
#include <GLFW/glfw3.h>
#include <Windows.h>
#define STB_IMAGE_IMPLEMENTATION
#include "imgui.h"
#include "event.hpp"

#define LEFTTOP 1
#define LEFT 2
#define LEFTBOTTOM 3
#define BOTTOM 4
#define RIGHTBOTTOM 5
#define RIGHT 6
#define RIGHTTOP 7
#define TOP 8

class CleanGui
{
private:
    char* title = "Boss";
    char* icon_image_path = "C:/dev/Resources/Icons/BossIcons/BossIcon-1.png";
    int glfw_pos_x_ = 0, glfw_pos_y_ = 0, w = 1100, h = 700, content_w = 1100, content_h = 700;
    UINT dpiX, dpiY;
    int SetWindowsTitleBar();

    int window_pos_x = 500;
    int window_pos_y = 100;
    int init_x = 0;
    int init_y = 0;
    POINT mouse_start_pos;
    ImVec2 window_start_pos = { 0, 0 };
    bool mouse_clicked = false;
    bool mouse_dragging = false;
    int resize_clicked = 0;
    double re_pos_x, re_pos_y, re_size_x, re_size_y, re_cur_x, re_cur_y;
    GLFWimage icon_files[5];
    GLFWcursor* icons[5];

protected:
    GLFWwindow* window;
public:
    bool isMaximized = false;
    bool isclose = false;
    bool resize_over = false;
    int init_glfw();
    int init_im_gui();

    int start_clean_window();
    int end_clean_window();

    int terminate_im_gui();
    int terminate_glfw();

    bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height);

    ImVec2 getWindowSize();
    void minimizeWindow();
    void maximizeWindow();
    void restoreWindow();
    void closeWindow();
    void setResizeCursor();
    void setDPI();
};