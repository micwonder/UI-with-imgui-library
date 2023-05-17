#include "imgui.h"
#include "clean_gui.hpp"

#include <iostream>
#include <GLFW/glfw3native.h>
#include <dwmapi.h>
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "stb_image.h"

#include <ShellScalingApi.h>
#pragma comment(lib, "User32.lib")

#include <GL/gl.h>

bool CleanGui::LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
{
    // Load from file
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);
    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); // Same

    // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}

int CleanGui::init_glfw()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, 1);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, false);
    window = glfwCreateWindow(w, h, title, nullptr, nullptr);
    hwnd = glfwGetWin32Window(window);
    glfwMakeContextCurrent(window);
    glfwShowWindow(window);

    GLFWimage images[1];
    images[0].pixels = stbi_load(icon_image_path, &images[0].width, &images[0].height, nullptr, 4);
    if (!images[0].pixels)
    {
        std::cout << "Failed to load the bmp file" << std::endl;
        return 1;
    }
    glfwSetWindowIcon(window, 1, images);
    stbi_image_free(images[0].pixels);
    return 0;
}

int CleanGui::init_im_gui()
{
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");// "#version 130"
    glfwSetWindowPos(window, window_pos_x, window_pos_y);
    return 0;
}

int CleanGui::start_clean_window()
{
    glfwGetWindowPos(window, &glfw_pos_x_, &glfw_pos_y_);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //resize
    int window_w, window_h;
    glfwGetWindowSize(window, &window_w, &window_h);
    ImGui::SetNextWindowSize(ImVec2(static_cast<float>(window_w), static_cast<float>(window_h)));

    //MainSpace
    ImGui::SetNextWindowPos({ 0, 0 });
    ImGui::SetNextWindowSizeConstraints(ImVec2(content_w, content_h), ImVec2(FLT_MAX, FLT_MAX));

    bool select = true;
    double curx, cury;
    glfwGetCursorPos(window, &curx, &cury);

    ImGui::Begin(title, &select, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoResize);
    if (isMaximized)
    {
        glfwSetWindowPos(window, 0, 0);
        int xScreenResolution = GetSystemMetrics(SM_CXSCREEN);
        int yScreenResolution = GetSystemMetrics(SM_CYSCREEN);
        glfwSetWindowSize(window, xScreenResolution, yScreenResolution);
        return 0;
    }
    if (resize_clicked == 0)
    {
        POINT mouse_pos;
        GetCursorPos(&mouse_pos);
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            if (!mouse_clicked)
            {
                mouse_start_pos = mouse_pos;
                init_x = window_pos_x;
                init_y = window_pos_y;
                mouse_clicked = true;
            }
        }
        else if (ImGui::IsMouseDragging(ImGuiMouseButton_Left))
        {
            if (mouse_clicked)
            {
                mouse_dragging = true;
                window_pos_x = init_x - mouse_start_pos.x + mouse_pos.x;
                window_pos_y = init_y - mouse_start_pos.y + mouse_pos.y;
                glfwSetWindowPos(window, window_pos_x, window_pos_y);
            }
        }
        else if (ImGui::IsMouseReleased(ImGuiMouseButton_Left))
        {
            if (mouse_clicked)
            {
                mouse_dragging = false;
                mouse_clicked = false;
            }
        }
    }
    else
        mouse_clicked = false;
    printf("%d %d\n", mouse_clicked, mouse_dragging);
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !mouse_dragging)
    {
        POINT pt;
        GetCursorPos(&pt);
        if (resize_clicked == 0)
        {
            re_pos_x = pt.x;
            re_pos_y = pt.y;
            re_size_x = window_w;
            re_size_y = window_h;
            if (curx <= 5) { resize_clicked = LEFT; }
            if (curx >= window_w - 5) { resize_clicked = RIGHT; }
            if (cury <= 5) { resize_clicked = TOP; }
            if (cury >= window_h - 5) { resize_clicked = BOTTOM; }
            if (curx <= 5 && cury <= 5) { resize_clicked = LEFTTOP; }
            if (curx <= 5 && cury >= window_h - 5) { resize_clicked = LEFTBOTTOM; }
            if (curx >= window_w - 5 && cury <= 5) { resize_clicked = RIGHTTOP; }
            if (curx >= window_w - 5 && cury >= window_h - 5) { resize_clicked = RIGHTBOTTOM; }
        }
        if (resize_clicked == LEFT) {
            window_pos_x = pt.x;
            w = re_size_x - pt.x + re_pos_x;
            if (w <= content_w) { w = content_w; window_pos_x = re_pos_x + re_size_x - content_w; }
        }
        if (resize_clicked == RIGHT) {
            w = re_size_x + pt.x - re_pos_x;
        }
        if (resize_clicked == TOP) {
            window_pos_y = pt.y;
            h = re_size_y - pt.y + re_pos_y;
            if (h < content_h) { h = content_h; window_pos_y = re_pos_y + re_size_y - content_h; }
        }
        if (resize_clicked == BOTTOM) {
            h = re_size_y + pt.y - re_pos_y;
        }
        if (resize_clicked == LEFTTOP) {
            window_pos_x = pt.x;
            w = re_size_x - pt.x + re_pos_x;
            window_pos_y = pt.y;
            h = re_size_y - pt.y + re_pos_y;
            if (w < content_w) { w = content_w; window_pos_x = re_pos_x + re_size_x - content_w; }
            if (h < content_h) { h = content_h; window_pos_y = re_pos_y + re_size_y - content_h; }
        }
        if (resize_clicked == LEFTBOTTOM) {
            window_pos_x = pt.x;
            w = re_size_x - pt.x + re_pos_x;
            h = re_size_y + pt.y - re_pos_y;
            if (w < content_w) { w = content_w; window_pos_x = re_pos_x + re_size_x - content_w; }
        }
        if (resize_clicked == RIGHTTOP) {
            w = re_size_x + pt.x - re_pos_x;
            window_pos_y = pt.y;
            h = re_size_y - pt.y + re_pos_y;
            if (h < content_h) { h = content_h; window_pos_y = re_pos_y + re_size_y - content_h; }
        }
        if (resize_clicked == RIGHTBOTTOM) {
            w = re_size_x + pt.x - re_pos_x;
            h = re_size_y + pt.y - re_pos_y;
        }
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) { resize_clicked = 0; }
    
    glfwSetWindowPos(window, window_pos_x, window_pos_y);
    w = w >= content_w ? w : content_w;
    h = h >= content_h ? h : content_h;
    glfwSetWindowSize(window, w, h);
    return 0;
}

int CleanGui::end_clean_window()
{
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
    glfwPollEvents();
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    return 0;
}

int CleanGui::terminate_im_gui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    return 0;
}

int CleanGui::terminate_glfw()
{
    //DwmEnableBlurBehindWindow(hwnd, NULL);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

ImVec2 CleanGui::getWindowSize() {
    if (!isMaximized) {
        return { (float)w, (float)h };
    }
    else
        return { (float)GetSystemMetrics(SM_CXSCREEN) , (float)GetSystemMetrics(SM_CYSCREEN) };
}
void CleanGui::minimizeWindow() { glfwIconifyWindow(window); }
void CleanGui::maximizeWindow() { isMaximized = true; }
void CleanGui::restoreWindow() { isMaximized = false; }
void CleanGui::closeWindow() { isclose = true; }