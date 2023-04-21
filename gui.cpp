#include "gui.hpp"
#include "clean_gui.hpp"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "design/abyssinica.h"
#include "design/icon_font.h"

ImFont* ico = nullptr;
ImFont* tab_ico = nullptr;
ImFont* tab_ico_two = nullptr;
ImFont* general_icon = nullptr;
ImFont* abys = nullptr;
ImFont* rubik = nullptr;
ImFont* rubik_input = nullptr;
ImFont* Reem_font = nullptr;
ImFont* sans = nullptr;

bool active_tab = false;

void create_dropdown_list(int &selected_item)
{
    const char *items[] = {"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10"};
    ImGui::PushItemWidth(150);
    ImGui::Combo("Default Hotkey", &selected_item, items, IM_ARRAYSIZE(items));
    ImGui::PopItemWidth();
}

void showAbout(bool &showWindow)
{
    if (showWindow)
    {
        ImGui::OpenPopup("About");
        ImGui::SetNextWindowSize(ImVec2(800, 400));
        if (ImGui::BeginPopupModal("About", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove))
        {
            ImGui::Text("Boss: Speech to Text");
            ImGui::Text("Version 2023.001.00001");
            ImGui::Text("Copyright 2023-2023 Bross LLC and its licensors. All Rights Reserved.");
            ImGui::Text(
                "Bross LLC, the Bross LLC logo, and Boss: Speech to Text are either registered trademarks or trademarks of Bross LLC in the United States and/or other countries. All other trademarks are the property of their respective owners.");
            ImGui::Text("Speech Transcription Technology by OpenAI. Copyright 2015–2023. All Rights Reserved.");
            ImGui::Text("This software uses libraries from the _____ project under the ____ -license-.");
            ImGui::Text(
                "Third Party notices, terms and conditions pertaining to third party software can be found at _____ and are incorporated by reference.");

            if (ImGui::Button("Close"))
            {
                showWindow = false;
            }
            ImGui::EndPopup();
        }
    }
}

Gui::Gui()
{
    init_glfw();
    init_im_gui();
    //auto io = ImGui::GetIO();
    //auto Test = "C:/dev/Resources/Fonts/open-sans/OpenSans-Regular.ttf";
    //font = io.Fonts->AddFontFromFileTTF(Test, 25.0f); //Adding modern font

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromMemoryTTF(&rubik_font_medium, sizeof rubik_font_medium, 23, NULL, io.Fonts->GetGlyphRangesCyrillic());

    rubik = io.Fonts->AddFontFromMemoryTTF(&rubik_font_medium, sizeof rubik_font_medium, 23, NULL, io.Fonts->GetGlyphRangesCyrillic());

    rubik_input = io.Fonts->AddFontFromMemoryTTF(&rubik_font_medium, sizeof rubik_font_medium, 20, NULL, io.Fonts->GetGlyphRangesCyrillic());

    ico = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 17, NULL, io.Fonts->GetGlyphRangesCyrillic());

    tab_ico = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 23, NULL, io.Fonts->GetGlyphRangesCyrillic());

    tab_ico_two = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 33, NULL, io.Fonts->GetGlyphRangesCyrillic());

    general_icon = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 20, NULL, io.Fonts->GetGlyphRangesCyrillic());

    Reem_font = io.Fonts->AddFontFromMemoryTTF(&Reem, sizeof Reem, 45, NULL, io.Fonts->GetGlyphRangesCyrillic());

    sans = io.Fonts->AddFontFromMemoryTTF(&open_sans, sizeof open_sans, 28, NULL, io.Fonts->GetGlyphRangesCyrillic());
}

bool Gui::isRunning() const
{
    return !glfwWindowShouldClose(window);
}

Gui::~Gui()
{
    terminate_im_gui();
    //terminate_glfw();
}

void Gui::renderFrame()
{
    start_clean_window();
    
    

    glfwPollEvents();

    end_clean_window();
}
