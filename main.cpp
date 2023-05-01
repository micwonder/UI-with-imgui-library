#include "Gui.hpp"
#include <vector>
#include <string>
#include <imgui_internal.h>

void Test_Page();
void Draw_ProgressBar(float value, ImVec2 size)
{
    ImVec2 pos = ImGui::GetCursorScreenPos();
    pos.x += 5;
    pos.y += 5;
    ImU32 col_a = ImGui::GetColorU32(IM_COL32(0x66, 0xa6, 0xff, 0xff));
    ImU32 col_b = ImGui::GetColorU32(IM_COL32(0x89, 0xf7, 0xfe, 0xff));
    int aR = 0x66, aG = 0xa6, aB = 0xff, aA = 0xff, bR = 0x89, bG = 0xf7, bB = 0xfe, bA = 0xff;
    ImU32 col_bg = ImGui::GetColorU32(IM_COL32(0x2b, 0x2d, 0x3c, 0xff));
    ImU32 color[11] = {col_a};
    
    for (int i = 1; i < 11; ++i)
    {
        int cR = aR + (int)(1.0 * (bR - aR) / 10 * i);
        int cG = aG + (int)(1.0 * (bG - aG) / 10 * i);
        int cB = aB + (int)(1.0 * (bB - aB) / 10 * i);
        int cA = aA + (int)(1.0 * (bA - aA) / 10 * i);
        color[i] = ImGui::GetColorU32(IM_COL32(cR, cG, cB, cA));
    }
    ImGui::GetWindowDrawList()->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), col_bg, 0.0f, ImDrawFlags_None);
    int count = 1;

    while (value >= 0.1)
    {
        ImGui::GetWindowDrawList()->AddRectFilledMultiColorRounded(ImVec2(pos.x + 1.0 * size.x / 10 * (count - 1), pos.y), ImVec2(pos.x + 1.0 * size.x / 10 * count, pos.y + size.y), col_bg, color[count - 1], color[count], color[count], color[count - 1], 5.0f, ImDrawFlags_RoundCornersAll);
        count++;
        value -= 0.1;
    }
    if (value > 0){ ImGui::GetWindowDrawList()->AddRectFilledMultiColorRounded(ImVec2(pos.x + 1.0 * size.x / 10 * (count - 1), pos.y), ImVec2(pos.x + 1.0 * size.x / 10 * (count - 1 + value / 0.1), pos.y + size.y), col_bg, color[count - 1], color[count], color[count], color[count - 1], 5.0f, ImDrawFlags_RoundCornersAll); }
}

void Draw_Graph(std::vector<char*> x_label, std::vector<float> y_label, ImVec2 size)
{
    ImVec2 pos = ImGui::GetWindowPos();
    ImU32 col_a = ImGui::GetColorU32(IM_COL32(0x66, 0xa6, 0xff, 0xff));
    ImU32 col_b = ImGui::GetColorU32(IM_COL32(0x89, 0xf7, 0xfe, 0xff));
    ImU32 col_bg = ImGui::GetColorU32(IM_COL32(0x21, 0x24, 0x30, 0xff));

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[10]);
    float maxVal = y_label[0];
    for (int i = 0; i < y_label.size(); ++i)
        if (maxVal < y_label[i])
            maxVal = y_label[i];
    char max_text[10];
    sprintf(max_text, "%.0f", maxVal);
    puts(max_text);

    for (int i = 0; i < 5; ++i)
    {
        char txt[10];
        sprintf(txt, "%d", (int)(maxVal - maxVal / 4 * i));
        ImGui::SetCursorScreenPos(ImVec2(pos.x + ImGui::CalcTextSize(max_text).x - ImGui::CalcTextSize(txt).x, pos.y + 1.0 * size.y / 6 * i));
        ImGui::Text(txt);
    }
    ImVec2 y_label_pos = ImVec2(pos.x + 30, pos.y + size.y / 6 * 5);
    ImGui::SetCursorScreenPos(y_label_pos);
    float gy = pos.y + size.y / 6 * 4 + ImGui::CalcTextSize(max_text).y / 2;
    float width = 20;
    float height = size.y / 6 * 4;
    ImGui::GetWindowDrawList()->AddLine({ pos.x + ImGui::CalcTextSize(max_text).x, pos.y + height + +ImGui::CalcTextSize(max_text).y / 2 }, {pos.x + size.x, pos.y + height + +ImGui::CalcTextSize(max_text).y / 2}, IM_COL32(0xff, 0xff, 0xff, 0xff));
    for (int i = 0; i < x_label.size(); ++i)
    {
        ImVec2 txtsize;
        if (i == 0)
            txtsize = ImVec2(0, 0);
        else
            txtsize = ImGui::CalcTextSize(x_label[i - 1]);
        y_label_pos = ImVec2(y_label_pos.x + txtsize.x + 5, y_label_pos.y);
        ImGui::SetCursorScreenPos(y_label_pos);
        ImGui::Text(x_label[i]);
        float gx = y_label_pos.x + ImGui::CalcTextSize(x_label[i]).x / 2;
        ImGui::GetWindowDrawList()->AddRectFilledMultiColorRounded(ImVec2(int(gx - width / 2), int(gy - height * y_label[i] / maxVal)), ImVec2(int(gx + width / 2), int(gy)), col_bg, col_a, col_a, col_b, col_b, 5.0f, ImDrawFlags_RoundCornersAll);
    }
    ImGui::PopFont();
}

