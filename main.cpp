#include "Gui.hpp"
#include <vector>
#include <string>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

void RegisterButtonClicked() { puts("register button clicked"); }
void ForgotButtonClicked() { puts("Forgot Password Button clicked"); }
void LoginButtonClicked() { puts("Login button clicked"); }
void AccountButtonClicked() { puts("Account button clicked"); }
void OverViewButtonClicked() { puts("Overview button clicked"); }
void DictationButtonClicked() { puts("Dictation button clicked"); }
void SettingButtonClicked() { puts("Setting button clicked"); }
void UserButtonClicked() { puts("User button clicked"); }
void MinimizeButtonClicked() { puts("Minimize button clicked"); }
void MaximizeButtonClicked() { puts("Maximize button clicked"); }
void RestoreButtonClicked() { puts("Restore button clicked"); }
void CloseButtonClicked() { puts("Close button clicked"); }

void EmailChanged(char* text) { printf("email: %s\n", text); }
void PasswordChanged(char* text) { printf("password: %s\n", text); }

void WpmSelected(int index, char* text) { printf("wpm: %d %s\n", index, text); }
void DeviceSelected(int index, char* text) { printf("device: %d %s\n", index, text); }
void NewsSelected(int index, char* text) { printf("news: %d %s\n", index, text); }

void RememberChecked(bool checked) { if (checked) { puts("remember checked"); } else{ puts("remember not checked"); }}
void CommandChecked(bool checked) { if (checked) { puts("command checked"); } else { puts("command not checked"); } }
void VadChecked(bool checked) { if (checked) { puts("vad checked"); } else { puts("vad not checked"); } }
void RulesChecked(bool checked) { if (checked) { puts("rules checked"); } else { puts("rules not checked"); } }

// TODO: write your own performance test for the graph
void graph_performance_test(Gui& gui)
{
    // update Histogram
    std::vector<float> hist;
    for (int i = 0; i < 1000; i++)
        hist.push_back(rand() % 255 / 255.0);
    gui.setHistogram(hist);

    // update Usage time graph
    std::vector<std::string> states = { "Week", "Month", "Year" };
    std::vector<std::vector<std::string>> valuenames = { { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}
        , {"First Week", "Second Week", "Third Week", "Fourth Week"}
        , {"Januray", "Feburay", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"}
        };
    std::vector<std::vector<float>> values = { {100, 200, 400, 300, 100, 200, 300}  
        ,{4000, 3000, 2000, 1000}
        ,{30000, 20000, 15000, 30000, 40000, 50000, 20000, 30000, 40000, 70000, 80000, 10000} };
    gui.setTimeState(states);
    gui.setTimeValues(valuenames, values);
    gui.setTimeValue(1, valuenames[1], values[1]);
}

// TODO: write other performance tests for different sections of the gui
void other_performance_test(Gui &gui)
{
    // set WPM
    gui.setWpm(300);
    // Set Wpm Average
    std::vector<std::string> wpm_items = { "Per Day", "Per Week", "Per Month" };
    std::vector<std::string> wpm_values = { "400", "3000", "13000" };
    gui.setWpmAverage(wpm_items, wpm_values);
    // Set history text
    gui.setHistoryText("This is history text testing");
    //set What's new text
    gui.setNewsText("This is news text testing");
    // update notification items
    std::vector<std::string> news_items = { "Test News1", "Test News2", "Test News3","Test News4", "Test News5", "Test News6","Test News7", "Test News8", "Test NewsLongLong" };
    gui.setNews(news_items);
    // update device items
    std::vector<std::string> device_items = { "Test Device1", "Test Device2", "Test Device3" };
    gui.setDevice(device_items);
    // update spoken language rates
    std::vector<char*> language_items = { "English", "German", "Spanish", "English", "German", "Spanish" };
    std::vector<float> language_values = { 0.56, 0.33, 0.12, 0.56, 0.33, 0.12 };
    gui.setLanguageSpoken(language_items, language_values);

    gui.setNotification(false);
}

int main()
{
    auto gui = Gui();
    gui.events["registerbuttonclicked"]->AddListener(RegisterButtonClicked);
    gui.events["forgotbuttonclicked"]->AddListener(ForgotButtonClicked);
    gui.events["loginbuttonclicked"]->AddListener(LoginButtonClicked);
    gui.events["accountbuttonclicked"]->AddListener(AccountButtonClicked);
    gui.events["overviewbuttonclicked"]->AddListener(OverViewButtonClicked);
    gui.events["dictationbuttonclicked"]->AddListener(DictationButtonClicked);
    gui.events["settingbuttonclicked"]->AddListener(SettingButtonClicked);
    gui.events["userbuttonclicked"]->AddListener(UserButtonClicked);
    gui.events["minimizebuttonclicked"]->AddListener(MinimizeButtonClicked);
    gui.events["maximizebuttonclicked"]->AddListener(MaximizeButtonClicked);
    gui.events["restorebuttonclicked"]->AddListener(RestoreButtonClicked);
    gui.events["closebuttonclicked"]->AddListener(CloseButtonClicked);

    gui.events["emailchanged"]->AddListener(EmailChanged);
    gui.events["passwordchanged"]->AddListener(PasswordChanged);
    
    gui.events["wpmselected"]->AddListener(WpmSelected);
    gui.events["deviceselected"]->AddListener(DeviceSelected);
    gui.events["newsselected"]->AddListener(NewsSelected);

    gui.events["rememberchecked"]->AddListener(RememberChecked);
    gui.events["commandchecked"]->AddListener(CommandChecked);
    gui.events["vadchecked"]->AddListener(VadChecked);
    gui.events["ruleschecked"]->AddListener(RulesChecked);

    graph_performance_test(gui);
    other_performance_test(gui);
    while (gui.isRunning())
    {
        gui.renderFrame();
    }
}
