#pragma once

#include "clean_gui.hpp"
#include "tiles.hpp"
#include "selector.hpp"
#include "inputtexts.hpp"
#include "button.hpp"
#include "checkbox.hpp"
#include "graph.hpp"

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

    int current_page;
    GLuint my_image_texture[20] = { 0 };
    bool checked_notification = true;

    Selector wpm_selector, device_selector, news_selector;
    Button register_button, forgot_button, login_button, account_button, overview_button, setting_button, dictation_button, user_button, minimize_button, maximize_button, restore_button, close_button;
    InputTexts email_input, password_input;
    CheckBox remember_checkbox, command_checkbox, vad_checkbox, rules_checkbox;
    VarGraph usage_time;
    LineGraph audio;

    int wpm = 185;
    std::vector<std::string> wpm_items = { "Per day", "Per week", "Per month", "Per year" };
    std::vector<std::string> wpm_values = { "165", "1200", "4300", "10000" };
    std::vector<std::string> device_items = { "Default", "Other" };
    std::vector<std::string> news_items = { "Default notification", "Other notification" };
    std::string history_text = "Boss: Speech to Text\nVersion 2023.001.00001\nCopyright 2023-2023 Bross LLC and its licensors. All Rights Reserved.\nBross LLC, the Bross LLC logo, and Boss: Speech to Text are either registered trademarks or trademarks of Bross LLC in the United States and/or other countries. All other trademarks are the property of their respective owners.\nSpeech Transcription Technology by OpenAI. Copyright 2015–2023. All Rights Reserved.\nThis software uses libraries from the _____ project under the ____ -license-.\nThird Party notices, terms and conditions pertaining to third party software can be found at _____ and are incorporated by reference.";
    std::string news_text = "Version 1.0.0\nDummy Text";
    std::vector<char*> languages = { "English", "Spanish", "Russian", "French" };
    std::vector<float> language_values = { 0.78, 0.08, 0.07, 0.07 };
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
    void createCheckBoxes();
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
    void createProgressBar(float value, ImVec2 size); //create progress bar
    void createLanguageSpoken(std::vector<char*> languages, std::vector<float> values, ImVec2 size);

    void setWpm(int _wpm) { wpm = _wpm; }
    void setWpmAverage(std::vector<std::string> _wpm_items, std::vector<std::string> _wpm_values);
    void setHistoryText(std::string _history_text) { history_text = _history_text; }
    void setNewsText(std::string _news_text) { news_text = _news_text; }
    void setLanguageSpoken(std::vector<char*> _languages, std::vector<float> _language_values);
    void setHistogram(std::vector<float> _histogram);
    void setTimeState(std::vector<std::string> _states) { usage_time.updateStates(_states); }
    void setTimeValue(int n, std::vector<std::string> _valuename, std::vector<float> _value) { usage_time.updateValue(n, _valuename, _value); }
    void setTimeValues(std::vector<std::vector<std::string>> _valuenames, std::vector<std::vector<float>> _values) { usage_time.updateValues(_valuenames, _values); }
};