void Dictation_Page(Gui& gui)
{
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(0, 0), ImVec2(75, 700), ImColor(0x21, 0x23, 0x2d, 0xff), 0.0f, ImDrawFlags_None);
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(75, 0), ImVec2(1100, 700), ImColor(0x0d, 0x12, 0x1d, 0xff), 0.0f, ImDrawFlags_None);
    
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
    ImGui::SetCursorPos(ImVec2(100, 35));
    ImGui::PopFont();
    ImGui::Text("Dictation");
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
    ImGui::SetCursorPos(ImVec2(120, 130));
    ImGui::Text("Command");
    ImGui::PopFont();

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);
    ImGui::SetWindowPos(ImVec2(120, -30));
    bool command_checked = false;
    ImGui::Checkbox("Application Control", &command_checked);
    ImGui::PopFont();

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
    ImGui::SetCursorPos(ImVec2(0, 280));
    ImGui::Text("VAD");
    ImGui::PopFont();

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);
    ImGui::SetWindowPos(ImVec2(120, -60));
    bool vad_checked = false;
    ImGui::Checkbox("Enable", &vad_checked);
    ImGui::PopFont();

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
    ImGui::SetCursorPos(ImVec2(0, 430));
    ImGui::Text("Rules");
    ImGui::PopFont();

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);
    ImGui::SetWindowPos(ImVec2(120, -90));
    bool rules_checked = false;
    ImGui::Checkbox("Enable All", &rules_checked);
    ImGui::PopFont();

    int my_image_width = 0;
    int my_image_height = 0;
    GLuint my_image_texture = 0;
    gui.LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/BossIcon-1.png", &my_image_texture, &my_image_width, &my_image_height);
    ImGui::SetCursorScreenPos(ImVec2(0, 0));
    ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(75, 75));

    gui.LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/Overview.png", &my_image_texture, &my_image_width, &my_image_height);
    ImGui::SetCursorScreenPos(ImVec2(20, 215));
    ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(35, 35));

    gui.LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/earphone.png", &my_image_texture, &my_image_width, &my_image_height);
    ImGui::SetCursorScreenPos(ImVec2(20, 260));
    ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(35, 35));
}

void Account_Page(Gui& gui)
{
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(0, 0), ImVec2(75, 700), ImColor(0x21, 0x23, 0x2d, 0xff), 0.0f, ImDrawFlags_None);
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(75, 0), ImVec2(1100, 700), ImColor(0x0d, 0x12, 0x1d, 0xff), 0.0f, ImDrawFlags_None);

    ImGui::SetCursorPos(ImVec2(100, 35));
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
    ImGui::Text("Account");
    ImGui::PopFont();

    int my_image_width = 0;
    int my_image_height = 0;
    GLuint my_image_texture = 0;
    gui.LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/BossIcon-1.png", &my_image_texture, &my_image_width, &my_image_height);
    ImGui::SetCursorScreenPos(ImVec2(0, 0));
    ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(75, 75));

    gui.LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/Overview.png", &my_image_texture, &my_image_width, &my_image_height);
    ImGui::SetCursorScreenPos(ImVec2(20, 215));
    ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(35, 35));

    gui.LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/earphone.png", &my_image_texture, &my_image_width, &my_image_height);
    ImGui::SetCursorScreenPos(ImVec2(20, 260));
    ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(35, 35));
}

