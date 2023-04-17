#include "Gui.hpp"

int main()
{
    auto gui = Gui();

    while (gui.isRunning())
    {
        gui.renderFrame();
    }
}
