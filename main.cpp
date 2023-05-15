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

    while (gui.isRunning())
    {
        gui.renderFrame();
    }
}