void Settings_Page(Gui& gui)
{
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(0, 0), ImVec2(75, 700), ImColor(0x21, 0x23, 0x2d, 0xff), 0.0f, ImDrawFlags_None);
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(75, 0), ImVec2(1100, 700), ImColor(0x0d, 0x12, 0x1d, 0xff), 0.0f, ImDrawFlags_None);

    ImGui::SetCursorPos(ImVec2(100, 35));
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
    ImGui::Text("Settings");
    ImGui::PopFont();

    int my_image_width = 0;
    int my_image_height = 0;
    GLuint my_image_texture = 0;
    gui.LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/BossIcon-1.png", &my_image_texture, &my_image_width, &my_image_height);
    ImGui::SetCursorScreenPos(ImVec2(0, 0));
    ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(75, 75));

    gui.LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/Overview.png", &my_image_texture, &my_image_width, &my_image_height);
    ImGui::SetCursorScreenPos(ImVec2(20, 215));
    ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(35, 35));

    gui.LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/earphone.png", &my_image_texture, &my_image_width, &my_image_height);
    ImGui::SetCursorScreenPos(ImVec2(20, 260));
    ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(35, 35));
}

void Boss_Dictation_Page(Gui& gui)
{
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(0, 0), ImVec2(680, 700), ImColor(0x6d, 0x84, 0xa2, 0xff), 0.0f, ImDrawFlags_None);
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(680, 0), ImVec2(1100, 700), ImColor(0x0d, 0x12, 0x1d, 0xff), 0.0f, ImDrawFlags_None);

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[9]);
    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0x3f, 0x4b, 0x57, 0xff));
    ImGui::SetCursorScreenPos(ImVec2(140, 50));
    ImGui::Text("Boss Dictation");
    ImGui::SetCursorScreenPos(ImVec2(770, 180));
    ImGui::Text("Welcome");
    ImGui::PopStyleColor();
    ImGui::PopFont();

    ImU32 email_dark = ImColor(0x15, 0x2d, 0x49, 0xff);
    ImU32 email_light = ImColor(0x23, 0x3a, 0x57, 0xff);
    ImU32 edge_color = ImColor(0x99, 0xb3, 0xd6, 0xff);
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);
    static char email[30];
    ImGui::SetCursorPos(ImVec2(725, 305));
    ImGui::SetNextItemWidth(320);
    ImGui::InputTextWithHint("##email", "Email", email, IM_ARRAYSIZE(email));
    ImGui::GetWindowDrawList()->AddRectFilledMultiColor({ 690, 305 }, { 1045, 340 }, email_dark, email_light, email_light, email_dark);
    ImGui::GetWindowDrawList()->AddRect({ 690, 305 }, { 1045, 340 }, edge_color, 2.0f, 0, 2.0f);
    ImGui::SetCursorPos({ 733, 313 });
    if (email[0] == NULL) {ImGui::Text("Email"); }
    else { ImGui::Text(email); }

    static char password[30];
    ImGui::SetCursorPos(ImVec2(725, 380));
    ImGui::SetNextItemWidth(320);
    ImGui::InputTextWithHint("##password", "********", password, IM_ARRAYSIZE(password));
    ImGui::GetWindowDrawList()->AddRectFilledMultiColor({ 690, 380 }, { 1045, 415 }, email_dark, email_light, email_light, email_dark);
    ImGui::GetWindowDrawList()->AddRect({ 690, 380 }, { 1045, 415 }, edge_color, 2.0f, 0, 2.0f);
    ImGui::SetCursorPos({ 733, 388 });
    if (password[0] == NULL) { ImGui::Text("********"); }
    else { ImGui::Text(password); }
    bool remeber_me_checked = true;
    ImGui::SetWindowPos(ImVec2(680, 0));
    ImGui::Checkbox("Remember me", &remeber_me_checked);
    ImGui::SetWindowPos(ImVec2(870, 460));
    ImGui::TextButton("##Register", "Register");
    ImGui::SetWindowPos(ImVec2(950, 460));
    ImGui::TextButton("##Forgot_Password", "Forgot Password?");

    ImGui::SetCursorPos(ImVec2(-190, 100));
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0x6f, 0x87, 0xa3, 0xff));
    ImGui::Button("Login", ImVec2(260, 50));
    ImGui::PopStyleColor();
    ImGui::PopFont();
}

