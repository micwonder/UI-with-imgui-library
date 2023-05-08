#include "gui.hpp"
#include "clean_gui.hpp"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "design/abyssinica.h"
#include "design/icon_font.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

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
    io.Fonts->AddFontFromMemoryTTF(&rubik_font_medium, sizeof rubik_font_medium, 40, NULL, io.Fonts->GetGlyphRangesCyrillic());

    rubik = io.Fonts->AddFontFromMemoryTTF(&rubik_font_medium, sizeof rubik_font_medium, 23, NULL, io.Fonts->GetGlyphRangesCyrillic());

    rubik_input = io.Fonts->AddFontFromMemoryTTF(&rubik_font_medium, sizeof rubik_font_medium, 20, NULL, io.Fonts->GetGlyphRangesCyrillic());

    ico = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 17, NULL, io.Fonts->GetGlyphRangesCyrillic());

    tab_ico = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 23, NULL, io.Fonts->GetGlyphRangesCyrillic());

    tab_ico_two = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 33, NULL, io.Fonts->GetGlyphRangesCyrillic());

    general_icon = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 20, NULL, io.Fonts->GetGlyphRangesCyrillic());

    Reem_font = io.Fonts->AddFontFromMemoryTTF(&Reem, sizeof Reem, 45, NULL, io.Fonts->GetGlyphRangesCyrillic());

    sans = io.Fonts->AddFontFromMemoryTTF(&open_sans, sizeof open_sans, 28, NULL, io.Fonts->GetGlyphRangesCyrillic());

    io.Fonts->AddFontFromMemoryTTF(&rubik_font_medium, sizeof rubik_font_medium, 55, NULL, io.Fonts->GetGlyphRangesCyrillic());

    io.Fonts->AddFontFromMemoryTTF(&rubik_font_medium, sizeof rubik_font_medium, 13, NULL, io.Fonts->GetGlyphRangesCyrillic());

    current_page = PAGE_LOGIN;

    loadImage();
    ImVec2 size = getWindowSize();
    input_email = InputTexts("##email", { size.x / 5 * 3, size.y / 5 * 2 }, { size.x / 5 * 2, size.y / 10 }, COLOR_INPUT_DARK, COLOR_INPUT_LIGHT, COLOR_INPUT_LIGHT, INPUT_TYPE_EMAIL, my_image_texture[10], my_image_texture[11], my_image_texture[12], my_image_texture[13]);
    input_password = InputTexts("##password", { size.x / 5 * 3, size.y / 2 }, { size.x / 5 * 2, size.y / 10 }, COLOR_INPUT_DARK, COLOR_INPUT_LIGHT, COLOR_INPUT_LIGHT, INPUT_TYPE_PASSWORD, my_image_texture[10], my_image_texture[11], my_image_texture[12], my_image_texture[13]);
}

Gui::~Gui()
{
    deleteImage();
    terminate_im_gui();
    terminate_glfw();
}

void Gui::loadImage()
{
    int my_image_width = 0;
    int my_image_height = 0;
    LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/minimize.png", &my_image_texture[0], &my_image_width, &my_image_height);
    LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/maximize.png", &my_image_texture[1], &my_image_width, &my_image_height);
    LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/restore.png", &my_image_texture[2], &my_image_width, &my_image_height);
    LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/close.png", &my_image_texture[3], &my_image_width, &my_image_height);
    LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/BossIcon-1.png", &my_image_texture[4], &my_image_width, &my_image_height);
    LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/Overview.png", &my_image_texture[5], &my_image_width, &my_image_height);
    LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/earphone.png", &my_image_texture[6], &my_image_width, &my_image_height);
    LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/setting.png", &my_image_texture[7], &my_image_width, &my_image_height);
    LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/audio.png", &my_image_texture[8], &my_image_width, &my_image_height);
    LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/notification.png", &my_image_texture[9], &my_image_width, &my_image_height);
    LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/user.png", &my_image_texture[10], &my_image_width, &my_image_height);
    LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/password.png", &my_image_texture[11], &my_image_width, &my_image_height);
    LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/eye_on.png", &my_image_texture[12], &my_image_width, &my_image_height);
    LoadTextureFromFile("C:/dev/Resources/Icons/BossIcons/eye_off.png", &my_image_texture[13], &my_image_width, &my_image_height);
}
void Gui::deleteImage()
{
    glDeleteTextures(14, my_image_texture);
}
bool Gui::isRunning() const
{
    if (!isclose)
        return !glfwWindowShouldClose(window);
    else
        return glfwWindowShouldClose(window);
}


