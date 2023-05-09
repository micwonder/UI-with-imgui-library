#include "Gui.hpp"
#include <vector>
#include <string>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

int main()
{
    auto gui = Gui();
    while (gui.isRunning()) 
    {
        gui.renderFrame();
    }
}
