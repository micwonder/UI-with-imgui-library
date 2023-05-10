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
    current_page = PAGE_LOGIN;

    createFonts();
    loadImage();

    createPopups();
    createButtons();
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

void Gui::createFonts()
{
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
}

void Gui::createPopups()
{
    std::vector<std::string> wpm_items = { "Per day", "Per week", "Per month", "Per year" };
    Popups popup1("##button_wpm", "WPM", wpm_items, { 0, 0 }, ImVec2(70, 100), ALIGN_LEFT);
    std::vector<std::string> device_items = { "Default", "Other" };
    Popups popup2("##button_device", "Device", device_items, { 0, 0 }, ImVec2(70, 100), ALIGN_LEFT);
    std::vector<std::string> news_items = { "Default notification", "Other notification" };
    Popups popup3("##button_new", "News", news_items, { 0, 0 }, ImVec2(170, 100), ALIGN_RIGHT, my_image_texture[9]);

    popups.push_back(popup1);
    popups.push_back(popup2);
    popups.push_back(popup3);
}

void Gui::createButtons()
{
    register_button = Button("##Register", "Register", { 0, 0 }, { 0, 0 }, ImGui::GetIO().Fonts->Fonts[2], BUTTON_TEXT);
    forgot_button = Button("##Forgot_Password", "Forgot Password?", { 0, 0 }, { 0, 0 }, ImGui::GetIO().Fonts->Fonts[2], BUTTON_TEXT);
    login_button = Button("##Button", "Login", { 0, 0 }, { 0, 0 }, ImGui::GetIO().Fonts->Fonts[2], BUTTON_NORMAL);
    account_button = Button("##button_account", { 0, 0 }, { 0, 0 }, my_image_texture[4]);
    overview_button = Button("##button_overview", { 0, 0 }, { 0, 0 }, my_image_texture[5]);
    dictation_button = Button("##button_dictation", { 0, 0 }, { 0, 0 }, my_image_texture[6]);
    setting_button = Button("##button_setting", { 0, 0 }, { 0, 0 }, my_image_texture[7]);

    events["registerbuttonclicked"] = register_button.clickEvent;
    events["forgotbuttonclicked"] = forgot_button.clickEvent;
    events["loginbuttonclicked"] = login_button.clickEvent;
    events["accountbuttonclicked"] = account_button.clickEvent;
    events["overviewbuttonclicked"] = overview_button.clickEvent;
    events["dictationbuttonclicked"] = dictation_button.clickEvent;
    events["settingbuttonclicked"] = setting_button.clickEvent;
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
void Gui::toAccountPage() { current_page = PAGE_ACCOUNT; }
void Gui::toOverviewPage() { current_page = PAGE_OVERVIEW; }
void Gui::toSettingPage() { current_page = PAGE_SETTING; }
void Gui::toDictationPage() { current_page = PAGE_DICTATION; }

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

void Gui::createLanguageSpoken(std::vector<char*> languages, std::vector<float> values, ImVec2 size)
{
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);
    ImGui::Text("Languages Spoken");
    for (int i = 0; i < languages.size(); ++i) {
        char value[10];
        sprintf(value, "%0.f", values[i] * 100);
        strcat(value, "%%");
        float width = size.x - ImGui::CalcTextSize(languages[i]).x - ImGui::CalcTextSize(value).x - 30;
        ImGui::Text(languages[i]);
        ImGui::SameLine(0, 0);
        createProgressBar(values[i], ImVec2(width, 7));
        ImGui::SameLine(0, width + 10);
        ImGui::Text(value);
    }
    ImGui::PopFont();
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
    if(size.x == 0 && size.y == 0)
        ImGui::SetCursorPos(pos);
    else
    {
        ImVec2 textsize = ImGui::CalcTextSize(text);
        ImGui::SetCursorPos({ pos.x + (size.x - textsize.x) / 2, pos.y + (size.y - textsize.y) / 2 });
    }
    ImGui::Text(text);
    ImGui::PopFont();
}
void Gui::createWrapText(char* text, ImFont* font, float wrap_pos, ImU32 color) //create wrap Text in specified font and color
{
    ImGui::PushStyleColor(ImGuiCol_Text, color);
    ImGui::PushFont(font);
    ImGui::PushTextWrapPos(wrap_pos);
    ImGui::TextWrapped(text);
    ImGui::PopTextWrapPos();
    ImGui::PopFont();
    ImGui::PopStyleColor();
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
    ImVec2 buttonsize = { 75, 75};
    ImGui::PushStyleColor(ImGuiCol_Button, COLOR_GUI_LEFT);

    account_button.render({ 0, 0 }, buttonsize);
    overview_button.render({ 0, size.y / 7 * 2 }, buttonsize);
    dictation_button.render({ 0, size.y / 7 * 3 }, buttonsize);
    setting_button.render({ 0, size.y / 7 * 5 }, buttonsize);
    
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

void Gui::clearPopup()
{
    for (int i = 0; i < popups.size(); ++i)
        popups[i].removeSelect();
}

void Gui::renderFrame()
{
    start_clean_window();
    if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) { clearPopup(); }
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
    register_button.render({ size.x / 5 * 4 - 20, size.y / 5 * 3 + 30 }, { 0, 0 });
    forgot_button.render({ size.x / 10 * 9 - 40, size.y / 5 * 3 + 30 }, { 0, 0 });
    
    ImGui::PushStyleColor(ImGuiCol_Button, COLOR_BUTTON_LOGIN);
    ImVec2 buttonsize = { 260, 50 };
    if (login_button.render({ size.x / 5 * 3 + (size.x / 5 * 2 - buttonsize.x) / 2, size.y / 5 * 4 + (size.y / 5 - buttonsize.y) / 2 }, buttonsize))
        toAccountPage();
    ImGui::PopStyleColor();
    ImGui::PopFont();
}