void Gui::createProgressBar(float value, ImVec2 size) //create progress bar
{
    ImVec2 pos = ImGui::GetCursorScreenPos();
    pos.x += 5;
    pos.y += 5;
    ImU32 col_a = ImGui::GetColorU32(IM_COL32(0x66, 0xa6, 0xff, 0xff));
    ImU32 col_b = ImGui::GetColorU32(IM_COL32(0x89, 0xf7, 0xfe, 0xff));
    int aR = 0x66, aG = 0xa6, aB = 0xff, aA = 0xff, bR = 0x89, bG = 0xf7, bB = 0xfe, bA = 0xff;
    ImU32 col_bg = ImGui::GetColorU32(IM_COL32(0x2b, 0x2d, 0x3c, 0xff));
    ImU32 color[11] = { col_a };
    for (int i = 1; i < 11; ++i){
        int cR = aR + (int)(1.0 * (bR - aR) / 10 * i);
        int cG = aG + (int)(1.0 * (bG - aG) / 10 * i);
        int cB = aB + (int)(1.0 * (bB - aB) / 10 * i);
        int cA = aA + (int)(1.0 * (bA - aA) / 10 * i);
        color[i] = ImGui::GetColorU32(IM_COL32(cR, cG, cB, cA));
    }
    ImGui::GetWindowDrawList()->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), col_bg, 0.0f, ImDrawFlags_None);
    int count = 1;
    while (value >= 0.1){
        ImGui::GetWindowDrawList()->AddRectFilledMultiColorRounded(ImVec2(pos.x + 1.0 * size.x / 10 * (count - 1), pos.y), ImVec2(pos.x + 1.0 * size.x / 10 * count, pos.y + size.y), col_bg, color[count - 1], color[count], color[count], color[count - 1], 5.0f, ImDrawFlags_RoundCornersAll);
        count++;
        value -= 0.1;
    }
    if (value > 0) { ImGui::GetWindowDrawList()->AddRectFilledMultiColorRounded(ImVec2(pos.x + 1.0 * size.x / 10 * (count - 1), pos.y), ImVec2(pos.x + 1.0 * size.x / 10 * (count - 1 + value / 0.1), pos.y + size.y), col_bg, color[count - 1], color[count], color[count], color[count - 1], 5.0f, ImDrawFlags_RoundCornersAll); }
}

void Gui::dividePane(float div_pos, ImU32 left_color, ImU32 right_color) // devide panel to left and right
{
    ImVec2 size = getWindowSize();
    ImGui::GetWindowDrawList()->AddRectFilled({ 0, 0 }, { div_pos, size.y }, left_color, 0.0f, ImDrawFlags_None);
    ImGui::GetWindowDrawList()->AddRectFilled({ div_pos, 0 }, size, right_color, 0.0f, ImDrawFlags_None);
}
void Gui::createText(ImVec2 pos, ImVec2 size, char* text, ImFont* font, ImU32 color) //create Text in specified font and color
{
    ImGui::PushFont(font);
    ImGui::PushStyleColor(ImGuiCol_Text, color);
    if(size.x == 0 && size.y == 0)
        ImGui::SetCursorPos(pos);
    else
    {
        ImVec2 textsize = ImGui::CalcTextSize(text);
        ImGui::SetCursorPos({ pos.x + (size.x - textsize.x) / 2, pos.y + (size.y - textsize.y) / 2 });
    }
    ImGui::Text(text);
    ImGui::PopStyleColor();
    ImGui::PopFont();
}
void Gui::createTitleBar(ImU32 color) // create minimize, maximize, close button
{
    ImVec2 size = getWindowSize();
    ImVec2 padding = ImGui::GetStyle().FramePadding;
    ImVec2 buttonsize = {30 - padding.x * 2, 30 - padding.x * 2};
    ImGui::PushStyleColor(ImGuiCol_Button, color);
    ImGui::SetCursorScreenPos({size.x - 90, 0});
    if (ImGui::ImageButton("##buttonminimize", (void*)(intptr_t)my_image_texture[0], buttonsize)) { minimizeWindow(); }
    ImGui::SetCursorScreenPos({ size.x - 60, 0 });
    if (!isMaximized){
        if (ImGui::ImageButton("##buttonmaximize", (void*)(intptr_t)my_image_texture[1], buttonsize)) {
            maximizeWindow();
            isMaximized = true;
        }
    }
    else{
        if (ImGui::ImageButton("##buttonrestore", (void*)(intptr_t)my_image_texture[2], buttonsize)) {
            restoreWindow();
            isMaximized = false;
        }
    }
    ImGui::SetCursorScreenPos({ size.x - 30, 0 });
    if (ImGui::ImageButton("##buttonclose", (void*)(intptr_t)my_image_texture[3], buttonsize)) { closeWindow(); }
    ImGui::PopStyleColor();
}

