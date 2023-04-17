#include "CleanGui.hpp"

#include <iostream>
#include <GLFW/glfw3native.h>
#include <dwmapi.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


int CleanGui::init_glfw()
{
    glfwInit();
    //glewInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, 1);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    window = glfwCreateWindow(w, h, title, nullptr, nullptr);
    hwnd = glfwGetWin32Window(window);
    glfwMakeContextCurrent(window);
    glViewport(0, 0, w, h);
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
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    auto io = ImGui::GetIO();
    io.IniFilename = nullptr;
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
    ImGui::SetNextWindowSize(ImVec2(static_cast<float>(window_w) + 3, static_cast<float>(window_h) + 2));
    ImGui::SetNextWindowPos(ImVec2(-1, -1));

    //MainSpace
    ImGui::SetNextWindowPos({0, 0});
    ImGui::SetNextWindowSizeConstraints(ImVec2(0 * 10 + 142, 50), ImVec2(FLT_MAX, FLT_MAX));
    ImGui::Begin(title, nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar |
                 ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_MenuBar);
    ImGui::SetWindowSize(ImVec2(w, h));
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