void Overview_Page(Gui& gui)
{
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(0, 0), ImVec2(75, 700), ImColor(0x21, 0x23, 0x2d, 0xff), 0.0f, ImDrawFlags_None);
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(75, 0), ImVec2(1100, 700), ImColor(0x0d, 0x12, 0x1d, 0xff), 0.0f, ImDrawFlags_None);

    ImGui::SetCursorPos(ImVec2(100, 35));
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
    ImGui::Text("Overview");
    ImGui::PopFont();

    std::vector<std::string> items = { "Per day", "Per week", "Per month", "Per year" };
    std::vector<int> value = { 165, 1155, 4620, 4000 };
    int current_selection = 0;

    int my_image_width = 0;
    int my_image_height = 0;
    GLuint my_image_texture = 0;
    gui.LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/BossIcon-1.png", &my_image_texture, &my_image_width, &my_image_height);
    ImGui::SetCursorScreenPos(ImVec2(0, 0));
    ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(75, 75));

    gui.LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/Overview.png", &my_image_texture, &my_image_width, &my_image_height);
    ImGui::SetCursorScreenPos(ImVec2(20, 215));
    ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(35, 35));

    gui.LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/earphone.png", &my_image_texture, &my_image_width, &my_image_height);
    ImGui::SetCursorScreenPos(ImVec2(20, 260));
    ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(35, 35));

    ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0x21, 0x24, 0x30, 0xff));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10.0f);
    
    // WPM child
    ImGui::GetWindowDrawList()->AddRect({ 95, 110 }, { 315, 205 }, IM_COL32(0x00, 0x00, 0x00, 0xff), 2.0f, 0, 2.0f);
    ImGui::BeginChild("WPM", ImVec2(220, 95), ImVec2(95, 110));
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
    ImGui::SetCursorPos(ImVec2(80, 10));
    ImGui::Text("WPM");
    ImGui::PopFont();
    ImGui::SetCursorPos(ImVec2(75, 40));
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
    ImGui::Text("185");
    ImGui::PopFont(); 
    ImGui::EndChild();

    // WPM Average child
    char* wpm_items[] = { "Per Day", "Per Week", "Per Month", "Per Year" };
    int wpm_values[] = { 165, 1150, 4000, 10000 };
    static int current_value = wpm_values[0];
    static char* current_wpm = wpm_items[0];
    static bool wpm_button_selected = false;

    ImGui::GetWindowDrawList()->AddRect({ 330, 110 }, { 550, 205 }, IM_COL32(0x00, 0x00, 0x00, 0xff), 2.0f, 0, 2.0f);
    ImGui::BeginChild("WPM Average", ImVec2(220, 95), ImVec2(330, 110));
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
    ImGui::SetCursorPos(ImVec2(50, 10));
    ImGui::Text("WPM Average");
    ImGui::PopFont();

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
    char txt[100];
    sprintf(txt, "%d", current_value);
    ImGui::SetCursorPos(ImVec2(110 - ImGui::CalcTextSize(txt).x / 2, 40));
    ImGui::Text(txt);
    ImGui::PopFont();

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[10]);
    ImGui::SetWindowPos({ 470, 180 });
    if (ImGui::TextButton("##button_wpm", current_wpm))
    {
        wpm_button_selected = !wpm_button_selected;
    }
    if (wpm_button_selected)
    {
        ImGui::SetNextWindowSize(ImVec2(70, 100));
        ImGui::SetNextWindowPos({ 470, 200 });
        ImGui::OpenPopup("WPM");
        if (ImGui::BeginPopup("WPM", ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove))
        {
            for (int n = 0; n < IM_ARRAYSIZE(wpm_items); n++)
            {
                bool is_selected = (current_wpm == wpm_items[n]); // You can store your selection however you want, outside or inside your objects
                if (ImGui::Selectable(wpm_items[n], is_selected))
                {
                    current_wpm = wpm_items[n];
                    current_value = wpm_values[n];
                    wpm_button_selected = false;
                }
                if (is_selected)
                    ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
            }
            ImGui::EndPopup();
        }
    }
    ImGui::PopFont();
    ImGui::EndChild();
    
    // Dictation Histroy child
    ImGui::GetWindowDrawList()->AddRect({ 94, 214 }, { 776, 516 }, IM_COL32(0x00, 0x00, 0x00, 0xff), 2.0f, 0, 4.0f);
    ImGui::BeginChild("Dictation History", ImVec2(680, 300), ImVec2(95, 215));
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
    ImGui::Text("Dictation History");
    ImGui::PopFont();
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);
    ImGui::Text("Boss: Speech to Text\nVersion 2023.001.00001\nCopyright 2023-2023 Bross LLC and its licensors. All Rights Reserved.\nBross LLC, the Bross LLC logo, and Boss: Speech to Text are either registered trademarks or trademarks of Bross LLC in the United States and/or other countries. All other trademarks are the property of their respective owners.\nSpeech Transcription Technology by OpenAI. Copyright 2015–2023. All Rights Reserved.\nThis software uses libraries from the _____ project under the ____ -license-.\nThird Party notices, terms and conditions pertaining to third party software can be found at _____ and are incorporated by reference.");
    ImGui::PopFont();
    ImGui::EndChild();

    // What's new child
    ImGui::GetWindowDrawList()->AddRect({ 829, 199 }, { 1071, 521 }, IM_COL32(0x00, 0x00, 0x00, 0xff), 2.0f, 0, 4.0f);
    ImGui::BeginChild("What's New", ImVec2(240, 320), ImVec2(830, 200));
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
    ImGui::Text("What's New");
    ImGui::PopFont();
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);

    ImGui::Text("Version 1.0.0\nDummy Text");
    ImGui::PopFont();
    ImGui::EndChild();

    // Language Spoken child
    ImGui::GetWindowDrawList()->AddRect({ 94, 534 }, { 576, 676 }, IM_COL32(0x00, 0x00, 0x00, 0xff), 2.0f, 0, 4.0f);
    ImGui::BeginChild("Languages Spoken", ImVec2(480, 140), ImVec2(95, 535));
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);
    ImGui::Text("Languages Spoken");

    ImGui::Text("English");
    ImGui::SameLine(0, 0);
    Draw_ProgressBar(0.78, ImVec2(360, 7));
    ImGui::SameLine(0, 370);
    ImGui::Text("78%%");

    ImGui::Text("Spanish");
    ImGui::SameLine(0, 0);
    Draw_ProgressBar(0.08, ImVec2(360, 7));
    ImGui::SameLine(0, 370);
    ImGui::Text("8%%");

    ImGui::Text("Russian");
    ImGui::SameLine(0, 0);
    Draw_ProgressBar(0.07, ImVec2(360, 7));
    ImGui::SameLine(0, 370);
    ImGui::Text("7%%");

    ImGui::Text("French");
    ImGui::SameLine(0, 0);
    Draw_ProgressBar(0.07, ImVec2(360, 7));
    ImGui::SameLine(0, 370);
    ImGui::Text("7%%");

    ImGui::PopFont();
    ImGui::EndChild();

    // Usage Time child
    std::vector<char*> week_x_label = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    std::vector<float> week_y_label = {480, 1440, 1200, 960, 720, 180, 540, 60};

    std::vector<char*> month_x_label = { "1-7", "8-14", "15-21", "22-28", "29-last"};
    std::vector<float> month_y_label = { 1200, 960, 720, 180, 1800 };

    std::vector<char*> year_x_label = { "1-3", "4-6", "7-9", "10-12"};
    std::vector<float> year_y_label = { 480, 1200, 720, 540 };
    static int time_flag = 0;
    ImGui::GetWindowDrawList()->AddRect({ 594, 534 }, { 1076, 676 }, IM_COL32(0x00, 0x00, 0x00, 0xff), 2.0f, 0, 4.0f);
    ImGui::BeginChild("Usage Time", ImVec2(480, 140), ImVec2(595, 535));
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);
    ImGui::SetWindowPos(ImVec2(625, 545));
    ImGui::Text("Usage Time (minutes)");
    ImGui::PopFont();
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[10]);
    ImGui::SetWindowPos(ImVec2(940, 545));
    if (ImGui::TextButton("##Week", "Week")) { time_flag = 0; }
    ImGui::SetWindowPos(ImVec2(980, 545));
    if (ImGui::TextButton("##Month", "Month")) { time_flag = 1; }
    ImGui::SetWindowPos(ImVec2(1025, 545));
    if (ImGui::TextButton("##Year", "Year")) { time_flag = 2; }
    ImGui::SetWindowPos(ImVec2(610, 570));
    if(time_flag == 0)
        Draw_Graph(week_x_label, week_y_label, ImVec2(460, 90));
    else if (time_flag == 1)
        Draw_Graph(month_x_label, month_y_label, ImVec2(460, 90));
    else
        Draw_Graph(year_x_label, year_y_label, ImVec2(460, 90));
    ImGui::PopFont();
    ImGui::EndChild();
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();

    // Audio File
    ImGui::GetWindowDrawList()->AddRect(ImVec2(825, 95), ImVec2(1075, 185), ImColor(0x1c, 0x24, 0x31, 0xff), 0, 0, 2.0f);
    gui.LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/audio.png", &my_image_texture, &my_image_width, &my_image_height);
    ImGui::SetCursorScreenPos(ImVec2(827, 97));
    ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(my_image_width, my_image_height));

    // Notification Icon
    gui.LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/notification.png", &my_image_texture, &my_image_width, &my_image_height);
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0x21, 0x24, 0x30, 0xff));
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[10]);
    char* news_items[] = { "Default notification", "Other notification" };
    static char* current_news = news_items[0];
    static bool news_button_selected = false;
    ImGui::SetCursorPos({ 995, 35 });
    if (ImGui::ImageButton("##button_news", (void*)(intptr_t)my_image_texture, ImVec2(30, 30)))
    {
        news_button_selected = !news_button_selected;
    }
    if (news_button_selected)
    {
        ImGui::SetNextWindowSize(ImVec2(170, 100));
        ImGui::SetNextWindowPos({ 855, 65 });
        ImGui::OpenPopup("News");
        if (ImGui::BeginPopup("News", ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove))
        {
            for (int n = 0; n < IM_ARRAYSIZE(news_items); n++)
            {
                bool is_selected = (current_news == news_items[n]); // You can store your selection however you want, outside or inside your objects
                if (ImGui::Selectable(news_items[n], is_selected))
                {
                    current_news = news_items[n];
                    news_button_selected = false;
                }
                if (is_selected)
                    ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
            }
            ImGui::EndPopup();
        }
    }
    ImGui::PopFont();
    ImGui::PopStyleColor();
    static bool checked_notification = true;
    if (checked_notification) { ImGui::GetWindowDrawList()->AddCircleFilled(ImVec2(1020, 46), 4.0f, ImColor(0x06, 0xe9, 0xfa, 0xff)); }

    // User Button
    gui.LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/user.png", &my_image_texture, &my_image_width, &my_image_height);
    ImGui::SetCursorScreenPos(ImVec2(1035, 35));
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0x21, 0x24, 0x30, 0xff));
    ImGui::ImageButton((void*)(intptr_t)my_image_texture, ImVec2(30, 30));
    ImGui::PopStyleColor();

    //Input device
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[10]);
    ImGui::GetWindowDrawList()->AddRectFilled({ 800, 30 }, { 980, 70 }, IM_COL32(0x21, 0x24, 0x30, 0xff));
    ImGui::GetWindowDrawList()->AddRectFilled({ 805, 45 }, { 975, 65 }, IM_COL32(0x0d, 0x12, 0x1d, 0xff));
    ImGui::SetCursorScreenPos({ 805, 30 });
    ImGui::Text("INPUT DEVICE");
    char* device_items[] = { "Default", "Other" };
    static char* current_device = device_items[0];
    static bool device_button_selected = false;
    ImGui::SetWindowPos({ 805, 45 });
    if (ImGui::TextButton("##button_device", current_device))
    {
        device_button_selected = !device_button_selected;
    }
    if (device_button_selected)
    {
        ImGui::SetNextWindowSize(ImVec2(70, 100));
        ImGui::SetNextWindowPos({ 805, 65 });
        ImGui::OpenPopup("Input");
        if (ImGui::BeginPopup("Input", ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove))
        {
            for (int n = 0; n < IM_ARRAYSIZE(device_items); n++)
            {
                bool is_selected = (current_device == device_items[n]); // You can store your selection however you want, outside or inside your objects
                if (ImGui::Selectable(device_items[n], is_selected))
                {
                    current_device = device_items[n];
                    device_button_selected = false;
                }
                if (is_selected)
                    ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
            }
            ImGui::EndPopup();
        }
    }
    ImGui::PopFont();

}


int main()
{
    auto gui = Gui();
    while (gui.isRunning())
    {
        gui.start_clean_window();
        Overview_Page(gui);
        // you should try these functions
        //Boss_Dictation_Page(gui);
        //Dictation_Page(gui);
        //Account_Page(gui);
        //Settings_Page(gui);
        gui.end_clean_window();
    }
}