void Gui::createTabIcon() // create account, overview, earphone, setting tab
{
    ImVec2 size = getWindowSize();
    ImVec2 padding = ImGui::GetStyle().FramePadding;
    ImVec2 buttonsize = { 75 - padding.x * 2, 75 - padding.x * 2 };
    ImGui::PushStyleColor(ImGuiCol_Button, COLOR_GUI_LEFT);

    ImGui::SetCursorScreenPos(ImVec2(0, 0));
    if (ImGui::ImageButton("##button_account", (void*)(intptr_t)my_image_texture[4], buttonsize)) { current_page = PAGE_ACCOUNT; }

    ImGui::SetCursorScreenPos(ImVec2(0, size.y / 7 * 2));
    if (ImGui::ImageButton("##button_overview", (void*)(intptr_t)my_image_texture[5], buttonsize)) { current_page = PAGE_OVERVIEW; }

    ImGui::SetCursorScreenPos(ImVec2(0, size.y / 7 * 3));
    if (ImGui::ImageButton("##button_dictation", (void*)(intptr_t)my_image_texture[6], buttonsize)) { current_page = PAGE_DICTATION; }

    ImGui::SetCursorScreenPos(ImVec2(0, size.y / 7 * 5));
    if (ImGui::ImageButton("##button_setting", (void*)(intptr_t)my_image_texture[7], buttonsize)) { current_page = PAGE_SETTING; }

    ImGui::PopStyleColor();
}


float Gui::createCheckBox(ImVec2 pos, char* title, char* check_label, bool* check_flag) // create a checkbox with title
{
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
    ImGui::SetCursorScreenPos(pos);
    ImGui::Text(title);
    ImGui::PopFont();

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);
    ImGui::SetWindowPos({pos.x, 0});
    ImGui::Checkbox(check_label, check_flag);
    ImGui::PopFont();

    return ImGui::GetCursorPos().y;
}

/*void Gui::createInputText(ImVec2 pos, ImVec2 size, int flag)
{
    float padding_x = 20;
    float padding_y = (ImGui::GetFontSize() - ImGui::GetStyle().FramePadding.y) * 2;
    float width = (size.x - padding_x * 2);
    float thick = 2.0f;
    ImVec2 start_pos = { pos.x + padding_x, pos.y + (size.y - padding_y) / 2};

    ImGui::SetCursorPos({ start_pos.x + padding_y, start_pos.y });
    ImGui::SetNextItemWidth(width - padding_y);
    if (flag == INPUT_TYPE_EMAIL)
        ImGui::InputTextWithHint("##email", "Email", email, IM_ARRAYSIZE(email));
    else
        ImGui::InputTextWithHint("##password", "********", password, IM_ARRAYSIZE(password));
    ImGui::GetWindowDrawList()->AddRectFilledMultiColor(start_pos, { start_pos.x + width, start_pos.y + padding_y }, COLOR_INPUT_DARK, COLOR_INPUT_LIGHT, COLOR_INPUT_LIGHT, COLOR_INPUT_DARK);
    ImGui::GetWindowDrawList()->AddRect({ start_pos.x - thick, start_pos.y - thick }, { start_pos.x + width + thick, start_pos.y + padding_y + thick }, COLOR_INPUT_EDGE, 2.0f, 0, thick);
    ImGui::SetCursorPos({ start_pos.x + padding_y + 8, start_pos.y + 8 });
    if (flag == INPUT_TYPE_EMAIL) {
        if (email[0] == NULL) { ImGui::Text("Email"); }
        else { ImGui::Text(email); }
    }
    else {
        if (password[0] == NULL) { ImGui::Text("********"); }
        else { ImGui::Text(password); }
    }
}*/

void Gui::clearPopup()
{
    wpm_button_clicked = false;
    device_button_clicked = false;
    news_button_clicked = false;
}

