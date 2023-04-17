    #include "Gui.hpp"
#include "CleanGui.hpp"

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
    auto io = ImGui::GetIO();
    auto Test = "C:/dev/Resources/Fonts/open-sans/OpenSans-Regular.ttf";
    font = io.Fonts->AddFontFromFileTTF(Test, 25.0f); //Adding modern font
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
    ImGui::PushFont(font);

    /*
    // Menu Bar2
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Account"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Settings"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("About"))
            {
            }

            if (ImGui::MenuItem("Check for updates"))
            {
                // code to check for updates
            }
            if (ImGui::MenuItem("Submit Feedback"))
            {
                // code to check for updates
            }
            if (ImGui::MenuItem("Support"))
            {
                // code to check for updates
            }

            ImGui::EndMenu();
        }
        //if (ImGui::MenuItem("MenuItem")) {} // You can also use MenuItem() inside a menu bar!
        ImGui::EndMenuBar();
    }

    // Add ImGui UI elemnts here--------------------
    ImGui::BeginChild("Checkbox List", ImVec2(0, ImGui::GetFrameHeightWithSpacing() * 6));
    int selected_item;
    create_dropdown_list(selected_item);
    ImGui::EndChild();
    ImGui::PopFont();
    */


    glfwPollEvents();

    end_clean_window();
}
