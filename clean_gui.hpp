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

class CleanGui
{
private:
    HWND hwnd;
    char *title = "Boss";
    char *icon_image_path = "C:/dev/Resources/Icons/BossIcons/BossIcon-1.png";
    int glfw_pos_x_ = 0, glfw_pos_y_ = 0, w = 1100, h = 700;
    int SetWindowsTitleBar();

    int window_pos_x = 100;
    int window_pos_y = 100;
    ImVec2 mouse_start_pos = {0, 0};
    bool mouse_clicked = false;

protected:
    GLFWwindow *window;

public:
    class Event
    {
    public:
        // Define a delegate type for the button click event
        using ClickDelegate = void(*)();

        // Add a listener to the button click event
        void AddClickListener(ClickDelegate listener)
        {
            m_clickListeners.push_back(listener);
        }

        // Remove a listener from the button click event
        void RemoveClickListener(ClickDelegate listener)
        {
            auto it = std::find(m_clickListeners.begin(), m_clickListeners.end(), listener);
            if (it != m_clickListeners.end())
            {
                m_clickListeners.erase(it);
            }
        }

        // Call all listeners when the button is clicked
        void OnClick()
        {
            for (auto listener : m_clickListeners)
            {
                listener();
            }
        }

    private:
        std::vector<ClickDelegate> m_clickListeners;
    };

    int init_glfw();
    int init_im_gui();

    int start_clean_window();
    int end_clean_window();

    int terminate_im_gui();
    int terminate_glfw();

    bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height);
};