void Gui::renderFrame()
{
    start_clean_window();
    switch (current_page)
    {
        case PAGE_LOGIN:
            bossDictationPage();
            break;
        case PAGE_OVERVIEW:
            overviewPage();
            break;
        case PAGE_ACCOUNT:
            accountPage();
            break;
        case PAGE_SETTING:
            settingPage();
            break;
        case PAGE_DICTATION:
            dictationPage();
            break;
        default:
            break;
    }
    end_clean_window();
}

void Gui::accountPage()
{
    dividePane(75, COLOR_GUI_LEFT, COLOR_GUI_RIGHT);
    createTitleBar(COLOR_GUI_RIGHT);
    createTabIcon();
    createText({ 100, 35 }, { 0, 0 }, "Account", ImGui::GetIO().Fonts->Fonts[0], COLOR_WHITE);
}

void Gui::settingPage()
{
    dividePane(75, COLOR_GUI_LEFT, COLOR_GUI_RIGHT);
    createTitleBar(COLOR_GUI_RIGHT);
    createTabIcon();
    createText({ 100, 35 }, { 0, 0 }, "Settings", ImGui::GetIO().Fonts->Fonts[0], COLOR_WHITE);
}

void Gui::dictationPage()
{
    dividePane(75, COLOR_GUI_LEFT, COLOR_GUI_RIGHT);
    createTitleBar(COLOR_GUI_RIGHT);
    createTabIcon();
    createText({ 100, 35 }, { 0, 0 }, "Dictation", ImGui::GetIO().Fonts->Fonts[0], COLOR_WHITE);

    float pos_y = 130;
    pos_y = createCheckBox({ 120, pos_y }, "Command", "Application Control", &checked_command);
    pos_y = createCheckBox({ 120, pos_y }, "VAD", "Enable", &checked_vad);
    pos_y = createCheckBox({ 120, pos_y }, "Rules", "Enable All", &checked_rules);
}

void Gui::bossDictationPage()
{
    ImVec2 size = getWindowSize();
    dividePane(size.x / 5 * 3, COLOR_GUI_LOGIN_LEFT, COLOR_GUI_LOGIN_RIGHT);
    createTitleBar(COLOR_GUI_LOGIN_RIGHT);
    createText({ 0, 0 }, { size.x / 5 * 3, size.y / 5 }, "Boss Dictation", ImGui::GetIO().Fonts->Fonts[9], COLOR_TITLE);
    createText({ size.x / 5 * 3, size.y / 5 }, { size.x / 5 * 2, size.y / 5 }, "Welcome", ImGui::GetIO().Fonts->Fonts[9], COLOR_TITLE);

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);
    input_email.render({ size.x / 5 * 3, size.y / 5 * 2 }, { size.x / 5 * 2, size.y / 10 });
    input_password.render({ size.x / 5 * 3, size.y / 2 }, { size.x / 5 * 2, size.y / 10 });

    ImGui::SetWindowPos({ size.x / 5 * 3, 0 });
    ImGui::Checkbox("Remember me", &checked_remeber_me);
    ImGui::SetWindowPos({ size.x / 5 * 4 - 20, size.y / 5 * 3 + 30 });
    ImGui::TextButton("##Register", "Register");
    ImGui::SetWindowPos({ size.x / 10 * 9 - 40, size.y / 5 * 3 + 30 });
    ImGui::TextButton("##Forgot_Password", "Forgot Password?");
    
    ImVec2 buttonsize = { 260, 50 };
    ImGui::SetCursorScreenPos({ size.x / 5 * 3 + (size.x / 5 * 2 - buttonsize.x) / 2, size.y / 5 * 4 + (size.y / 5 - buttonsize.y) / 2 });
    ImGui::PushStyleColor(ImGuiCol_Button, COLOR_BUTTON_LOGIN);
    if (ImGui::Button("Login", buttonsize))
        current_page = PAGE_ACCOUNT;
    ImGui::PopStyleColor();
    ImGui::PopFont();
}

