#include "imgui.h"
#include "clean_gui.hpp"

#include <iostream>
#include <GLFW/glfw3native.h>
#include <dwmapi.h>
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "stb_image.h"

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
    ImGui::SetNextWindowPos({0, 0});
    ImGui::SetNextWindowSizeConstraints(ImVec2(1100, 700), ImVec2(FLT_MAX, FLT_MAX));

    bool select = true;

    ImGui::Begin(title, &select,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar |
                 ImGuiWindowFlags_NoBringToFrontOnFocus);
    if (ImGui::IsWindowHovered())
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
                window_pos_x = init_x - mouse_start_pos.x + mouse_pos.x;
                window_pos_y = init_y - mouse_start_pos.y + mouse_pos.y;
                glfwSetWindowPos(window, window_pos_x, window_pos_y);
            }
        }
        else if (ImGui::IsMouseReleased(ImGuiMouseButton_Left))
        {
            if (mouse_clicked)
                mouse_clicked = false;
        }
    }
    else
        mouse_clicked = false;
    w = (int)ImGui::GetWindowSize().x >= 1100 ? (int)ImGui::GetWindowSize().x : 1100;
    h = (int)ImGui::GetWindowSize().y >= 700 ? (int)ImGui::GetWindowSize().y : 700;
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

ImVec2 CleanGui::getWindowSize() { return { (float)w, (float)h }; }
void CleanGui::minimizeWindow() { glfwIconifyWindow(window); }
void CleanGui::maximizeWindow() { glfwMaximizeWindow(window); }
void CleanGui::restoreWindow() { glfwRestoreWindow(window); }
void CleanGui::closeWindow() { isclose = true; }