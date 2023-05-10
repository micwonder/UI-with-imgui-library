#pragma once

#include "clean_gui.hpp"
#include "tiles.hpp"
#include "selector.hpp"
#include "inputtexts.hpp"
#include "button.hpp"
#include "checkbox.hpp"

#include <map>

#define COLOR_BLACK IM_COL32(0x00, 0x00, 0x00, 0xff)
#define COLOR_WHITE IM_COL32(0xff, 0xff, 0xff, 0xff)
#define COLOR_GUI_LEFT IM_COL32(0x21, 0x23, 0x2d, 0xff)
#define COLOR_GUI_RIGHT IM_COL32(0x0d, 0x12, 0x1d, 0xff)
#define COLOR_GUI_LOGIN_LEFT IM_COL32(0x6d, 0x84, 0xa2, 0xff)
#define COLOR_GUI_LOGIN_RIGHT IM_COL32(0x21, 0x23, 0x2d, 0xff)
#define COLOR_TITLE IM_COL32(0x3f, 0x4b, 0x57, 0xff)
#define COLOR_INPUT_DARK IM_COL32(0x15, 0x2d, 0x49, 0xff)
#define COLOR_INPUT_LIGHT IM_COL32(0x23, 0x3a, 0x57, 0xff)
#define COLOR_INPUT_EDGE IM_COL32(0x99, 0xb3, 0xd6, 0xff)
#define COLOR_BUTTON_LOGIN IM_COL32(0x6f, 0x87, 0xa3, 0xff)
#define COLOR_BUTTON_USER IM_COL32(0x21, 0x24, 0x30, 0xff)
#define COLOR_AUDIO_EDGE IM_COL32(0x1c, 0x24, 0x31, 0xff)
#define COLOR_AUDIO_GRAPH IM_COL32(0x2c, 0x9f, 0xff, 0xff)
#define COLOR_NOTIFICATION IM_COL32(0x06, 0xe9, 0xfa, 0xff)
#define COLOR_TILE IM_COL32(0x21, 0x24, 0x30, 0xff)

#define INPUT_TYPE_EMAIL 0
#define INPUT_TYPE_PASSWORD 1

#define PAGE_LOGIN 0
#define PAGE_ACCOUNT 1
#define PAGE_SETTING 2
#define PAGE_OVERVIEW 3
#define PAGE_DICTATION 4

class Gui : public CleanGui
{
private:
    //ImFont *font;
    bool isMaximized = false;

    bool checked_command = false;
    bool checked_vad = false;
    bool checked_rules = false;
    bool checked_remeber_me = true;

    bool checked_notification = true;

    int current_page;
    GLuint my_image_texture[20] = { 0 };

    Selector wpm_selector, device_selector, news_selector;
    Button register_button, forgot_button, login_button, account_button, overview_button, setting_button, dictation_button;
    InputTexts email_input, password_input;
    CheckBox remember_checkbox, command_checkbox, vad_checkbox, rules_checkbox;
public:
    std::map<std::string, Event*> events;
    Gui();
    ~Gui();

    bool isRunning() const;
    void renderFrame();
    void dictationPage();
    void bossDictationPage();
    void accountPage();
    void settingPage();
    void overviewPage();

    void createFonts();
    void createButtons();
    void createInputTexts();
    void createSelectors();
    void clearSelectors();
    void createCheckboxes();
    void loadImage();
    void deleteImage();

    void toAccountPage();
    void toOverviewPage();
    void toDictationPage();
    void toSettingPage();

    void dividePane(float div_pos, ImU32 left_color, ImU32 right_color); // devide panel to left and right
    void createTitleBar(ImU32 color); // create minimize, maximize, close button
    void createTabIcon(); // create account, overview, earphone, setting tab
    void createText(ImVec2 pos, ImVec2 size, char* text, ImFont* font, ImU32 color); //create Text in specified font and color
    void createWrapText(char* text, ImFont* font, float wrap_pos, ImU32 color); //create wrap Text in specified font and color
    float createCheckBox(ImVec2 pos, char* title, char* check_label, bool* check_flag); // create a checkbox with title
    void createProgressBar(float value, ImVec2 size); //create progress bar
    void createLanguageSpoken(std::vector<char*> languages, std::vector<float> values, ImVec2 size);
};