void Gui::overviewPage()
{
    ImVec2 windowsize = getWindowSize();
    ImVec2 tilepos, tilesize;

    dividePane(75, COLOR_GUI_LEFT, COLOR_GUI_RIGHT);
    createTitleBar(COLOR_GUI_RIGHT);
    createTabIcon();
    createText({ 100, 35 }, { 0, 0 }, "Overview", ImGui::GetIO().Fonts->Fonts[0], COLOR_WHITE);

    ImGui::PushStyleColor(ImGuiCol_ChildBg, COLOR_TILE);

    // WPM tile
    Tiles tiles({ 100, 60 }, windowsize - ImVec2(100, 60), { 4, 7 }, 10.0f);
    tilepos = { 0, 1 }; tilesize = { 1, 1 };
    tiles.addTile("WPM", tilepos, tilesize, COLOR_BLACK);
    {
        Tiles subtiles({0, 0}, tiles.curSize(), {1, 2}, 0.0f, 0.0f);
        subtiles.addTile("WPM_CHILD1", { 0, 0 }, { 1, 1 }, COLOR_BLACK);
        createText({0, 0}, subtiles.curSize(), "WPM", ImGui::GetIO().Fonts->Fonts[1], COLOR_WHITE);
        subtiles.endTile();
        subtiles.addTile("WPM_CHILD2", { 0, 1 }, { 1, 1 }, COLOR_BLACK);
        createText({0, 0}, subtiles.curSize(), "185", ImGui::GetIO().Fonts->Fonts[1], COLOR_WHITE);
        subtiles.endTile();
    }
    tiles.endTile();

    // Dictation Histroy child
    char history[] = "Boss: Speech to Text\nVersion 2023.001.00001\nCopyright 2023-2023 Bross LLC and its licensors. All Rights Reserved.\nBross LLC, the Bross LLC logo, and Boss: Speech to Text are either registered trademarks or trademarks of Bross LLC in the United States and/or other countries. All other trademarks are the property of their respective owners.\nSpeech Transcription Technology by OpenAI. Copyright 2015–2023. All Rights Reserved.\nThis software uses libraries from the _____ project under the ____ -license-.\nThird Party notices, terms and conditions pertaining to third party software can be found at _____ and are incorporated by reference.";
    
    tilepos = { 0, 2 }; tilesize = { 3, 3 };
    tiles.addTile("Dictation History", tilepos, tilesize, COLOR_BLACK);
    createText({ 0, 0 }, { 0, 0 }, "WPM Average", ImGui::GetIO().Fonts->Fonts[1], COLOR_WHITE);
    createWrapText(history, ImGui::GetIO().Fonts->Fonts[2], tiles.curSize().x, COLOR_WHITE);
    tiles.endTile();

    // What's new child
    char news[] = "Version 1.0.0\nDummy Text";

    tilepos = { 3, 2 }; tilesize = { 1, 3 };
    tiles.addTile("What's New", tilepos, tilesize, COLOR_BLACK);
    createText({ 0, 0 }, { 0, 0 }, "What's New", ImGui::GetIO().Fonts->Fonts[1], COLOR_WHITE);
    createWrapText(news, ImGui::GetIO().Fonts->Fonts[2], tiles.curSize().x, COLOR_WHITE);
    tiles.endTile();

    // WPM Average child
    std::vector<std::string> wpm_values = { "165", "1200", "4300", "10000" };

    tilepos = { 1, 1 }; tilesize = { 1, 1 };
    tiles.addTile("WPM Average", tilepos, tilesize, COLOR_BLACK);
    {
        Tiles subtiles({ 0, 0 }, tiles.curSize(), { 1, 2 }, 0.0f, 0.0f);
        subtiles.addTile("Average_CHILD1", { 0, 0 }, { 1, 1 }, COLOR_BLACK);
        createText({ 0, 0 }, subtiles.curSize(), "WPM Average", ImGui::GetIO().Fonts->Fonts[1], COLOR_WHITE);
        subtiles.endTile();
        subtiles.addTile("Average_CHILD2", { 0, 1 }, { 1, 1 }, COLOR_BLACK);
        createText({ 0, 0 }, subtiles.curSize(), wpm_values[popups[0].currentIndex()].data(), ImGui::GetIO().Fonts->Fonts[1], COLOR_WHITE);
        popups[0].doModal({tiles.curPos() + tiles.curSize() - ImVec2(60, 20)}, {70, 100});
        subtiles.endTile();
    }
    tiles.endTile();

    // Language Spoken child
    tilepos = { 0, 5 }; tilesize = {2, 2};
    std::vector<char*> languages = { "English", "Spanish", "Russian", "French" };
    std::vector<float> values = { 0.78, 0.08, 0.07, 0.07 };

    tiles.addTile("Language Spoken", tilepos, tilesize, COLOR_BLACK);
    createLanguageSpoken(languages, values, tiles.curSize());
    tiles.endTile();

    // Usage Time child
    tilepos = { 2, 5 }; tilesize = { 2, 2 };
    tiles.addTile("Usage Time", tilepos, tilesize, COLOR_BLACK);
    tiles.endTile();

    // Audio File
    tilepos = { 3, 1 }; tilesize = { 1, 1 };
    tiles.addTile("What's New", tilepos, tilesize, COLOR_AUDIO_EDGE);
    // add graph of audio here
    tiles.endTile();
    ImGui::SetCursorScreenPos(tiles.curPos());
    ImGui::Image((void*)(intptr_t)my_image_texture[8], tiles.curSize());

    ImVec2 curpos, cursize;
    //Input device
    curpos = ImVec2(windowsize.x - 300, 35);
    cursize = ImVec2(180, 40);
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[10]);
    ImGui::GetWindowDrawList()->AddRectFilled(curpos, curpos + cursize, IM_COL32(0x21, 0x24, 0x30, 0xff));
    ImGui::GetWindowDrawList()->AddRectFilled(curpos + ImVec2(5, 15), curpos + cursize - ImVec2(5, 5), IM_COL32(0x0d, 0x12, 0x1d, 0xff));
    ImGui::SetCursorScreenPos(curpos + ImVec2(5, 0));
    ImGui::Text("INPUT DEVICE");
    popups[1].doModal(curpos + ImVec2(0, 15), ImVec2(70, 100));
    ImGui::PopFont();

    // Notification Icon
    curpos = ImVec2(windowsize.x - 110, 35);
    cursize = ImVec2(30, 30);
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[10]);
    popups[2].doModal(curpos, {170, 100});
    ImGui::PopFont();
    if (checked_notification) { ImGui::GetWindowDrawList()->AddCircleFilled(curpos + ImVec2(25, 10), 4.0f, COLOR_NOTIFICATION); }

    // User Button
    curpos = ImVec2(windowsize.x - 70, 35);
    cursize = ImVec2(30, 30);
    ImGui::SetCursorScreenPos(curpos);
    ImGui::PushStyleColor(ImGuiCol_Button, COLOR_BUTTON_USER);
    ImGui::ImageButton("##button_user", (void*)(intptr_t)my_image_texture[10], cursize);
    ImGui::PopStyleColor();

    ImGui::PopStyleColor();
}