void Gui::overviewPage()
{
    ImVec2 windowsize = getWindowSize();
    ImVec2 viewport = { windowsize.x / 1100, windowsize.y / 700 };
    ImVec2 tilepos, tilesize;

    if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left)){clearPopup();}

    dividePane(75, COLOR_GUI_LEFT, COLOR_GUI_RIGHT);
    createTitleBar(COLOR_GUI_RIGHT);
    createTabIcon();
    createText({ 100, 35 }, { 0, 0 }, "Overview", ImGui::GetIO().Fonts->Fonts[0], COLOR_WHITE);

    Tiles tiles;
    ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0x21, 0x24, 0x30, 0xff));

    // WPM tile
    tilepos = ImVec2(95, 110) * viewport;
    tilesize = ImVec2(220, 95) * viewport;

    tiles.addTile("WPM", tilepos, tilesize, COLOR_BLACK);
    createText({0, 0}, ImVec2(tilesize.x, tilesize.y / 2), "WPM", ImGui::GetIO().Fonts->Fonts[1], COLOR_WHITE);
    createText(ImVec2(0, tilesize.y / 2), ImVec2(tilesize.x, tilesize.y / 2), "185", ImGui::GetIO().Fonts->Fonts[0], COLOR_WHITE);
    tiles.endTile();

    // Dictation Histroy child
    tilepos = ImVec2(95, 215) * viewport;
    tilesize = ImVec2(680, 300) * viewport;
    tiles.addTile("Dictation History", tilepos, tilesize, COLOR_BLACK);
    createText({ 0, 0 }, { 0, 0 }, "WPM Average", ImGui::GetIO().Fonts->Fonts[1], COLOR_WHITE);
    char history[] = "Boss: Speech to Text\nVersion 2023.001.00001\nCopyright 2023-2023 Bross LLC and its licensors. All Rights Reserved.\nBross LLC, the Bross LLC logo, and Boss: Speech to Text are either registered trademarks or trademarks of Bross LLC in the United States and/or other countries. All other trademarks are the property of their respective owners.\nSpeech Transcription Technology by OpenAI. Copyright 2015–2023. All Rights Reserved.\nThis software uses libraries from the _____ project under the ____ -license-.\nThird Party notices, terms and conditions pertaining to third party software can be found at _____ and are incorporated by reference.";
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);
    ImGui::PushTextWrapPos(tilesize.x);
    ImGui::TextWrapped(history);
    ImGui::PopTextWrapPos();
    ImGui::PopFont();
    tiles.endTile();

    // WPM Average child
    std::vector<std::string> wpm_items = { "Per day", "Per week", "Per month", "Per year" };
    std::vector<std::string> wpm_values = { "165", "1200", "4300", "10000" };
    static std::string current_wpm = wpm_items[0];
    static std::string current_wpm_value = wpm_values[0];
    tilepos = ImVec2(330, 110) * viewport;
    tilesize = ImVec2(220, 95) * viewport;
    tiles.addTile("WPM Average", tilepos, tilesize, COLOR_BLACK);
    createText({ 0, 0 }, ImVec2(tilesize.x, tilesize.y / 2), "WPM Average", ImGui::GetIO().Fonts->Fonts[1], COLOR_WHITE);
    createText(ImVec2(0, tilesize.y / 2), ImVec2(tilesize.x, tilesize.y / 2), current_wpm_value.data(), ImGui::GetIO().Fonts->Fonts[0], COLOR_WHITE);
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[10]);
    ImVec2 button_pos = tilepos + tilesize - ImVec2(60, 20);
    ImGui::SetWindowPos(button_pos);
    button_pos = button_pos + ImVec2(0, 20);
    if (ImGui::TextButton("##button_wpm", current_wpm.data())) { wpm_button_clicked = true;  }
    if (wpm_button_clicked) {
        Popups popup("WPM", wpm_items, button_pos, ImVec2(70, 100));
        wpm_button_clicked = popup.render();
        if (wpm_button_clicked == false) {
            current_wpm = popup.currentItem();
            current_wpm_value = wpm_values[popup.currentIndex()];
        }
    }
    ImGui::PopFont();
    tiles.endTile();

    

    // What's new child
    tilepos = ImVec2(830, 200) * viewport;
    tilesize = ImVec2(240, 320) * viewport;
    tiles.addTile("What's New", tilepos, tilesize, COLOR_BLACK);
    createText({ 0, 0 }, { 0, 0 }, "What's New", ImGui::GetIO().Fonts->Fonts[1], COLOR_WHITE);
    char news[] = "Version 1.0.0\nDummy Text";
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);
    ImGui::PushTextWrapPos(tilesize.x);
    ImGui::TextWrapped(news);
    ImGui::PopTextWrapPos();
    ImGui::PopFont();
    tiles.endTile();

    // Language Spoken child
    tilepos = ImVec2(95, 535) * viewport;
    tilesize = ImVec2(480, 140) * viewport;
    std::vector<char*> languages = { "English", "Spanish", "Russian", "French" };
    std::vector<float> values = { 0.78, 0.08, 0.07, 0.07 };

    tiles.addTile("Language Spoken", tilepos, tilesize, COLOR_BLACK);
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);
    ImGui::Text("Languages Spoken");
    for (int i = 0; i < languages.size(); ++i){
        char value[10];
        sprintf(value, "%0.f", values[i] * 100);
        strcat(value, "%%");
        float width = tilesize.x - ImGui::CalcTextSize(languages[i]).x - ImGui::CalcTextSize(value).x - 50;
        ImGui::Text(languages[i]);
        ImGui::SameLine(0, 0);
        createProgressBar(values[i], ImVec2(width, 7));
        ImGui::SameLine(0, width + 10);
        ImGui::Text(value);
    }
    ImGui::PopFont();
    tiles.endTile();

    // Usage Time child
    tilepos = ImVec2(595, 535) * viewport;
    tilesize = ImVec2(480, 140) * viewport;
    tiles.addTile("Usage Time", tilepos, tilesize, COLOR_BLACK);
    tiles.endTile();

    // Audio File
    tilepos = ImVec2(825, 95) * viewport;
    tilesize = ImVec2(250, 90) * viewport;
    tiles.addTile("What's New", tilepos, tilesize, COLOR_AUDIO_EDGE);
    // add graph of audio here
    tiles.endTile();
    ImGui::SetCursorScreenPos(tilepos);
    ImGui::Image((void*)(intptr_t)my_image_texture[8], tilesize);

    //Input device
    tilepos = ImVec2(windowsize.x - 300, 35);
    tilesize = ImVec2(180, 40);
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[10]);
    ImGui::GetWindowDrawList()->AddRectFilled(tilepos, tilepos + tilesize, IM_COL32(0x21, 0x24, 0x30, 0xff));
    ImGui::GetWindowDrawList()->AddRectFilled(tilepos + ImVec2(5, 15), tilepos + tilesize - ImVec2(5, 5), IM_COL32(0x0d, 0x12, 0x1d, 0xff));
    ImGui::SetCursorScreenPos(tilepos + ImVec2(5, 0));
    ImGui::Text("INPUT DEVICE");
    std::vector<std::string> device_items = { "Default", "Other" };
    static std::string current_device = device_items[0];
    ImGui::SetWindowPos(tilepos + ImVec2(0, 15));
    if (ImGui::TextButton("##button_device", current_device.data())) { device_button_clicked = true; }
    if (device_button_clicked) {
        Popups popup("Device", device_items, tilepos + ImVec2(0, 35), ImVec2(70, 100));
        device_button_clicked = popup.render();
        if (device_button_clicked == false) { current_device = popup.currentItem(); }
    }
    ImGui::PopFont();

    // Notification Icon
    tilepos = ImVec2(windowsize.x - 110, 35);
    tilesize = ImVec2(30, 30);
    std::vector<std::string> news_items = { "Default notification", "Other notification" };
    static std::string current_news = news_items[0];
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[10]);
    ImGui::SetCursorScreenPos(tilepos);
    ImGui::PushStyleColor(ImGuiCol_Button, COLOR_BUTTON_USER);
    if (ImGui::ImageButton("##button_news", (void*)(intptr_t)my_image_texture[9], tilesize)) { news_button_clicked = true; }
    ImGui::PopStyleColor();
    if (news_button_clicked) {
        Popups popup("News", news_items, tilepos + ImVec2(-140, 30), ImVec2(170, 100));
        news_button_clicked = popup.render();
        if (news_button_clicked == false) { current_news = popup.currentItem(); }
    }
    ImGui::PopFont();
    if (checked_notification) { ImGui::GetWindowDrawList()->AddCircleFilled(tilepos + ImVec2(25, 10), 4.0f, COLOR_NOTIFICATION); }

    // User Button
    tilepos = ImVec2(windowsize.x - 70, 35);
    tilesize = ImVec2(30, 30);
    ImGui::SetCursorScreenPos(tilepos);
    ImGui::PushStyleColor(ImGuiCol_Button, COLOR_BUTTON_USER);
    ImGui::ImageButton("##button_user", (void*)(intptr_t)my_image_texture[10], tilesize);
    ImGui::PopStyleColor();

    ImGui::PopStyleColor();
}