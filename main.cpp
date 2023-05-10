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
    while (gui.isRunning()) 
    {
        gui.renderFrame();
    }
}
